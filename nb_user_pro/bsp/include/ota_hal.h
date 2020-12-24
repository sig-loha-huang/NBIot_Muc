/*******************************************************************************
********************************************************************************
* �ļ�����: ota_hal.h
* ��������: 
* ����˵��: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** ͷ�ļ�������ͷ ******************************/
#ifndef OTA_HAL_H
#define OTA_HAL_H

/******************************** �����ļ����� ********************************/
#include <type_def.h>

/******************************** ��ͳ������� ********************************/
#define     MCUBOOT_ADDR0           0x120000   //MCU VERSION1
#define     MCUBOOT_ADDR1           0x190000   //MCU VERSION2

#define     NB_VERSION_ADDR0        0x000000
#define     NB_VERSION_ADDR1        0x200000

#define     SYSCFG_FLASH_ADDR       0x300000

#define     FLASH_MAGIC_VALUE       0x2345ACDB


/******************************** ���Ͷ��� ************************************/
typedef struct
{
    U32 Magic;

	U32 McuRunState;
	U32 McuWorkingFileId;//0,1.	

    U32 McuVer1Len;
    U32 McuVer2Len;
    
	U32 NBRunState;
	U32 NBWorkingFileId;//0,1.

    U32 NBVer1Len;
    U32 NBVer2Len;

    U32 CfgCrc32;
}FlashCfgInfo_t;

typedef enum
{
	MCULOADER_0,
	MCULOADER_1
}FlashBootlaoerNum_EMCU;

typedef enum
{
	NBLOADER_0,
	NBLOADER_1
}FlashBootlaoerNum_ENB;

typedef enum
{
	FIRST_INIT_STATE,
	TEST_RUN_STATE,
	NORMAL_RUN_STATE
}BootState_E;
/******************************** ȫ�ֱ������� ********************************/
extern FlashCfgInfo_t gStrVerCfg;          /*�洢������Ϣ*/

/******************************** �ⲿ����ԭ������ ****************************/
extern U32 CalculateCrc32(U8 *Buf, U32 Size);
extern void Dd_Flash_Ota_VerCfg_Read(void);
extern u8 Dd_Flash_ota_CheckandUpdate_VerCfg(FlashCfgInfo_t *cfg);
extern void Dd_Flash_Ota_VerCfg_McuUpdate(u32 u32len);
extern void Dd_Flash_Ota_Write_McuRunState(u32 u32RunState);

extern void Dd_Flash_Ota_McuVersionBakup(void);


/******************************** ͷ�ļ�������β ******************************/
#endif /*OTA_HAL_H*/
/******************************** ͷ�ļ����� **********************************/


