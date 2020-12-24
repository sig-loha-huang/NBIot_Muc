/*******************************************************************************
 * COPYRIGHT@SIGBEAN
 *******************************************************************************
 * 文件名称:  
 * 功能描述: （简要描述本文件的功能、内容及主要模块）    
 * 使用说明: （描述使用文件功能时的制约条件）
 * 文件作者:                
 * 编写日期: 
 * 修改历史: 
 *  
 * 修改日期修改人  BugID/CRID      修改内容
 * -----------------------------------------------------------------------------
 * 
 ******************************************************************************/
/******************************* 包含文件声明 *********************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>  
#include "cortex_m4.h"
#include "platform.h"
#include "vos.h"
#include "sys_cmd.h"
/******************************* 局部宏定义 ***********************************/
/******************************* 全局变量定义/初始化 **************************/
#define SYS_CMD_TASK_ENABLE
#define AT_TOOL_STAR_PONIT
#ifdef SYS_CMD_TASK_ENABLE 

Bool SystemCmdStart = FALSE;                    /*sys cmd 任务起始状态*/
void* DdCmdDataReadySem = NULL;         /*用于串口中断发送的信号量*/
u8 g_u8UartCmdBuf[2048];                      /*用于存储COMMON命令*/
u8 g_u8AppCmdBuf[2048];                      /*用于存储COMMON命令*/
u32  g_u32AtCmdLenApp = 0; 
u32  g_u32CmdIndex= 0;
extern void * NBMsgQ;
/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/
u32 AtUartDataProc(void);
/******************************* 函数实现 *************************************/

/*******************************************************************************
* 函数名称: SystemCmdTask
* 函数功能: syscmd(用于串口解析)任务执行函数
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 
* 函数说明:

* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
#if (UART_USE_MEM_POOL == 1)
NB_FAST_CODE void SystemCmdTask(void *arg)
{    
    u8 RetFlag = 0;
    /*采用信号量的方式通知*/
   	osal_SemaphoreCreate(&DdCmdDataReadySem, 0);
	buf_init(&SendToUartData);

    SystemCmdStart = TRUE;
    while(1)
    {    
        osal_SemaphoreTake(DdCmdDataReadySem, 0xFFFFFFFF);  
        RetFlag = AtUartDataProc();
        if(1 == RetFlag)
        {
            SysCmdCommon(g_u8AppCmdBuf,g_u32AtCmdLenApp);
        }  
    }
}
#else
NB_FAST_CODE void SystemCmdTask(void *arg)
{    
    /*采用信号量的方式通知*/
   	osal_SemaphoreCreate(&DdCmdDataReadySem, 0);
    
    SystemCmdStart = TRUE;
    while(1)
    {    
        osal_SemaphoreTake(DdCmdDataReadySem, 0xFFFFFFFF);           
        SysCmdCommon(g_u8AppCmdBuf,g_u32AtCmdLenApp);
    }
}
#endif
/*******************************************************************************
* 函数名称: AtUartDataProc
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 
* 函数说明:

* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
u32 AtUartDataProc(void)
{
    unsigned int i;
    unsigned int u32flag = 0;
    unsigned int numberOfBytesRead;
    u8 DataRev[64];
    
	numberOfBytesRead = buf_pop(&SendToUartData, (char *)DataRev, 64);
            
    if(numberOfBytesRead != 0)
    {
        memcpy(&g_u8UartCmdBuf[g_u32CmdIndex],DataRev,numberOfBytesRead);
        g_u32CmdIndex += numberOfBytesRead;

        /*第一包数据*/
        if(numberOfBytesRead == g_u32CmdIndex)
        {
            for(i = 0;  i<numberOfBytesRead ;i++)
            {      
                #ifdef AT_TOOL_STAR_PONIT
                if((g_u8UartCmdBuf[i] == 0x0D) || (g_u8UartCmdBuf[i+1] == 0x1A) || (g_u8UartCmdBuf[i+1] == 0x1B))                
                #else
                if((g_u8UartCmdBuf[i] == 0x0D && g_u8UartCmdBuf[i+1] == 0x0A) || (g_u8UartCmdBuf[i+1] == 0x1A) || (g_u8UartCmdBuf[i+1] == 0x1B))
                #endif
                {
                    u32flag = 1;
                    break;
                }    
                else
                {
                    u32flag = 0;
                }    
            } 
        }    
        else 
        {
            /*从上一包的最后一个数据开始查找*/
            for(i = (g_u32CmdIndex - numberOfBytesRead - 1);  i<g_u32CmdIndex ;i++)
            {            
                #ifdef AT_TOOL_STAR_PONIT
                if((g_u8UartCmdBuf[i] == 0x0D) || (g_u8UartCmdBuf[i+1] == 0x1A) || (g_u8UartCmdBuf[i+1] == 0x1B))                
                #else
                if((g_u8UartCmdBuf[i] == 0x0D && g_u8UartCmdBuf[i+1] == 0x0A) || (g_u8UartCmdBuf[i+1] == 0x1A) || (g_u8UartCmdBuf[i+1] == 0x1B))
                #endif
                {
                    u32flag = 1;
                    break;
                }    
                else
                {
                    u32flag = 0;
                }    
            } 
        }    
        if(1 == u32flag)
        {
            g_u32AtCmdLenApp = g_u32CmdIndex;    
            memcpy((void *)&g_u8AppCmdBuf[0],(void *)&g_u8UartCmdBuf[0],g_u32AtCmdLenApp);
            g_u32CmdIndex = 0;
        }    
    }  
    return u32flag;
}

