/*******************************************************************************
* COPYRIGHT@ SIGBEAN
********************************************************************************
* 文件名称: flash.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __FLASH_H__
#define __FLASH_H__
/******************************** 包含文件声明 ********************************/

/******************************** 宏和常量定义 ********************************/

/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/

/********************************* IC 操作flash ********************************/
extern void Dd_flash_Ic_Init(void);
extern void Dd_Fast_read_config(void);
extern int Dd_flash_Ic_write(int addr, unsigned char *data, int len);
extern int Dd_flash_Ic_normal_read(int addr,unsigned char *data,int len,unsigned long *numberOfBytesRead);
extern int Dd_flash_Ic_erase(int sector_tmp,int size);
extern int Dd_flash_Ic_read(int addr,unsigned char *data,int len,unsigned long *numberOfBytesRead);
extern int Dd_flash_Ic_erase_block(int BlockAddr,int size);
extern void Dd_flash_Ic_Test(void);
extern void Dd_flash_Test(void);
/******************************** 头文件保护结尾 ******************************/
#endif /*_FLASH_H__*/
/******************************** 头文件结束 **********************************/

