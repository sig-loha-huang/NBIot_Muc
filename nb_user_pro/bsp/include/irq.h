/*******************************************************************************
********************************************************************************
* 文件名称: irq.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef IRQ_H
#define IRQ_H

/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/

/*各个外设的中断号*/
#define IRQ_WDT0              0
#define IRQ_WDT1              1
#define IRQ_GPIOA             2
#define IRQ_GPIOB             3
#define IRQ_TIMER0            4
#define IRQ_TIMER1            5
#define IRQ_RESV              6
#define IRQ_I2C               7
#define IRQ_UART0             8
#define IRQ_UART1             9
#define IRQ_UART2             10
#define IRQ_UART3             11
#define IRQ_SPI0              12
#define IRQ_SPI1              13
#define IRQ_SPI2              14
#define IRQ_SCI               15
#define IRQ_DAA               16
#define IRQ_CIPHER            17
#define IRQ_ADC               18
#define IRQ_SHA               19
#define IRQ_CPM0              20
#define IRQ_CPM1              21
#define IRQ_CPM2              22
#define IRQ_SDMA              23
#define IRQ_DMAC0_CH0         24
#define IRQ_DMAC0_CH1         25
#define IRQ_DMAC0_CH2         26
#define IRQ_DMAC0_CH3         27
#define IRQ_DMAC1_CH0         28
#define IRQ_DMAC1_CH1         29
#define IRQ_DMAC1_CH2         30
#define IRQ_DMAC1_CH3         31




/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/

extern void Dd_DoReset(void);
extern void Dd_InterVectorRemap(void);


/******************************** 头文件保护结尾 ******************************/
#endif /*IRQ_H*/
/******************************** 头文件结束 **********************************/

