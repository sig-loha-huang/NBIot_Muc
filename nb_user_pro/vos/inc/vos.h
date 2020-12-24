/*******************************************************************************
* COPYRIGHT@ SIGBEAN
********************************************************************************
* 文件名称: vos.h
* 功能描述: 
* 其它说明: 
* 编写日期: 
* 修改历史: 
* 修改日期修改人BugID/CRID      修改内容
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef __VOS_H__
#define __VOS_H__

/******************************** 包含文件声明 ********************************/
#include <cortex_m4.h>

/******************************** 宏和常量定义 ********************************/

#define OSAL_SEM_TIMEOUT_INFINITE 0xFFFFFFFF
#define OSAL_SEM_NO_WAIT          0x0

#define	OSAL_RET_SUCCESS            0           /* success */
#define	OSAL_RET_ERROR              -1          /* general error code */


#define VOS_QUEUQ_AT_RESP           0xA0001
#define VOS_QUEUQ_PSM               0xA0002


#define VOS_AT_NETWORK_START        0xA1000
#define VOS_AT_CMDNS                0xA1001
#define VOS_MQTT_KEEPALIVE          0xA1002
#define VOS_MQTT_OPEN               0xA1003
#define VOS_MQTT_CONNECT            0xA1004
#define VOS_MQTT_THINGS_SET         0xA1005
#define VOS_MQTT_UPGRADE_SET        0xA1006
#define VOS_MQTT_VERSION_REPORT     0xA1007


#define VOS_AT_NORMAL_CGMR          0xA2000
#define VOS_AT_CFUN0                0xA2001
#define VOS_AT_CFUN1                0xA2002

#define VOS_AT_FRUTECH_CMDNS              0xA3000
#define VOS_AT_FRUTECH_IPSTART            0xA3001
#define VOS_AT_FRUTECH_IPRCFG             0xA3002
#define VOS_AT_FRUTECH_IPSEND_LOGIN       0xA3003  
#define VOS_AT_FRUTECH_IPSEND_SIM         0xA3004
#define VOS_AT_FRUTECH_IPSEND_HEART_BEAT  0xA3005

#define VOS_MQTT_END                0xAF000

#define VOS_OTA_START               0xA4000
#define VOS_OTA_CONNECT             0xA4001
#define VOS_OTA_DATA                0xA4002


#define LOS_WAIT_FOREVER            0xFFFFFFFF


#define     APP_TASK_ID_PRI             24
#define     MCURXNB_Task_ID_PRI         26
#define     AT_CMD_Task_ID_PRI          23

#define     APP_TASK_STACK_SIZE          (1024)
#define     MCURXNB_Task_STACK_SIZE      (512)
#define     AT_CMD_Task_STACK_SIZE       (1024)

/******************************** 类型定义 ************************************/




/******************************** 全局变量声明 ********************************/



/******************************** 外部函数原形声明 ****************************/

extern void *osal_MemAlloc(unsigned long ulSize,unsigned long ulWaitOption);
extern void osal_MemFree(void *pFirmMem);
extern u32 osal_GetFreeHeapSize(void);


extern u8 osal_SemaphoreCreate(osal_SemHandle *semHandle, u32 initialCount);
extern u8 osal_SemaphoreTake(osal_SemHandle semHandle, u32 timeout_ms);
extern u8 osal_SemaphoreGive( osal_SemHandle semHandle );
extern void osal_SemaphoreGiveFromIsr( void * semHandle );
extern u8 osal_SemaphoreDelete( osal_SemHandle semHandle );
extern u8 osal_MutexCreate(osal_MutexHandle *mutHandle);
extern u8 osal_MutexTake(osal_MutexHandle mutHandle, U32 timeout_ms);
extern u8 osal_MutexGive(osal_MutexHandle mutHandle);
extern u8 osal_MutexDelete(osal_MutexHandle mutHandle);



extern u8 osal_CreateTask(osalTaskHandle *pTaskHandle, 
                            osalEntryFunction taskEntryFunction, 
                            U32 taskPriority, 
                            U32 stackSize, 
                            char *taskName,
                            void *pArgs);
//extern Osal_TaskState osal_GetTaskState(osalTaskHandle pTaskHandle);
extern void osal_Sleep(U32 period_us);
extern u8 osal_DestroyTask(osalTaskHandle pTaskHandle);
extern void osal_StartScheduler(void);
extern u8 osal_MessageQCreate(osal_MsgQHandle *hMsgQ,U32 msgSize,U32 numMsgs);
extern u8 osal_MessageQDelete(osal_MsgQHandle hMsgQ);
extern U32 osal_GetMessageQCount(osal_MsgQHandle hMsgQ);
extern u8 osal_MessageQSend (osal_MsgQHandle hMsgQ,void *msg);
extern u8 osal_MessageQReceive(osal_MsgQHandle hMsgQ, void *pMsg);
extern u8 osal_MessageQSendFromIsr (osal_MsgQHandle hMsgQ, void *msg);
extern u8 osal_MessageQReceiveTimer(osal_MsgQHandle hMsgQ, void *pMsg,u32 Timers);


extern void NB_SendMsg(osal_MsgQHandle pMsgQueueId,void *pucMsg,u32 MsgCode,u32 MsgLen);
extern u8 NB_RcvMsg(osal_MsgQHandle pMsgQueueId,void *pucMsg);


extern u8 osal_CreateTimer(osal_TimerHandle* pTimerHandle, U32 period_ms, OSAL_TIMER_PERIODICITY periodicity,pOSAL_TimerCallBackFnc pSystemCallBackFn);
extern u8 osal_StartTimer(osal_TimerHandle hTimer);
extern u8 osal_CancelTimer(osal_TimerHandle hTimer);
extern u8 osal_DestroyTimer(osal_TimerHandle hTimer);
extern u32 Osal_GetTickCount(void);

void OsAssertCalled( const char * pcFile, unsigned long ulLine ,char * pucFunc);
#define OsconfigASSERT( x ) if( ( x ) != 1 ) OsAssertCalled( __FILE__, __LINE__ ,__FUNCTION__)

/******************************** 头文件保护结尾 ******************************/
#endif /* __VOS_H__ */
/******************************** 头文件结束 **********************************/


