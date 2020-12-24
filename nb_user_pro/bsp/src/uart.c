/******************************* 包含文件声明 *********************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <cortex_m4.h>
#include <vos.h>
/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/
extern osal_SemHandle DdCmdDataReadySem;
unsigned int g_u32Uart2Clk = 0;
/******************************* 全局变量定义 *********************************/
extern u8 g_u8UartCmdBuf[2048];
extern u8 g_u8AppCmdBuf[2048];
extern u32  g_u32AtCmdLenApp ; 
extern u32  g_u32CmdIndex;
/******************************* 函数实现 *************************************/
int Dd_Uart2_Init(int U32BaudRate,char U8StopBit,char U8Parity,int pllclk)
{
    int U32Data;
    int div;  
    int Remainder;

    if(g_u32Uart2Clk == pllclk)
        return 0;

    Dd_Uart2_Reset();
    
    /* GPIO复用配置 */    
    REG(REG_IO_FUNC_HSEL0_SET) |= ((1<<UART2_RX_PIN)|(1<<UART2_TX_PIN));
    REG(REG_IO_FUNC_LSEL0_CLR) |= ((1<<UART2_RX_PIN)|(1<<UART2_TX_PIN)); 
    
    /* 数据位为8 */
    U32Data = (U8Parity << 3) | (U8StopBit << 2) | 0x00000002 | 1 ;
    
    REG(REG_UART2_LCR_OS) = U32Data;

    div = pllclk/U32BaudRate >> 4;
    
    Remainder = (pllclk/U32BaudRate)%16;
    
    if(Remainder>8)
    {
        div++;
    }    
    
    REG(REG_UART2_LCR_OS) |= 0x80;
    
    REG(REG_UART2_DLL_OS) = (div&0xff);
    REG(REG_UART2_DLH_OS) = (div>>8);
    
    REG(REG_UART2_LCR_OS) &= 0xffffff7f;

    #if (UART_USE_MEM_POOL == 1)
    {
        /*配置uart DMA 模式 */
     //   REG(REG_UART2_FCR_OS) = 0xb9;
        REG(REG_UART2_FCR_OS) = 0x01|(1<<1)|(1<<6) ; /* FIFO 1/2 full */
    }
    #endif
    /*使能接收中断*/
    REG(REG_UART2_IER_OS) = 0x01;

    g_u32Uart2Clk = pllclk;

    return 0;
}

void Dd_Uart2_Reset(void)
{
    int Count = 0;
    REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) & (~(1<<19));
    REG(REG_CLK_GATE) = REG(REG_CLK_GATE) & (~(1<<19)); 
    for(Count = 0;Count<0x100;Count++);
    REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) | (1<<19);
    REG(REG_CLK_GATE) = REG(REG_CLK_GATE) | (1<<19);         
}

void Dd_Uart2_Putc(const char u8Ch)
{
    while(!(REG(REG_UART2_LSR_OS) & 0x20));
    REG(REG_UART2_THR_OS) = u8Ch;
    return;
}
void Dd_Uart2_Puts(char *s)
{
	while (*s)
	{
		Dd_Uart2_Putc(*s++);
	}
}
NB_FAST_CODE unsigned char Dd_Uart2_Getc(void)
{
    unsigned char u8Ch;
    while((REG(REG_UART2_LSR_OS) & 0x01) == 0);
    u8Ch = (unsigned char) (REG(REG_UART2_RBR_OS) & 0xff);
    return u8Ch;
}



void Dd_Uart2_Printf(char *args, ...)
{
    char  	trace_mesg[1024] = {0};
    int     trace_size;

    va_list p_arguments;

    va_start(p_arguments, args);
   
    trace_size = vsprintf(trace_mesg, args, p_arguments);
    trace_mesg[trace_size] = '\0';
    va_end(p_arguments);

	Dd_Uart2_Puts(trace_mesg);
}

