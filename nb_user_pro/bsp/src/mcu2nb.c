/*******************************************************************************
* COPYRIGHT@SIGBEN
*******************************************************************************
* 文件名称:  mcu2nb.c
* 功能描述: 
* 使用说明:
* 文件作者:                
* 编写日期: 
* 修改历史: 
* 修改日期修改人  BugID/CRID      修改内容
* -----------------------------------------------------------------------------
* 
******************************************************************************/

/******************************* 包含文件声明 *********************************/
#include <stdio.h>
#include <string.h>
#include <cortex_m4.h>
#include <core_cm3.h>
#include <vos.h>
#include <platform.h>
#include <sys_cmd.h> 
/******************************* 局部宏定义 ***********************************/

/******************************* 全局变量定义/初始化 **************************/
#define  M_NB2MCU_WRITE_INDEX_ADDR  0x20003E00
#define  M_NB2MCU_READ_INDEX_ADDR   0x20003E04

#define  M_MCU2NB_WRITE_INDEX_ADDR  0x20003E08
#define  M_MCU2NB_READ_INDEX_ADDR   0x20003E0C

#define  M_MCU2NB_AT_INTERRUPT_ADDR 0x20003E10

volatile unsigned int *g_u32Mcu2NbWriteIndex = (unsigned int * )M_MCU2NB_WRITE_INDEX_ADDR;
volatile unsigned int *g_u32Mcu2NbReadIndex = (unsigned int * )M_MCU2NB_READ_INDEX_ADDR;

volatile unsigned int *g_u32AtMsgFLag = (unsigned int * )M_MCU2NB_AT_INTERRUPT_ADDR;

volatile unsigned int g_u32LongMsgIndex = 0;
/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/
/******************************* 函数实现 *************************************/
void clear_share_memory(void)
{
    /*清除共享buffer数据*/
    memset((void *)SRAM_ADDR,0,(SRAM_SIZE-1024));
    REG(M_MCU2NB_WRITE_INDEX_ADDR) = 0;
    REG(M_MCU2NB_READ_INDEX_ADDR) = 0;
    REG(M_NB2MCU_WRITE_INDEX_ADDR) = 0;
    REG(M_NB2MCU_READ_INDEX_ADDR) = 0;
}

void clear_share_memory_no_index(void)
{
    /*清除共享buffer数据*/
    memset((void *)SRAM_ADDR,0,(SRAM_SIZE-1024));
}


void Dd_Mcu2NbIntInit(void)
{
    /*nvic enable*/
    NVIC_EnableIRQ(IRQ_CPM1);    
    NVIC_SetPriority(IRQ_CPM1,20);

}

void Dd_McuForceNbInt(void)
{
    /*cpm0 int enable bit0*/
    REG(CPM_INTENA) |= 1;
    REG(CPM_INTUNM) |= 1;
    /*force int*/
    REG(CPM_INTFRC) |= 1;
}

NB_FAST_CODE void Dd_McuRecNbInt_Isr(void)
{
    u32 IntFlag = 0;
    /*read int*/
    IntFlag = REG(CPM_INTFLG);
    
    /*clear int*/
    if((IntFlag & 0x02) == 0x02)
    {
        REG(CPM_INTCLR) = 0x02;
    }   
    osal_SemaphoreGiveFromIsr(RxNbDataReadySem); 
}    

