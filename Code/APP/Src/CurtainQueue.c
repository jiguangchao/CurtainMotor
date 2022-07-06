

/*!
*****************************************************************
	\author 			xuyixin
    <b>Company:</b>\n	menred automation\n
修改记录
*****************************************************************/

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "BSP.h"
#include "main.h"
#include "CurtainProtocol.h"
#include "CurtainInterface.h"
#include "CurtainQueue.h"
/*============================ MACROS ========================================*/

CurtainSendQueue_Typedef  CurtainSend;   //窗帘发送
CurtainReadQueue_Typedef  CurtainRead;   //窗帘接收


/**
   * @brief
   * @param
   * @retval
   */
void CurtainQueue_Tick1ms(void)
{

    CurtainSend.u8SendWait++;

    if ( CurtainSend.u8SendWait >= 100 )
    {
        CurtainSend.u8SendFlag = 1;
    }
    

    if ( 1 == CurtainRun.u8CurtainDropFlag )
    {
        CurtainRun.u32CurtainDropTime++;

        if ( CurtainRun.u32CurtainDropTime > 1500 )
        {
            CurtainRun.u8CurtainDropCount++;
            CurtainRun.u32CurtainDropTime = 0;
        }

        if ( CurtainRun.u8CurtainDropCount > 3 )
        {
            CurtainRun.eFaultCode = eCURTAINRUN_EQUIPMENT_DROPS ;
            CurtainRun.u8CurtainDropCount = 0;
        }
           
    }

}
/************************************************************************************/
/******************************  发送串口队列   **************************************/
/************************************************************************************/
/**
  * @brief: 发送队列初始化
  * @param
  * @retval None
  */
void CurtainSendQueue_Init(void)
{
    CurtainSend.u8Head = 0;
    CurtainSend.u8End  = 0;
    CurtainSend.u8QueueNum = 0;
}
/**
  * @brief: 判断队列是否为满 IsEmpty
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_IsEmpty(void)
{
    if (CurtainSend.u8Head == CurtainSend.u8End && CurtainSend.u8QueueNum == CURTAIN_TX_QUEUE_MAX )
    {
        return OK;    //队列已满
    }
    else
    {
        return !OK;   //队列未满
    }
}
/**
  * @brief: 清除队列的数据
  * @param
  * @retval None
  */
void CurtainSendQueue_ClearID(void)
{
    uint8_t i;

    CurtainSend.u8Data[CurtainSend.u8Head].u8State   = 0;
    CurtainSend.u8Data[CurtainSend.u8Head].u8ByteMax = 0;
    CurtainSend.u8Data[CurtainSend.u8Head].u8MessageType = 0;

    for (i = 0 ;i < CURTAIN_RX_BUFF; i++)
    {
        CurtainSend.u8Data[CurtainSend.u8Head].u8Byte[i] = 0;
    }
}
/**
  * @brief: 设置发送队列的数据
  * @param
  * @retval None
  */
void CurtainSendQueue_SetID(void)
{
    CurtainSend.u8Data[CurtainSend.u8End].u8State   = 1;
}
/**
  * @brief: 入队  into 
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_IntoQueue(void)
{
    if ( OK == CurtainSendQueue_IsEmpty() )
    {
        return !OK;
    }
    
    CurtainSend.u8End++;
    
    if ( CurtainSend.u8End >= CURTAIN_TX_QUEUE_MAX )
    {
        CurtainSend.u8End = 0;
    }
    
    CurtainSend.u8QueueNum++;

    //CurtainSendQueue_SetID();
    return OK;
}
/**
  * @brief: 出队 out EnQueue
  * @param
  * @retval None
  */
