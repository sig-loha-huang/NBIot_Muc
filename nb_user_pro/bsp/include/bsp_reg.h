/*******************************************************************************
 * COPYRIGHT@SIGBEAN
********************************************************************************
* 文件名称: bsp_reg.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __BSP_REG_H__
#define __BSP_REG_H__


/******************************** 包含文件声明 ********************************/
/***************************     驱动头文件包含   *****************************/ 
/******************************** 宏和常量定义 ********************************/

/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/

#define FLASH_ADDR            0x08000000

#define SRAM_ADDR             0x20000000
#define SRAM_SIZE             0x4000

#define ARM_CLK               (134400000)
#define CLK_19P2M              19200000
#define CLK_9P6M                9600000
#define CLK_2P4M                2400000
#define CLK_4P8M                4800000
#define CLK_1P92M               1920000
//#define NO_SYS_OS             1             /*无操作系统*/
//#define OTA_FUNC_TEST                         /*OTA功能测试*/
//#define RF_REG_CHECK            1             /*rf寄存器筛片测试*/
//#define  ALIYUN_CONNECT           1             /*连接阿里云物联网平台*/


#define UART_USE_MEM_POOL       0
#define AT_RESP_DEBUG           1
//#define AI_FTECH_SZ              1           /*Test GGH*/
//#define NB_DEBUG_ADD_TIMESTAMP   1

/* 管脚复用部分配置 */
#define  IOCTRL_BASE_ADDR                       0x40010000

#define  REG_IO_FUNC_LSEL0_SET                  (IOCTRL_BASE_ADDR + 0x000)
#define  REG_IO_FUNC_LSEL0_CLR                  (IOCTRL_BASE_ADDR + 0x004)
#define  REG_IO_FUNC_HSEL0_SET                  (IOCTRL_BASE_ADDR + 0x008)
#define  REG_IO_FUNC_HSEL0_CLR                  (IOCTRL_BASE_ADDR + 0x00c)
#define  REG_GPIO_REN_SET                       (IOCTRL_BASE_ADDR + 0x010)
#define  REG_GPIO_REN_CLR                       (IOCTRL_BASE_ADDR + 0x014)

#define  REG_B_IO_FUNC_LSEL0_SET                (IOCTRL_BASE_ADDR + 0x100)
#define  REG_B_IO_FUNC_LSEL0_CLR                (IOCTRL_BASE_ADDR + 0x104)
#define  REG_B_IO_FUNC_HSEL0_SET                (IOCTRL_BASE_ADDR + 0x108)
#define  REG_B_IO_FUNC_HSEL0_CLR                (IOCTRL_BASE_ADDR + 0x10c)
#define  REG_B_GPIO_REN_SET                     (IOCTRL_BASE_ADDR + 0x110)
#define  REG_B_GPIO_REN_CLR                     (IOCTRL_BASE_ADDR + 0x114)

//-----------------------------------------------------------------
// CPM Register Map
//head-------------------------------------------------------------
#define CPM_BASE_ADDR                               (0x40000000)

