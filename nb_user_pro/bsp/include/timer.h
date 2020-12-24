/*******************************************************************************
* COPYRIGHT@ SIGBEN
********************************************************************************
* 文件名称: timer.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef TIMER_H
#define TIMER_H

/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/
#define         REG_TIMER_GRP_OS                (TIMERB_BASE_ADDR - TIMERA_BASE_ADDR)
#define         REG_TIMER_OS                    (TIMERA1_BASE_ADDR - TIMERA0_BASE_ADDR)

#define 		TIMER_BASE_ADDR                 (0x40040000)                    /*移植需要修改的BASE地址 */
        		
#define 		TIMERA_BASE_ADDR                (TIMER_BASE_ADDR + 0x0000)
#define 		TIMERA0_BASE_ADDR               (TIMERA_BASE_ADDR + 0x0000)
#define 		TIMERA1_BASE_ADDR               (TIMERA0_BASE_ADDR + 0x0014)
#define 		TIMERA2_BASE_ADDR               (TIMERA1_BASE_ADDR + 0x0014)
#define 		TIMERA3_BASE_ADDR               (TIMERA2_BASE_ADDR + 0x0014)
#define 		TIMERA4_BASE_ADDR               (TIMERA3_BASE_ADDR + 0x0014)
#define 		TIMERA5_BASE_ADDR               (TIMERA4_BASE_ADDR + 0x0014)
#define 		TIMERA6_BASE_ADDR               (TIMERA5_BASE_ADDR + 0x0014)
#define 		TIMERA7_BASE_ADDR               (TIMERA6_BASE_ADDR + 0x0014)
        		
#define 		TIMERB_BASE_ADDR                (TIMER_BASE_ADDR + 0x1000)       /*移植需要修改的BASE地址 */
#define 		TIMERB0_BASE_ADDR               (TIMERB_BASE_ADDR + 0x0000)
#define 		TIMERB1_BASE_ADDR               (TIMERB0_BASE_ADDR + 0x0014)
#define 		TIMERB2_BASE_ADDR               (TIMERB1_BASE_ADDR + 0x0014)
#define 		TIMERB3_BASE_ADDR               (TIMERB2_BASE_ADDR + 0x0014)
#define 		TIMERB4_BASE_ADDR               (TIMERB3_BASE_ADDR + 0x0014)
#define 		TIMERB5_BASE_ADDR               (TIMERB4_BASE_ADDR + 0x0014)
#define 		TIMERB6_BASE_ADDR               (TIMERB5_BASE_ADDR + 0x0014)
#define 		TIMERB7_BASE_ADDR               (TIMERB6_BASE_ADDR + 0x0014)
        		