uint8_t CurtainSendQueue_OutQueue(void)
{
    if ( OK == CurtainSendQueue_IsEmpty() )
    {
        return !OK;
    }
    
    CurtainSend.u8Head++;
    
    if ( CurtainSend.u8Head >= CURTAIN_TX_QUEUE_MAX )
    {
        CurtainSend.u8Head = 0;
    }

    CurtainSend.u8QueueNum--;

    CurtainSendQueue_ClearID();
    return OK;
}
/**
  * @brief: 入队数据处理   
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueData(uint8_t u8Code,uint8_t u8Cmd,uint8_t u8Data)
{
    uint8_t u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = (uint8_t)CURTAIN_MESSAGE_HEAD>>24 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = (uint8_t)CURTAIN_MESSAGE_HEAD>>16 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = (uint8_t)CURTAIN_MESSAGE_HEAD>>8  ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = (uint8_t)CURTAIN_MESSAGE_HEAD     ;

    if (CURTAIN_CMD_READ == u8Code)
    {
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
        u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 7);
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;

        CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    }
    else if (CURTAIN_CMD_SET == u8Code)
    {
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Data;
        u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 8);
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;

        CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    }
    else if (CURTAIN_CMD_CTRL == u8Code)
    {
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
        if (0x0C == u8Cmd)
        {
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Data;
            u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 8);
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;

            CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
        }
        else
        {
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
            u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 7);
            CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;

            CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
        }
    }

    //CurtainSendQueue_SetID();
    CurtainSendQueue_IntoQueue();

}

/**
  * @brief: 入队数据处理   查询数据
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataQuery(uint8_t u8Cmd)
{
    uint8_t u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = (uint8_t)CURTAIN_MESSAGE_HEAD>>24 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = (uint8_t)CURTAIN_MESSAGE_HEAD>>16 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = (uint8_t)CURTAIN_MESSAGE_HEAD>>8  ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = (uint8_t)CURTAIN_MESSAGE_HEAD     ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
    u8Crc                                           = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;

    //CurtainSendQueue_SetID();
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief: 入队数据处理   设置数据
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataSet(uint8_t u8Cmd,uint8_t u8Data)
{
    uint8_t u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = (uint8_t)CURTAIN_MESSAGE_HEAD>>24 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = (uint8_t)CURTAIN_MESSAGE_HEAD>>16 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = (uint8_t)CURTAIN_MESSAGE_HEAD>>8  ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = (uint8_t)CURTAIN_MESSAGE_HEAD     ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Data;
    u8Crc                                           = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;

    //CurtainSendQueue_SetID();
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief: 入队数据处理   控制
  * @param
  * @retval None
  */
void CurtainSendQueue_IntoQueueDataConyrol(uint8_t u8Cmd,uint8_t u8Data)
{
    uint8_t u8Crc;

    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = (uint8_t)CURTAIN_MESSAGE_HEAD>>24 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = (uint8_t)CURTAIN_MESSAGE_HEAD>>16 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = (uint8_t)CURTAIN_MESSAGE_HEAD>>8  ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = (uint8_t)CURTAIN_MESSAGE_HEAD     ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;

    if (0x0C == u8Cmd)
    {
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Data;
        u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 8);
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;

        CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    }
    else
    {
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = u8Cmd;
        u8Crc = CRC8Maxim_Check(CurtainSend.u8Data[CurtainSend.u8End].u8Byte, 7);
        CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;

        CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    }

    //CurtainSendQueue_SetID();
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:  出队数据处理
  * @param
  * @retval None
  */
void CurtainSendQueue_OutQueueData(void)
{
    uint8_t i;

    for (i = 0; i < CURTAIN_TX_BUFF; i++)
    {
        CURTAIN_UART.Frame.pu8Send[i] = CurtainSend.u8Data[CurtainSend.u8Head].u8Byte[i];
    }

    CURTAIN_UART.Frame.u16SendBytesMax = CurtainSend.u8Data[CurtainSend.u8Head].u8ByteMax;

    CurtainSendQueue_OutQueue();
}

/************************************************************************************/
/******************************  接收串口队列   **************************************/
/************************************************************************************/
/**
  * @brief: 发送队列初始化
  * @param
  * @retval None
  */

void CurtainReadQueue_Init(void)
{
    CurtainRead.u8Head = 0;
    CurtainRead.u8End  = 0;
    CurtainRead.u8QueueNum = 0;
}
/**
  * @brief: 判断队列是否为满 IsEmpty
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_IsEmpty(void)
{
    if (CurtainRead.u8Head == CurtainRead.u8End && CurtainRead.u8QueueNum == CURTAIN_RX_QUEUE_MAX )
    {
        return OK;    //队列已满
    }
    else
    {
        return !OK;   //队列未满
    }
}
/**
  * @brief: 清除队列的数据
  * @param
  * @retval None
  */
