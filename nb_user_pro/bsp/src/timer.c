/*******************************************************************************
* COPYRIGHT@SIGBEN
*******************************************************************************
* 文件名称:  timer.c
* 功能描述: 
* 使用说明:
* 文件作者:                
* 编写日期: 
* 修改历史: 
* 修改日期修改人  BugID/CRID      修改内容
* -----------------------------------------------------------------------------
* 
******************************************************************************/
/******************************* 包含文件声明 *********************************/
#include <cortex_m4.h>
/******************************* 局部宏定义 ***********************************/
#define CONFIG_MAX_PERIOD	(10 * 1000 * 1000)	/* 10 seconds default */


/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/
void Dd_Timer_Init(int TimerNum, int TimerPrdMs)
{
    int TimerPrd ;

    TimerPrd = (ARM_CLK /1000) * TimerPrdMs;

    TIMER_DISABLE(TimerNum)  ;
    TIMER_MODELOAD(TimerNum) ;
    TIMER_LOADCNT(TimerNum, TimerPrd) ;
}

unsigned char Dd_Timer4_Init(void)
{
    unsigned int u32ReadNull;

    TIMER_DISABLE(TIMER_NUM_4)  ;
    TIMER_MODELOAD(TIMER_NUM_4) ;
    TIMER_LOADCNT(TIMER_NUM_4, 0xFFFFFFFF) ;

    u32ReadNull=TIMER_INTCLR(TIMER_NUM_4)    ;
    TIMER_INTMASK(TIMER_NUM_4)   ;
    TIMER_ENABLE(TIMER_NUM_4)    ;
    return u32ReadNull;
}

unsigned char Dd_Timer_Start(int TimerNum,int InterruptFlag) 
{
    unsigned int u32ReadNull;

    u32ReadNull = TIMER_INTCLR(TimerNum)    ;
    
    if(TIMER_INTERRUPT_ENABLE == InterruptFlag)
    {    
        TIMER_INTUNMASK(TimerNum) ;
    }
    else
    {
        TIMER_INTMASK(TimerNum)   ;
    }
    
    TIMER_ENABLE(TimerNum)    ;
    
    return u32ReadNull;
}
unsigned char Dd_Timer_Stop(int TimerNum)  
{
    unsigned int u32ReadNull;

    TIMER_DISABLE(TimerNum)  ;
    u32ReadNull=TIMER_INTCLR(TimerNum)   ;
    return u32ReadNull;
}

void udelay(unsigned long usec)
{
    u32 TimerVal = 0;
    u32 TmpVal = 0;
    u32 TmpVal1 = 0;

    Dd_Timer4_Init();

    TimerVal = Dd_Timer_ReadCounter(TIMER_NUM_4);
    TmpVal = (usec/10) * (CLK_19P2M/100000);
    
    /*定时器的结束时间*/
    TmpVal1 = TimerVal + TmpVal;

    while(1)
    {
        TimerVal = Dd_Timer_ReadCounter(TIMER_NUM_4);
        if(TmpVal1 < TimerVal)
        {
            break;
        }    
    }
}

void Dd_Timer1_isr(void)
{
    unsigned int IntFlag = 0;
    /* read int flag */
    IntFlag = READ_REG(REG_TIMERB_INT_FLG);
    
    if((IntFlag & (0x01)) == (0x01)) /*timer 8*/
    {
        TIMER_INTCLR(TIMER_NUM_8);
    }   
    if((IntFlag & (0x02)) == (0x02)) /*timer 9*/
    {
        TIMER_INTCLR(TIMER_NUM_9);
    }    
    if((IntFlag & (0x04)) == (0x04)) /*timer 10*/
    {
        TIMER_INTCLR(TIMER_NUM_10);
    }   
    if((IntFlag & (0x08)) == (0x08)) /*timer 11*/
    {
        TIMER_INTCLR(TIMER_NUM_11);
    }    
    if((IntFlag & (0x10)) == (0x10)) /*timer 12*/
    {
        TIMER_INTCLR(TIMER_NUM_12);
    }   
    if((IntFlag & (0x20)) == (0x20)) /*timer 13*/
    {
        TIMER_INTCLR(TIMER_NUM_13);
    }    
    if((IntFlag & (0x40)) == (0x40)) /*timer 14*/
    {
        TIMER_INTCLR(TIMER_NUM_14);
    }   
    if((IntFlag & (0x80)) == (0x80)) /*timer 15*/
    {
        TIMER_INTCLR(TIMER_NUM_15);
    }
}    

