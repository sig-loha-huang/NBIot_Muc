#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "string.h"
#include "cortex_m4.h"
#include "vos.h"
#include "platform.h"
#include "sys_cmd.h"


#define  OTA_NB_FILE            0x1000
#define  OTA_MCU_FILE           0x2000
#define  SYS_MQTT_ALIVE_TIME    (10000)

void *              RxNbDataReadySem = NULL;         /*用于核间通信的信号量*/
void *              OtaSem           = NULL;
void *              NBMsgQ           = NULL;
osal_TimerHandle    gTimerHandle;
u32                 g_u32MsgType;


#ifdef AI_FTECH_SZ
osal_TimerHandle    gAiHeartBeatTimer = NULL;
#endif

void Dd_Test_Puts(void)
{
    //Sys_At_SoftVersionCheck();
    //DD_DEBUG_PUTS("Test Puts 3S\r\n");
    rccc_wirte();
}
void AppMain(void * pvParameters)
{
    u8                  lResult = -1; 
    u8                  ATState = 0;
    u32                 au32RcvMsg[4];    
    u8                  *pRcvMsg = NULL;
    u32                 MsgLen;
    u32                 u32FlashEraseFlag = 0;
    u8                  u8HeartBeatTimerStart = 0;

#ifdef OTA_FUNC_TEST
    u32                 u32OtaFile = OTA_MCU_FILE;
#endif    
    lResult = osal_MessageQCreate(&NBMsgQ,16,32);
#ifdef AI_FTECH_SZ
    //osal_CreateTimer(&gTimerHandle, 30000, OSAL_TIMER_PERIODIC, Dd_Test_Puts);
    /*keep alive all the time*/
    //osal_StartTimer(gTimerHandle);
#endif
    for( ;; )
    {
        lResult = osal_MessageQReceive(NBMsgQ,(void *)au32RcvMsg);

        pRcvMsg = (u8 *)au32RcvMsg[1];
        MsgLen = au32RcvMsg[2];

        switch(au32RcvMsg[0])
        {
            case VOS_AT_NETWORK_START:
            {
                osal_Sleep(5000000);

                #ifdef OTA_FUNC_TEST
                    if(u32FlashEraseFlag == 0)
                    {
                        Dd_Flash_Ota_McuVersionBakup();
                        u32FlashEraseFlag = 1;
                    } 
                    else
                    {
                        Sys_Ota_HttpCreat();
                    }
                    g_u32MsgType = VOS_OTA_START;
                #endif
                #ifdef AI_FTECH_SZ
                    /*read SoftVersion*/
                    Sys_At_SoftVersion();
                    g_u32MsgType = VOS_AT_NORMAL_CGMR;
                #endif
                #ifdef ALIYUN_CONNECT
                    Sys_MqttSetAiliyunDns();
                    g_u32MsgType = VOS_AT_CMDNS;
                    ATState = AT_RESP_CHECK_START;
                #endif  
                
                break;
            }
            case VOS_AT_CFUN0:
            {
                ATState = Sys_At_CfunCheck((void *)pRcvMsg,ATState);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_At_Cfun1();
                    g_u32MsgType = VOS_AT_CFUN1;
                    ATState = AT_RESP_CHECK_START;
                }       
                break;
            }            
            case VOS_AT_CMDNS:
            {   
                ATState = Sys_At_CMDNSRespCheck((void *)pRcvMsg,ATState);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_MqttKeepAlive(1);
                    g_u32MsgType = VOS_MQTT_KEEPALIVE;
                    ATState = AT_RESP_CHECK_START;
                }
                break;
            }
#ifdef ALIYUN_CONNECT
            /*MQTT MSG PROC*/
            case VOS_MQTT_KEEPALIVE:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_MqttOpen();
                    g_u32MsgType = VOS_MQTT_OPEN;
                    ATState = AT_RESP_CHECK_START; 
                }  
                break;
            case VOS_MQTT_OPEN:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_MqttConnect();
                    g_u32MsgType = VOS_MQTT_CONNECT;
                    ATState = AT_RESP_CHECK_START;
                }  
                break;
            case VOS_MQTT_CONNECT:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_Ota_MQTTSubscribeTopicSys();
                    g_u32MsgType = VOS_MQTT_THINGS_SET;
                    ATState = AT_RESP_CHECK_START; 
                }  
                break;                
            case VOS_MQTT_THINGS_SET:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_Ota_MQTTSubscribeTopicUpgrade(); 
                    g_u32MsgType = VOS_MQTT_UPGRADE_SET;
                    ATState = AT_RESP_CHECK_START;                
                }  
                break;
            case VOS_MQTT_UPGRADE_SET:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_Ota_VersionReprot();
                    g_u32MsgType = VOS_MQTT_VERSION_REPORT;
                    ATState = AT_RESP_CHECK_START;                
                }  
                break;                
            case VOS_MQTT_VERSION_REPORT:
                ATState = Sys_At_MqttMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    g_u32MsgType = VOS_MQTT_END;
                    ATState = AT_RESP_CHECK_START;                
                }  
                break;