#define 		REG_TIMERA0_LOAD                 (TIMERA0_BASE_ADDR + 0x000)
#define 		REG_TIMERA0_CUR                  (TIMERA0_BASE_ADDR + 0x004)
#define 		REG_TIMERA0_CTRL                 (TIMERA0_BASE_ADDR + 0x008)
#define 		REG_TIMERA0_INT_RDCLR            (TIMERA0_BASE_ADDR + 0x00c)
#define 		REG_TIMERA0_INT_FLG              (TIMERA0_BASE_ADDR + 0x010)
#define 		REG_TIMERA1_LOAD                 (TIMERA1_BASE_ADDR + 0x000)
#define 		REG_TIMERA1_CUR                  (TIMERA1_BASE_ADDR + 0x004)
#define 		REG_TIMERA1_CTRL                 (TIMERA1_BASE_ADDR + 0x008)
#define 		REG_TIMERA1_INT_RDCLR            (TIMERA1_BASE_ADDR + 0x00c)
#define 		REG_TIMERA1_INT_FLG              (TIMERA1_BASE_ADDR + 0x010)
#define 		REG_TIMERA2_LOAD                 (TIMERA2_BASE_ADDR + 0x000)
#define 		REG_TIMERA2_CUR                  (TIMERA2_BASE_ADDR + 0x004)
#define 		REG_TIMERA2_CTRL                 (TIMERA2_BASE_ADDR + 0x008)
#define 		REG_TIMERA2_INT_RDCLR            (TIMERA2_BASE_ADDR + 0x00c)
#define 		REG_TIMERA2_INT_FLG              (TIMERA2_BASE_ADDR + 0x010)
#define 		REG_TIMERA3_LOAD                 (TIMERA3_BASE_ADDR + 0x000)
#define 		REG_TIMERA3_CUR                  (TIMERA3_BASE_ADDR + 0x004)
#define 		REG_TIMERA3_CTRL                 (TIMERA3_BASE_ADDR + 0x008)
#define 		REG_TIMERA3_INT_RDCLR            (TIMERA3_BASE_ADDR + 0x00c)
#define 		REG_TIMERA3_INT_FLG              (TIMERA3_BASE_ADDR + 0x010)
#define 		REG_TIMERA4_LOAD                 (TIMERA4_BASE_ADDR + 0x000)
#define 		REG_TIMERA4_CUR                  (TIMERA4_BASE_ADDR + 0x004)
#define 		REG_TIMERA4_CTRL                 (TIMERA4_BASE_ADDR + 0x008)
#define 		REG_TIMERA4_INT_RDCLR            (TIMERA4_BASE_ADDR + 0x00c)
#define 		REG_TIMERA4_INT_FLG              (TIMERA4_BASE_ADDR + 0x010)
#define 		REG_TIMERA5_LOAD                 (TIMERA5_BASE_ADDR + 0x000)
#define 		REG_TIMERA5_CUR                  (TIMERA5_BASE_ADDR + 0x004)
#define 		REG_TIMERA5_CTRL                 (TIMERA5_BASE_ADDR + 0x008)
#define 		REG_TIMERA5_INT_RDCLR            (TIMERA5_BASE_ADDR + 0x00c)
#define 		REG_TIMERA5_INT_FLG              (TIMERA5_BASE_ADDR + 0x010)
#define 		REG_TIMERA6_LOAD                 (TIMERA6_BASE_ADDR + 0x000)
#define 		REG_TIMERA6_CUR                  (TIMERA6_BASE_ADDR + 0x004)
#define 		REG_TIMERA6_CTRL                 (TIMERA6_BASE_ADDR + 0x008)
#define 		REG_TIMERA6_INT_RDCLR            (TIMERA6_BASE_ADDR + 0x00c)
#define 		REG_TIMERA6_INT_FLG              (TIMERA6_BASE_ADDR + 0x010)
#define 		REG_TIMERA7_LOAD                 (TIMERA7_BASE_ADDR + 0x000)
#define 		REG_TIMERA7_CUR                  (TIMERA7_BASE_ADDR + 0x004)
#define 		REG_TIMERA7_CTRL                 (TIMERA7_BASE_ADDR + 0x008)
#define 		REG_TIMERA7_INT_RDCLR            (TIMERA7_BASE_ADDR + 0x00c)
#define 		REG_TIMERA7_INT_FLG              (TIMERA7_BASE_ADDR + 0x010)
#define 		REG_TIMERA_INT_FLG               (TIMERA_BASE_ADDR + 0x0a0)
#define 		REG_TIMERA_INT_RDCLR             (TIMERA_BASE_ADDR + 0x0a4)
#define 		REG_TIMERA_INT_PREMSK            (TIMERA_BASE_ADDR + 0x0a8)
#define 		REG_TIMERA_VERSION               (TIMERA_BASE_ADDR + 0x0ac)