void Dd_Uart2_SendString (const char *str, int strLength)
{
    int counter;
    for(counter = 0; counter < strLength; counter++)
    {
        //Dd_Func_ReadCicle_Start();
        Dd_Uart2_Putc(str[counter]);
        //Dd_Func_ReadCicle_End();
    }
}
#if (UART_USE_MEM_POOL == 1)
NB_FAST_CODE void Dd_Uart2_isr(void)
{
    unsigned int U32Statue,u32LineState;    
    unsigned int u32AppCmdIndex = 0;
    unsigned char u8AppUartCmdBuf[64];

    /*读取中断状态*/
    U32Statue = REG(REG_UART2_IIR_OS)&0x0f;
    if((U32Statue&0x0f) == UART_RX_INTERRUPT)
    {
        /*Data Ready*/
        while((REG(REG_UART2_LSR_OS) & UART_LSR_DR))
        {   
            /*read data*/
            u8AppUartCmdBuf[u32AppCmdIndex++]  = (unsigned char) (REG(REG_UART2_RBR_OS) & 0xff);

        }
    } 
    else if((U32Statue&0x0f) == UART_RX_TIMEOUT_INT)
    {
        /*Data Ready*/
        while((REG(REG_UART2_LSR_OS) & UART_LSR_DR))
        {   
            /*read data*/
            u8AppUartCmdBuf[u32AppCmdIndex++] = (unsigned char) (REG(REG_UART2_RBR_OS) & 0xff);
        }  
    }     
    else if((U32Statue&0x0f) == UART_LINE_STATUS)/*Error 中断*/
    {
        /*clear int by read LSR*/
        u32LineState = REG(REG_UART2_LSR_OS);
        if(0 != (u32LineState & 0x9E))
        {
            u8AppUartCmdBuf[u32AppCmdIndex++] = 0xEE;    
        }
    }    
    else if((U32Statue&0x0f) == UART_RX_BUSY)
    {
        READ_REG(REG_UART2_USR_OS);
    }    
    buf_push(&SendToUartData, (void *)u8AppUartCmdBuf, u32AppCmdIndex);   
    u32AppCmdIndex = 0;
    /*通知驱动任务*/
    osal_SemaphoreGiveFromIsr(DdCmdDataReadySem);  

} 
#else
u32 g_u32DoubleQuotationCount = 0;
NB_FAST_CODE void Dd_Uart2_isr(void)
{
    int U32Statue;    
    unsigned char rxData;
    int index;
    /*读取中断状态*/
    U32Statue = REG(REG_UART2_IIR_OS);
    if((U32Statue&0x0f) == UART_RX_INTERRUPT)
    {
        /*判断接收命令类型*/
        rxData = Dd_Uart2_Getc();
		g_u8UartCmdBuf[g_u32CmdIndex++] = rxData;

        if((rxData == 'T')||(rxData == 't')||(rxData == 'A')||(rxData == 'a'))
        {
            /*rx at msg*/
            *g_u32AtMsgFLag = 1;
            
            if(g_u32CmdIndex>=2)
            {
                if((g_u8UartCmdBuf[g_u32CmdIndex - 2] == 'a')||(g_u8UartCmdBuf[g_u32CmdIndex - 2] == 'A'))
                {
                    g_u32DoubleQuotationCount = 0;
      //              g_u8UartCmdBuf[0] = g_u8UartCmdBuf[g_u32CmdIndex - 2];
      //              g_u8UartCmdBuf[1] = g_u8UartCmdBuf[g_u32CmdIndex - 1];
      //              g_u32CmdIndex = 2;
                }    
            }    
        }

        if(rxData == '"')
        {
            g_u32DoubleQuotationCount++;
            if(g_u32DoubleQuotationCount == 2)
            {
                g_u32DoubleQuotationCount = 0;
            }    
        }
        if(0 == g_u32DoubleQuotationCount)
        {
    		if(rxData == CARRIAGERETURN)
    		{
    			g_u8UartCmdBuf[g_u32CmdIndex] = '\0';
                
                for(index = 0;index <= g_u32CmdIndex;index++)
                {
                    g_u8AppCmdBuf[index] = g_u8UartCmdBuf[index];
                } 
                g_u32AtCmdLenApp = g_u32CmdIndex;
        		g_u32CmdIndex = 0;

                /*通知驱动任务*/
                *g_u32AtMsgFLag = 0;
                osal_SemaphoreGiveFromIsr(DdCmdDataReadySem);  
    		}
        }
    }   
    else if((U32Statue&0x0f) == UART_RX_BUSY)
    {
        READ_REG(REG_UART2_USR_OS);
    }    
} 
#endif

/******************************* 源文件结束 ***********************************/

