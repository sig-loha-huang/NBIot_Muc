/*******************************************************************************
********************************************************************************
* 文件名称: uart.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef UART_H
#define UART_H

/******************************** 包含文件声明 ********************************/
#include <bsp_reg.h>
/******************************** 宏和常量定义 ********************************/
#define UART3_RX_PIN                            1
#define UART3_TX_PIN                            0

#define UART2_RX_PIN                            3
#define UART2_TX_PIN                            2

#define UART_RX_INTERRUPT                       0x04
#define UART_RX_TIMEOUT_INT                     0x0C
#define UART_RX_BUSY                            0x07

#ifdef RF_REG_CHECK
#define UART2_BAUD_RATE                         115200
#else
#define UART2_BAUD_RATE                         150000
#endif

#define UART_LINE_STATUS                        0x06

#define UART_LSR_DR		                        0x01 /* Receiver data ready */

#define LINEFEED				0x0a
#define CARRIAGERETURN			0x0d

#define UART_INT_SET            0x01
#define UART_INT_OUT            0x00                        

#define UART_BASE_ADDR                          (0x40050000)

#define UART0_BASE_ADDR                         (UART_BASE_ADDR + 0x0000)
#define UART1_BASE_ADDR                         (UART_BASE_ADDR + 0x1000)
#define UART2_BASE_ADDR                         (UART_BASE_ADDR + 0x2000)
#define UART3_BASE_ADDR                         (UART_BASE_ADDR + 0x3000)

#define REG_UART0_RBR_OS                        (UART0_BASE_ADDR + 0x000)
#define REG_UART0_THR_OS                        (UART0_BASE_ADDR + 0x000)
#define REG_UART0_DLL_OS                        (UART0_BASE_ADDR + 0x000)
#define REG_UART0_IER_OS                        (UART0_BASE_ADDR + 0x004)
#define REG_UART0_DLH_OS                        (UART0_BASE_ADDR + 0x004)
#define REG_UART0_IIR_OS                        (UART0_BASE_ADDR + 0x008)
#define REG_UART0_FCR_OS                        (UART0_BASE_ADDR + 0x008)
#define REG_UART0_LCR_OS                        (UART0_BASE_ADDR + 0x00c)
#define REG_UART0_MCR_OS                        (UART0_BASE_ADDR + 0x010)
#define REG_UART0_LSR_OS                        (UART0_BASE_ADDR + 0x014)
#define REG_UART0_MSR_OS                        (UART0_BASE_ADDR + 0x018)
#define REG_UART0_SCR_OS                        (UART0_BASE_ADDR + 0x01c)
#define REG_UART0_LPDLL_OS                      (UART0_BASE_ADDR + 0x020)
#define REG_UART0_LPDLH_OS                      (UART0_BASE_ADDR + 0x024)
#define REG_UART0_SRBR_LOW_OS                   (UART0_BASE_ADDR + 0x030)
#define REG_UART0_SRBR_HIGH_OS                  (UART0_BASE_ADDR + 0x06c)
#define REG_UART0_STHR_LOW_OS                   (UART0_BASE_ADDR + 0x030)
#define REG_UART0_STHR_HIGH_OS                  (UART0_BASE_ADDR + 0x06c)
#define REG_UART0_FAR_OS                        (UART0_BASE_ADDR + 0x070)
#define REG_UART0_TFR_OS                        (UART0_BASE_ADDR + 0x074)
#define REG_UART0_RFW_OS                        (UART0_BASE_ADDR + 0x078)
#define REG_UART0_USR_OS                        (UART0_BASE_ADDR + 0x07c)
#define REG_UART0_TFL_OS                        (UART0_BASE_ADDR + 0x080)
#define REG_UART0_RFL_OS                        (UART0_BASE_ADDR + 0x084)
#define REG_UART0_SRR_OS                        (UART0_BASE_ADDR + 0x088)
#define REG_UART0_SRTS_OS                       (UART0_BASE_ADDR + 0x08c)
#define REG_UART0_SBCR_OS                       (UART0_BASE_ADDR + 0x090)
#define REG_UART0_SDMAM_OS                      (UART0_BASE_ADDR + 0x094)
#define REG_UART0_SFE_OS                        (UART0_BASE_ADDR + 0x098)
#define REG_UART0_SRT_OS                        (UART0_BASE_ADDR + 0x09c)
#define REG_UART0_STET_OS                       (UART0_BASE_ADDR + 0x0a0)
#define REG_UART0_HTX_OS                        (UART0_BASE_ADDR + 0x0a4)
#define REG_UART0_DMASA_OS                      (UART0_BASE_ADDR + 0x0a8)
#define REG_UART0_CPR_OS                        (UART0_BASE_ADDR + 0x0f4)
#define REG_UART0_CV_OS                         (UART0_BASE_ADDR + 0x0f8)
#define REG_UART0_CTR_OS                        (UART0_BASE_ADDR + 0x0fc)

