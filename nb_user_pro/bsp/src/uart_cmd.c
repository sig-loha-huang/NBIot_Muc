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
#include <cortex_m4.h>
#include <core_cm3.h>
#include <stdio.h>
#include <rf_test.h>
/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/
u32 g_u32TimerCicle = 0;        /*记录cicle时间*/

NB_FAST_CODE void Dd_Func_ReadCicle_Start(void)
{
    g_u32TimerCicle = Dd_Timer_ReadCounter(TIMER_NUM_8);
}
NB_FAST_CODE void Dd_Func_ReadCicle_End(void)
{
    g_u32TimerCicle = Dd_Timer_ReadCounter(TIMER_NUM_8) - g_u32TimerCicle;
    DD_DEBUG_PRINTF("Cicle %x\r\n",g_u32TimerCicle);
}
u32 g_u32PllFlag = 0;
extern u32 g_u32CpmValue;
unsigned char Dd_CmdMemSet(unsigned char *pData,unsigned int u32Data)
{
    u32 Counti =0;
    u32 u32CmdTimerCount = 0;    

    int cfoComp = 15000;
    int amp = 512;

    u16 regid,regdata;
    u16 readval;
    if(pData == NULL)
    {    return 0;  }

    /***************************************************************************
     *****************             外设测试用例                ***************** 
     **************************************************************************/    
    if((u32)pData == 0x80000001) /*NVIC 部分*/
    {
        Dd_Func_ReadCicle_Start();
        NVIC_EnableIRQ(u32Data);    
        Dd_Func_ReadCicle_End(); 
    }    
    else if((u32)pData == 0x80000002)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_DisableIRQ(u32Data);    
        Dd_Func_ReadCicle_End();     
    }
    else if((u32)pData == 0x80000003)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_SetPriorityGrouping(u32Data);
        Dd_Func_ReadCicle_End();     
    }    
    else if((u32)pData == 0x80000004)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_PriorityGroupConfig(u32Data);
        Dd_Func_ReadCicle_End();         
    }
    else if((u32)pData == 0x80000005) 
    { 
        Dd_Func_ReadCicle_Start();
        NVIC_GetPriorityGrouping();
        Dd_Func_ReadCicle_End();         
    }
    else if((u32)pData == 0x80000006) 
    {
        Dd_Func_ReadCicle_Start();
        NVIC_GetPendingIRQ(u32Data);
        Dd_Func_ReadCicle_End();
    } 
    else if((u32)pData == 0x80000007)        
    {
        Dd_Func_ReadCicle_Start();
        NVIC_SetPendingIRQ(u32Data);   
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000008)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_ClearPendingIRQ(u32Data);
        Dd_Func_ReadCicle_End();
    }   
    else if((u32)pData == 0x80000009)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_GetActive(u32Data);    
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x8000000a)   
    {
        Dd_Func_ReadCicle_Start();
        NVIC_SetPriority((u32Data & 0x0000FFFF),((u32Data & 0xFFFF0000)>>16));    
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x8000000b)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_GetPriority(u32Data);
        Dd_Func_ReadCicle_End();
    }    
    else if((u32)pData == 0x8000000c)
    {
        Dd_Func_ReadCicle_Start();
        NVIC_EncodePriority(0,1,1);
        Dd_Func_ReadCicle_End();
    }    
    else if((u32)pData == 0x8000000d)  
    {
        Dd_Func_ReadCicle_Start();
        u32 pPreemptPriority, pSubPriority;      
        NVIC_DecodePriority(0,1,(void *)(&pPreemptPriority),(void *)(&pSubPriority));
        Dd_Func_ReadCicle_End();
    } 
    else if((u32)pData == 0x8000000E)
    {
    }     
    else if((u32)pData == 0x8000000F)
    {
    }  
    else if((u32)pData == 0x80000010) /*GPIO 部分*/
    {
        Dd_Func_ReadCicle_Start();
        Dd_SetIOBFunction0(u32Data);        
        Dd_Func_ReadCicle_End();
    }  
    else if((u32)pData == 0x80000011)
    {
        Dd_Func_ReadCicle_Start();
        Dd_SetIOBFunction1(u32Data);      
        Dd_Func_ReadCicle_End();
    }    
    else if((u32)pData == 0x80000012)
    {
        Dd_Func_ReadCicle_Start();
        Dd_SetIOBFunction2(u32Data);   
        Dd_Func_ReadCicle_End();
    }    
    else if((u32)pData == 0x80000013)
    {
        Dd_Func_ReadCicle_Start();
        Dd_SetIOBFunction3(u32Data);   
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000014)
    {
        Dd_Func_ReadCicle_Start();
        Dd_GpioB_SetDir((u32Data&0x0000FFFF),((u32Data&0xFFFF0000)>>16));
        Dd_Func_ReadCicle_End(); 
    }    
    else if((u32)pData == 0x80000015)
    {
        Dd_Func_ReadCicle_Start();
        Dd_GpioB_SetOut((u32Data&0x0000FFFF),((u32Data&0xFFFF0000)>>16));
        Dd_Func_ReadCicle_End(); 
    }    
    else if((u32)pData == 0x80000016)
    {
        Dd_Func_ReadCicle_Start();
        u32Data = Dd_GpioB_ReadData();
        Dd_Func_ReadCicle_End();   
        DD_DEBUG_PRINTF("GPIOB Data %x\r\n",u32Data);
    }   
    else if((u32)pData == 0x80000017)
    {
        Dd_Func_ReadCicle_Start();
        Dd_GpioB_SetInterFun((u32Data&0x00ff),((u32Data&0xff00)>>8),(u32Data&0xffff0000)>>16);
        Dd_Func_ReadCicle_End();   
        DD_DEBUG_PRINTF("GPIOB Data %x\r\n",u32Data);    
    }    
    else if((u32)pData == 0x80000018)
    {
        Dd_SetIOAFunction0(14);
        REG(REG_GPIO_SWPORTA_DDR) &=  (~(0x1 << 14));
    }
    else if((u32)pData == 0x80000019)
    {
        printf("GPIOA Data %x\r\n",REG(REG_GPIO_SWPORTA_EXT_PORTA));    
    }  
    else if((u32)pData == 0x8000001a)
    {
                
    }  
    else if((u32)pData == 0x8000001b)
    {
                    
    }
    else if((u32)pData == 0x8000001c)
    {
        
    }
    else if((u32)pData == 0x8000001d)
    {
            
    }   
    else if((u32)pData == 0x8000001e)
    {
          
    }   
    else if((u32)pData == 0x8000001f)
    {
                    
    }
    else if((u32)pData == 0x80000020) //RTC部分
    {
        //Dd_Func_ReadCicle_Start();
        /*Rtc Detect*/
        u32 rtc_clock = 0;
        g_u32CpmValue = 0;
        Dd_Rtc_Detect(u32Data);
        while(g_u32CpmValue==0);
        rtc_clock = 134400000/((float)g_u32CpmValue/(u32Data*2));
        DD_DEBUG_PRINTF("RTC_CLOCK:%d Hz\r\n",rtc_clock);
        //Dd_Func_ReadCicle_End(); 
    } 
    else if((u32)pData == 0x80000021)
    {
        //Dd_Func_ReadCicle_Start();
        /*Get Current Rtc Time*/
        Dd_Rtc_Time();
        //Dd_Func_ReadCicle_End();
    }    
    else if((u32)pData == 0x80000022)
    {
        //Dd_Func_ReadCicle_Start();
        /*PAD唤醒模式*/
        Dd_Rtc_ExternSignalWakeUp_Init();
        //Dd_Func_ReadCicle_End();
    }   
    else if((u32)pData == 0x80000023)
    {
        //Dd_Func_ReadCicle_Start();
        /*Pad计量清零*/
        Dd_Rtc_PadClrMeasure(u32Data);
        //Dd_Func_ReadCicle_End();        
        
    }            
    else if((u32)pData == 0x80000024)
    {
        //Dd_Func_ReadCicle_Start();
        /*进入低功耗模式*/
        Dd_Rtc_EnterLowPowerMode();
        //Dd_Func_ReadCicle_End();
    }      
    else if((u32)pData == 0x80000025)
    {
        
    }
    else if((u32)pData == 0x80000026)
    {
        Dd_Mipi_LowPowerMode();
        Dd_Rtc_LowPowerTest(u32Data,0);   

    }   
    else if((u32)pData == 0x80000027)
    {
        
    }
    else if((u32)pData == 0x80000028)
    {
        
    }
    else if((u32)pData == 0x80000029)
    {
        
    }
    else if((u32)pData == 0x8000002a)
    {
        Dd_Adc_Test();
    }
    else if((u32)pData == 0x8000002b)
    {
    }
    else if((u32)pData == 0x8000002c)
    {
    }
    else if((u32)pData == 0x8000002d)
    {
    }
    else if((u32)pData == 0x8000002e)
    {
        
    }    
    else if((u32)pData == 0x8000002f) /*低功耗后恢复NB*/
    {
        if(1 == u32Data)
        {
            if(1 == g_u32PllFlag)
            {
                REG(REG_BOOT_MODE) = 0x01;
                REG(REG_CLK_GATE) =  REG(REG_CLK_GATE) | 0x01 ;
                REG(REG_RSTN_SOFT) = REG(REG_CLK_GATE) | 0x01;
                g_u32PllFlag = 0;
            }   
        }    
        else if(0 == u32Data) 
        {
            REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) & (0xFFFFFFFE);
            REG(REG_CLK_GATE) = REG(REG_CLK_GATE) & (0xFFFFFFFE);    
            Dd_Rf_Close();
        }    
    }
    else if((u32)pData == 0x80000030)/**/
    {
        Dd_Func_ReadCicle_Start();
        /*Dd_Timer_Init*/
        Dd_Timer_Init(TIMER_NUM_8,1000);
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000031) /*close NB*/
    {
        REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) & (0xFFFFFFFE);
        REG(REG_CLK_GATE) = REG(REG_CLK_GATE) & (0xFFFFFFFE);    
        Dd_Rf_Close();
        Dd_Mipi_LowPowerMode();
        Dd_LNAAndLpen_Low();
        Dd_Clock_Pll_268M_DIV_Test(u32Data);
        g_u32PllFlag = 1;
    }
    else if((u32)pData == 0x80000032)
    {
        Dd_Clock_Use_ExtClock_DIV_Test(u32Data);
    }
    else if((u32)pData == 0x80000033)
    {
        Dd_Func_ReadCicle_Start();
        /**/
        WatchDog1Init(WATCH_PERI_32M_CLOCKS);
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000034)
    {
        Dd_Func_ReadCicle_Start();
        /**/
        udelay(1000);
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000035)
    {
        Dd_Func_ReadCicle_Start();
        /**/
        Dd_Timer_ReadCounter(TIMER_NUM_8);
        Dd_Func_ReadCicle_End();
    }
    else if((u32)pData == 0x80000036)
    {
    }
    else if((u32)pData == 0x80000037)
    {
        
    }
    else if((u32)pData == 0x80000038)
    {
        REG(REG_IO_FUNC_HSEL0_CLR) |= (1<<23);
        REG(REG_IO_FUNC_LSEL0_CLR) |= (1<<23); 

        REG(REG_GPIO_SWPORTA_DDR) |=  (0x1 << 23); 
        if(u32Data == 0)
        {
            REG(REG_GPIO_SWPORTA_DR) &= (~(0x1 << 23));
        }    
        else
        {
            REG(REG_GPIO_SWPORTA_DR) |= (0x1 << 23);
        }    
    }
    else if((u32)pData == 0x81000000)    /*0.配置RF寄存器*/
    {
        regid = u32Data & 0x0000FFFF;
        regdata = (u32Data & 0xFFFF0000) >> 16;
        Dd_Rf_IcWriteReg(regid,regdata);    
    }    
    else if((u32)pData == 0x81000001)    /*1.读取RF寄存器*/
    {
        regid = u32Data & 0x0000FFFF;
        readval = Dd_Rf_IcReadReg(regid);
        printf("Read Reg%d:[0x%04x]\r\n",regid,readval);
    }
    else if((u32)pData == 0x81000002)    /*2.读取所有寄存器*/
    {
        Rf_ReadRegAll();     
    }  
    else
    {
        return 0;
    }    
    return 1;
}    

/******************************* 源文件结束 ***********************************/


