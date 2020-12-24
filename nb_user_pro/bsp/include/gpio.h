/*******************************************************************************
* COPYRIGHT@ SIGBEN
********************************************************************************
* 文件名称: gpio.h
* 功能描述: 
* 其它说明: 
* 编写日期: 
* 修改历史: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef GPIO_H
#define GPIO_H
/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/
/******************************** GPIO PIN TEST *******************************/
#define GPIO_PIN_02         2
#define GPIO_PIN_03         3

#define GPIO_LED_RED_PIN    29
#define GPIO_LED_GREEN_PIN  30

#define GPIO_DIR_INPUT      0
#define GPIO_DIR_OUTPUT     1
#define GPIO_OUTPUT_LOW     0
#define GPIO_OUTPUT_HIGH    1

#define GPIO_INT_TYPE_LEVEL     0
#define GPIO_INT_TYPE_EDGE      1

#define GPIO_INT_POLA_LOW          0
#define GPIO_INT_POLA_HIGH         1
#define GPIO_INT_POLA_BOTH         2

//-----------------------------------------------------------------
// GPIO Register Map
//head-------------------------------------------------------------
#define GPIOA_BASE_ADDR                          (0x40020000)
#define REG_GPIO_SWPORTA_DR                     (GPIOA_BASE_ADDR + 0x000)    //数据寄存器
#define REG_GPIO_SWPORTA_DDR                    (GPIOA_BASE_ADDR + 0x004)    //方向寄存器 1:输出 0:输入
#define REG_GPIO_SWPORTA_CTL                    (GPIOA_BASE_ADDR + 0x008) 

#define REG_GPIO_SWPORTA_INTEN                  (GPIOA_BASE_ADDR + 0x030)  
#define REG_GPIO_SWPORTA_INTMAK                 (GPIOA_BASE_ADDR + 0x034)  
#define REG_GPIO_SWPORTA_INTTYPE_LEVEL          (GPIOA_BASE_ADDR + 0x038)  
#define REG_GPIO_SWPORTA_INT_POLARITY           (GPIOA_BASE_ADDR + 0x03C)  
#define REG_GPIO_SWPORTA_INTSTATUS              (GPIOA_BASE_ADDR + 0x040)  
#define REG_GPIO_SWPORTA_RAW_INTSTATUS          (GPIOA_BASE_ADDR + 0x044)  
#define REG_GPIO_SWPORTA_DEBOUNCE               (GPIOA_BASE_ADDR + 0x048)   //去抖寄存器
#define REG_GPIO_SWPORTA_PORTA_EOI              (GPIOA_BASE_ADDR + 0x04C)  


#define REG_GPIO_SWPORTA_EXT_PORTA              (GPIOA_BASE_ADDR + 0x050)  
#define REG_GPIO_SWPORTA_INT_BOTHEDGE           (GPIOA_BASE_ADDR + 0x068)    //GPIO双沿中断寄存器

#define GPIOB_BASE_ADDR                          (0x40021000)

#define REG_GPIO_SWPORTB_DR                     (GPIOB_BASE_ADDR + 0x000)    //数据寄存器
#define REG_GPIO_SWPORTB_DDR                    (GPIOB_BASE_ADDR + 0x004)    //方向寄存器 1:输出 0:输入
#define REG_GPIO_SWPORTB_CTL                    (GPIOB_BASE_ADDR + 0x008) 

#define REG_GPIO_SWPORTB_INTEN                  (GPIOB_BASE_ADDR + 0x030)  
#define REG_GPIO_SWPORTB_INTMAK                 (GPIOB_BASE_ADDR + 0x034)  
#define REG_GPIO_SWPORTB_INTTYPE_LEVEL          (GPIOB_BASE_ADDR + 0x038)  
#define REG_GPIO_SWPORTB_INT_POLARITY           (GPIOB_BASE_ADDR + 0x03C)  
#define REG_GPIO_SWPORTB_INTSTATUS              (GPIOB_BASE_ADDR + 0x040)  
#define REG_GPIO_SWPORTB_RAW_INTSTATUS          (GPIOB_BASE_ADDR + 0x044)  
#define REG_GPIO_SWPORTB_DEBOUNCE               (GPIOB_BASE_ADDR + 0x048)   //去抖寄存器
#define REG_GPIO_SWPORTB_PORTA_EOI              (GPIOB_BASE_ADDR + 0x04C)  

#define REG_GPIO_SWPORTB_EXT_PORTA              (GPIOB_BASE_ADDR + 0x050)  
#define REG_GPIO_SWPORTB_INT_BOTHEDGE           (GPIOB_BASE_ADDR + 0x068)    //GPIO双沿中断寄存器
 


//end--------------------------------------------------------------

/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern void Dd_SetIOBFunction0(u32 PinBit);
extern void Dd_SetIOBFunction1(u32 PinBit);
extern void Dd_SetIOBFunction2(u32 PinBit);
extern void Dd_SetIOBFunction3(u32 PinBit);
extern void Dd_GpioB_SetDir(u32 u32PinBit,u32 u32DirFlag);
extern void Dd_GpioB_SetOut(u32 u32PinBit,u32 u32OutFlag);
extern u32 Dd_GpioB_ReadData(void);
extern void Dd_GpioB_SetInterFun(u8 IntTpye,u8 IntPolarity,u32 u32PinBit);
extern void Dd_GpioB_Isr(void);
extern void Dd_SetIOAFunction0(u32 PinBit);
extern void Dd_SetIOAFunction1(u32 PinBit);
extern void Dd_SetIOAFunction2(u32 PinBit);
extern void Dd_SetIOAFunction3(u32 PinBit);
extern u32 Dd_GpioA_ReadData(void);
extern u8 Dd_GpioA_ReadPinBit(u32 u32PinBit);
extern u8 Dd_GpioB_ReadPinBit(u32 u32PinBit);
extern void Dd_GpioA_Isr(void);


extern void Dd_Gpio_Led_Init(void);
extern void Dd_Gpio_Led_RedOn(void);
extern void Dd_Gpio_Led_RedOff(void);
extern void Dd_Gpio_Led_GreenOn(void);
extern void Dd_Gpio_Led_GreenOff(void);


/******************************** 头文件保护结尾 ******************************/
#endif /* GPIO_H */
/******************************** 头文件结束 **********************************/