#define REG_UART1_RBR_OS                        (UART1_BASE_ADDR + 0x000)
#define REG_UART1_THR_OS                        (UART1_BASE_ADDR + 0x000)
#define REG_UART1_DLL_OS                        (UART1_BASE_ADDR + 0x000)
#define REG_UART1_IER_OS                        (UART1_BASE_ADDR + 0x004)
#define REG_UART1_DLH_OS                        (UART1_BASE_ADDR + 0x004)
#define REG_UART1_IIR_OS                        (UART1_BASE_ADDR + 0x008)
#define REG_UART1_FCR_OS                        (UART1_BASE_ADDR + 0x008)
#define REG_UART1_LCR_OS                        (UART1_BASE_ADDR + 0x00c)
#define REG_UART1_MCR_OS                        (UART1_BASE_ADDR + 0x010)
#define REG_UART1_LSR_OS                        (UART1_BASE_ADDR + 0x014)
#define REG_UART1_MSR_OS                        (UART1_BASE_ADDR + 0x018)
#define REG_UART1_SCR_OS                        (UART1_BASE_ADDR + 0x01c)
#define REG_UART1_LPDLL_OS                      (UART1_BASE_ADDR + 0x020)
#define REG_UART1_LPDLH_OS                      (UART1_BASE_ADDR + 0x024)
#define REG_UART1_SRBR_LOW_OS                   (UART1_BASE_ADDR + 0x030)
#define REG_UART1_SRBR_HIGH_OS                  (UART1_BASE_ADDR + 0x06c)
#define REG_UART1_STHR_LOW_OS                   (UART1_BASE_ADDR + 0x030)
#define REG_UART1_STHR_HIGH_OS                  (UART1_BASE_ADDR + 0x06c)
#define REG_UART1_FAR_OS                        (UART1_BASE_ADDR + 0x070)
#define REG_UART1_TFR_OS                        (UART1_BASE_ADDR + 0x074)
#define REG_UART1_RFW_OS                        (UART1_BASE_ADDR + 0x078)
#define REG_UART1_USR_OS                        (UART1_BASE_ADDR + 0x07c)
#define REG_UART1_TFL_OS                        (UART1_BASE_ADDR + 0x080)
#define REG_UART1_RFL_OS                        (UART1_BASE_ADDR + 0x084)
#define REG_UART1_SRR_OS                        (UART1_BASE_ADDR + 0x088)
#define REG_UART1_SRTS_OS                       (UART1_BASE_ADDR + 0x08c)
#define REG_UART1_SBCR_OS                       (UART1_BASE_ADDR + 0x090)
#define REG_UART1_SDMAM_OS                      (UART1_BASE_ADDR + 0x094)
#define REG_UART1_SFE_OS                        (UART1_BASE_ADDR + 0x098)
#define REG_UART1_SRT_OS                        (UART1_BASE_ADDR + 0x09c)
#define REG_UART1_STET_OS                       (UART1_BASE_ADDR + 0x0a0)
#define REG_UART1_HTX_OS                        (UART1_BASE_ADDR + 0x0a4)
#define REG_UART1_DMASA_OS                      (UART1_BASE_ADDR + 0x0a8)
#define REG_UART1_CPR_OS                        (UART1_BASE_ADDR + 0x0f4)
#define REG_UART1_CV_OS                         (UART1_BASE_ADDR + 0x0f8)
#define REG_UART1_CTR_OS                        (UART1_BASE_ADDR + 0x0fc)

