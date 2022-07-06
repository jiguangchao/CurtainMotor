

/*!
*****************************************************************
						$Name$
						$Revision: 27601 $
						$Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
	\file 				Enocean_ESP.c
	\brief 				MSG management related functions
	\author 			zhoujinbang


    <b>Company:</b>\n	menred automation\n
修改记录
1、
2、
3、
4、
5、
6、
*****************************************************************/

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "BSP.h"
#include "main.h"
#include "CurtainInterface.h"
#include "CurtainProtocol.h"
#include "CurtainQueue.h"
#include "EnOceanTelegram.h"
#include "LED.h"

/*============================ MACROS ========================================*/
//#define IIC_NOTE       (0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/******************************************************************************/



uint8_t CURTAIN_TX_Buff[CURTAIN_TX_BUFF];
uint8_t CURTAIN_RX_Buff[CURTAIN_RX_BUFF];
uint8_t CURTAIN_DMABuff[CURTAIN_RX_BUFF];

CurtainRun_Typedef   CurtainRun;
CurtainData_Typedef  CurtainData;
USART_Function_Typedef CURTAIN_UART;

/**************************************************************************************/
/*                   窗帘串口初始化                                                   */
/*********************************************************************** **************/
/**
 * @brief
 * @param
 * @retval
 */
