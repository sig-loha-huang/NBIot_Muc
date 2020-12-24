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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cortex_m4.h>
#include <core_cm3.h>

/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/
u8 g_u8DayForMonth[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
u32 g_u32CpmValue = 0;
/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/
/*******************************************************************************
* 函数名称: Dd_Rtc_InitTimeConfig
* 函数功能: Rtc初始化表时间
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_InitTimeConfig(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;


    /* 配置计s单元 32768 clk/s */
    WRITE_REG(REG_RTC_SEC_UNIT,0x8000); 

    /* 配置初始化的时间 */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    WRITE_REG(REG_RTC_TIMING,value);

    /* 使能并调表 */
    REG(REG_RTC_CTRL) |= 1;
}

/*******************************************************************************
* 函数名称: Dd_Rtc_RelativeToInitialTimeWakeUp 
* 函数功能: Rtc定点唤醒相对于初始时间
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_RelativeToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;

    /* 配置定点唤醒的时间 */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    
    WRITE_REG(REG_RTC_WAKEUP_M,value); 

}
/*******************************************************************************
* 函数名称: Dd_Rtc_RelativeToInitialTimeWakeUp 
* 函数功能: 
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_AfterToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;

    /* 配置定点唤醒的时间 */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    
    WRITE_REG(REG_RTC_WAKEUP_D,value); 
}

/*******************************************************************************
* 函数名称:  Dd_Rtc_ExternSignalWakeUp(void)
* 函数功能: 
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_ExternSignalWakeUp_Init(void)
{
    u32 value = 0;

    /*Signal0 去抖滤波阶数 Signal1去抖滤波阶数 */
    u8 Order0 = 8;
    u8 Order1 = 8;
    /*pad0 上升沿 唤醒，pad1上升沿 计量*/
    value = Order0 | (Order1 << 4) | (1<<8) | (1<<9) | (1<<11) | (1<<13);

    WRITE_REG(REG_RTC_PAD_MODE,value); 
    
}
/*******************************************************************************
* 函数名称:  Dd_Rtc_PadClrMeasure(u8 PadNum)
* 函数功能:  Pad计量清零
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_PadClrMeasure(u8 PadNum)
{
    if(PadNum == 0)
    {
       REG(REG_RTC_CTRL) |= 2;
    }    
    else if(PadNum == 1)
    {
       REG(REG_RTC_CTRL) |= 4;
    }    
}
/*******************************************************************************
* 函数名称:  Dd_Rtc_EnterLowPowerMode
* 函数功能: 
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_EnterLowPowerMode(void)
{
    /*bit25 = 1*/
    //REG(REG_PMU_CFG2) = 0x3FC86864;

    //REG(REG_PMU_CFG3) &= ~(1<<25);
    //REG(REG_PMU_CFG3) |= (1<<30);


    /* 配置reset延时 */
    REG(REG_RSTN_DLY) = 0x80;    

    
    /* 配置1位reg用于休眠快速唤醒 */
    REG(REG_RETENTION00) |= 1;

    /* 触发进入低功耗模式 */
    REG(REG_RTC_CTRL) |= (1<<3);
}

/*******************************************************************************
* 函数名称:  Dd_Cpm2_IntInit
* 函数功能:  使能rtc定时中断
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Cpm2_IntInit(void)
{

    NVIC_EnableIRQ(IRQ_CPM2);    
    NVIC_SetPriority(IRQ_CPM2,20);

    /* clear interrupt */
    REG(CPM_INTCLR) |= (1<<6);
    /*enable interrupt*/
    REG(CPM_INTENA) |= (1<<6);
    REG(CPM_INTUNM) |= (1<<6);
}

/*******************************************************************************
* 函数名称:  Dd_CPM2_Isr
* 函数功能:  中断服务程序
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
NB_FAST_CODE void Dd_CPM2_Isr(void)
{
    u32 val;
    u32 regval;  
    u32 sec,min,hour,day;
    
    val = REG(CPM_INTFLG);

    /*read flag*/
    if((val & (1<<0)) != 0)
    {
  //      Dd_Uart2_Puts("M2NB Error\n");
    }
    if((val & (1<<1)) != 0)
    {
  //      Dd_Uart2_Puts("NB2M Error\n");
    }
    if((val & (1<<5)) != 0)
    {
         REG(CPM_INTCLR) |= (1<<5);

         regval = REG(0x40000208);
         /*disable rtc det*/
         REG(REG_RTC_DETECT_CTRL) &= (~(1<<8));
         g_u32CpmValue = regval;
         DD_DEBUG_PRINTF("RTC_DETECT_VALUE:%d\r\n",regval);
    }    
    /* rtc 定时中断(非低功耗模式下) */
    if((val & (1<<6)) != 0)
    {
        /* clear interrupt */
        REG(CPM_INTCLR) |= (1<<6);
        
        /*read rtc current value*/
        regval = READ_REG(REG_RTC_TIMING_R);

        /**add user code **/
        #if 1
        u32 year,month,i;
        
        sec = regval & 0x3f;
        min = (regval & 0xfc0)>>6;
        hour = (regval & 0x1f000)>>12;
        day = (regval & 0xfffe0000)>>17;  
        year = day / 365 + 2020;

    	for (i = 0; day > g_u8DayForMonth[i]; i ++) 
        {
    		day -= g_u8DayForMonth[i];
    	}
        month = i+1;
        //DD_DEBUG_PRINTF("%d/%02d/%02d   %02d:%02d:%02d\n",year,month,day,hour,min,sec);
        #endif        
    }
    
}