#define REG_UART2_RBR_OS                        (UART2_BASE_ADDR + 0x000)
#define REG_UART2_THR_OS                        (UART2_BASE_ADDR + 0x000)
#define REG_UART2_DLL_OS                        (UART2_BASE_ADDR + 0x000)
#define REG_UART2_IER_OS                        (UART2_BASE_ADDR + 0x004)
#define REG_UART2_DLH_OS                        (UART2_BASE_ADDR + 0x004)
#define REG_UART2_IIR_OS                        (UART2_BASE_ADDR + 0x008)
#define REG_UART2_FCR_OS                        (UART2_BASE_ADDR + 0x008)
#define REG_UART2_LCR_OS                        (UART2_BASE_ADDR + 0x00c)
#define REG_UART2_MCR_OS                        (UART2_BASE_ADDR + 0x010)
#define REG_UART2_LSR_OS                        (UART2_BASE_ADDR + 0x014)
#define REG_UART2_MSR_OS                        (UART2_BASE_ADDR + 0x018)
#define REG_UART2_SCR_OS                        (UART2_BASE_ADDR + 0x01c)
#define REG_UART2_LPDLL_OS                      (UART2_BASE_ADDR + 0x020)
#define REG_UART2_LPDLH_OS                      (UART2_BASE_ADDR + 0x024)
#define REG_UART2_SRBR_LOW_OS                   (UART2_BASE_ADDR + 0x030)
#define REG_UART2_SRBR_HIGH_OS                  (UART2_BASE_ADDR + 0x06c)
#define REG_UART2_STHR_LOW_OS                   (UART2_BASE_ADDR + 0x030)
#define REG_UART2_STHR_HIGH_OS                  (UART2_BASE_ADDR + 0x06c)
#define REG_UART2_FAR_OS                        (UART2_BASE_ADDR + 0x070)
#define REG_UART2_TFR_OS                        (UART2_BASE_ADDR + 0x074)
#define REG_UART2_RFW_OS                        (UART2_BASE_ADDR + 0x078)
#define REG_UART2_USR_OS                        (UART2_BASE_ADDR + 0x07c)
#define REG_UART2_TFL_OS                        (UART2_BASE_ADDR + 0x080)
#define REG_UART2_RFL_OS                        (UART2_BASE_ADDR + 0x084)
#define REG_UART2_SRR_OS                        (UART2_BASE_ADDR + 0x088)
#define REG_UART2_SRTS_OS                       (UART2_BASE_ADDR + 0x08c)
#define REG_UART2_SBCR_OS                       (UART2_BASE_ADDR + 0x090)
#define REG_UART2_SDMAM_OS                      (UART2_BASE_ADDR + 0x094)
#define REG_UART2_SFE_OS                        (UART2_BASE_ADDR + 0x098)
#define REG_UART2_SRT_OS                        (UART2_BASE_ADDR + 0x09c)
#define REG_UART2_STET_OS                       (UART2_BASE_ADDR + 0x0a0)
#define REG_UART2_HTX_OS                        (UART2_BASE_ADDR + 0x0a4)
#define REG_UART2_DMASA_OS                      (UART2_BASE_ADDR + 0x0a8)
#define REG_UART2_CPR_OS                        (UART2_BASE_ADDR + 0x0f4)
#define REG_UART2_CV_OS                         (UART2_BASE_ADDR + 0x0f8)
#define REG_UART2_CTR_OS                        (UART2_BASE_ADDR + 0x0fc)

