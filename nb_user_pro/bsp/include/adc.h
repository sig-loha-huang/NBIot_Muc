/*******************************************************************************
* COPYRIGHT@ SIGBEAN
********************************************************************************
* 文件名称: adc.h
* 功能描述: 
* 其它说明: 
* 编写日期: 
* 修改历史: 
* 修改日期修改人BugID/CRID      修改内容
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __ADC_H__
#define __ADC_H__

/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/
/************************ ADC REG  ************************************/
#define    ADC_ENA			        0x400A0000
#define    ADC_SOC			        0x400A0004	
#define    ADC_CHN			        0x400A0008
#define    ADC_CTRL			        0x400A000C
#define    ADC_RSTN			        0x400A0010
#define    ADC_CLK_DIV			    0x400A0014
#define    ADC_RSLT			        0x400A0018
#define    TEMSEN_ENA			    0x400A001C
                 	
#define    ADC_CTRL_INTCFG			0x400A0F00
#define    ADC_CTRL_INTFLG			0x400A0F04
#define    ADC_CTRL_INTENA			0x400A0F08
#define    ADC_CTRL_INTUNE			0x400A0F0C
#define    ADC_CTRL_INTMSK			0x400A0F10
#define    ADC_CTRL_INTUNM			0x400A0F14
#define    ADC_CTRL_INTCLR			0x400A0F18
#define    ADC_CTRL_INTFRC			0x400A0F1C
#define    ADC_CTRL_INTOVF			0x400A0F20
#define    ADC_CTRL_SHDCLR			0x400A0F24
#define    ADC_CTRL_OVFCLR			0x400A0F28
#define    ADC_CTRL_SRCTYP			0x400A0F2C
#define    ADC_CTRL_SRCEDG			0x400A0F30
#define    ADC_CTRL_SRCPOL			0x400A0F34
/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern void Dd_Adc_Isr(void);
extern void Dd_Adc_Enable(unsigned int channel_num);
extern void Dd_Adc_IntInit(void);
extern void Dd_Adc_Test(void);

/******************************** 头文件保护结尾 ******************************/
#endif /* __ADC_H__ */
/******************************** 头文件结束 **********************************/