/******************************* for test ***********************************/
void Dd_Rtc_Detect(unsigned int u32Data)
{
    REG(REG_RTC_DETECT_CTRL)=0;
    
    NVIC_EnableIRQ(IRQ_CPM2);    
    NVIC_SetPriority(IRQ_CPM2,20);

    /* clear interrupt */
    REG(CPM_INTCLR) |= (1<<5);
    //Dd_Uart3_Printf("CPM_INTCLR:%x\n",REG(CPM_INTCLR));
    /*enable interrupt*/
    REG(CPM_INTENA) |= (1<<5);
    //Dd_Uart3_Printf("CPM_INTENA:%x\n",REG(CPM_INTENA));
    REG(CPM_INTUNM) |= (1<<5);
    //Dd_Uart3_Printf("CPM_INTUNM:%x\n",REG(CPM_INTUNM));
    REG(REG_RTC_DETECT_CTRL)|= (1<<8)|u32Data;
}

void Dd_Rtc_Time(void)
{
    u32 year,month,day,hour,min,sec;
    u32 i;
    sec = READ_REG(REG_RTC_TIMING_R) & 0x3f;
    min = (READ_REG(REG_RTC_TIMING_R) & 0xfc0)>>6;
    hour = (READ_REG(REG_RTC_TIMING_R) & 0x1f000)>>12;
    day = (READ_REG(REG_RTC_TIMING_R) & 0xfffe0000)>>17;  
    year = day / 365 + 2020;
    for (i = 0; day > g_u8DayForMonth[i]; i ++) 
    {
        day -= g_u8DayForMonth[i];
    		
    }
    month = i+1;
    DD_DEBUG_PRINTF("Current time is %d/%02d/%02d   %02d:%02d:%02d\n",year,month,day,hour,min,sec);

}

void Dd_Rtc_InitTime(u32 year,u32 month,u32 day,u32 hour,u32 min,u32 sec)
{
    u32 DAY = 0;
    u32 i;

    /*添加润年处理*/   
    for(i = 2020; i<year ;i++)
    {
        if((i%4==0&&i%100!=0)||(i%400==0)) 
        {
            DAY++;                        
        }
    }
    for(i = 0;i<month-1;i++)
    {
        DAY += g_u8DayForMonth[i];  
    }
    DAY += (year - 2020) * 365 + day;
    /*使能RTC定时中断*/
    //Dd_Cpm2_IntInit();
    
    //DD_DEBUG_PRINTF("RTC start time is %d/%02d/%02d   %02d:%02d:%02d\n",year,month,day,hour,min,sec);
    /*初始化表时钟*/
    //Dd_Func_ReadCicle_Start();
    Dd_Rtc_InitTimeConfig(DAY,hour,min,sec);
    //Dd_Func_ReadCicle_End();       
}

void Dd_Rtc_RelativeToInitialTimeWakeUpTest(u32 year,u32 month,u32 day,u32 hour,u32 min,u32 sec)
{
    u32 DAY = 0;
    u32 i;

    /*添加润年处理*/   
    for(i = 2020; i<year ;i++)
    {
        if((i%4==0&&i%100!=0)||(i%400==0)) 
        {
            DAY++;            
        }
    }    
    
    for(i = 0;i<month-1;i++)
    {
        DAY += g_u8DayForMonth[i];  
    }
    DAY += (year - 2020) * 365 + day;
    //DD_DEBUG_PRINTF("Wake up time is %d/%02d/%02d   %02d:%02d:%02d\n",year,month,day,hour,min,sec);
    //Dd_Func_ReadCicle_Start();
    Dd_Rtc_RelativeToInitialTimeWakeUp(DAY,hour,min,sec); 
    //Dd_Func_ReadCicle_End();

    /*进入低功耗模式*/
    //Dd_Rtc_EnterLowPowerMode();    
}
void Dd_Rtc_LowPowerTest(u32 u32Data,u32 msTime)
{
    u32 DAY;
    u32 hour;
    u32 min;
    u32 sec;

    /*no sleep*/
    if((u32Data == 0) && (msTime == 0))
    {
        return ;
    }    
    
    REG(REG_PMU_CFG3) = 0x40400020;

    Dd_Rtc_ExternSignalWakeUp_Init();

    DAY = u32Data/(24*60*60);
    hour = (u32Data%(24*60*60))/(60*60);
    min = ((u32Data%(24*60*60))%(60*60))/60;
    sec = ((u32Data%(24*60*60))%(60*60))%60;
    /*ms clear*/
    REG(REG_RTC_WAKEUP_SU) = (REG(REG_RTC_WAKEUP_SU) & (0xFFFF0000));
    
    Dd_Rtc_InitTime(2020,4,23,11,40,0);

    Dd_Rtc_RelativeToInitialTimeWakeUpTest(2020,4,23+DAY,11+hour,40+min,sec);
    /*ms*/
    msTime = msTime*32768/1000;
    REG(REG_RTC_WAKEUP_SU) = (REG(REG_RTC_WAKEUP_SU) & (0xFFFF0000)) | (msTime);
    //    Dd_Rtc_AfterToInitialTimeWakeUp(DAY,hour,min,sec);

    Dd_Rtc_EnterLowPowerMode();
}


/******************************* 源文件结束 ***********************************/