#endif                
#ifdef OTA_FUNC_TEST
            case VOS_OTA_START:
                ATState = Sys_At_HttpMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    if(u32OtaFile ==OTA_NB_FILE)
                    {
                        Sys_Ota_HttpConnectNB();
                    }
                    else
                    {
                        Sys_Ota_HttpConnectMcu();
                    }
                    g_u32MsgType = VOS_OTA_CONNECT;
                    ATState = AT_RESP_CHECK_START;  
                }    
                break;
            case VOS_OTA_CONNECT:
                ATState = Sys_At_HttpMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                break;
#endif
#ifdef AI_FTECH_SZ
            case VOS_AT_NORMAL_CGMR:
                /*check version*/
                lResult = Sys_At_Resp_SoftVersion(pRcvMsg);
                if(lResult == TRUE)
                {
                    Sys_NetWork_AiCMDNS();
                    g_u32MsgType = VOS_AT_FRUTECH_CMDNS;
                    ATState = AT_RESP_CHECK_START;
                }                  
                break;
            case VOS_AT_FRUTECH_CMDNS:
                ATState = Sys_At_CMDNSRespCheck((void *)pRcvMsg,ATState);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_NetWork_IpStart();
                    g_u32MsgType = VOS_AT_FRUTECH_IPSTART;
                    ATState = AT_RESP_CHECK_START;
                }                
                break;
            case VOS_AT_FRUTECH_IPSTART:
                ATState = Sys_At_FrutechMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_NetWork_IprCfg();
                    g_u32MsgType = VOS_AT_FRUTECH_IPRCFG;
                    ATState = AT_RESP_CHECK_START;
                }                  
                break;
            case VOS_AT_FRUTECH_IPRCFG:
                ATState = Sys_At_FrutechMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_NetWork_IpSendLoginIn();
                    g_u32MsgType = VOS_AT_FRUTECH_IPSEND_LOGIN;
                    ATState = AT_RESP_CHECK_START;
                }          
                break;
            case VOS_AT_FRUTECH_IPSEND_LOGIN:
                ATState = Sys_At_FrutechMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_NetWork_IpSendUsimData();
                    g_u32MsgType = VOS_AT_FRUTECH_IPSEND_SIM;
                    ATState = AT_RESP_CHECK_START;
                }                  
                break;
            case VOS_AT_FRUTECH_IPSEND_SIM:
                ATState = Sys_At_FrutechMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    Sys_NetWork_IpSendHearBeat();
                    if(gAiHeartBeatTimer == NULL)
                    {
                        osal_CreateTimer(&gAiHeartBeatTimer, 60000, OSAL_TIMER_PERIODIC, Sys_NetWork_IpSendHearBeat);
                    }    
                    g_u32MsgType = VOS_AT_FRUTECH_IPSEND_HEART_BEAT;
                    ATState = AT_RESP_CHECK_START;
                }                  
                break;
            case VOS_AT_FRUTECH_IPSEND_HEART_BEAT:
                ATState = Sys_At_FrutechMsgCheck((void *)pRcvMsg,ATState,au32RcvMsg[0]);
                if(ATState == AT_RESP_CHECK_OK)
                {
                    if(u8HeartBeatTimerStart == 0)
                    {
                        osal_StartTimer(gAiHeartBeatTimer);
                        u8HeartBeatTimerStart = 1;
                    }    
                    g_u32MsgType = VOS_AT_FRUTECH_IPSEND_HEART_BEAT;
                    ATState = AT_RESP_CHECK_START;                    
                }
                else if(ATState == AT_RESP_CHECK_ERROR)
                {
                    /*close timer*/
                    osal_CancelTimer(gAiHeartBeatTimer);
                    u8HeartBeatTimerStart = 0;

                    /*关机*/
                    Sys_At_Cfun0();
                    g_u32MsgType = VOS_AT_CFUN0;
                    ATState = AT_RESP_CHECK_START;
                }
                break;
#endif
            default:
                break;
        }
        memset((void *)pRcvMsg,0,MsgLen);
        osal_MemFree((void *)pRcvMsg);
    }
}

void McuRxNbTask(void * pvParameters)
{
    osal_SemaphoreCreate(&RxNbDataReadySem, 0);
    
    for( ;; )
    {
        osal_SemaphoreTake(RxNbDataReadySem, 0xFFFFFFFF);
        Dd_McuRxNbMsg();        
    }
}


void main(void)
{
    void * AppMainID          =   NULL;
    void * McuRxNBTask        =   NULL;       
    void * ATCmdTask          =   NULL;
    
    Dd_init();
    g_StruNBStatue.u32NBState =  NB_STATE_OPEN;
    /*清除共享buffer数据*/
    memset((void *)SRAM_ADDR,0,SRAM_SIZE);

    osal_CreateTask(&AppMainID, AppMain, APP_TASK_ID_PRI, APP_TASK_STACK_SIZE, "AppMain", NULL);
    osal_CreateTask(&McuRxNBTask, McuRxNbTask, MCURXNB_Task_ID_PRI, MCURXNB_Task_STACK_SIZE, "McuRxNbTask", NULL);
    osal_CreateTask(&ATCmdTask, SystemCmdTask, AT_CMD_Task_ID_PRI, AT_CMD_Task_STACK_SIZE, "ATCmdTask", NULL);

	/* 启动调度器，任务开始执行 */
    osal_StartScheduler();
    while(1);    
}


