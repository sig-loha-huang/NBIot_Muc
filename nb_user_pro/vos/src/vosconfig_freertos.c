/*******************************************************************************
* COPYRIGHT@SIGBEN
*******************************************************************************
* 文件名称:  vosconfig_freertos.c
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
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

#include "vos.h"

/******************************* 局部宏定义 ***********************************/

/******************************* 全局变量定义/初始化 **************************/
//static int gMemSizeAccumulator = 0;

/******************************* 局部常数和类型定义 ***************************/

/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/

/*******************************************************************************
* 函数名称:  osal_MemAlloc
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void *osal_MemAlloc(unsigned long ulSize,unsigned long ulWaitOption)
{
    uint8_t *pheader;

	pheader = (uint8_t*)pvPortMalloc(ulSize);
    if (pheader != (uint8_t *)0)
    {
        return pheader;
    }
    else
    {
		printf("Mem Alloc failed\r\n");
        return NULL;
    }
}
/*******************************************************************************
* 函数名称:  osal_MemFree
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void osal_MemFree(void *pFirmMem)
{
    uint8_t	*pmsg = (uint8_t *)pFirmMem;
    vPortFree(pmsg);
}
/*******************************************************************************
* 函数名称:  osal_GetFreeHeapSize
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u32 osal_GetFreeHeapSize(void)
{
    return xPortGetFreeHeapSize();
}    
/*******************************************************************************
* 函数名称:  osal_SemaphoreCreate
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_SemaphoreCreate(osal_SemHandle *semHandle, u32 initialCount)
{

	SemaphoreHandle_t xSemaphore = NULL;

	if(NULL != *semHandle)
	{
		printf("Semaphore create failed. Semaphore is already created.\n");
		return -1;
	}
	
	xSemaphore = xSemaphoreCreateCounting(16, initialCount);

	if (NULL == xSemaphore)
	{
		printf("Semaphore create failed");
		return -1;
	}
	
	*semHandle = (osal_SemHandle)xSemaphore;
	
	return 0;
}
/*******************************************************************************
* 函数名称:  osal_SemaphoreTake
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_SemaphoreTake(osal_SemHandle semHandle, u32 timeout_ms)
{
	u32  ticks;

	switch(timeout_ms)
	{
		case OSAL_SEM_NO_WAIT:
			ticks = 0;
			break;
			
		case OSAL_SEM_TIMEOUT_INFINITE:
			ticks = portMAX_DELAY;
			break;
			
		default:
			//ticks = (portTICK_PERIOD_MS * timeout_ms);
			ticks = (timeout_ms/portTICK_PERIOD_MS);
			break;
	}

	if (xSemaphoreTake(semHandle, ticks) == pdTRUE)
	{
		return 0;
	}
	else
	{
		return -1;
	}

}
/*******************************************************************************
* 函数名称:  osal_SemaphoreGive
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_SemaphoreGive( osal_SemHandle semHandle )
{
	if (xSemaphoreGive(semHandle) != pdTRUE)
	{
		DD_DEBUG_PRINTF("Semaphore give failed %x\n",semHandle);
		return OSAL_RET_ERROR;
	}
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_SemaphoreDelete
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_SemaphoreDelete( osal_SemHandle semHandle )
{
	vSemaphoreDelete(semHandle);

	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_MutexCreate
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MutexCreate(osal_MutexHandle *mutHandle)
{
	SemaphoreHandle_t xSemaphore;

	if(NULL != *mutHandle)
	{
		DD_DEBUG_PRINTF("Mutex create failed. Mutex is already created.\n");
		return OSAL_RET_ERROR;
	}

	/* Create a mutex to provide protection over a
	common resource. */
	xSemaphore = xSemaphoreCreateMutex();

	if(xSemaphore == NULL)
	{
		DD_DEBUG_PRINTF("Mutex create failed\n");
		return OSAL_RET_ERROR;
	}

	*mutHandle = (osal_MutexHandle)xSemaphore;

	return OSAL_RET_SUCCESS;
}