#define REG_CLK_GLO_SRC                         	(CPM_BASE_ADDR + 0x000)
#define REG_CLK_DIV                         		(CPM_BASE_ADDR + 0x004)
#define REG_RSTN_SYS_SOFT                       	(CPM_BASE_ADDR + 0x008)
#define REG_PLL_CTRL                            	(CPM_BASE_ADDR + 0x00c)
#define REG_CLK_GATE                         		(CPM_BASE_ADDR + 0x010)
#define REG_RSTN_SOFT                         	    (CPM_BASE_ADDR + 0x018)
#define REG_RSTN_SPC_SOFT                           (CPM_BASE_ADDR + 0x020)
#define REG_BOOT_MODE                               (CPM_BASE_ADDR + 0x100)
#define REG_CACHE_CTRL                          	(CPM_BASE_ADDR + 0x104)
#define REG_CPU0_IRQ_MASK                           (CPM_BASE_ADDR + 0x108)
#define REG_CPU1_IRQ_MASK                           (CPM_BASE_ADDR + 0x10c)
#define REG_OTP_TIMING_CFG                          (CPM_BASE_ADDR + 0x110)
#define REG_USIM_IO_MODE                     	    (CPM_BASE_ADDR + 0x118)
#define REG_FLASH_TIMING_CFG                        (CPM_BASE_ADDR + 0x120)
#define REG_FLASH_CMD0                 		        (CPM_BASE_ADDR + 0x124)
#define REG_FLASH_CMD1                 		        (CPM_BASE_ADDR + 0x128)
#define REG_FLASH_CMD2                 		        (CPM_BASE_ADDR + 0x12c)
#define REG_PSRAM_TIMING_CFG                        (CPM_BASE_ADDR + 0x130)
#define REG_PSRAM_CMD0                 		        (CPM_BASE_ADDR + 0x134)
#define REG_PSRAM_CMD1                 		        (CPM_BASE_ADDR + 0x138)
#define REG_PSRAM_CMD2                 		        (CPM_BASE_ADDR + 0x13c)

#define REG_CACHE_RGN0	                            (CPM_BASE_ADDR + 0x140) //nb使用
#define REG_CACHE_RGN1	                            (CPM_BASE_ADDR + 0x144) //nb使用
#define REG_CACHE_RGN2	                            (CPM_BASE_ADDR + 0x148) //mcu使用
#define REG_CACHE_RGN3	                            (CPM_BASE_ADDR + 0x14C) //mcu使用

#define REG_FLASH_WAIT_CFG1	                        (CPM_BASE_ADDR + 0x150)	
#define REG_FLASH_WAIT_CFG2	                        (CPM_BASE_ADDR + 0x154)	
#define REG_BUS_CTRL                                (CPM_BASE_ADDR + 0x400)


#define REG_PWR_MODE_SWITCH                         (CPM_BASE_ADDR + 0x200)
#define REG_RTC_DETECT_CTRL                 	    (CPM_BASE_ADDR + 0x204)
#define REG_RTC_DETECT_VAL                 	        (CPM_BASE_ADDR + 0x208)
#define REG_PLL_LOCK                 			    (CPM_BASE_ADDR + 0x20c)

#define REG_MCU_BOOT_MODE                           (CPM_BASE_ADDR + 0x300) 



#define CPM_INTCFG                              (CPM_BASE_ADDR + 0xf00)
#define CPM_INTFLG                              (CPM_BASE_ADDR + 0xf04)
#define CPM_INTENA                              (CPM_BASE_ADDR + 0xf08)
#define CPM_INTUNE                              (CPM_BASE_ADDR + 0xf0c)
#define CPM_INTMSK                              (CPM_BASE_ADDR + 0xf10)
#define CPM_INTUNM                              (CPM_BASE_ADDR + 0xf14)
#define CPM_INTCLR                              (CPM_BASE_ADDR + 0xf18)
#define CPM_INTFRC                              (CPM_BASE_ADDR + 0xf1c)
#define CPM_INTOVF                              (CPM_BASE_ADDR + 0xf20)
#define CPM_SHDCLR                              (CPM_BASE_ADDR + 0xf24)
#define CPM_OVFCLR                              (CPM_BASE_ADDR + 0xf28)
#define CPM_SRCTYP                              (CPM_BASE_ADDR + 0xf2c)
#define CPM_SRCEDG                              (CPM_BASE_ADDR + 0xf30) 
#define CPM_SRCPOL                              (CPM_BASE_ADDR + 0xf34) 

