/*******************************************************************************
********************************************************************************
* 文件名称: cortex_m4.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __CORTEX_M4_H__
#define __CORTEX_M4_H__


/******************************** 包含文件声明 ********************************/
/***************************     驱动头文件包含   *****************************/ 
#include <stdarg.h>

#include <bsp_reg.h>
#include <type_def.h>
#include <circbuf.h>
#include <uart.h>
#include <irq.h>
#include <timer.h>
#include <uart.h>
#include <cache.h>
#include <clock.h>
#include <board.h>
#include <flash.h>
#include <gpio.h>
#include <load_nb.h>
#include <mcu2nb.h>
#include <rtc.h>
#include <ota_hal.h>
#include <adc.h>
#include <uart_cmd.h>
/******************************** 宏和常量定义 ********************************/

/******************************** 类型定义 ************************************/
typedef unsigned char      U8;
typedef unsigned short     U16;
typedef unsigned int       U32;

typedef signed char        S8;
typedef signed short       S16;
typedef signed int         S32;

typedef S32 Bool;

typedef void* osalTaskHandle;
typedef void* osal_SemHandle;
typedef void* osal_MsgQHandle;
typedef void* osal_MutexHandle;
typedef void* osal_TimerHandle;
typedef enum
{
	OSAL_TIMER_PERIODIC,
	OSAL_TIMER_ONESHOT
} OSAL_TIMER_PERIODICITY;

typedef void (*pOSAL_TimerCallBackFnc)(void);
typedef void (*osalEntryFunction)(void* pArgs);     

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
#define REG(x)                                  (*((volatile unsigned int *)(x)))
#define READ_REG(reg)                           (REG(reg))
#define WRITE_REG(reg, val)                     (REG(reg) = (val))

#define CPU_IDLE_MODE()                         __asm volatile( "wfi")  //@ Wait for interrupt;WFI指令  CPU IDLE指令
#define NB_FAST_CODE                            __attribute__ ((section(".fastcode")))


#define DD_DEBUG_PUTS(str)                      Dd_Uart2_Puts(str)
#ifdef NB_DEBUG_ADD_TIMESTAMP
#define DD_DEBUG_PRINTF(str,...) do {\
        Dd_Uart2_Printf("%d:  "str"", \
        Osal_GetTickCount(),##__VA_ARGS__);\
    } while (0)
#else
#define DD_DEBUG_PRINTF(str,...)                Dd_Uart2_Printf(str,##__VA_ARGS__)
#endif
/******************************** 头文件保护结尾 ******************************/
#endif /*__CORTEX_M4_H__*/
/******************************** 头文件结束 **********************************/