/*******************************************************************************
* 函数名称:  osal_MutexTake
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MutexTake(osal_MutexHandle mutHandle, U32 timeout_ms)
{
	U32  ticks;

	switch (timeout_ms)
	{
	case OSAL_SEM_NO_WAIT:
		ticks = 0;
		break;

	case OSAL_SEM_TIMEOUT_INFINITE:
		ticks = portMAX_DELAY;
		break;

	default:
		//ticks = (portTICK_PERIOD_MS * timeout_ms);
		ticks = (timeout_ms/portTICK_PERIOD_MS);
		break;
	}

	if (xSemaphoreTake(mutHandle, ticks) == pdTRUE)
	{
		return OSAL_RET_SUCCESS;
	}
	else
	{
		return OSAL_RET_ERROR;
	}

}

/*******************************************************************************
* 函数名称:  osal_MutexTake
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MutexGive(osal_MutexHandle mutHandle)
{
	if (xSemaphoreGive(mutHandle) != pdTRUE)
	{
		DD_DEBUG_PRINTF("Mutex give failed\n");
		return OSAL_RET_ERROR;
	}
	return OSAL_RET_SUCCESS;
}

/*******************************************************************************
* 函数名称:  osal_MutexDelete
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MutexDelete(osal_MutexHandle mutHandle)
{
	vSemaphoreDelete(mutHandle);

	return OSAL_RET_SUCCESS;
}

/*******************************************************************************
* 函数名称:  osal_SemaphoreGiveFromIsr
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void osal_SemaphoreGiveFromIsr( void * semHandle )
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if (xSemaphoreGiveFromISR(semHandle, &xHigherPriorityTaskWoken) != pdTRUE)
	{
		//return -1;
	}

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	//return 0;
}

/*******************************************************************************
* 函数名称:  osal_CreateTask
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_CreateTask(osalTaskHandle *pTaskHandle, 
                            osalEntryFunction taskEntryFunction, 
                            U32 taskPriority, 
                            U32 stackSize, 
                            char *taskName,
                            void *pArgs)
{
    TaskHandle_t xHandle = NULL;

    if (xTaskCreate( taskEntryFunction, taskName, (U16)stackSize, &pArgs, taskPriority, &xHandle ) != pdPASS)
    {
		DD_DEBUG_PRINTF("osal TaskCreate error \n");
    }
    
	*pTaskHandle = (osalTaskHandle) xHandle;
	
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_GetTaskState
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
#if 0
Osal_TaskState osal_GetTaskState(osalTaskHandle pTaskHandle)
{
    return eTaskGetState(pTaskHandle);
}
#endif
/*******************************************************************************
* 函数名称:  osal_Sleep
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void osal_Sleep(U32 period_us)
{
	period_us /= 1000;
	U32 timer_ticks = period_us / portTICK_PERIOD_MS;
	
	/* Force to at least one tick! */
	timer_ticks = timer_ticks ? timer_ticks : 1;	
	
    vTaskDelay( timer_ticks );
}
/*******************************************************************************
* 函数名称:  osal_DestroyTask
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_DestroyTask(osalTaskHandle pTaskHandle)
{
    vTaskDelete( pTaskHandle );

	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_StartScheduler
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void osal_StartScheduler(void)
{
	vTaskStartScheduler();
}


/*******************************************************************************
* 函数名称:  osal_MessageQCreate
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQCreate(osal_MsgQHandle *hMsgQ,U32 msgSize,U32 numMsgs)
{
	QueueHandle_t pQueue;
	
	pQueue = xQueueCreate(numMsgs, msgSize);

	if(pQueue == NULL)
	{
		DD_DEBUG_PRINTF("osal msg queue create error\n");
		return OSAL_RET_ERROR;
	}
	
	*hMsgQ = pQueue;
	
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_MessageQDelete
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQDelete(osal_MsgQHandle hMsgQ)
{
    vQueueDelete( (QueueHandle_t*) hMsgQ );
	
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_GetMessageQCount
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
U32 osal_GetMessageQCount(osal_MsgQHandle hMsgQ)
{
	return (uxQueueMessagesWaiting(hMsgQ));
}
/*******************************************************************************
* 函数名称:  osal_GetMessageQCount
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQSend (osal_MsgQHandle hMsgQ,void *msg)
{
	/* Send a message to destination queue*/
	/* If status equals pdPASS, the message "pMsg" is in the queue. */
	if(xQueueSend( hMsgQ, msg, portMAX_DELAY))
    {
        return OSAL_RET_SUCCESS;
    }
    else
	{
		DD_DEBUG_PRINTF("osal msg queue send error\n");
		return OSAL_RET_ERROR;
	}
	
}

/*******************************************************************************
* 函数名称:  osal_MessageQReceive
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQReceive(osal_MsgQHandle hMsgQ, void *pMsg)
{
	/* Retrieve a message from a queue. If the queue is
	empty, suspend until a message is present. Note that
	this suspension is only possible from application
	threads. */
    if( xQueueReceive( hMsgQ, pMsg, portMAX_DELAY) )
    {
        return OSAL_RET_SUCCESS;
    }
    else
    {
		printf("osal msg queue receive error\n");
		return OSAL_RET_ERROR;
	}
}
/*******************************************************************************
* 函数名称:  osal_MessageQReceiveTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQReceiveTimer(osal_MsgQHandle hMsgQ, void *pMsg,u32 Timers)
{
	/* Retrieve a message from a queue. If the queue is
	empty, suspend until a message is present. Note that
	this suspension is only possible from application
	threads. */
    if( xQueueReceive( hMsgQ, pMsg, Timers) )
    {
        return OSAL_RET_SUCCESS;
    }
    else
    {
		printf("osal msg queue receive error\n");
		return OSAL_RET_ERROR;
	}
}

