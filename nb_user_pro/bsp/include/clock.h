/*******************************************************************************
* COPYRIGHT@ SIGBEAN
********************************************************************************
* �ļ�����: clock.h
* ��������: 
* ����˵��: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** ͷ�ļ�������ͷ ******************************/
#ifndef CLOCK_H
#define CLOCK_H

/******************************** �����ļ����� ********************************/

/******************************** ��ͳ������� ********************************/
#define  PLL_DIV_PRE   4
#define  PLL_DIV_LOOP  112
#define  PLL_DIV_OUT   2
 
#define  PLL_SW_VCO_60_120M       1
#define  PLL_SW_VCO_100_200M      2
#define  PLL_SW_VCO_160_280M      3
#define  PLL_SW_VCO_220_360M      4
#define  PLL_SW_VCO_300_440M      5
#define  PLL_SW_VCO_380_520M      6
#define  PLL_SW_VCO_460_600M      7


#define  PLL_SW_ICP          1         //��charge pump����ֵ�й�
#define  PLL_SW_LP           1         //1:at low power mode; 0:not at low power mode
#define  PLL_SW_LOCK         0         //��ʼֵΪ0��0:Not bypass PLL lock; 1:Bypass PLL lock
#define  PLL_SW_VREG         2         //��ʼֵΪ2��b01���빩���ѹ�й�

#define  PLL_EN_PLL          1         //1��Ч

#define  PLL_USE_EXTCLK      0x01
#define  PLL_USE_PLLCLK      0x02
/******************************** ���Ͷ��� ************************************/

/******************************** ȫ�ֱ������� ********************************/

/******************************** �ⲿ����ԭ������ ****************************/
extern void Dd_Clock_Init(void);
extern void Dd_Pll_Enable(void);
extern unsigned long clock_get_apb(void);
extern void Dd_Clock_Pll_268M(void);
extern void Dd_Clock_Pll_153M(void);
extern void Dd_Clock_Pll_76M(void);
extern void Dd_Clock_Pll_268M_DIV_Test(u32 PllDiv);
extern void Dd_Clock_Use_ExtClock(void);
extern void Dd_Clock_Use_ExtClock_DIV_Test(u32 PllDiv);
extern void vPortUseExtClkSetupSysTick(void);

/******************************** ͷ�ļ�������β ******************************/
#endif /*CLOCK_H*/
/******************************** ͷ�ļ����� **********************************/