#define 		REG_TIMERA0_LOAD1                (TIMERA0_BASE_ADDR + 0x0b0)
#define 		REG_TIMERA1_LOAD1                (TIMERA0_BASE_ADDR + 0x0b4)
#define 		REG_TIMERA2_LOAD1                (TIMERA0_BASE_ADDR + 0x0b8)
#define 		REG_TIMERA3_LOAD1                (TIMERA0_BASE_ADDR + 0x0bC)
#define 		REG_TIMERA4_LOAD1                (TIMERA0_BASE_ADDR + 0x0C0)
#define 		REG_TIMERA5_LOAD1                (TIMERA0_BASE_ADDR + 0x0C4)
#define 		REG_TIMERA6_LOAD1                (TIMERA0_BASE_ADDR + 0x0C8)
#define 		REG_TIMERA7_LOAD1                (TIMERA0_BASE_ADDR + 0x0CC)

        		
#define 		REG_TIMERB0_LOAD                 (TIMERB0_BASE_ADDR + 0x000)
#define 		REG_TIMERB0_CUR                  (TIMERB0_BASE_ADDR + 0x004)
#define 		REG_TIMERB0_CTRL                 (TIMERB0_BASE_ADDR + 0x008)
#define 		REG_TIMERB0_INT_RDCLR            (TIMERB0_BASE_ADDR + 0x00c)
#define 		REG_TIMERB0_INT_FLG              (TIMERB0_BASE_ADDR + 0x010)
#define 		REG_TIMERB1_LOAD                 (TIMERB1_BASE_ADDR + 0x000)
#define 		REG_TIMERB1_CUR                  (TIMERB1_BASE_ADDR + 0x004)
#define 		REG_TIMERB1_CTRL                 (TIMERB1_BASE_ADDR + 0x008)
#define 		REG_TIMERB1_INT_RDCLR            (TIMERB1_BASE_ADDR + 0x00c)
#define 		REG_TIMERB1_INT_FLG              (TIMERB1_BASE_ADDR + 0x010)
#define 		REG_TIMERB2_LOAD                 (TIMERB2_BASE_ADDR + 0x000)
#define 		REG_TIMERB2_CUR                  (TIMERB2_BASE_ADDR + 0x004)
#define 		REG_TIMERB2_CTRL                 (TIMERB2_BASE_ADDR + 0x008)
#define 		REG_TIMERB2_INT_RDCLR            (TIMERB2_BASE_ADDR + 0x00c)
#define 		REG_TIMERB2_INT_FLG              (TIMERB2_BASE_ADDR + 0x010)
#define 		REG_TIMERB3_LOAD                 (TIMERB3_BASE_ADDR + 0x000)
#define 		REG_TIMERB3_CUR                  (TIMERB3_BASE_ADDR + 0x004)
#define 		REG_TIMERB3_CTRL                 (TIMERB3_BASE_ADDR + 0x008)
#define 		REG_TIMERB3_INT_RDCLR            (TIMERB3_BASE_ADDR + 0x00c)
#define 		REG_TIMERB3_INT_FLG              (TIMERB3_BASE_ADDR + 0x010)
#define 		REG_TIMERB4_LOAD                 (TIMERB4_BASE_ADDR + 0x000)
#define 		REG_TIMERB4_CUR                  (TIMERB4_BASE_ADDR + 0x004)
#define 		REG_TIMERB4_CTRL                 (TIMERB4_BASE_ADDR + 0x008)
#define 		REG_TIMERB4_INT_RDCLR            (TIMERB4_BASE_ADDR + 0x00c)
#define 		REG_TIMERB4_INT_FLG              (TIMERB4_BASE_ADDR + 0x010)
#define 		REG_TIMERB5_LOAD                 (TIMERB5_BASE_ADDR + 0x000)
#define 		REG_TIMERB5_CUR                  (TIMERB5_BASE_ADDR + 0x004)
#define 		REG_TIMERB5_CTRL                 (TIMERB5_BASE_ADDR + 0x008)
#define 		REG_TIMERB5_INT_RDCLR            (TIMERB5_BASE_ADDR + 0x00c)
#define 		REG_TIMERB5_INT_FLG              (TIMERB5_BASE_ADDR + 0x010)
#define 		REG_TIMERB6_LOAD                 (TIMERB6_BASE_ADDR + 0x000)
#define 		REG_TIMERB6_CUR                  (TIMERB6_BASE_ADDR + 0x004)
#define 		REG_TIMERB6_CTRL                 (TIMERB6_BASE_ADDR + 0x008)
#define 		REG_TIMERB6_INT_RDCLR            (TIMERB6_BASE_ADDR + 0x00c)
#define 		REG_TIMERB6_INT_FLG              (TIMERB6_BASE_ADDR + 0x010)
#define 		REG_TIMERB7_LOAD                 (TIMERB7_BASE_ADDR + 0x000)
#define 		REG_TIMERB7_CUR                  (TIMERB7_BASE_ADDR + 0x004)
#define 		REG_TIMERB7_CTRL                 (TIMERB7_BASE_ADDR + 0x008)
#define 		REG_TIMERB7_INT_RDCLR            (TIMERB7_BASE_ADDR + 0x00c)
#define 		REG_TIMERB7_INT_FLG              (TIMERB7_BASE_ADDR + 0x010)
#define 		REG_TIMERB_INT_FLG               (TIMERB_BASE_ADDR + 0x0a0)
#define 		REG_TIMERB_INT_RDCLR             (TIMERB_BASE_ADDR + 0x0a4)
#define 		REG_TIMERB_INT_PREMSK            (TIMERB_BASE_ADDR + 0x0a8)
#define 		REG_TIMERB_VERSION               (TIMERB_BASE_ADDR + 0x0ac)

