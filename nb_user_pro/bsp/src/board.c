/******************************* �����ļ����� *********************************/
#include <stdio.h>
#include <cortex_m4.h>
#include <core_cm3.h>
#include <string.h>
#include <mcu2nb.h>
/******************************* �ֲ��궨�� ***********************************/

/******************************* �ֲ����������Ͷ��� ***************************/
#define  NVIC_VTOR_REG   0xE000ED08             /*�ж�������ƫ�����Ĵ���*/

/******************************* �ֲ�����ԭ������ *****************************/

/******************************* ����ʵ�� *************************************/
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

    /*����cache��ӳ��ĵ�ַ��Χ ����flash��ǰ384KΪcache��*/
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
    Dd_Flash_ota_CheckandUpdate_VerCfg(&gStrVerCfg); //�ж��Ƿ�Ϊ������ģʽ����������ģʽ����Ϊ����ģʽ
#endif
#ifdef RF_REG_CHECK
    Dd_Uart2_Puts("mcu Start\r\n");
    Rf_ParaReg_Compar();
    DD_DEBUG_PRINTF("RF Calibration code version LH3200_01. Build Time: %s %s .\r\n",__DATE__,__TIME__);
#endif    
    init_NbModule();                              //����JTAG���Դ򿪴˺���
}

/******************************************************************************/
