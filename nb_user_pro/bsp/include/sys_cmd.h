/*******************************************************************************
********************************************************************************
* 文件名称: sys_cmd.h
* 功能描述: 
* 其它说明: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** 头文件保护开头 ******************************/
#ifndef SYS_CMD_H
#define SYS_CMD_H

/******************************** 包含文件声明 ********************************/
#include <type_def.h>
/******************************** 宏和常量定义 ********************************/
#define AT_RESP_CHECK_START            0x00
#define AT_RESP_CHECK_OK               0x01
#define AT_RESP_CHECK_ERROR            0xFF
#define AT_RESP_CHECK_STEP_1           0x11
#define AT_RESP_CHECK_STEP_2           0x12
#define AT_RESP_CHECK_STEP_3           0x13


/******************************** 类型定义 ************************************/

/******************************** 全局变量声明 ********************************/

/******************************** 外部函数原形声明 ****************************/
extern void SysCmdCommon(u8 * at_buffer, u32 at_buffer_len );
extern void SysMemSet(U32  u32MemAddr, U32 u32Memdata,U8 u8SetMemType);

extern void SystemCmdTask(void *arg);
extern u8   Sys_NBAutoCmdCheck(void *pRcvMsg);


extern void Sys_MqttConnect(void);
extern void Sys_MqttSetAiliyunDns(void);
extern void Sys_MqttKeepAlive(u32 u32data);
extern void Sys_MqttOpen(void);
extern void Sys_Ota_HttpCreat(void);
extern void Sys_Ota_HttpConnectMcu(void);
extern void Sys_NetWork_PingCmd(void);
extern void Sys_Ota_HttpConnectNB(void);
extern void Sys_Ota_MQTTPublishTopicInform(void);
extern void Sys_Ota_MQTTSubscribeTopicUpgrade(void);
extern void Sys_Ota_MQTTPublishTopicProgress(void);
extern void Sys_Ota_MQTTSubscribeTopicSys(void);
extern u8 Sys_NBAtGeneralCmdCheck(void *pRcvMsg);
extern S32 SysLoadInt(const char *data, int *x);

extern void Sys_At_SoftVersion(void);
extern u8 Sys_At_Resp_SoftVersion(u8 *pu8data);
extern void Sys_At_ImsiRead(void);
extern void Sys_NetWork_AiCMDNS(void);
extern void Sys_NetWork_IpStart(void);
extern void Sys_NetWork_IprCfg(void);
extern void Sys_NetWork_IpSendLoginIn(void);
extern void Sys_NetWork_IpSendUsimData(void);
extern void Sys_NetWork_IpSendHearBeat(void);
extern void Sys_At_SoftVersionCheck(void);
extern void Sys_At_Cfun0(void);
extern void Sys_At_Cfun1(void);
extern void Sys_Ota_VersionReprot(void);


extern u8 Sys_At_CMDNSRespCheck(u8 * pRcvMsg, u8 ATState);
extern u8 Sys_At_MqttMsgCheck(u8 * pRcvMsg, u8 ATState, u32 MsgTpye);
extern u8 Sys_At_HttpMsgCheck(u8 * pRcvMsg, u8 ATState, u32 MsgTpye);


/******************************** 头文件保护结尾 ******************************/
#endif /*SYS_CMD_H*/
/******************************** 头文件结束 **********************************/