/*******************************************************************************
* 函数名称: SysLoadInt
* 函数功能: 
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 
* 函数说明:

* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
S32 SysLoadInt(const char *data, int *x)
{
    const char *pos = data;

    *x = 0;

    while (*pos == ' ' || *pos == '\t')
        pos++;

    if (strncmp(pos, "0x", 2) == 0)
    {
        if (sscanf(pos, "%x", x) != 1)
            return -1;
    }else if (strncmp(pos, "0", 1) == 0)
    {
        if (sscanf(pos, "%o", x) != 1)
            return -1;
    }
    else
    {
        if (sscanf(pos, "%d", x) != 1)
            return -1;
    }

    return 0;
}

void SysCmdCommon(u8 * at_buffer, u32 at_buffer_len )
{    
    unsigned char *u8pBuf = NULL;
    unsigned int  *u32pBuf = NULL;
    unsigned int index_mem = 0;

    int param1 = 0, param2 = 0;
    int Div;
    int Remainder;

    char *p = NULL;
    char *pos = NULL;

    StrATCmdMsg StrAtMsg;

    if(NULL != (p = strstr((void *)at_buffer,"atsetmem4")))
    {
        /*除去命令外的第一个空格*/
        p = strstr(p, " ");
        if(NULL == p)
        {
            DD_DEBUG_PRINTF("cmd_handle:: Input error\n");
            return;
        }

        pos = p;

        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param1) != 0)
        {
            DD_DEBUG_PRINTF("cmd_handle: invalid Addr\n");
            return;
        }

        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param2) != 0)
        {
            DD_DEBUG_PRINTF("cmd_handle: invalid Addr\n");
            return;
        }

        DD_DEBUG_PRINTF("\r\nThe cmd is : %s\r\n",at_buffer);
        
        SysMemSet(param1, param2,2);
    } 
    else if(NULL != (p = strstr((void *)at_buffer,"atgetmem")))
    {
        /*除去命令外的第一个空格*/
        p = strstr(p, " ");
        if(NULL == p)
        {
            DD_DEBUG_PRINTF("cmd_handle:: Input error\n");
            return;
        }

        pos = p;

        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param1) != 0)
        {
            DD_DEBUG_PRINTF("cmd_handle: invalid Addr\n");
            return;
        }

        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param2) != 0)
        {
            DD_DEBUG_PRINTF("cmd_handle: invalid Addr\n");
            return;
        }

		DD_DEBUG_PRINTF("The cmd is : %s\r\n",at_buffer);

		if(param2%4 == 0)
        {
            u32pBuf = (unsigned int *)param1;

    		for(index_mem = 1; index_mem <= (param2/4); index_mem++)
    		{
    			DD_DEBUG_PRINTF("%08x", *(u32pBuf++));
    			DD_DEBUG_PRINTF(" ");
    			if(index_mem % 16 == 0)
    				DD_DEBUG_PRINTF("\n");
                else if(index_mem == (param2/4))
    				DD_DEBUG_PRINTF("\n");
    		}            
        }    
        else
        {    
        	u8pBuf = (unsigned char *)param1;
    		for(index_mem = 1; index_mem <= param2; index_mem++)
    		{
    			DD_DEBUG_PRINTF("%02x", *(u8pBuf++));
    			DD_DEBUG_PRINTF(" ");
    			if(index_mem % 16 == 0)
    				DD_DEBUG_PRINTF("\n");
                else if(index_mem == param2)
    				DD_DEBUG_PRINTF("\n");
    		}
        }
    }        
    else if(NULL != (p = strstr((void *)at_buffer,"AT+MCUV?")))
    {
        DD_DEBUG_PRINTF("Mcu code version LH3200_MCU %s %s .\r\n",__DATE__,__TIME__);
    }    
    else if(NULL != (p = strstr((void *)at_buffer,"AT+RESETNB")))
    {
        stop_Nb();
        start_Nb();
    }    
    else if(NULL != (p = strstr((void *)at_buffer,"AT+SSRAMCLR")))
    {
        clear_share_memory_no_index();
    }
    else if(NULL != (p = strstr((void *)at_buffer,"AT+ERASE")))
    {
        /*除去命令外的第一个空格*/
        p = strstr(p, " ");
        if(NULL == p)
        {
            DD_DEBUG_PRINTF("cmd_handle:: Input error\n");
            return;
        }

        pos = p;

        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param1) != 0)
        {
            DD_DEBUG_PRINTF("cmd_handle: invalid Addr\n");
            return;
        }
        stop_Nb();
        Dd_flash_Ic_erase(param1,0x40000);   
        start_Nb();
        Dd_Uart2_Puts("erase ok \r\n");
    }
	else
	{
        /*add only for at+cfun=0 cmd start */
        for(index_mem = 0; index_mem < at_buffer_len; index_mem++)
        {
            if((at_buffer[index_mem] == 'a') || (at_buffer[index_mem] == 'A'))
            {
                if((at_buffer[index_mem+1] == 't') || (at_buffer[index_mem+1] == 'T'))
                {
                    break;
                }    
            }    
        }   
        if(at_buffer[index_mem+2] == '+')
        {
            if((at_buffer[index_mem+3] == 'c') || (at_buffer[index_mem+3] == 'C'))
            {
                if((at_buffer[index_mem+4] == 'f') || (at_buffer[index_mem+4] == 'F'))
                {
                    if((at_buffer[index_mem+5] == 'u') || (at_buffer[index_mem+5] == 'U'))
                    {
                        if((at_buffer[index_mem+6] == 'n') || (at_buffer[index_mem+6] == 'N'))
                        {
                            if((at_buffer[index_mem+7] == '=') && (at_buffer[index_mem+8] == '0'))
                            {
                                *g_u32AtMsgFLag = 1;
                            }    
                        }    
                    }
                }
            }            
        }    
        /*add only for at+cfun=0 cmd end */
    
        memset((void *)&StrAtMsg,0,sizeof(StrATCmdMsg));
        StrAtMsg.Hdr.header_opc = NB2MCU_AT_REQ_MSG;
        StrAtMsg.Hdr.message_len = at_buffer_len;
        Div = at_buffer_len / 496;
        Remainder = at_buffer_len % 496;
        
        if(Div != 0)
        {
            for(index_mem = 0;index_mem<Div;index_mem++)
            {
                memcpy((void *)&StrAtMsg.AtCmdData[0],(void *)at_buffer[496*index_mem],496);
                Dd_McuSendToNbMsg((void *)&StrAtMsg);                
            }   
            if(Remainder != 0)
            {
                memcpy((void *)&StrAtMsg.AtCmdData[0],(void *)at_buffer[496*index_mem],Remainder);
                Dd_McuSendToNbMsg((void *)&StrAtMsg);   
            }    
        }
        else
        {
            memcpy((void *)&StrAtMsg.AtCmdData[0],at_buffer,at_buffer_len);
            Dd_McuSendToNbMsg((void *)&StrAtMsg);
        }    
        
	}
	memset(at_buffer, 0, at_buffer_len);
}  

