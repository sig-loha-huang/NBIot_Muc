/*******************************************************************************
* COPYRIGHT@ SIGBEAN
********************************************************************************
* 文件名称: rtc.h
* 功能描述: 
* 其它说明: 
* 编写日期: 
* 修改历史: 
* 修改日期修改人BugID/CRID      修改内容
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __RTC_H__
#define __RTC_H__

/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/
/************************ RTC and PMU REG  ************************************/
#define    REG_RTC_SEC_UNIT			0x400C0000
#define    REG_RTC_TIMING			0x400C0004	
#define    REG_RTC_WAKEUP_SU		0x400C0008
#define    REG_RTC_WAKEUP_M			0x400C000C
#define    REG_RTC_WAKEUP_D			0x400C0010
#define    REG_RTC_PAD_MODE			0x400C0014
#define    REG_RTC_CTRL				0x400C0018
#define    REG_RSTN_DLY				0x400C001C
#define    REG_PMU_CFG0				0x400C0020
#define    REG_PMU_CFG1				0x400C0024
#define    REG_PMU_CFG2				0x400C0028
#define    REG_PMU_CFG3				0x400C002C
                 	
#define    REG_RETENTION00			0x400C0030
#define    REG_RETENTION01			0x400C0034
#define    REG_RETENTION02			0x400C0038
#define    REG_RETENTION03			0x400C003C
#define    REG_RETENTION04			0x400C0040
#define    REG_RETENTION05			0x400C0044
#define    REG_RETENTION06			0x400C0048
#define    REG_RETENTION07			0x400C004C
#define    REG_RETENTION08			0x400C0050
#define    REG_RETENTION09			0x400C0054
#define    REG_RETENTION10			0x400C0058
#define    REG_RETENTION11			0x400C005C
#define    REG_RETENTION12			0x400C0060
#define    REG_RETENTION13			0x400C0064
#define    REG_RETENTION14			0x400C0068
#define    REG_RETENTION15			0x400C006C
#define    REG_RTC_SEC_UNIT_R		0x400C0070
#define    REG_RTC_TIMING_R			0x400C0074
#define    REG_RTC_VALUE_R			0x400C0078
/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern void Dd_Rtc_InitTimeConfig(u16 day,u8  hour,u8  min,u8  sec);
extern void Dd_Rtc_RelativeToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec);
extern void Dd_Rtc_AfterToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec);
extern void Dd_Rtc_ExternSignalWakeUp_Init(void);
extern void Dd_Rtc_PadClrMeasure(u8 PadNum);
extern void Dd_Rtc_EnterLowPowerMode(void);


extern void Dd_Cpm2_IntInit(void);
extern void Dd_CPM2_Isr(void);

/******************************* for test ***********************************/
extern void Dd_Rtc_Detect(unsigned int u32Data);
extern void Dd_Rtc_InitTime(u32 year,u32 month,u32 day,u32 hour,u32 min,u32 sec);
extern void Dd_Rtc_Time(void);
extern void Dd_Rtc_RelativeToInitialTimeWakeUpTest(u32 MAndDay,u32 MAndSec,u32 DAndDay,u32 DAndhour,u32 DAndmin,u32 DAndsec);
extern void Dd_Rtc_AfterToInitialTimeWakeUpTest(u32 MAndDay,u32 MAndSec,u32 DAndDay,u32 DAndhour,u32 DAndmin,u32 DAndsec);
extern void Dd_Rtc_LowPowerTest(u32 u32Data,u32 msTime);
extern void Dd_Mipi_LowPowerMode(void);


/******************************** 头文件保护结尾 ******************************/
#endif /* __RTC_H__ */
/******************************** 头文件结束 **********************************/


