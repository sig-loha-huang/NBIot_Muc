/*******************************************************************************
* COPYRIGHT@ SIGBEN
********************************************************************************
* �ļ�����: mcu2nb.h
* ��������: 
* ����˵��: 
* ��д����: 
* �޸���ʷ: 
* ------------------------------------------------------------------------------
* 
*******************************************************************************/

/******************************** ͷ�ļ�������ͷ ******************************/
#ifndef MCU2NB_H
#define MCU2NB_H
/******************************** �����ļ����� ********************************/

/******************************** ��ͳ������� ********************************/
#define MCU2NB_MSG_MAX_SIZE                        (1024)

#define MCU2NB_INTERFACE_MSGBUFFER_NUM             7

#define MCU2NB_SHARED_MSG_ADDR                     0x20000000 
#define NB2MCU_SHARED_MSG_ADDR                     0x20002000 

#define NB2MCU_AT_REQ_MSG                         0xA0000001
#define NB2MCU_AT_RSP_MSG                         0x80000001
#define NB2MCU_PSM_MSG                            0x80000002
#define NB2MCU_OTA_MSG                            0x80000003
#define NB2MCU_FREQ_REDU_MSG                      0x80000004
#define NB2MCU_FREQ_RISE_MSG                      0x80000005


#define WRITE_READY_FLAG                            0
#define READ_READY_FLAG                             1

#define MCU_INT_SET                                 1
#define MCU_INT_OUT                                 0

/******************************** ���Ͷ��� ************************************/
typedef struct NB2MCU_Interface_Msg_Unit
{
    u32 Flag;    /*0:ready to write; 1:ready to read*/

    u8  MsgData[MCU2NB_MSG_MAX_SIZE-4];
}NB2MCU_Interface_Msg_Unit;
typedef struct MCU2NB_Interface_Msg_Unit
{
    u32 Flag;    /*0:ready to write; 1:ready to read*/

    u8  MsgData[MCU2NB_MSG_MAX_SIZE-4];
}MCU2NB_Interface_Msg_Unit;

typedef struct  MsgHeader
{
    u32         header_opc;       /*msg opcode*/
    u32         timing_record;    /*send timing*/
    u32         message_len;      /*send msg len*/
}MsgHeader; 

typedef struct  StrATCmdMsg
{
    MsgHeader   Hdr;                                    /*msg hdr*/
    u8          AtCmdData[MCU2NB_MSG_MAX_SIZE-16];      /*send msg len*/
}StrATCmdMsg; 

/******************************** ȫ�ֱ������� ********************************/
extern void * RxNbDataReadySem;
extern volatile unsigned int *g_u32AtMsgFLag;
/******************************** �ⲿ����ԭ������ ****************************/
extern void Dd_Mcu2NbIntInit(void);
extern void Dd_McuForceNbInt(void);
extern void Dd_McuRecNbInt_Isr(void);

extern void Dd_McuSendToNbMsg(void * pMsg);
extern void Dd_McuRxNbMsg(void);
extern void Dd_AT_Msg(void * pMsg,u32 len,u32 flag);
extern void clear_share_memory_no_index(void);

/******************************** ͷ�ļ�������β ******************************/
#endif /* MCU2NB_H */
/******************************** ͷ�ļ����� **********************************/


