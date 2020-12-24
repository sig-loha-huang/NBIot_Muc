/******************************* 包含文件声明 *********************************/
#include <stdio.h>
#include <cortex_m4.h>
#include <core_cm3.h>
#include <string.h>
#include <mcu2nb.h>
/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/
#define  NVIC_VTOR_REG   0xE000ED08             /*中断向量表偏移量寄存器*/

/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/
void Dd_InterVectorRemap(void)
{
    memset((void *)(0x00000000) ,0,512);
    memcpy((void *)(0x00000000) ,(void *)(0x08120000),512);
    WRITE_REG(NVIC_VTOR_REG,0);
}

void Dd_init(void)
{
    Dd_Clock_Init();
    
    Dd_InterVectorRemap();

    /*设置cache所映射的地址范围 设置flash的前384K为cache区*/
    //Dd_Cache_SetCacheableMemRGN2(0x08120000,0x08180000); 

    NVIC_EnableIRQ(IRQ_UART2);    
    NVIC_SetPriority(IRQ_UART2,20);

    Dd_Uart2_Reset();
    
    Dd_Uart2_Init(UART2_BAUD_RATE,0,0,ARM_CLK);
//    Dd_Cpm2_IntInit();
    Dd_Mcu2NbIntInit();   

    /*clear rtc bit0*/
    REG(REG_RETENTION00) &= 0xFFFFFFFE;

//    NVIC_EnableIRQ(IRQ_GPIOA);    
//    Dd_GpioTest(3);

    WatchDogInit(WATCH_PERI_2G_CLOCKS);
    NVIC_EnableIRQ(IRQ_WDT0);    
    NVIC_SetPriority(IRQ_WDT0,20);

#ifdef OTA_FUNC_TEST
    Dd_Flash_Ota_VerCfg_Read();
    Dd_Flash_ota_CheckandUpdate_VerCfg(&gStrVerCfg); //判断是否为试运行模式，是试运行模式更新为正常模式
#endif
#ifdef RF_REG_CHECK
    Dd_Uart2_Puts("mcu Start\r\n");
    Rf_ParaReg_Compar();
    DD_DEBUG_PRINTF("RF Calibration code version LH3200_01. Build Time: %s %s .\r\n",__DATE__,__TIME__);
#endif    
    init_NbModule();                              //基于JTAG调试打开此函数
}

/******************************************************************************/