#define REG_UART3_RBR_OS                        (UART3_BASE_ADDR + 0x000)
#define REG_UART3_THR_OS                        (UART3_BASE_ADDR + 0x000)
#define REG_UART3_DLL_OS                        (UART3_BASE_ADDR + 0x000)
#define REG_UART3_IER_OS                        (UART3_BASE_ADDR + 0x004)
#define REG_UART3_DLH_OS                        (UART3_BASE_ADDR + 0x004)
#define REG_UART3_IIR_OS                        (UART3_BASE_ADDR + 0x008)
#define REG_UART3_FCR_OS                        (UART3_BASE_ADDR + 0x008)
#define REG_UART3_LCR_OS                        (UART3_BASE_ADDR + 0x00c)
#define REG_UART3_MCR_OS                        (UART3_BASE_ADDR + 0x010)
#define REG_UART3_LSR_OS                        (UART3_BASE_ADDR + 0x014)
#define REG_UART3_MSR_OS                        (UART3_BASE_ADDR + 0x018)
#define REG_UART3_SCR_OS                        (UART3_BASE_ADDR + 0x01c)
#define REG_UART3_LPDLL_OS                      (UART3_BASE_ADDR + 0x020)
#define REG_UART3_LPDLH_OS                      (UART3_BASE_ADDR + 0x024)
#define REG_UART3_SRBR_LOW_OS                   (UART3_BASE_ADDR + 0x030)
#define REG_UART3_SRBR_HIGH_OS                  (UART3_BASE_ADDR + 0x06c)
#define REG_UART3_STHR_LOW_OS                   (UART3_BASE_ADDR + 0x030)
#define REG_UART3_STHR_HIGH_OS                  (UART3_BASE_ADDR + 0x06c)
#define REG_UART3_FAR_OS                        (UART3_BASE_ADDR + 0x070)
#define REG_UART3_TFR_OS                        (UART3_BASE_ADDR + 0x074)
#define REG_UART3_RFW_OS                        (UART3_BASE_ADDR + 0x078)
#define REG_UART3_USR_OS                        (UART3_BASE_ADDR + 0x07c)
#define REG_UART3_TFL_OS                        (UART3_BASE_ADDR + 0x080)
#define REG_UART3_RFL_OS                        (UART3_BASE_ADDR + 0x084)
#define REG_UART3_SRR_OS                        (UART3_BASE_ADDR + 0x088)
#define REG_UART3_SRTS_OS                       (UART3_BASE_ADDR + 0x08c)
#define REG_UART3_SBCR_OS                       (UART3_BASE_ADDR + 0x090)
#define REG_UART3_SDMAM_OS                      (UART3_BASE_ADDR + 0x094)
#define REG_UART3_SFE_OS                        (UART3_BASE_ADDR + 0x098)
#define REG_UART3_SRT_OS                        (UART3_BASE_ADDR + 0x09c)
#define REG_UART3_STET_OS                       (UART3_BASE_ADDR + 0x0a0)
#define REG_UART3_HTX_OS                        (UART3_BASE_ADDR + 0x0a4)
#define REG_UART3_DMASA_OS                      (UART3_BASE_ADDR + 0x0a8)
#define REG_UART3_CPR_OS                        (UART3_BASE_ADDR + 0x0f4)
#define REG_UART3_CV_OS                         (UART3_BASE_ADDR + 0x0f8)
#define REG_UART3_CTR_OS                        (UART3_BASE_ADDR + 0x0fc)
/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern int Dd_Uart2_Init(int U32BaudRate,char U8StopBit,char U8Parity,int pllclk);
extern void Dd_Uart2_Putc(const char u8Ch);
extern void Dd_Uart2_Puts(char *s);
extern unsigned char Dd_Uart2_Getc(void);
extern void Dd_Uart2_Printf(char *args, ...);
extern void Dd_Uart2_SendString (const char *str, int strLength);
extern void Dd_Uart2_Reset(void);

/******************************* for test ***********************************/
extern void Dd_Uart2_Test(void);

/******************************** 头文件保护结尾 ******************************/
#endif /*UART_H*/
/******************************** 头文件结束 **********************************/