uint8_t CURTAIN_Init(USART_Function_Typedef *pUSART)
{
    pUSART->Frame.pu8Receive              = CURTAIN_RX_Buff;
    pUSART->Frame.pu8Send                 = CURTAIN_TX_Buff;
    pUSART->Frame.pu8DMAReceive           = CURTAIN_DMABuff;
    pUSART->Frame.u16ReceiveBuffMax       = CURTAIN_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig        = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.eBaudID];

    pUSART->SerialDevInit                 = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK               = CURTAINReceiveOK;
    pUSART->SerialDevError                = CURTAINDevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset                = CURTAINReset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart                        = BSP_CURTAINSendStart;
    pUSART->pStop                         = BSP_CURTAINSendStop;
    pUSART->pSend                         = BSP_CURTAINDirectSend;
    pUSART->pReceive                      = BSP_CURTAINDirectReceive;

    pUSART->pReceive();
    
    BSP_CURTAINUsartDMA_Init(CURTAIN_DMABuff,CURTAIN_TX_Buff);
    BSP_CURTAINUSART_Init((uint32_t)eBaudRateTab[pUSART->Frame.eBaudID], pUSART->Frame.eStop, pUSART->Frame.eParity);

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINSendOK(void)
{
    if (eSERIAL_BUS_STATE_SEND_DATA == CURTAIN_UART.Frame.eTxState)
    {
        CURTAIN_UART.Frame.eTxState = eSERIAL_BUS_STATE_SEND_DATA_OK;
        CURTAIN_UART.Frame.u8IdleNms = CURTAIN_UART.Frame.u8IdleNmsConfig;
        CURTAIN_UART.Frame.u8RxTxShiftNms = u8SerialRxTxShiftTimeConfigTab[CURTAIN_UART.Frame.eBaudID];
        return OK;
    }
    return !OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINReset(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINDevError(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINReceiveOK(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;
    /*
    uint32_t u32HeadMessage;
    uint8_t  u8CRC;
    u32HeadMessage = pSerial->pu8Receive[0] << 24 | pSerial->pu8Receive[1] << 16 | pSerial->pu8Receive[2] << 8 | pSerial->pu8Receive[3];    
    */
    //CurtainRun.u8CurtainDropFlag = 0;
    if (pSerial->u16ReceiveBytesMax >= 18)
    {
        if (pSerial->pu8Receive[13] == 0x04 )
        {
            if (pSerial->pu8Receive[15] == 0x05)
            {
                CurtainData.Query.u8MotorState = pSerial->pu8Receive[16] ;
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
    if ( 0x00 != pSerial->pu8Receive[0])
    {
        CurtainReadQueue_IntoQueueData();
    }
    
    
    /*
    if (0x5AA55AA5 == u32HeadMessage)
    {
        u8CRC = Curtain_CRC8(pSerial->pu8Receive, (pSerial->u16ReceiveBytesMax - 1));
        CurtainRun.u8CRCteat = u8CRC;

        if (u8CRC == pSerial->pu8Receive[pSerial->u16ReceiveBytesMax - 1])
        {
           if ( OK == Curtain_Read_Unpack(pSerial->pu8Receive))
           {
               CurtainRun.eFaultCode = eCURTAINRUN_NORMAL;
           }
           else
           {
               CurtainRun.eFaultCode = eCURTAINRUN_ABNORMAL_DATA;
           }
        }
        else
        {
            CurtainRun.eFaultCode = eCURTAINRUN_EXCEPTION_MESSAGE;
        }
    }
    else
    {
        CurtainRun.eFaultCode = eCURTAINRUN_EXCEPTION_MESSAGE;
    }
    */
    return OK;
}
/**
   * @brief
   * @param
   * @retval
   */
void CurtainRun_Tick1ms(CurtainRun_Typedef *pCurtainRun)
{
    if (pCurtainRun->u32CurtainRunWait)
    {
        pCurtainRun->u32CurtainRunWait--;
    }
    if (pCurtainRun->u32LEDFlashTime)
    {
        pCurtainRun->u32LEDFlashTime--;
    }

    pCurtainRun->u32SanCurtainRunStateTime++;
    if ( pCurtainRun->u32SanCurtainRunStateTime > 200 )
    {
        pCurtainRun->u32SanCurtainRunStateTime = 0;
        pCurtainRun->u8SanCurtainRunStateFlag  = 1;
    }
    
    
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Curtain_CRC8(uint8_t *ptr, uint8_t len)
{
    uint8_t crc = 0;
    uint8_t i;

    while (len--)
    {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++)
        {
            if (crc & 0x01)
            {
                crc = crc >> 1;
                crc = crc ^ 0x8c;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**************************************************************************************/
/*                   窗帘接收函数                                                   */
/*********************************************************************** **************/
/**
 * @brief   判断窗帘是否运行到端点
 * @param
 * @retval
 */
uint8_t CurtainRunLimit(void)
{
    if (CurtainData.Query.u32UpLimit > CurtainData.Query.u32DownLimit)
    {
        if (CurtainData.Query.u32RealtimeLimt == CurtainData.Query.u32UpLimit + 0x2000000 
        || CurtainData.Query.u32RealtimeLimt == CurtainData.Query.u32DownLimit - 0x2000000 
        || CurtainData.Query.u32RealtimeLimt == 0x00008000)
        {
            CurtainRun.u8MotorStateFlag = 0;
            CurtainRun.eRunState        = eCURTAINRUN_CURTAIN_QUERYB;
            return OK;
        }
    }
    /*
    else if (CurtainData.Query.u32UpLimit < CurtainData.Query.u32DownLimit)
    {
        if (CurtainData.Query.u32RealtimeLimt == CurtainData.Query.u32UpLimit - 0x2000000 
        || CurtainData.Query.u32RealtimeLimt == CurtainData.Query.u32DownLimit + 0x2000000 
        || CurtainData.Query.u32RealtimeLimt == 0x00008000)
        {
            CurtainRun.u8MotorStateFlag = 0;
            return OK;
        }        
    }
    */
    return !OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Read_Unpack(uint8_t *p8ReceiveBuff)   //接收拆包
{

    switch (p8ReceiveBuff[4])
    {
    case CURTAIN_CMD_REPORT:
        if (OK == Curtain_Reply_Report(p8ReceiveBuff))
        {
            return OK;
        }
        break;

    case CURTAIN_CMD_REPLY_READ:
        if (OK == Curtain_Reply_Query(p8ReceiveBuff))
        {
            return OK;
        }
        break;
    
    case CURTAIN_CMD_REPLY_CTRL:
        if (OK == Curtain_Reply_Conyrol(p8ReceiveBuff))
        {
            return OK;
        }   
        break; 

    case CURTAIN_CMD_REPLY_SET:
        if (OK == Curtain_Reply_Set(p8ReceiveBuff))
        {
            return OK;
        }
        break; 

    default:
        return !OK;
        break;
    }
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Report(uint8_t *p8ReceiveBuff) //接收回复查询数据
{
    uint8_t u8FunctionCode;

    u8FunctionCode = p8ReceiveBuff[6];

    switch (u8FunctionCode)
    {
    case 0x01: //上限位/
        CurtainData.Query.u32UpLimit = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x02: //下限位
        CurtainData.Query.u32DownLimit = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x03: //第三限位
        CurtainData.Query.u32ThirdLimt = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x04: //实时位置
        CurtainData.Query.u32RealtimeLimt = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x05: //电机运行状态
        CurtainData.Query.u8MotorState = p8ReceiveBuff[7];
        CurtainRun.u8MotorStateFlag = CurtainData.Query.u8MotorState;
        break;

    case 0x06: //电机运行方向
        CurtainData.Query.u8MotorDirection = p8ReceiveBuff[7];
        break;

    case 0x07: //强电模式
        CurtainData.Query.u8HighVoltageMode = p8ReceiveBuff[7];
        break;

    case 0x08: //弱电模式
        CurtainData.Query.u8LowVoltageMode = p8ReceiveBuff[7];
        break;

    case 0x13: //手拉模式
        CurtainData.Set.u8SetManualMode = p8ReceiveBuff[7];
        break;

    case 0x15: //按键按下
        CurtainRun.u8ButtonFlag = 0x01;
        break;

    case 0x16: //按键松开
        CurtainRun.u8ButtonFlag = 0x00;
        break;

    case 0x17: //手拉开关

        break;
    case 0x18: //回复出厂设置

        break;

    default:
        break;
    }
    return OK;
}

/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Query(uint8_t * p8ReceiveBuff) //接收回复查询数据
{
    uint8_t u8FunctionCode;

    u8FunctionCode = p8ReceiveBuff[6];

    switch (u8FunctionCode)
    {
    case 0x01: //上限位
        CurtainData.Query.u32UpLimit = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x02: //下限位
        CurtainData.Query.u32DownLimit = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x03: //第三限位
        CurtainData.Query.u32ThirdLimt = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x04: //实时限位
        CurtainData.Query.u32RealtimeLimt = p8ReceiveBuff[7] << 24 | p8ReceiveBuff[8] << 16 | p8ReceiveBuff[9] << 8 | p8ReceiveBuff[10];
        break;

    case 0x05: //电机运行状态
        CurtainData.Query.u8MotorState = p8ReceiveBuff[7];
        break;

    case 0x06: //电机运行方向
        CurtainData.Query.u8MotorDirection = p8ReceiveBuff[7];
        break;

    case 0x07: //强电模式
        CurtainData.Query.u8HighVoltageMode = p8ReceiveBuff[7];
        break;

    case 0x08: //弱电模式
        CurtainData.Query.u8LowVoltageMode = p8ReceiveBuff[7];
        break;

    case 0x09: //窗帘百分比位置
        CurtainRun.u8CurtainDropFlag  = 0;
        CurtainRun.u32CurtainDropTime = 0;
        CurtainRun.u8CurtainDropCount = 0;
        CurtainRun.eFaultCode         = eCURTAINRUN_NORMAL;

        CurtainData.Query.u8CurtainPercentage = p8ReceiveBuff[7];
        JudgeCurtainRunState();
        //JudgeEnoceanControl();
        break;

    case 0xA0: //窗帘类型
        CurtainData.Query.u8CurtainType = p8ReceiveBuff[7];
        break;

    case 0x17: //软件版本
        CurtainData.Query.u32SoftwareVersion = p8ReceiveBuff[7] << 16 | p8ReceiveBuff[8] << 8 | p8ReceiveBuff[9] ;
        break;

    case 0x18://eREMOTE_BATTERY_STATE: //电池电量
        CurtainData.Query.u8BatteryPower = p8ReceiveBuff[7];
        break;
    default:
        break;
    }
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Conyrol(uint8_t * p8ReceiveBuff) //接收回复控制数据
{
    uint8_t u8FunctionCode;

    u8FunctionCode = p8ReceiveBuff[6];

    switch (u8FunctionCode)
    {
    case 0x09: //上运行回复
        if (0x09 == p8ReceiveBuff[6])
        {
            return OK;
        }
        return !OK;
        break;
    case 0xA0: //下运行回复
        if (0x0A == p8ReceiveBuff[6])
        {
            return OK;
        }
        return !OK;
        break;
    case 0xB0: //停止运行回复
        if (0x0B == p8ReceiveBuff[6])
        {
            return OK;
        }
        return !OK;
        break;
    case 0xC0: //百分比
        if (CurtainData.Conyrol.u8Percentage == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x18: //电动回复
        if (CurtainData.Conyrol.u8Jog == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;

    default:
        return !OK;
        break;
    }
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Set(uint8_t * p8ReceiveBuff) //接收回复设置数据
{
    uint8_t u8FunctionCode;

    u8FunctionCode = p8ReceiveBuff[6];

    switch (u8FunctionCode)
    {
    case 0x0D: //设置上限位回复
        if (CurtainData.Set.u8SetUpLimit == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x0E: //设置下限位回复
        if (CurtainData.Set.u8SetDownLimit == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x0F: //设置第三限位
        if (CurtainData.Set.u8SetThirdLimit == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x10: //设置电机运行方向
        if (CurtainData.Set.u8SetMotorDirection == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x11: //设置强电模式
        if (CurtainData.Set.u8SetHighVoltageMode == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x12: //设置弱电模式
        if (CurtainData.Set.u8SetLowVoltageMode == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x13: //设置手拉模式
        if (CurtainData.Set.u8SetManualMode == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x14: //设置指示灯
        if (CurtainData.Set.u8SetLndicatorLED == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;

    case 0x15: //设置学习状态
        CurtainData.Set.u8SetLearnState = p8ReceiveBuff[7];
        EnoceanRemanMotorLearnDev_333(&Radio);
        EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM, &Radio);
        return OK;
        break;
        
    case 0x16: //删除行程
        if (CurtainData.Set.u8SetDeleteTrip == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;
    case 0x17: //设置窗帘类型
        if (CurtainData.Set.u8SetCurtainType == p8ReceiveBuff[7])
        {
            return OK;
        }
        return !OK;
        break;

    default:
        return !OK;
        break;
    }
}
/**************************************************************************************/
/*                   窗帘运行函数                                                   */
/*********************************************************************** **************/

/**
 * @brief    窗帘运行测试状态机
 * @param
 * @retval   
 */
void Curtain_SetState_Test(CurtainRun_Typedef *pCurtainRun) 
{
    switch (pCurtainRun->eRunStateTest)
    {
    case eCURTAINRUN_TEST_IDLE:
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINON;
        break;
        /*      控制打开窗帘        */
    case eCURTAINRUN_TEST_CURTAINON:

        CurtainSendQueueControlOn();
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINON_WAIT;
        pCurtainRun->u32CurtainRunWait = CURTAIN_RUN_TEST_TIME;
        break;   

    case eCURTAINRUN_TEST_CURTAINON_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINSTOP_A;
        break;

                /*      控制停止窗帘        */   
    case eCURTAINRUN_TEST_CURTAINSTOP_A:

        CurtainSendQueueControlStop();
        pCurtainRun->u32CurtainRunWait = CURTAIN_RUN_TEST_TIME;
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINSTOP_WAIT_A;
        break;        

    case eCURTAINRUN_TEST_CURTAINSTOP_WAIT_A:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINOFF ;
        break;

    /*      控制关闭窗帘        */
    case eCURTAINRUN_TEST_CURTAINOFF:

        CurtainSendQueueControlOff();
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINOFF_WAIT;
        pCurtainRun->u32CurtainRunWait = CURTAIN_RUN_TEST_TIME;
        break;

    case eCURTAINRUN_TEST_CURTAINOFF_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINSTOP_B;
        break;

     /*      控制停止窗帘        */   
    case eCURTAINRUN_TEST_CURTAINSTOP_B:

        CurtainSendQueueControlStop();
        pCurtainRun->u32CurtainRunWait = CURTAIN_RUN_TEST_TIME;
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINSTOP_WAIT_B;
        break;        

    case eCURTAINRUN_TEST_CURTAINSTOP_WAIT_B:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        pCurtainRun->eRunStateTest = eCURTAINRUN_TEST_CURTAINON ;
        break;


    default:
        break;
    }

}
/**
 * @brief    窗帘控制状态机
 * @param
 * @retval   
 */
uint8_t Curtain_ControlState(CurtainRun_Typedef *pCurtainRun) 
{

    if ( pCurtainRun->eRunState >= eCURTAINRUN_SETTRIP_START && pCurtainRun->eRunState <= eCURTAINRUN_SETTRIP_UP_WAIT )
    {
        return !OK;
    }
    

    switch ( pCurtainRun->eControlState )
    {
    case eCURTAINCONTROL_IDLE:
        //pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        break;
        /*      控制打开窗帘        */
    case eCURTAINRUN_CURTAINON:

        CurtainSendQueueControlOn();
        pCurtainRun->eControlState = eCURTAINCONTROL_IDLE;
        break;   


    /*      控制关闭窗帘        */
    case eCURTAINRUN_CURTAINOFF:

        CurtainSendQueueControlOff();
        pCurtainRun->eControlState = eCURTAINCONTROL_IDLE;
        break;



    /*      百分比控制窗帘        */
    case eCURTAINRUN_CURTAINPERCENTAGE:

        CurtainSendQueueControlSetPercent(pCurtainRun->u8CurtainPercentage);
        pCurtainRun->eControlState = eCURTAINCONTROL_IDLE;
        break;   




    /*      控制停止窗帘        */   
    case eCURTAINRUN_CURTAINSTOP:

        CurtainSendQueueControlStop();
        pCurtainRun->eControlState = eCURTAINCONTROL_IDLE;
        break;        


    default:
        pCurtainRun->eControlState = eCURTAINCONTROL_IDLE;
        break;
    }
    return  OK;
}


/**
 * @brief    窗帘运行状态机
 * @param
 * @retval   
 */
void Curtain_SetState(CurtainRun_Typedef *pCurtainRun) 
{
    //JudgeCurtainRunState();
    
    if ( 1 == pCurtainRun->u8SanCurtainRunStateFlag )
    {
        //JudgeCurtainRunState();
        JudgeEnoceanControl();
        pCurtainRun->u8SanCurtainRunStateFlag = 0;
    }

    switch (pCurtainRun->eRunState)
    {
    case eCURTAINRUN_IDLE:
        pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        break;

    /*   轮询查询数据  */
    case eCURTAINRUN_POLL_QUERY:
        Curtain_PowerON_Poll(pCurtainRun);
        pCurtainRun->u8PowerONPollCount++;
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY_WAIT;
        break;

    case eCURTAINRUN_POLL_QUERY_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        if (pCurtainRun->u8PowerONPollCount > 13 )
        {
            //pCurtainRun->eRunState = eCURTAINRUN_IDLE;
            pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB;
            pCurtainRun->u8PowerONPollCount = 0;
            break;   
        }
        pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        break;


    /*   设置上限位  */
    case eCURTAINRUN_SET_UPLIMIT:

        if (0x00 == CurtainData.Query.u8MotorState)
        {
            CurtainSendQueueSetLimitUp(CurtainData.Set.u8SetUpLimit);
            ////CurtainUsart_Send();
            pCurtainRun->u32CurtainRunWait = 100;
            pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
            break;
        }
        else
        {
            pCurtainRun->eRunState = eCURTAINRUN_IDLE;
            break;
        }
        break;

    /*   设置下限位  */
    case eCURTAINRUN_SET_DOWNLIMIT:

        if (CurtainData.Query.u8MotorState == 0x00)
        {
            CurtainSendQueueSetLimitDown(CurtainData.Set.u8SetDownLimit);
            //CurtainUsart_Send();
            pCurtainRun->u32CurtainRunWait = 100;
            pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
            break;
        }
        else
        {
            pCurtainRun->eRunState = eCURTAINRUN_IDLE;
            break;
        }
        break;

    /*   设置第三限位  */
    case eCURTAINRUN_SET_THIRDLIMIT:

        if (CurtainData.Query.u8MotorState == 0x00)
        {
            if (CurtainData.Query.u32UpLimit == 0x00FFFF00 && CurtainData.Query.u32DownLimit == 0xFF000000)
            {
                if (CurtainData.Query.u32ThirdLimt == 0x00008000)
                {
                    CurtainData.Set.u8SetThirdLimit = 0x01;
                }
                if (CurtainData.Query.u32UpLimit > CurtainData.Query.u32ThirdLimt && CurtainData.Query.u32DownLimit < CurtainData.Query.u32ThirdLimt)
                {
                    CurtainData.Set.u8SetThirdLimit = 0x01;
                }
            }

            if (CurtainData.Set.u8SetDownLimit == 0x01)
            {
                CurtainSendQueueSetLimitUp(CurtainData.Set.u8SetUpLimit);
                //CurtainUsart_Send();
                pCurtainRun->u32CurtainRunWait = 100;
                pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
                break;
            }
        }
        else
        {
            pCurtainRun->eRunState = eCURTAINRUN_IDLE;
            break;
        }
        break;

    /*     设置电机运转方向        */
    case eCURTAINRUN_SET_DIRECTION:

        CurtainSendQueueSetDirect(CurtainData.Set.u8SetMotorDirection);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break;

    /*     设置强电模式        */
    case eCURTAINRUN_SET_HIGHMODE:

        CurtainSendQueueSetHighPowerMode(CurtainData.Set.u8SetHighVoltageMode);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break;    

    /*     设置弱电模式        */
    case eCURTAINRUN_SET_LOWMODE:

        CurtainSendQueueSetSmallPowerMode(CurtainData.Set.u8SetLowVoltageMode);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break;       

    /*     设置手拉模式        */
    case eCURTAINRUN_SET_MANUALMODE:

        CurtainSendQueueSetHandOnOff(CurtainData.Set.u8SetManualMode);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break;     

    /*     设置学习模式        */
    case eCURTAINRUN_SET_LEARNSTATE:

        CurtainSendQueueSetMotorLearn();
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break; 

    /*     设置删除行程        */
    case eCURTAINRUN_SET_DELETETRIP:

        CurtainSendQueueSetDeleteRoute(CurtainData.Set.u8SetDeleteTrip);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break; 

    /*     设置窗帘类型        */
    case eCURTAINRUN_SET_CURTAINTYPE:

        CurtainSendQueueSetDeleteRoute(CurtainData.Set.u8SetCurtainType);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 100;
        pCurtainRun->eRunState = eCURTAINRUN_SET_WAIT;
        break;         


    /*     设置等待命令        */
    case eCURTAINRUN_SET_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }  
        pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        break;

#if 0
    /*      控制打开窗帘        */
    case eCURTAINRUN_CURTAINON:

        CurtainSendQueueControlOn();
        pCurtainRun->u8MotorStateFlag = 1;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAINON_WAIT;
        pCurtainRun->u32CurtainRunWait = 100;
        break;   

    case eCURTAINRUN_CURTAINON_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE ;
        //pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        //pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYA;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB;
        break;



    /*      控制关闭窗帘        */
    case eCURTAINRUN_CURTAINOFF:

        CurtainSendQueueControlOff();
        pCurtainRun->u8MotorStateFlag = 1;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAINOFF_WAIT;
        pCurtainRun->u32CurtainRunWait = 100;
        break;

    case eCURTAINRUN_CURTAINOFF_WAIT:

        
        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE ;
        //pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        //pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYA;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB;
        break;
        /*
        if (CurtainData.Query.u8MotorState == 0)
        {
            pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY ;
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE ;
        break;
        */

    /*      百分比控制窗帘        */
    case eCURTAINRUN_CURTAINPERCENTAGE:
        /*
        if (CurtainData.Query.u32UpLimit != 0x00FFFF00 || CurtainData.Query.u32DownLimit != 0xFF000000 )
        {
            CurtainSendQueueControlSetPercent(&CURTAIN_UART.Frame, 0x64);
        }
        else
        {
            CurtainSendQueueControlOn(&CURTAIN_UART.Frame);
        }
        */
        CurtainSendQueueControlSetPercent(pCurtainRun->u8CurtainPercentage);
        //CurtainUsart_Send();
        pCurtainRun->u8MotorStateFlag = 1;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAINON_WAIT;
        pCurtainRun->u32CurtainRunWait = 100;
        break;   

    case eCURTAINRUN_CURTAINPERCENTAGE_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE ;
        //pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        //pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYA;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB;
        break;


    /*      控制停止窗帘        */   
    case eCURTAINRUN_CURTAINSTOP:

        CurtainSendQueueControlStop();
        //CurtainUsart_Send();
        pCurtainRun->u8MotorStateFlag = 0;
        pCurtainRun->u32CurtainRunWait = 120;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAINSTOP_WAIT;
        break;        

    case eCURTAINRUN_CURTAINSTOP_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE ;
        //pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY ;
        //pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYA ;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB ;
        break;

#endif

    case eCURTAINRUN_CURTAIN_QUERYB://查询电机百分比位置 

        CurtainSendQueueQueryLocation();
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 150;
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB_WAIT;
        break;

    case eCURTAINRUN_CURTAIN_QUERYB_WAIT://查询等待 

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        } 
        if ( OK == DropFault_Deal() )
        {
            break;
        }
  
        pCurtainRun->eRunState = eCURTAINRUN_CURTAIN_QUERYB;
        break;
        






    /*        设置行程命令          */
    case eCURTAINRUN_SETTRIP_START:   //清除行程

        CurtainSendQueueSetDeleteRoute(0x00);
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 5000;
        BSP_LEDON_RED();
        //LED_Slow_Blink(&LED,10);
        pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_START_WAIT;
        break;  

    case eCURTAINRUN_SETTRIP_START_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        //pCurtainRun->eRunState = eCURTAINRUN_IDLE;
        pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_DOWN;
        break;     

    case eCURTAINRUN_SETTRIP_DOWN:

        CurtainSendQueueControlOff();
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 20*1000; //10S
        pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_DOWN_WAIT;
        break;  

    case eCURTAINRUN_SETTRIP_DOWN_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        if (CurtainData.Query.u8MotorState == 0)
        {
            pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_UP;
        }
        break;       

    case eCURTAINRUN_SETTRIP_UP:

        CurtainSendQueueControlOn();
        //CurtainUsart_Send();
        pCurtainRun->u32CurtainRunWait = 20*1000; //10S
        pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_UP_WAIT;
        break;  

    case eCURTAINRUN_SETTRIP_UP_WAIT:
   
        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        if (CurtainData.Query.u8MotorState == 0)
        {
            BSP_LEDOFF_RED();
            pCurtainRun->eRunState = eCURTAINRUN_POLL_QUERY;
        }
        break;        

    /*       出厂自检测试电机          */
    case eCURTAINRUN_HWTEST_FORWARD:

        CurtainSendQueueControlOn();
        //CurtainUsart_Send();
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_FORWARD_WAIT;
        pCurtainRun->u32CurtainRunWait = 2000;
        break;

    case eCURTAINRUN_HWTEST_FORWARD_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_FORWARD_STOP;
        break;    

    case eCURTAINRUN_HWTEST_FORWARD_STOP:

        CurtainSendQueueControlStop();
        //CurtainUsart_Send();
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_FORWARD_STOP_WAIT;
        pCurtainRun->u32CurtainRunWait = 100;
        break;

    case eCURTAINRUN_HWTEST_FORWARD_STOP_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_REVERSE;
        break;            

    case eCURTAINRUN_HWTEST_REVERSE:

        CurtainSendQueueControlOff();
        //CurtainUsart_Send();
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_REVERSE_WAIT;
        pCurtainRun->u32CurtainRunWait = 1500;
        break;

    case eCURTAINRUN_HWTEST_REVERSE_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_REVERSE_STOP;
        break;        

    case eCURTAINRUN_HWTEST_REVERSE_STOP:

        CurtainSendQueueControlStop();
        //CurtainUsart_Send();
        pCurtainRun->eRunState = eCURTAINRUN_HWTEST_REVERSE_STOP_WAIT;
        pCurtainRun->u32CurtainRunWait = 100;
        break;

    case eCURTAINRUN_HWTEST_REVERSE_STOP_WAIT:

        if (pCurtainRun->u32CurtainRunWait != 0)
        {
            break;
        }
        if ( OK == DropFault_Deal() )
        {
            break;
        }
        pCurtainRun->eRunState = eCURTAINRUN_IDLE;
        break;                 

    default:
        break;
    }
}
/**
 * @brief   窗帘电机上电轮询
 * @param
 * @retval
 */
void Curtain_PowerON_Poll(CurtainRun_Typedef *pCurtainRun)
{
    switch (pCurtainRun->u8PowerONPollCount)
    {
    case 0x00:
        CurtainSendQueueQueryLimitUp();
        break;
    case 0x01:
        CurtainSendQueueQueryLimitDown();
        break;
    case 0x02:
        CurtainSendQueueQueryLimitThrid();
        break;
    case 0x03:
        CurtainSendQueueQueryRunLimit();
        break;                    
    case 0x04:
        CurtainSendQueueQueryRunState();
        break;        
    case 0x05:
        CurtainSendQueueQueryDirect();
        break;
    case 0x06:
        CurtainSendQueueQueryHighPowerMode();
        break;
    case 0x07:
        CurtainSendQueueQuerySmallPowerMode();
        break;
    case 0x08:
        CurtainSendQueueQueryLocation();
        break;        
    case 0x09:
        CurtainSendQueueQueryCurtainType();
        break;    
    case 0x0A:
        CurtainSendQueueQuerySoftVersion();
        break;    
    case 0x0B:
        CurtainSendQueueQueryBattery();
        break;  
    case 0x0C:
        //CurtainSendSetDeleteRoute(&CURTAIN_UART.Frame,0x00);
        break;                        

    default:
        break;
    }
    //CurtainUsart_Send();

    if (CurtainData.Query.u32UpLimit == 0x00FFFF00)
    {
        CurtainData.Set.u8SetUpLimit = 0x00;
    }
    if (CurtainData.Query.u32DownLimit == 0xFF000000)
    {
        CurtainData.Set.u8SetDownLimit = 0x00;
    }
    if (CurtainData.Query.u32ThirdLimt == 0x00008000)
    {
        CurtainData.Set.u8SetThirdLimit = 0x00;
    }
}


/**
  * @brief   手动设置模式扫描
  * @param
  * @retval None     
  */
void ManualSetMode_Scan(CurtainRun_Typedef *pCurtainRun)
{

    switch (pCurtainRun->eManualSetRun)
    {
    case eMANUAL_SET_NONE :

        break;

    case eMANUAL_SET_MOTORDIRECTION: //设置换向

        if (CurtainData.Set.u8SetMotorDirection == 0x00)
        {
            CurtainData.Set.u8SetMotorDirection = 0x01;
        }
        else if(CurtainData.Set.u8SetMotorDirection == 0x01)
        {
            CurtainData.Set.u8SetMotorDirection = 0x00;
        }
        pCurtainRun->eRunState = eCURTAINRUN_SET_DIRECTION;
        LED_Slow_Blink(&LED,5);
        Dev.u8PassiveSwitchSetModeFalg = 0;
        pCurtainRun->eManualSetRun = eMANUAL_SET_NONE;
        break;

    case eMANUAL_SET_MANUALMODE:  //设置轻触功能

        if (CurtainData.Set.u8SetManualMode == 0x00)
        {
            CurtainData.Set.u8SetManualMode = 0x01;
        }
        else if(CurtainData.Set.u8SetManualMode == 0x01)
        {
            CurtainData.Set.u8SetManualMode = 0x00;
        }
        pCurtainRun->eRunState = eCURTAINRUN_SET_MANUALMODE;
        LED_Slow_Blink(&LED,5);
        Dev.u8PassiveSwitchSetModeFalg = 0;
        pCurtainRun->eManualSetRun = eMANUAL_SET_NONE;
        break;

    case eMANUAL_SET_SETTRIP:  //设置行程

        pCurtainRun->eRunState = eCURTAINRUN_SETTRIP_START;
        LED_Slow_Blink(&LED,5);
        Dev.u8PassiveSwitchSetModeFalg = 0;
        pCurtainRun->eManualSetRun = eMANUAL_SET_NONE;
        break;

    default:
        break;
    }

    
}
/**
 * @brief   掉线故障处理
 * @param
 * @retval
 */
uint8_t DropFault_Deal(void)
{
    /*
    if (CurtainRun.u8CurtainDropFlag != 0)
    {
        CurtainRun.u8CurtainDropCount++;
        if (CurtainRun.u8CurtainDropCount > 5 )
        {
            CurtainRun.u8CurtainDropCount = 0;
            CurtainRun.eFaultCode = eCURTAINRUN_EQUIPMENT_DROPS;
        }
        CurtainRun.eRunState  = CurtainRun.eRecordLastRunState;
        return OK;
    }    
    else
    {
        return !OK;
    }
    */
    return !OK;
}
/**
 * @brief   窗帘电机串口发送
 * @param
 * @retval
 */
void CurtainUsart_Send(void)
{
    //CurtainRun.u8CurtainDropFlag = 1;    //串口掉线标记
    CurtainRun.u8CurtainDropFlag = 0;   
    
    USART_StateSetSend(&CURTAIN_UART.Frame, CURTAIN_UART.Frame.u16SendBytesMax, 0, 0);
}
/**
 * @brief    判断窗帘的运行状态judge
 * @param
 * @retval
 */
uint8_t JudgeCurtainRunState(void)
{
    //CurtainRun.u32RecordCurtainLocation = CurtainData.Query.u32RealtimeLimt ; //记录当前窗帘的位置
    CurtainRun.u8RecordCurtainLocation = CurtainData.Query.u8CurtainPercentage ; //记录当前窗帘的百分比位置

    
    if ( CurtainRun.u8RecordCurtainLocation > CurtainRun.u8RecordLastCurtainLocation )
    {
        CurtainRun.u8RecordLastCurtainLocation = CurtainRun.u8RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_ON;
        return OK;
    }
    else if ( CurtainRun.u8RecordCurtainLocation < CurtainRun.u8RecordLastCurtainLocation )
    {
        CurtainRun.u8RecordLastCurtainLocation = CurtainRun.u8RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_OFF;
        return OK;
    }    
    else if (  CurtainRun.u8RecordCurtainLocation == CurtainRun.u8RecordLastCurtainLocation )
    {
        CurtainRun.u8RecordLastCurtainLocation = CurtainRun.u8RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_MID;
        return OK;
    }   
    
#if 0    
    //if ( CurtainRun.u8RecordCurtainLocation < 0x01  && CurtainRun.eCurtainRunSteta != eCURTAIN_RUN_ON )
    if ( CurtainRun.u32RecordCurtainLocation < CurtainData.Query.u32DownLimit )
    {
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_DOWN;   
        return OK;
    }
    //else if ( CurtainRun.u8RecordCurtainLocation > 0x63 &&  CurtainRun.eCurtainRunSteta != eCURTAIN_RUN_OFF )
    else if ( CurtainRun.u32RecordCurtainLocation > CurtainData.Query.u32UpLimit )
    {
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_UP;
        return OK;
    }
    else if ( CurtainRun.u32RecordCurtainLocation > CurtainRun.u32RecordLastCurtainLocation )
    {
        CurtainRun.u32RecordLastCurtainLocation = CurtainRun.u32RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_ON;
        return OK;
    }
    else if ( CurtainRun.u32RecordCurtainLocation < CurtainRun.u32RecordLastCurtainLocation )
    {
        CurtainRun.u32RecordLastCurtainLocation = CurtainRun.u32RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_OFF;
        return OK;
    } 
    else if ( CurtainRun.u32RecordCurtainLocation < CurtainData.Query.u32UpLimit 
           && CurtainRun.u32RecordCurtainLocation > CurtainData.Query.u32DownLimit 
           && CurtainRun.u32RecordCurtainLocation == CurtainRun.u32RecordLastCurtainLocation )
    {
        CurtainRun.u32RecordLastCurtainLocation = CurtainRun.u32RecordCurtainLocation ;
        CurtainRun.eCurtainRunSteta            = eCURTAIN_RUN_MID;
        return OK;
    }  
#endif

    return !OK;
}
/**
 * @brief    判断Enceoan控制没有生效后补发数据
 * @param
 * @retval
 */
uint8_t JudgeEnoceanControl(void)
{


    if ( CurtainRun.eEnoceanControl == eENOCEAN_CONTROL_ON )
    {
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_ON )
        {
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_IDLE;
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
            //CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_ON;
            return OK;
        }
    }

    if ( CurtainRun.eEnoceanControl == eENOCEAN_CONTROL_OFF )
    {
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_OFF )
        {
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_IDLE;
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
            //CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_OFF;
            return OK;
        }
    }

    if ( CurtainRun.eEnoceanControl == eENOCEAN_CONTROL_STOP )
    {
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_MID  )
        {
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_IDLE;
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP;
            //CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_MID;
            return OK;
        }
    }
    /*
    if ( CurtainRun.eEnoceanControl == eENOCEAN_CONTROL_PERCENTAGE )
    {
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_ON || CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_OFF )
        {
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_IDLE;
            return OK;
        }
        else
        {
            CurtainRun.eRunState = eCURTAINRUN_CURTAIN_QUERYB;
            return OK;
        }
    }
    */
    
    return !OK;
}