void SysMemSet(U32  u32MemAddr, U32 u32Memdata,U8 u8SetMemType)
{
    U8 *u8pBuf = NULL;
    U16 *u16pBuf = NULL;
    U32 *u32pBuf = NULL;
    U32 u32Data = u32Memdata;
    U8 *pData = (U8 *)u32MemAddr;
    U8 flag = 1;

    flag = Dd_CmdMemSet(pData,u32Data);

    if(flag == 1) return;
    
    switch(u8SetMemType)
    {
        case 0:
            u8pBuf = pData;
            *u8pBuf = (U8)u32Data;
            break;
        case 1:
            u16pBuf = (U16 *)pData;
            *u16pBuf = (U16)u32Data;
            break;
        case 2:
            u32pBuf = (U32 *)pData;
            *u32pBuf = u32Data;
            break;
        default:
            break;            
    }  
}


u8 Sys_NBAutoCmdCheck(void *pRcvMsg)
{
    int param1 = 0;
    char *p = NULL;
    char *pos = NULL;

    if(NULL != (p = strstr(pRcvMsg,"^SIMST:")))
    {    
        pos = p;
        while (*pos != ' ' && *pos != '\t' && *pos != '\0') pos++;
        while (*pos == ' ' || *pos == '\t') pos++;
        if (*pos == '\0' || SysLoadInt(pos, &param1) != 0)
        {
           // DD_DEBUG_PRINTF("cmd_handle: invalid para\n");
            g_StruNBStatue.u32NBState =  NB_STATE_UNKNOWN;
        }
        if(param1 == 1)
        {
            //DD_DEBUG_PRINTF("NB_STATE_USIM_READY.\r\n");
            g_StruNBStatue.u32NBState =  NB_STATE_USIM_READY;
        }
        else if(param1 == 0)
        {
            //DD_DEBUG_PRINTF("NB_STATE_USIM_OUT.\r\n");
            g_StruNBStatue.u32NBState = NB_STATE_USIM_OUT;
        }   
        return NB_AT_AUTO_RESP;
    }
    /*attach compleat*/
    else if(NULL != (p = strstr(pRcvMsg,"+CGEV: ME PDN ACT 5")))
    {
        /*attached */
        g_StruNBStatue.u32NBState =  NB_STATE_ATTACHED;
        //DD_DEBUG_PRINTF("NB ATTACHED COMPLEAT !!!!\r\n");

        u8 MsgStart[4] = {0x01,0x02,0x03,0x04};
        NB_SendMsg(NBMsgQ,MsgStart,VOS_AT_NETWORK_START,4);

        return NB_AT_AUTO_RESP;
    }
    else if(NULL != (p = strstr(pRcvMsg,"+CGEV: ME PDN DEACT 5")))
    {
        /*attached */
        //g_StruNBStatue.u32NBState =  NB_STATE_DEATACHED;
        //DD_DEBUG_PRINTF("NB_STATE_DEATACHED !!!\r\n");
        return NB_AT_USER_RESP;
    }
    else if(NULL != (p = strstr(pRcvMsg,"ASSERT CALLED")))
    {
        DD_DEBUG_PRINTF("NB_ASSERT!!!\r\n");
        /*reset*/
        //init_NbModule();
        //DD_DEBUG_PRINTF("Restrat NB!!!\r\n");
    }
    else
    {
        return NB_AT_USER_RESP;
    }    
}
u8 Sys_NBAtGeneralCmdCheck(void *pRcvMsg)
{
    char *p= NULL;

    /*常规命令*/
    if(g_StruNBStatue.u32NBState != NB_STATE_ATTACHED)
    {
        
    }   

    return 0;
}