#define 		REG_TIMERB0_LOAD1                (TIMERB0_BASE_ADDR + 0x0b0) 
#define 		REG_TIMERB1_LOAD1                (TIMERB0_BASE_ADDR + 0x0b4) 
#define 		REG_TIMERB2_LOAD1                (TIMERB0_BASE_ADDR + 0x0b8) 
#define 		REG_TIMERB3_LOAD1                (TIMERB0_BASE_ADDR + 0x0bC) 
#define 		REG_TIMERB4_LOAD1                (TIMERB0_BASE_ADDR + 0x0C0) 
#define 		REG_TIMERB5_LOAD1                (TIMERB0_BASE_ADDR + 0x0C4) 
#define 		REG_TIMERB6_LOAD1                (TIMERB0_BASE_ADDR + 0x0C8) 
#define 		REG_TIMERB7_LOAD1                (TIMERB0_BASE_ADDR + 0x0CC) 


#define         TIMER_NUM_0          0
#define         TIMER_NUM_1          1
#define         TIMER_NUM_2          2
#define         TIMER_NUM_3          3
#define         TIMER_NUM_4          4
#define         TIMER_NUM_5          5
#define         TIMER_NUM_6          6
#define         TIMER_NUM_7          7
#define         TIMER_NUM_8          8
#define         TIMER_NUM_9          9
#define         TIMER_NUM_10         10
#define         TIMER_NUM_11         11
#define         TIMER_NUM_12         12
#define         TIMER_NUM_13         13
#define         TIMER_NUM_14         14
#define         TIMER_NUM_15         15


#define         TIMER_INTERRUPT_ENABLE     1
#define         TIMER_INTERRUPT_DISABLE    0
/*-------------------------------------------------------------------------------
*                       Timer Ctrl Operation Mode                              *
-------------------------------------------------------------------------------*/
#define TIMER_MODEFREE(n)      WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) & 0xfffffffd))

#define TIMER_MODELOAD(n)      WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) | 0x00000002))

/*-------------------------------------------------------------------------------
*                        Timer Load Counter                                    *
-------------------------------------------------------------------------------*/
#define TIMER_LOADCNT(n,timer_ldcnt) WRITE_REG((REG_TIMERA0_LOAD + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                                     timer_ldcnt)
#define TIMER_LOADCNT1(n,timer_ldcnt) WRITE_REG((REG_TIMERA0_LOAD1 + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * 0x04), \
                                     timer_ldcnt)
/*-------------------------------------------------------------------------------
*                        Timer Enable                                          *
-------------------------------------------------------------------------------*/
#define TIMER_ENABLE(n)        WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS),\
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) | 0x00000001))

