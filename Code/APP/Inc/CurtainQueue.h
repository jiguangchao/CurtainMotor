/*!
*****************************************************************
	\file 				
	\brief 				Curtain code
	\author 			xuyixin

    <b>Company:</b>\n	menred automation\n
修改记录
*****************************************************************/

#ifndef _CURTAIN_QUEUE_H_
#define _CURTAIN_QUEUE_H_

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "BSP.h"

#include "main.h"
#include "CurtainProtocol.h"

/*============================ MACROS ========================================*/
//#define IIC_NOTE       (0)




/******************************************************************************/
/******************************串口队列   **************************************/
/******************************************************************************/
#define CURTAIN_TX_QUEUE_MAX                                (10)//queue  发送队列数量
#define CURTAIN_RX_QUEUE_MAX                                (10)//queue  接收队列数量

typedef struct
{

    //uint8_t  u8Cmd;
    uint8_t  u8State;             //状态
    // rock expand DI or enocean 
    uint8_t  u8MessageType;       //消息类型
    uint8_t  u8ByteMax;           //数据长度
    //uint8_t  u8PacketType;
    uint8_t  u8Byte[CURTAIN_TX_BUFF];    
    //uint8_t  u8DstPhyaddress;

} CurtainSendQueueData_Typedef;  //发送队列

typedef struct
{

  uint8_t  u8Head;          //队列头
  uint8_t  u8End;           //队列尾
  uint8_t  u8QueueNum;       //队列数量
  CurtainSendQueueData_Typedef  u8Data[CURTAIN_TX_QUEUE_MAX];    

  uint8_t  u8SendWait;      //发送等待
  uint8_t  u8SendFlag;      //发送发送标记

} CurtainSendQueue_Typedef;  //发送队列


typedef struct
{

    //uint8_t  u8Cmd;
    uint8_t  u8State;              //状态 
    // rock expand DI or enocean             
    uint8_t  u8MessageType;        //消息类型      
    uint8_t  u8ByteMax;            //数据长度   
    //uint8_t  u8PacketType;
    uint8_t  u8Byte[CURTAIN_RX_BUFF];    
    //uint8_t  u8DstPhyaddress;

} CurtainReadQueueData_Typedef;  //接收队列


typedef struct
{
  
  uint8_t  u8Head;          //队列头
  uint8_t  u8End;           //队列尾
  uint8_t  u8QueueNum;      //队列数量
  CurtainReadQueueData_Typedef  u8Data[CURTAIN_RX_QUEUE_MAX];    

} CurtainReadQueue_Typedef;  //接收队列


extern CurtainSendQueue_Typedef  CurtainSend;   //窗帘发送
extern CurtainReadQueue_Typedef  CurtainRead;   //窗帘接收


/**
   * @brief
   * @param
   * @retval
   */
void CurtainQueue_Tick1ms(void);

/************************************************************************************/
/******************************  发送串口队列   **************************************/
/************************************************************************************/
/**
  * @brief: 发送队列初始化
  * @param
  * @retval None
  */
void CurtainSendQueue_Init(void);
/**
  * @brief: 判断队列是否为满 IsEmpty
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_IsEmpty(void);
/**
  * @brief: 清除队列的数据
  * @param
  * @retval None
  */
void CurtainSendQueue_ClearID(void);
/**
  * @brief: 设置发送队列的数据
  * @param
  * @retval None
  */
void CurtainSendQueue_SetID(void);
/**
  * @brief: 入队  into 
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_IntoQueue(void);
/**
  * @brief: 出队 out EnQueue
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_OutQueue(void);
/**
  * @brief: 入队数据处理   查询数据
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataQuery(uint8_t u8Cmd);
/**
  * @brief: 入队数据处理   设置数据
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataSet(uint8_t u8Cmd,uint8_t u8Data);
/**
  * @brief: 入队数据处理   控制
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataSet(uint8_t u8Cmd,uint8_t u8Data);
/**
  * @brief:  出队数据处理
  * @param
  * @retval None
  */
void CurtainSendQueue_OutQueueData(void);

/************************************************************************************/
/******************************  接收串口队列   **************************************/
/************************************************************************************/
/**
  * @brief: 发送队列初始化
  * @param
  * @retval None
  */

void CurtainReadQueue_Init(void);
/**
  * @brief: 判断队列是否为满 IsEmpty
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_IsEmpty(void);
/**
  * @brief: 清除队列的数据
  * @param
  * @retval None
  */
void CurtainReadQueue_ClearID(void);
/**
  * @brief: 设置发送队列的数据
  * @param
  * @retval None
  */
void CurtainReadQueue_SetID(void);
/**
  * @brief: 入队  into 
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_IntoQueue(void);
/**
  * @brief: 出队 out EnQueue
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_IntoQueue(void);
/**
  * @brief: 入队数据处理   
  * @param
  * @retval None
  */
void CurtainReadQueue_IntoQueueData(void);
/**
 * @brief: 出队数据处理
 * @param
 * @retval None
 */
uint8_t CurtainReadQueue_OutQueueData(void);
/************************************************************************************/
/******************************  队列处理函数   **************************************/
/************************************************************************************/
/**
 * @brief:  队列处理函数
 * @param
 * @retval None
 */
uint8_t CurtainQueueRun(void);



#endif