void Sys_At_SoftVersion(void)
{
    char *pString = {"AT+CGMR\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1); 
}

u8 Sys_At_Resp_SoftVersion(u8 *pu8data)
{
    u8 *p = NULL;
    if(NULL != (p = strstr(pu8data,"LH3200")))
    {
        return TRUE;
    }
    return FALSE;
}  


void Sys_At_ImsiRead(void)
{
    char *pString = {"AT+CGSN\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1); 
}

void Sys_MqttSetAiliyunDns(void)
{
    char *pString = {"AT+CMDNS=a1jm62AjFBi.iot-as-mqtt.cn-shanghai.aliyuncs.com\r\n"};
    
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}
void Sys_MqttKeepAlive(u32 u32data)
{
    char *pString = {"AT+MQTTCFG=keepalive,0,300\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}


void Sys_MqttOpen(void)
{
    char *pString = {"AT+MQTTOPEN=0,\"139.196.135.135\",1883\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}
void Sys_MqttConnect(void)
{
    char *pString = {"AT+MQTTCONN=0,\"a1jm62AjFBi\",\"nb_lh3200\",\"0f11cf806eba9c77230d42958b4e3499\",1\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}


void Sys_Ota_HttpCreat(void)
{
//    char *pString = {"AT+HTTPCREATE=\"http://172.28.1.165:20201/\"\r\n"};

    char *pString = {"AT+HTTPCREATE=\"http://120.79.251.94:53697/\"\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_Ota_HttpConnectMcu(void)
{
//    char *pString = {"AT+HTTPSEND=0,0,\"/OTA/nb_user_pro.bin\"\r\n"};

    char *pString = {"AT+HTTPSEND=0,0,\"/web/smart-lock-dev-v1.10.bin\"\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}
void Sys_Ota_HttpConnectNB(void)
{
    char *pString = {"AT+HTTPSEND=0,0,\"/OTA/NBIot_pro.bin\"\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}


void Sys_Ota_MQTTPublishTopicInform(void)
{
    char *pString = {"AT+MQTTPUB=\"/ota/device/inform/a1jm62AjFBi/nb_lh3200\",1\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_Ota_MQTTSubscribeTopicUpgrade(void)
{
    char *pString = {"AT+MQTTSUB=\"/ota/device/upgrade/a1jm62AjFBi/nb_lh3200\",1\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_Ota_MQTTPublishTopicProgress(void)
{
    char *pString = {"AT+MQTTPUB=\"/ota/device/Progress/a1jm62AjFBi/nb_lh3200\",1\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_Ota_MQTTSubscribeTopicSys(void)
{
    char *pString = {"AT+MQTTSUB=\"/sys/a1jm62AjFBi/nb_lh3200/thing/service/property/set\",1\r\n"};
    
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}


void Sys_Ota_VersionReprot(void)
{
    char *pString = {"AT+MQTTPUB=\"/ota/device/inform/a1jm62AjFBi/nb_lh3200\",1,0,0,0,{\"id\":\"0000\",\"params\":{\"version\": \"000001\",\"module\": \"MCU\"}}\r\n"};
	//第一时间上报版本
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}    

void Sys_NetWork_PingCmd(void)
{
    char *pString = {"at+ping=114.114.114.114,16,5000,5\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_NetWork_AiCMDNS(void)
{
    char *pString = {"AT+CMDNS=\"ws-gxkj.com\"\r\n"};

    Dd_AT_Msg((void *)pString,strlen(pString),1);
    
}
void Sys_NetWork_IpStart(void)
{
    char *pString = {"AT+IPSTART=0,\"tcp\",\"47.108.196.230\",18888\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_NetWork_IprCfg(void)
{
    char *pString = {"AT+IPRCFG=1\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}    

void Sys_NetWork_IpSendLoginIn(void)
{
    char *pString = {"AT+IPSEND=0,0,\"GX029C620LOGIN [1033543990] [v2.11] \r\n\"\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}    

void Sys_NetWork_IpSendUsimData(void)
{
    char *pString = {"AT+IPSEND=0,0,\"GX0370026SIM [1033543990] [460043193203707] \r\n\"\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}
void Sys_NetWork_IpSendHearBeat(void)
{
    char *pString = {"AT+IPSEND=0,0,\"GX04060BDINFO [1033543990] [8.39] [CLOSE] [66] \r\n\"\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);
}

void Sys_At_SoftVersionCheck(void)
{
    char *pString = {"AT+CGMR\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);    
}    

void Sys_At_Cfun0(void)
{
    char *pString = {"AT+CFUN=0\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);   
}

void Sys_At_Cfun1(void)
{
    char *pString = {"AT+CFUN=1\r\n"};
    Dd_AT_Msg((void *)pString,strlen(pString),1);       
}

u8 Sys_At_CfunCheck(u8 * pRcvMsg, u8 ATState, u8 MsgLen)
{
    u8                  *pstr = NULL;
    if(ATState == AT_RESP_CHECK_START)
    {
        if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
        {
            ATState = AT_RESP_CHECK_OK;
        } 
        else
        {            
            ATState = AT_RESP_CHECK_START;//wa8t AT+CFUN Deal OK
        }    
    }  
    
    return ATState;
}    

u8 Sys_At_CMDNSRespCheck(u8 * pRcvMsg, u8 ATState)
{
    u8                  *pstr = NULL;

    if(ATState == AT_RESP_CHECK_START)
    {
        if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
        {
            ATState = AT_RESP_CHECK_STEP_1;
        }
    }    
    else if(ATState == AT_RESP_CHECK_STEP_1)
    {
        if(NULL != (pstr = strstr((void *)pRcvMsg,"CMDNS SUCCESS")))
        {
            ATState = AT_RESP_CHECK_STEP_2;
        }
    }    
    else if(ATState == AT_RESP_CHECK_STEP_2)
    {
        if(NULL != (pstr = strstr((void *)pRcvMsg,"+CMDNS:")))
        {
            ATState = AT_RESP_CHECK_OK;
            DD_DEBUG_PRINTF("CMDNS Success\r\n");
        }
    }       
    return ATState;
}
#ifdef ALIYUN_CONNECT
u8 Sys_At_MqttMsgCheck(u8 * pRcvMsg, u8 ATState, u32 MsgTpye)
{
    u8                  *pstr = NULL;
    u32                 u32number;
    switch(MsgTpye)
    {
        case VOS_MQTT_KEEPALIVE:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_OK;
                }
                else
                {
                    DD_DEBUG_PRINTF("MQTT_KEEPALIVE FALSE\r\n");
                }    
            }  
            break;
         case VOS_MQTT_OPEN:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
                else
                {
                    DD_DEBUG_PRINTF("MQTT_OPEN FALSE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"CONNECT OK")))
                {
                    ATState = AT_RESP_CHECK_OK;
                }
                else
                {
                    DD_DEBUG_PRINTF("MQTT CONNECT FAILE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            break;  
         case VOS_MQTT_CONNECT:
         case VOS_MQTT_THINGS_SET:
         case VOS_MQTT_UPGRADE_SET:
         case VOS_MQTT_VERSION_REPORT:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
                else
                {
                    DD_DEBUG_PRINTF("MQTT FAILE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }                  
            }    
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+MQTTSTAT:")))
                {
                    pstr = pstr+10;
                    u32number = atol(pstr);
                    DD_DEBUG_PRINTF("MqttState:%d \r\n",u32number);
                    if(u32number == 0)
                    {
                        ATState = AT_RESP_CHECK_OK;
                    }   
                    else
                    {
                        DD_DEBUG_PRINTF("MQTT FAILE\r\n");
                        ATState = AT_RESP_CHECK_ERROR;
                    }    
                }
            }    
            break;
          default:
            break;
    }    
    return ATState;
}
#endif

#ifdef OTA_FUNC_TEST
u8 Sys_At_HttpMsgCheck(u8 * pRcvMsg, u8 ATState, u32 MsgTpye)
{
    u8                  *pstr = NULL;
    static  u32         u32updateFilesize = 0;
    static  u32         OtaCurLen = 0;
    switch(MsgTpye)
    {
        case VOS_OTA_START:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
                else
                {
                    DD_DEBUG_PRINTF("Http_Start FALSE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"CONNECT OK")))
                {
                    ATState = AT_RESP_CHECK_OK;
                }
                else
                {
                    DD_DEBUG_PRINTF("Http_Connect FAILE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            break;  
        case VOS_OTA_CONNECT:
            //DD_DEBUG_PRINTF("State %x,Filesize %d,CurLen %d\r\n",ATState,OtaCurLen,u32updateFilesize);
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"Content-Length:")))
                {
                    pstr = pstr+15;
                    u32updateFilesize = atol(pstr);
                    DD_DEBUG_PRINTF("updateFilesize:%d \r\n",u32updateFilesize);  
                    ATState = AT_RESP_CHECK_STEP_1;
                }   
            }
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+HTTPNMIC:")))
                {
                    if(NULL != (pstr = strstr((void *)pRcvMsg,"+HTTPNMIC: 0,1024,")))
                    {
                        pstr = pstr+18;
                        OtaCurLen = atol(pstr);
                        DD_DEBUG_PRINTF("CurFlashAddr:%d \r\n",OtaCurLen);  
                        ATState = AT_RESP_CHECK_STEP_1;
                    }
                    else if(NULL != (pstr = strstr((void *)pRcvMsg,"+HTTPNMIC: 0,")))//last data len
                    {
                        pstr = pstr+14;
                        //DD_DEBUG_PUTS(pos);
                        if(NULL != (pstr = strstr((void *)pstr,",")))
                        {
                            pstr++;
                            OtaCurLen = atol(pstr);
                            DD_DEBUG_PRINTF("CurFlashAddr:%d \r\n",OtaCurLen);  
                        }    
                    }
                    if(OtaCurLen == u32updateFilesize)
                    {
                        DD_DEBUG_PRINTF("OTA DOWNLOAD SUCCESS !\r\n");  
                        Dd_Flash_Ota_VerCfg_McuUpdate(u32updateFilesize);
                        ATState = AT_RESP_CHECK_OK;
                    }
                }
            }    
            break;  
          default:
            break;            
    }
    return ATState;
}
#endif

#ifdef AI_FTECH_SZ
u8 Sys_At_FrutechMsgCheck(u8 * pRcvMsg, u8 ATState, u32 MsgTpye)
{
    u8                  *pstr = NULL;

    switch(MsgTpye)
    {
        case VOS_AT_FRUTECH_IPSTART:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
                else
                {
                    DD_DEBUG_PRINTF("IP_Start FALSE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"CONNECT OK")))
                {
                    ATState = AT_RESP_CHECK_OK;
                }
                else
                {
                    DD_DEBUG_PRINTF("IPStart_Connect FAILE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }
            break;  
        case VOS_AT_FRUTECH_IPRCFG:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"OK")))
                {
                    ATState = AT_RESP_CHECK_OK;
                }
                else
                {
                    DD_DEBUG_PRINTF("IPRCFG FALSE\r\n");
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }            
            break;  
        case VOS_AT_FRUTECH_IPSEND_LOGIN:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPSEND:")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
            }    
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPRD:")))
                {
                    if((pstr = strstr((void *)pRcvMsg,"LOGIN [OK]")))
                    {
                        ATState = AT_RESP_CHECK_OK;
                    }
                    else
                    {
                        DD_DEBUG_PRINTF("IPLOGIN FALSE\r\n");
                        ATState = AT_RESP_CHECK_ERROR;
                    }    
                }
            }    
            break; 
        case VOS_AT_FRUTECH_IPSEND_SIM:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPSEND:")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
            }    
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPRD:")))
                {
                    if((pstr = strstr((void *)pRcvMsg,"SIM [OK]")))
                    {
                        ATState = AT_RESP_CHECK_OK;
                    }
                    else
                    {
                        DD_DEBUG_PRINTF("IPSEND_SIM FALSE\r\n");
                        ATState = AT_RESP_CHECK_ERROR;
                    }  
                }
            } 
            break; 
        case VOS_AT_FRUTECH_IPSEND_HEART_BEAT:
            if(ATState == AT_RESP_CHECK_START)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPSEND:")))
                {
                    ATState = AT_RESP_CHECK_STEP_1;
                }
                else if(NULL != (pstr = strstr((void *)pRcvMsg,"ERROR")))
                {
                    ATState = AT_RESP_CHECK_ERROR;
                }    
            }    
            else if(ATState == AT_RESP_CHECK_STEP_1)
            {
                if(NULL != (pstr = strstr((void *)pRcvMsg,"+IPRD:")))
                {
                    if((pstr = strstr((void *)pRcvMsg,"INFO [OK]")))
                    {
                        ATState = AT_RESP_CHECK_OK;
                    }  
                    else
                    {
                        ATState = AT_RESP_CHECK_ERROR;
                    }    
                }
            }                
            break; 
          default:
            break;            
    }
    return ATState;    
}
#endif


#endif
/******************************* 源文件结束 ***********************************/