/* RST clock */
#define CPU0_CLK_RST				(1<<0)
#define CPU1_CLK_RST				(1<<1)
#define CPM_CLK_RST					(1<<2)
#define BUS_CLK_RST					(1<<3)
#define OTPIF_CLK_RST				(1<<4)
#define FLASHIF_CLK_RST				(1<<5)
#define PSRAMIF_CLK_RST			    (1<<6)
#define DMAC0_CLK_RST				(1<<7)
#define DMAC1_CLK_RST				(1<<8)
#define SDRAM_CLK_RST				(1<<9)
#define GPIO_CLK_RST				(1<<10)
#define TIMER0_INNER_CLK_RST		(1<<11)
#define TIMER0_OUTER_CLK_RST		(1<<12)
#define TIMER1_INNER_CLK_RST		(1<<13)
#define TIMER1_OUTER_CLK_RST		(1<<14)
#define WDT0_CLK_RST				(1<<15)
#define WDT1_CLK_RST				(1<<16)
#define UART0_CLK_RST				(1<<17)
#define UART1_CLK_RST				(1<<18)
#define UART2_CLK_RST				(1<<19)
#define UART3_CLK_RST				(1<<20)
#define SPI_M0_CLK_RST				(1<<21)
#define SPI_M1_CLK_RST				(1<<22)
#define SPI_S0_CLK_RST				(1<<23)
#define I2C_CLK_RST					(1<<24)
#define USIM_CLK_RST				(1<<25)
#define CIPHER_CLK_RST				(1<<26)
#define DAA_CLK_RST					(1<<27)
#define RF_CTRL_CLK_RST				(1<<28)
#define ADC_CTRL_CLK_RST			(1<<29)

//end--------------------------------------------------------------
//-----------------------------------------------------------------

/******************************** WDT REG *************************************/
#define WDT0_BASE                                0x40030000
#define WDT0_CR                                  (WDT0_BASE + 0x000)
#define WDT0_TORR                                (WDT0_BASE + 0x004)
#define WDT0_CCVR                                (WDT0_BASE + 0x008)
#define WDT0_CRR                                 (WDT0_BASE + 0x00C)
#define WDT0_STAT                                (WDT0_BASE + 0x010)   
#define WDT0_EOI                                 (WDT0_BASE + 0x014)
#define WDT0_PROT_LEVEL                          (WDT0_BASE + 0x01C)
#define WDT0_COMP_PARAM_5                        (WDT0_BASE + 0x0e4)
#define WDT0_COMP_PARAM_4                        (WDT0_BASE + 0x0e8)
#define WDT0_COMP_PARAM_3                        (WDT0_BASE + 0x0ec)
#define WDT0_COMP_PARAM_2                        (WDT0_BASE + 0x0f0)
#define WDT0_COMP_PARAM_1                        (WDT0_BASE + 0x0f4)
#define WDT0_COMP_VERSION                        (WDT0_BASE + 0x0f8)
#define WDT0_COMP_TYPE                           (WDT0_BASE + 0x0fc)

#define WDT1_BASE                                0x40031000
#define WDT1_CR                                  (WDT1_BASE + 0x000)
#define WDT1_TORR                                (WDT1_BASE + 0x004)
#define WDT1_CCVR                                (WDT1_BASE + 0x008)
#define WDT1_CRR                                 (WDT1_BASE + 0x00C)
#define WDT1_STAT                                (WDT1_BASE + 0x010)   
#define WDT1_EOI                                 (WDT1_BASE + 0x014)
#define WDT1_PROT_LEVEL                          (WDT1_BASE + 0x01C)
#define WDT1_COMP_PARAM_5                        (WDT1_BASE + 0x0e4)
#define WDT1_COMP_PARAM_4                        (WDT1_BASE + 0x0e8)
#define WDT1_COMP_PARAM_3                        (WDT1_BASE + 0x0ec)
#define WDT1_COMP_PARAM_2                        (WDT1_BASE + 0x0f0)
#define WDT1_COMP_PARAM_1                        (WDT1_BASE + 0x0f4)
#define WDT1_COMP_VERSION                        (WDT1_BASE + 0x0f8)
#define WDT1_COMP_TYPE                            (WDT1_BASE + 0x0fc)


/******************************** 头文件保护结尾 ******************************/
#endif /*__BSP_REG_H__*/
/******************************** 头文件结束 **********************************/