/*******************************************************************************
* 函数名称: Dd_McuSendToNbMsg
* 函数功能: Mcu给NB发送消息
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明: 
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_McuSendToNbMsg(void * pMsg)
{
    MCU2NB_Interface_Msg_Unit * pMcu2NbMsg = (MCU2NB_Interface_Msg_Unit *)(MCU2NB_SHARED_MSG_ADDR+(*g_u32Mcu2NbWriteIndex)*MCU2NB_MSG_MAX_SIZE);
    
//    DD_DEBUG_PRINTF(" MCU SEND MSG !!!\n");
    
    if(WRITE_READY_FLAG == pMcu2NbMsg->Flag)
    {
        memcpy((void *)(pMcu2NbMsg->MsgData),pMsg,(MCU2NB_MSG_MAX_SIZE-4));
        pMcu2NbMsg->Flag = READ_READY_FLAG;
        
        (*g_u32Mcu2NbWriteIndex)++;
        if(MCU2NB_INTERFACE_MSGBUFFER_NUM == (*g_u32Mcu2NbWriteIndex))
        {
            (*g_u32Mcu2NbWriteIndex)= 0;
        }
        
        Dd_McuForceNbInt();        
    }
    else
    {
    //    DD_DEBUG_PRINTF(" SEND TO NB MSG ERROR!!! FLAG:%x ,Index : %d\n",pMcu2NbMsg->Flag,*g_u32Mcu2NbWriteIndex);
    }    
}

void Dd_AT_Msg(void * pMsg,u32 len,u32 flag)
{
    StrATCmdMsg StrAtMsg;

    DD_DEBUG_PRINTF("%s\r\n",pMsg);
    
    memset((void *)&StrAtMsg,0,sizeof(StrATCmdMsg));
    StrAtMsg.Hdr.header_opc = NB2MCU_AT_REQ_MSG;
    StrAtMsg.Hdr.message_len = len;
    memcpy((void *)&StrAtMsg.AtCmdData[0],pMsg,len);
    Dd_McuSendToNbMsg((void *)&StrAtMsg);       
}

/*******************************************************************************
* 函数名称: Dd_McuRxNbMsg
* 函数功能: Mcu接收Nb发送的消息
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明: 
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
extern void * NBMsgQ;
extern u32    g_u32MsgType;
extern unsigned char g_u8PllClkFlag;
extern u32    g_u32CgmrTimerCount;

extern void vPortUseExtClkSetupSysTick(void);
extern void vPortUsePllSetupSysTick(void);
void Dd_McuRxNbMsg(void)
{
    NB2MCU_Interface_Msg_Unit * Nb2McuMsg = (NB2MCU_Interface_Msg_Unit *)(NB2MCU_SHARED_MSG_ADDR+(*g_u32Mcu2NbReadIndex)*MCU2NB_MSG_MAX_SIZE);

    StrATCmdMsg * pRecAtMsg;
    u8 *pMsg = NULL;
    u32 Msglength=0;
    u32 PsmTimes = 0;
    u32 PsmTimems = 0;
    int Count = 0;
	u32 TickCount;
    while(Nb2McuMsg->Flag == READ_READY_FLAG)
    {
        Nb2McuMsg->Flag = WRITE_READY_FLAG;
        
//        Dd_Uart2_Puts("McuRxNbMsg!!!\n");
        
        /*add user code*/
        //XXXXXXXXXXXXXXXXXXXXXXXXX
        //printf("RX NB MSG!!!\n");
        pRecAtMsg = (StrATCmdMsg *)Nb2McuMsg->MsgData;

        if(pRecAtMsg->Hdr.header_opc == NB2MCU_AT_RSP_MSG)
        {
            Msglength = pRecAtMsg->Hdr.message_len;

            /*Send AT Msg To Test Task*/
#if AT_RESP_DEBUG
            /***标注:在NB使用仿真器模式下，第一条消息通知MCU升频处理 start*/
            if(g_u8PllClkFlag == PLL_USE_EXTCLK)
            {
                if(NULL != (pMsg = strstr(pRecAtMsg->AtCmdData,"^SIMST:")))
                {
                    Dd_Uart2_Init(UART2_BAUD_RATE,0,0,ARM_CLK);
                }   
            }    
            /****标注:在NB使用仿真器模式下，第一条消息通知MCU升频处理 end*/

            for(Count = 0 ; Count<Msglength;Count++)
            {
                Dd_Uart2_Putc(pRecAtMsg->AtCmdData[Count]);
            }
#endif

            /*nb resp user at cmd*/
            if(NB_AT_USER_RESP == Sys_NBAutoCmdCheck(pRecAtMsg->AtCmdData))
            {

                Sys_NBAtGeneralCmdCheck(pRecAtMsg->AtCmdData);

                if(g_StruNBStatue.u32NBState == NB_STATE_ATTACHED)
                {                
                    NB_SendMsg(NBMsgQ,(void *)(pRecAtMsg->AtCmdData),g_u32MsgType,Msglength);
                }
            }         

        }   
        else if(pRecAtMsg->Hdr.header_opc == NB2MCU_PSM_MSG)
        {
            /*Send PSM Msg To Test Task*/

            PsmTimes = pRecAtMsg->Hdr.timing_record / 1000;
            PsmTimems = pRecAtMsg->Hdr.timing_record % 1000;
            /*call RTC */
            Dd_Rtc_LowPowerTest(PsmTimes,PsmTimems);
        }    
        else if(pRecAtMsg->Hdr.header_opc == NB2MCU_OTA_MSG)
        {
            Msglength = pRecAtMsg->Hdr.message_len;
        
            NB_SendMsg(NBMsgQ,pRecAtMsg->AtCmdData,VOS_OTA_DATA,Msglength);            
        }     
        else if(pRecAtMsg->Hdr.header_opc == NB2MCU_FREQ_REDU_MSG)
        {
            //Dd_Clock_Use_ExtClock();

            vPortUseExtClkSetupSysTick();
            Dd_Uart2_Init(UART2_BAUD_RATE,0,0,CLK_4P8M);
            g_u8PllClkFlag = PLL_USE_EXTCLK; 
    //        TickCount = Osal_GetTickCount();
            DD_DEBUG_PRINTF("REDU Freq\r\n");
            
        }      
        else if(pRecAtMsg->Hdr.header_opc == NB2MCU_FREQ_RISE_MSG)
        {
            //Dd_Pll_Enable();
            vPortUsePllSetupSysTick();
            Dd_Uart2_Init(UART2_BAUD_RATE,0,0,ARM_CLK);
            g_u8PllClkFlag = PLL_USE_PLLCLK; 
   //         TickCount = Osal_GetTickCount();
            DD_DEBUG_PRINTF("RISE Freq\r\n");
        }        
        /*判断消息队列的深度并返回*/
        (*g_u32Mcu2NbReadIndex)++;
        if(MCU2NB_INTERFACE_MSGBUFFER_NUM == (*g_u32Mcu2NbReadIndex))
        {
            (*g_u32Mcu2NbReadIndex) = 0;
            Nb2McuMsg = (NB2MCU_Interface_Msg_Unit  *)(NB2MCU_SHARED_MSG_ADDR);
        }
        else
        {
            Nb2McuMsg = (NB2MCU_Interface_Msg_Unit  *)(NB2MCU_SHARED_MSG_ADDR+MCU2NB_MSG_MAX_SIZE*(*g_u32Mcu2NbReadIndex));
        }
    }
}   
/******************************* 源文件结束 ***********************************/