#define TIMER_DISABLE(n)       WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) & 0xfffffffe))

/*-------------------------------------------------------------------------------
                         Timer Current Counter 
--------------------------------------------------------------------------------*/
#define TIMER_CURVALUE(n)      READ_REG(REG_TIMERA0_CUR + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS)

/*-------------------------------------------------------------------------------
*                         Timer Interrupt Mask                                  *
-------------------------------------------------------------------------------*/
#define TIMER_INTMASK(n)       WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) | 0x00000004))

#define TIMER_INTUNMASK(n)     WRITE_REG((REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS), \
                               (READ_REG(REG_TIMERA0_CTRL + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS) & 0xfffffffb))

/*-------------------------------------------------------------------------------
*                        Timer Interrupt Clear                                  *
-------------------------------------------------------------------------------*/
#define TIMER_INTCLR(n)        READ_REG(REG_TIMERA0_INT_RDCLR + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS)

/*-------------------------------------------------------------------------------
                         Timer Grp Interrupt Clear 
-------------------------------------------------------------------------------*/
#define TIMER_GRP_INTCLR(n)    READ_REG(REG_TIMERA_INT_RDCLR + n * REG_TIMER_GRP_OS)

/*-------------------------------------------------------------------------------
                         Timer Interrupt Flag 
-------------------------------------------------------------------------------*/
#define TIMER_INTFLG(n)        READ_REG(REG_TIMERA0_INT_FLG + (n>>3) * REG_TIMER_GRP_OS + (n&0x00000007) * REG_TIMER_OS)

/*-------------------------------------------------------------------------------
                         Timer Grp Interrupt Flag 
-------------------------------------------------------------------------------*/
#define TIMER_GRP_INTFLG(n)    READ_REG(REG_TIMERA_INT_FLG + n * REG_TIMER_GRP_OS)
 
/**************************WATCH DOG TIMER ************************************/
#define   WATCH_PERI_64K_CLOCKS         0x0 
#define   WATCH_PERI_128K_CLOCKS        0x11 
#define   WATCH_PERI_256K_CLOCKS        0x22 
#define   WATCH_PERI_512K_CLOCKS        0x33 
#define   WATCH_PERI_1M_CLOCKS          0x44 
#define   WATCH_PERI_2M_CLOCKS          0x55 
#define   WATCH_PERI_4M_CLOCKS          0x66 
#define   WATCH_PERI_8M_CLOCKS          0x77 
#define   WATCH_PERI_16M_CLOCKS         0x88 
#define   WATCH_PERI_32M_CLOCKS         0x99 
#define   WATCH_PERI_64M_CLOCKS         0xaa 
#define   WATCH_PERI_128M_CLOCKS        0xbb 
#define   WATCH_PERI_256M_CLOCKS        0xcc 
#define   WATCH_PERI_512M_CLOCKS        0xdd 
#define   WATCH_PERI_1G_CLOCKS          0xee 
#define   WATCH_PERI_2G_CLOCKS          0xff 

/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern void Dd_Timer_Init(int TimerNum, int TimerPrdMs);
extern unsigned char Dd_Timer15_Init(void);
extern unsigned char Dd_Timer_Start(int TimerNum,int InterruptFlag) ;
extern unsigned char Dd_Timer_Stop(int TimerNum);
extern unsigned int Dd_Timer_ReadCounter(unsigned char TimerNum);
extern void udelay(unsigned long usec);
extern void Dd_Timer1_isr(void);
extern void WatchDogInit(int TimerPeri);
extern void WatchDog1Init(int TimerPeri1);
extern void Dd_Wdt1_IntISR(void);
extern void Dd_Timer_PwmN_Config(u32 PwmNum,u32 HPeri,u32 LPeri);

/******************************* for test ***********************************/
extern void Dd_Pwm_GpioB12_Test(u32 pllset);
/******************************** 头文件保护结尾 ******************************/
#endif /*TIMER_H*/
/******************************** 头文件结束 **********************************/
