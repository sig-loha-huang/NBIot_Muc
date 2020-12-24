/*******************************************************************************
 * COPYRIGHT@SIGBEAN
 *******************************************************************************
 * �ļ�����:  
 * ��������: ����Ҫ�������ļ��Ĺ��ܡ����ݼ���Ҫģ�飩    
 * ʹ��˵��: ������ʹ���ļ�����ʱ����Լ������
 * �ļ�����:                
 * ��д����: 
 * �޸���ʷ: 
 *  
 * �޸������޸���  BugID/CRID      �޸�����
 * -----------------------------------------------------------------------------
 * 
 ******************************************************************************/
/******************************* �����ļ����� *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cortex_m4.h>
#include <core_cm3.h>

/******************************* �ֲ��궨�� ***********************************/

/******************************* �ֲ����������Ͷ��� ***************************/
u8 g_u8DayForMonth[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
u32 g_u32CpmValue = 0;
/******************************* �ֲ�����ԭ������ *****************************/

/******************************* ����ʵ�� *************************************/
/*******************************************************************************
* ��������: Dd_Rtc_InitTimeConfig
* ��������: Rtc��ʼ����ʱ��
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_InitTimeConfig(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;


    /* ���ü�s��Ԫ 32768 clk/s */
    WRITE_REG(REG_RTC_SEC_UNIT,0x8000); 

    /* ���ó�ʼ����ʱ�� */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    WRITE_REG(REG_RTC_TIMING,value);

    /* ʹ�ܲ����� */
    REG(REG_RTC_CTRL) |= 1;
}

/*******************************************************************************
* ��������: Dd_Rtc_RelativeToInitialTimeWakeUp 
* ��������: Rtc���㻽������ڳ�ʼʱ��
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_RelativeToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;

    /* ���ö��㻽�ѵ�ʱ�� */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    
    WRITE_REG(REG_RTC_WAKEUP_M,value); 

}
/*******************************************************************************
* ��������: Dd_Rtc_RelativeToInitialTimeWakeUp 
* ��������: 
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_AfterToInitialTimeWakeUp(u16 day,u8  hour,u8  min,u8  sec)
{
    u32 value = 0;

    /* ���ö��㻽�ѵ�ʱ�� */
    value = day<<17 | hour<<12 | min<<6 | sec<<0;
    
    WRITE_REG(REG_RTC_WAKEUP_D,value); 
}

/*******************************************************************************
* ��������:  Dd_Rtc_ExternSignalWakeUp(void)
* ��������: 
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_ExternSignalWakeUp_Init(void)
{
    u32 value = 0;

    /*Signal0 ȥ���˲����� Signal1ȥ���˲����� */
    u8 Order0 = 8;
    u8 Order1 = 8;
    /*pad0 ������ ���ѣ�pad1������ ����*/
    value = Order0 | (Order1 << 4) | (1<<8) | (1<<9) | (1<<11) | (1<<13);

    WRITE_REG(REG_RTC_PAD_MODE,value); 
    
}
/*******************************************************************************
* ��������:  Dd_Rtc_PadClrMeasure(u8 PadNum)
* ��������:  Pad��������
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
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
* ��������:  Dd_Rtc_EnterLowPowerMode
* ��������: 
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Rtc_EnterLowPowerMode(void)
{
    /*bit25 = 1*/
    //REG(REG_PMU_CFG2) = 0x3FC86864;

    //REG(REG_PMU_CFG3) &= ~(1<<25);
    //REG(REG_PMU_CFG3) |= (1<<30);


    /* ����reset��ʱ */
    REG(REG_RSTN_DLY) = 0x80;    

    
    /* ����1λreg�������߿��ٻ��� */
    REG(REG_RETENTION00) |= 1;

    /* ��������͹���ģʽ */
    REG(REG_RTC_CTRL) |= (1<<3);
}

/*******************************************************************************
* ��������:  Dd_Cpm2_IntInit
* ��������:  ʹ��rtc��ʱ�ж�
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
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
* ��������:  Dd_CPM2_Isr
* ��������:  �жϷ������
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��:
* �޸����ڰ汾���޸����޸�����
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
    /* rtc ��ʱ�ж�(�ǵ͹���ģʽ��) */
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

    /*������괦��*/   
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
    /*ʹ��RTC��ʱ�ж�*/
    //Dd_Cpm2_IntInit();
    
    //DD_DEBUG_PRINTF("RTC start time is %d/%02d/%02d   %02d:%02d:%02d\n",year,month,day,hour,min,sec);
    /*��ʼ����ʱ��*/
    //Dd_Func_ReadCicle_Start();
    Dd_Rtc_InitTimeConfig(DAY,hour,min,sec);
    //Dd_Func_ReadCicle_End();       
}

void Dd_Rtc_RelativeToInitialTimeWakeUpTest(u32 year,u32 month,u32 day,u32 hour,u32 min,u32 sec)
{
    u32 DAY = 0;
    u32 i;

    /*������괦��*/   
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

    /*����͹���ģʽ*/
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


/******************************* Դ�ļ����� ***********************************/