/*******************************************************************************
* 函数名称:  osal_MessageQSendFromIsr
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_MessageQSendFromIsr (osal_MsgQHandle hMsgQ, void *msg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	/* Send a message to destination queue*/
	/* If status equals pdPASS, the message "pMsg" is in the queue. */
	if(xQueueSendFromISR(hMsgQ, (void *)&msg,&xHigherPriorityTaskWoken))
    {
        return OSAL_RET_SUCCESS;
    }
    else
	{
		DD_DEBUG_PRINTF("osal msg queue send error\n");
		return OSAL_RET_ERROR;
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*******************************************************************************
* 函数名称:  NB_SendMsg
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void NB_SendMsg(osal_MsgQHandle pMsgQueueId,void *pucMsg,u32 MsgCode,u32 MsgLen)
{
    u32 ret;
    u32 aulMsg[4];

    void *pAtRecMsg = NULL;

    pAtRecMsg = osal_MemAlloc(MsgLen,0); 
    memcpy(pAtRecMsg,pucMsg,MsgLen);

    aulMsg[0] = MsgCode;                                                        /* message type                            */
    aulMsg[1] = (u32)pAtRecMsg;                                                 /* message address                         */
    aulMsg[2] = MsgLen;                                                         /* msg len                                 */
    aulMsg[3] = 0;                                                              /* reserve                                 */

    osal_MessageQSend(pMsgQueueId,(void*)aulMsg);
    return;
}
/*******************************************************************************
* 函数名称:  NB_RcvMsg
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 NB_RcvMsg(osal_MsgQHandle pMsgQueueId,void *pucMsg)
{
    return osal_MessageQReceive(pMsgQueueId,pucMsg);
}

/*******************************************************************************
* 函数名称:  osal_CreateTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_CreateTimer(osal_TimerHandle* pTimerHandle, U32 period_ms, OSAL_TIMER_PERIODICITY periodicity,pOSAL_TimerCallBackFnc pSystemCallBackFn)
{
	TimerHandle_t timerHandle;
	U32     ticks;
    U8      timerFlag;

	//ticks = (portTICK_PERIOD_MS * period_ms);
    ticks = (period_ms / portTICK_PERIOD_MS);
	ticks = ticks ? ticks : 1;	
	timerFlag = (periodicity == OSAL_TIMER_PERIODIC) ? 1 : 0;
	

	timerHandle = xTimerCreate( "timer",         // Just a text name, not used by the kernel.
		                        ticks,          // The timer period in ticks.
                                timerFlag,      // The timers will auto-reload themselves when they expire.
                                NULL,           // Assign each timer a unique id equal to its array index.
                               (TimerCallbackFunction_t) pSystemCallBackFn  // Each timer calls the same callback when it expires.
                                );

    
	
	*pTimerHandle = timerHandle;
	
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_ResetTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_ResetTimer(osal_TimerHandle hTimer, U32 period_ms, pOSAL_TimerCallBackFnc pSystemCallBackFn)
{
    if( xTimerReset( hTimer, 0 ) != pdPASS )
    {
		DD_DEBUG_PRINTF("OSAL Timer ResetTimer Error\n");
		return OSAL_RET_ERROR;
    }
		
	return OSAL_RET_SUCCESS;
}
/*******************************************************************************
* 函数名称:  osal_StartTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_StartTimer(osal_TimerHandle hTimer)
{
    
    if( xTimerStart( hTimer, 0 ) != pdPASS )
    {
		DD_DEBUG_PRINTF("OSAL Timer StartTimer Error\n");
		return OSAL_RET_ERROR;
    }
	
	return OSAL_RET_SUCCESS;
}

/*******************************************************************************
* 函数名称:  osal_CancelTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_CancelTimer(osal_TimerHandle hTimer)
{	
    xTimerStop( hTimer, 0 );
	
	return OSAL_RET_SUCCESS;
}

/*******************************************************************************
* 函数名称:  osal_DestroyTimer
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
u8 osal_DestroyTimer(osal_TimerHandle hTimer)
{

    if (xTimerDelete( hTimer, 0 ))
    {
        return OSAL_RET_SUCCESS;
    }
    else
    {
		DD_DEBUG_PRINTF("OSAL Timer DestroyTimer Error\n");
        return OSAL_RET_ERROR;
    }
	
}

u32 Osal_GetTickCount(void)
{
    return xTaskGetTickCount();
}
/*******************************************************************************
* 函数名称:  OsAssertCalled
* 函数功能:  
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 
*******************************************************************************/
void OsAssertCalled( const char * pcFile, unsigned long ulLine ,char * pucFunc)
{
	DD_DEBUG_PRINTF("ASSERT CALLED (OS)\r\n");
	DD_DEBUG_PRINTF("- Func: %s\r\n", pucFunc);
	DD_DEBUG_PRINTF("- File: %s\r\n", pcFile);
    while(1);    
}
/******************************* 源文件结束 ***********************************/