unsigned int Dd_Timer_ReadCounter(unsigned char TimerNum)
{
    return (~TIMER_CURVALUE(TimerNum));
}    

void Dd_Wdt_IntISR(void)
{
    /*retart*/
    //WRITE_REG(WDT0_CRR, 0x76);
    DD_DEBUG_PUTS("WDT TimerOut Reboot !\r\n");

    Dd_DoReset();
}    
void WatchDogInit(int TimerPeri)
{
    /* WatchDog clock = 80Mhz*/
    /*Time out of WDT_USER_TOP_INIT_0 or 1M Clocks*/
    WRITE_REG(WDT0_TORR, TimerPeri);

    /* 256  pclk cycles  Response mode: Generate a system reset .Watchdog timer enable */
    WRITE_REG(WDT0_CR, 0x0f);
    
    /* Watchdog timer restart command */
    WRITE_REG(WDT0_CRR, 0x76);
}
void Feed_dog(void)
{
    /* Watchdog timer restart command */
    WRITE_REG(WDT0_CRR, 0x76);
} 


void WatchDog1Init(int TimerPeri1)
{
    /* WatchDog clock = 80Mhz*/
    /*Time out of WDT_USER_TOP_INIT_0 or 1M Clocks*/
    WRITE_REG(WDT1_TORR, TimerPeri1);
    /* 256  pclk cycles  Response mode: Generate a system reset .Watchdog timer enable */
    WRITE_REG(WDT1_CR, 0x0f);
    
    /* Watchdog timer restart command */
    WRITE_REG(WDT1_CRR, 0x76);
}

void Dd_Wdt1_IntISR(void)
{       
    /*retart*/
    WRITE_REG(WDT1_CRR, 0x76);
}   

void Dd_Timer_PwmN_Config(u32 PwmNum,u32 HPeri,u32 LPeri)
{
    u8 TimerNum = 0;        /*Timer Number*/
    if(0 == PwmNum)
    {
        TimerNum = 0;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA0_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 38.4M clock period*/
        REG(REG_TIMERA0_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 38.4M clock period*/
        REG(REG_TIMERA0_LOAD1) = HPeri;
    }   
    else if(1 == PwmNum)
    {
        TimerNum = 1;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA1_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 38.4M clock period*/
        REG(REG_TIMERA1_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 38.4M clock period*/
        REG(REG_TIMERA1_LOAD1) = HPeri;
    }  
    else if(2 == PwmNum)
    {
        TimerNum = 4;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA4_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 19.2M clock period*/
        REG(REG_TIMERA4_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 19.2M clock period*/
        REG(REG_TIMERA4_LOAD1) = HPeri;
    }    
    else if(3 == PwmNum)
    {
        TimerNum = 5;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA5_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 19.2M clock period*/
        REG(REG_TIMERA5_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 19.2M clock period*/
        REG(REG_TIMERA5_LOAD1) = HPeri;
    }  
    else if(4 == PwmNum)
    {
        TimerNum = 8;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERB0_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 38.4M clock period*/
        REG(REG_TIMERB0_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 38.4M clock period*/
        REG(REG_TIMERB0_LOAD1) = HPeri;     
    } 
    else if(5 == PwmNum)
    {
        TimerNum = 9;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERB1_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 38.4M clock period*/
        REG(REG_TIMERB1_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 38.4M clock period*/
        REG(REG_TIMERB1_LOAD1) = HPeri;     
    }     
    else if(6 == PwmNum)
    {
        TimerNum = 12;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA4_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 9.6M clock period*/
        REG(REG_TIMERA4_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 9.6M clock period*/
        REG(REG_TIMERA4_LOAD1) = HPeri;
        
    }   
    else if(7 == PwmNum)
    {
        TimerNum = 13;
        /*disable timer*/
        TIMER_DISABLE(TimerNum);

        /*enable pwm mode  user mode*/
        REG(REG_TIMERA4_CTRL) |= (1<<4) |(1<<3) | (1<<1);
        /* LOW period =  TimerNLoadCount * 9.6M clock period*/
        REG(REG_TIMERA4_LOAD) = LPeri;
        /* HIGH period =  TimerNLoadCount1 * 9.6M clock period*/
        REG(REG_TIMERA4_LOAD1) = HPeri;
    } 

    /*disable interrupt*/
    TIMER_INTMASK(TimerNum)   ;

    /*enable timer pwm mode*/
    TIMER_ENABLE(TimerNum)    ;   
    
}    


/******************************* 源文件结束 ***********************************/
    