void CurtainReadQueue_ClearID(void)
{
    uint8_t i;

    CurtainRead.u8Data[CurtainRead.u8Head].u8State   = 0;
    CurtainRead.u8Data[CurtainRead.u8Head].u8ByteMax = 0;
    CurtainRead.u8Data[CurtainRead.u8Head].u8MessageType = 0;

    for (i = 0; i < CURTAIN_RX_BUFF; i++)
    {
        CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[i] = 0;
    }
}
/**
  * @brief: 设置发送队列的数据
  * @param
  * @retval None
  */
void CurtainReadQueue_SetID(void)
{
    CurtainRead.u8Data[CurtainRead.u8End].u8State   = 1;
}
/**
  * @brief: 入队  into 
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_IntoQueue(void)
{
    if ( OK == CurtainReadQueue_IsEmpty() )
    {
        return !OK;
    }
    
    CurtainRead.u8End++;
    
    if ( CurtainRead.u8End >= CURTAIN_TX_QUEUE_MAX )
    {
        CurtainRead.u8End = 0;
    }
    
    CurtainRead.u8QueueNum++;

    CurtainReadQueue_SetID();
    return OK;
}
/**
  * @brief: 入队数据处理   
  * @param
  * @retval None
  */
void CurtainReadQueue_IntoQueueData(void)
{
    uint8_t i;

    for (i = 0; i < CURTAIN_RX_BUFF; i++)
    {
        CurtainRead.u8Data[CurtainRead.u8End].u8Byte[i] = CURTAIN_UART.Frame.pu8Receive[i];
    }

    CurtainRead.u8Data[CurtainRead.u8End].u8ByteMax = CURTAIN_UART.Frame.u16ReceiveBytesMax;

    CurtainReadQueue_IntoQueue();
}

/**
  * @brief: 出队 out EnQueue
  * @param
  * @retval None
  */
uint8_t CurtainReadQueue_OutQueue(void)
{
    if ( OK == CurtainReadQueue_IsEmpty() )
    {
        return !OK;
    }
    
    CurtainReadQueue_ClearID();
    
    CurtainRead.u8Head++;
    
    if ( CurtainRead.u8Head >= CURTAIN_TX_QUEUE_MAX )
    {
        CurtainRead.u8Head = 0;
    }

    CurtainRead.u8QueueNum--;

    
    return OK;
}
/**
 * @brief: 出队数据处理
 * @param
 * @retval None
 */
uint8_t CurtainReadQueue_OutQueueData(void)
{
    uint32_t u32HeadMessage;
    uint8_t u8CRC;

    u32HeadMessage = CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[0] << 24 | CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[1] << 16 | CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[2] << 8 | CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[3];  

    if (0x5AA55AA5 == u32HeadMessage)
    {
        u8CRC = Curtain_CRC8(CurtainRead.u8Data[CurtainRead.u8Head].u8Byte, (CurtainRead.u8Data[CurtainRead.u8Head].u8ByteMax - 1));
        CurtainRun.u8CRCteat = u8CRC;
        
        if (u8CRC == CurtainRead.u8Data[CurtainRead.u8Head].u8Byte[CurtainRead.u8Data[CurtainRead.u8Head].u8ByteMax - 1])
        {
            if (OK == Curtain_Read_Unpack(CurtainRead.u8Data[CurtainRead.u8Head].u8Byte))
            {
                return OK;
            }
            else
            {
                return !OK;
            }
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return !OK;
}

/************************************************************************************/
/******************************  队列处理函数   **************************************/
/************************************************************************************/
/**
 * @brief:  队列处理函数
 * @param
 * @retval None
 */
uint8_t CurtainQueueRun(void)
{
    if ( 0x00 != CurtainRead.u8QueueNum  )
    {
        CurtainReadQueue_OutQueueData();  //接收队列
        CurtainReadQueue_OutQueue();
    }

    if ( 1 == CurtainSend.u8SendFlag && 0x00 != CurtainSend.u8QueueNum  )
    {
        CurtainSendQueue_OutQueueData(); //出队处理
        CurtainUsart_Send();             //串口发送
        CurtainSend.u8SendFlag = 0;

        CurtainRun.u8CurtainDropFlag = 1;   //掉线标志
    }
    
    return OK;

}



