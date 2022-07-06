

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
#include "EnOceanlibInclude.h"
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "EnOceanTelegram.h"
#include "EnOceanMSC.h"
#include "CurtainInterface.h"
#include "Button.h"
#include "LED.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*============================ IMPLEMENTATION ================================*/

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanDebug(void);

/*============================ IMPLEMENTATION ================================*/
/**
  * @brief 
  * @param
  * @retval None
  */
void EnoceanPassiveSwitchSetTime_1ms(void)
{
    if (Dev.u32PassiveSwitchSetTime)
    {
        Dev.u32PassiveSwitchSetTime--;
    }

    if (Dev.u32RemoteControlLreanTime)
    {
        Dev.u32RemoteControlLreanTime--;
    }

    if (Dev.u32PassiveSwitchSetContinuedTime)
    {
        Dev.u32PassiveSwitchSetContinuedTime--;
    }

    if (Dev.u32ManualLearnTiming)
    {
        Dev.u32ManualLearnTiming--;

        if ( 0x00 == Dev.u8ManualLearnState)
        {
            Dev.u32ManualLearnTiming = 0;
        }
        
    }
    
}
/**
  * @brief
  * @param
  * @retval None
  * 清理各个标记位
  */
void ClearAllFlag(void)
{
    if (Dev.u32RemoteControlLreanTime == 0x00 )
    {
        CurtainData.Set.u8SetLearnState = 0;    
    }

    if (Dev.u32PassiveSwitchSetTime == 0x00 )
    {
        Dev.u8PassiveSwitchSetCount = 0;
        //Dev.u8PassiveSwitchSetModeFalg = 0;
    }    

    if (Dev.u32PassiveSwitchSetContinuedTime == 0x00)
    {
        Dev.u8PassiveSwitchSetModeFalg = 0;
    }
    
    if (Dev.u32ManualLearnTiming == 0x00)
    {
        Dev.u8ManualLearnState = 0x00;
        Button.u8ResrtFlag     = 0x00;
    }
    
}
/**
  * @brief  EnOcean学习发送
  * @param
  * @retval None
  */
void EnOceanLearnSend(void)
{
    if (Dev.u8State == 1)
    {  
        if (0 == Dev.u8LearnAutoSendEEPTime)
        {
            /* 30*0.1s = 3s send the learn telegram */
            Dev.u8LearnAutoSendEEPTime = 30;
            Dev.u8State = 0;
            
            EnOceanDevSendEEPInfo2GateWay(&Radio, CURTAIN_EEP, 0);
            EnOceanUTERadioData(&Radio, 0);
        }
    }
    
    if (!Dev.u8LearnSuccessTime)
    {
        Dev.u8LearnState = 0;
    }
}


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMapChannel(uint8_t u8MapChannel, uint8_t *pu8IOChannel, uint8_t u8CascadeAdd)
{
    uint8_t u8Channel;

    u8Channel = u8MapChannel;

    if (0 == u8Channel)
    {
        return OK;
    }

    return !OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMSC(Radio_Typedef *pRadio)
{

    uint16_t u16ManID;
    //uint8_t u8BaseOffsetID;
    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;

    uint8_t u8Cmd;
    //uint8_t u8BuffChannel;
    //uint8_t u8MSCChannel;

    u8Cmd = pRadio->Telegram.raw.bytes[1] & 0x0F;
    //u8MSCChannel = pRadio->Telegram.raw.bytes[2];

    u16ManID = ((uint16_t)pRadio->Telegram.raw.bytes[0] << 4) | ((uint16_t)(pRadio->Telegram.raw.bytes[1] & 0xF0) >> 4);
    if (ENOCEAN_MENRED_MAN_ID != u16ManID)
    {
        return !OK;
    }

    EnOceanGetHWBaseID(&u32EnOceanBaseID);
    EnOceanGetHWChipID(&u32EnOceanChipID);

    if (pRadio->Param.p_rx.u32DestinationId == u32EnOceanChipID)
    {
        // EnOceanRadioMapChannel(u8MSCChannel,&u8BuffChannel,Dev.Cfg.u8CascadePhyAdd);
        if (eMSC_CMD_WRITE == u8Cmd)
        {
            if (OK == EnOceanMSCWrite(&Radio, &Dev))
            {
                /* Only save profile parameter */
                return OK;
            }
        }
        else if (eMSC_CMD_READ == u8Cmd)
        {
            if (OK == EnOceanMSCResponse(&Radio, &Dev))
            {
                return OK;
            }
        }
    }
    else if ((pRadio->Param.p_rx.u32DestinationId & 0xFFFFFF00) == (u32EnOceanBaseID & 0xFFFFFF00))
    {
        //u8BaseOffsetID = pRadio->Param.p_rx.u32DestinationId - u32EnOceanBaseID;
        // EnOceanRadioMapChannel(u8MSCChannel,&u8BuffChannel,Dev.Cfg.u8CascadePhyAdd);

        if (eMSC_CMD_WRITE == u8Cmd)
        {
            /* Only save profile parameter */
            return OK;
        }
        else if (eMSC_CMD_READ == u8Cmd)
        {
            return OK;
        }
    }
    else
    {
        return !OK;
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_ReceiveAndResponse(Radio_Typedef *pRadio)
{
    uint8_t u8Cmd;
    //uint8_t u8I;
    //uint8_t u8Status;
    //uint8_t u8Channel;
    //uint8_t u8ChannelMax;



    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;


    EnOceanGetHWBaseID(&u32EnOceanBaseID);
    EnOceanGetHWChipID(&u32EnOceanChipID);

    if ( pRadio->Param.p_rx.u32DestinationId != u32EnOceanChipID )
    {
        return !OK;
    }
    
    if ( 4 == pRadio->u16DataLength - 6 )
    {
        u8Cmd        = pRadio->Telegram.raw.bytes[3] & 0x0F;
    }
    else if ( 1 == pRadio->u16DataLength - 6 )
    {
        u8Cmd        = pRadio->Telegram.raw.bytes[0] & 0x0F;
    }
     
    //u8Channel    = pRadio->Telegram.raw.bytes[0]&0x0F;
    /*
    if ( 0x01 == u8Cmd )
    {
        if ( pRadio->Param.p_rx.u8SubTelNum != 0x04 )
        {
            return !OK;
        }
    }
    else if ( 0x02 == u8Cmd )
    {
        if ( pRadio->Param.p_rx.u8SubTelNum != 0x01 )
        {
            return !OK;
        }
    }
    */
    switch (u8Cmd)
    {
    case 0x01://窗帘移动
        EEPD20502_GotoPositionandAngle_01(pRadio);
        break;

    case 0x02://窗帘停止
        //CurtainRun.eRunState = eCURTAINRUN_CURTAINSTOP;
        CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP;  
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_MID; 
        CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_STOP;
        break;

    case 0x03://窗帘查询
        EEPD20502_ReplyPositionandAngle_04(pRadio);
        break;
    default:
        break;
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_GotoPositionandAngle_01(Radio_Typedef *pRadio)
{
    //uint8_t u8LOCK;
    uint8_t u8REPO;
    
    //u8LOCK       = pRadio->Telegram.raw.bytes[1]&0x0F;
    u8REPO       = pRadio->Telegram.raw.bytes[2]>>4;

    if (1 == Dev.u8PowerOnFlag)
    {
        CurtainRun.eRunState = eCURTAINRUN_SETTRIP_START;
        Dev.u8PowerOnFlag = 0;
        return OK;
    }

    switch (u8REPO)
    {
    case 0x00: //百分比移动

        CurtainRun.u8CurtainPercentage =  pRadio->Telegram.raw.bytes[0];
        //CurtainRun.eRunState = eCURTAINRUN_CURTAINPERCENTAGE;
        CurtainRun.eControlState = eCURTAINRUN_CURTAINPERCENTAGE;
        return OK;
        break;

    case 0x01: //合窗帘

        CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_OFF; 
        CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_OFF;
        /*
        //CurtainRun.eRunState = eCURTAINRUN_CURTAINON;
        CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_ON; 
        CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_ON;
        */
        return OK;
        break;

    case 0x02: //打开窗帘

        CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_ON; 
        CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_ON;
        /*
        //CurtainRun.eRunState = eCURTAINRUN_CURTAINOFF;
        CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
        CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_OFF; 
        CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_OFF;
        */
        return OK;
        break;

    default:
        break;
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_ReplyPositionandAngle_04(Radio_Typedef *pRadio)
{
    uint8_t u8Cmd;
    uint8_t u8Channel;
    uint8_t u8LOCK;
    uint8_t u8Angle;    //角度
    uint8_t u8Position; //百分比位置

    u8Cmd       = 0x04;
    u8Channel   = 0x00;
    u8LOCK      = 0x00;
    u8Angle     = 0x00;
    u8Position  = CurtainData.Query.u8CurtainPercentage;

    pRadio->Telegram.raw.bytes[3]  = u8Cmd;
    pRadio->Telegram.raw.bytes[3] |= u8Channel ;

    pRadio->Telegram.raw.bytes[2] = u8LOCK;

    pRadio->Telegram.raw.bytes[1] = u8Angle;

    pRadio->Telegram.raw.bytes[0] = u8Position;


    EnOceanVLDRadioData(pRadio, 4, 0, 0xFFFFFFFF);
    return OK;
}
/**
  * @brief  Enocean设置按键
  * @param
  * @retval None
  */
void EnOceanRPSSetButton(void)
{
    uint8_t u8Data;

    u8Data = Radio.Telegram.RPS.u8Data;

    if (0x17 == u8Data)
    {
        if (Dev.u8PassiveSwitchSetCount == 0)
        {
            Dev.u32PassiveSwitchSetTime = 10*1000;
        }

        Dev.u8PassiveSwitchSetCount++;

        if ( 0 == Dev.u32PassiveSwitchSetTime )
        {
            Dev.u8PassiveSwitchSetCount    = 0;
            Dev.u8PassiveSwitchSetModeFalg = 0;
        }

        if (Dev.u8PassiveSwitchSetCount >= 3)
        {
            Dev.u32PassiveSwitchSetContinuedTime    = 300*1000;  //设置时间5分钟
            Dev.u8PassiveSwitchSetCount    = 0;
            Dev.u32PassiveSwitchSetTime    = 0;
            LED_Fast_Blink(&LED,3);
            Dev.u8PassiveSwitchSetModeFalg = 1;
        }
        
    }
}
/**
  * @brief  Enocean手动设置
  * @param
  * @retval None
  */
void EnOceanManualSet(void)
{
    uint8_t u8Data;

    u8Data = Radio.Telegram.RPS.u8Data;

    switch (u8Data)
    {
    case 0x37: //设置换向

        CurtainRun.eManualSetRun = eMANUAL_SET_MOTORDIRECTION;
        break;

    case 0x15: //设置轻触功能

        CurtainRun.eManualSetRun = eMANUAL_SET_MANUALMODE;
        break;

    case 0x17: //清除行程
       
        CurtainRun.u8DeleteTripFlag++;
        if ( CurtainRun.u8DeleteTripFlag > 1 )
        {
            CurtainRun.eManualSetRun = eMANUAL_SET_SETTRIP;
            CurtainRun.u8DeleteTripFlag = 0;
        }
        break;

    default:
        break;
    }
} 
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanManualLearn(Radio_Typedef *pRadio)
{
    uint8_t u8LearnState;

    if (  Button.eButtonEvent == eButton_LONG_PRESS_2S || 0x01 == Dev.u8ManualLearnState )
    {
        if ( ( eLEARN_STATUS_ADD_SUCCESS == Dev.u8LearnState )||( eLEARN_STATUS_DEL_SUCCESS == Dev.u8LearnState ) )
        {
            return;
        }

        u8LearnState     = EnOceanLearnSensor(pRadio,Dev.u8LearnChannel, Dev.u8LearnMode);

        if ( ( eLEARN_STATUS_ADD_SUCCESS == u8LearnState )||( eLEARN_STATUS_DEL_SUCCESS == u8LearnState ) )
        {
            Dev.u8LearnState = u8LearnState;
            Dev.u8LearnSuccessTime = 50;            
        } 
    }      
}
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanLearnSensor(Radio_Typedef *pRadio,uint8_t u8LearnChannel, uint8_t u8LearnOutMode)
{
    ID_SEARCH_TYPE Search;
    ID_LEARN_INFO  LearnInfo;

    uint32_t u32EnOceanChipID;

    EnOceanGetHWChipID  ( &u32EnOceanChipID );

    Search.u8Start = 0;

    LearnInfo.u8Channel = u8LearnChannel;
    LearnInfo.u8Cmd     = 0;
    LearnInfo.u8Enable  = LRN_SERACH;
    LearnInfo.u8Type    = LRN_MANUAL;
    LearnInfo.u8OutMode = u8LearnOutMode;

    if (RADIO_CHOICE_RPS == pRadio->Telegram.raw.u8RORG)
    {
        LED_Fast_Blink(&LED, 3);
        FLASHRUN.u8LearnUpdateFlag = 1;
        Dev.u8ManualLearnState     = 0x00;
        if (OK != EnOceanGetSearchLearnDataByRPSLeft(pRadio, &Search, &LearnInfo))
        {
            // EnOceanManualLearnDev2Tab(&Search);
            return eLEARN_STATUS_IDLE;
        }
    }
    else if ( RADIO_CHOICE_4BS == pRadio->Telegram.raw.u8RORG )
    {
        if ( OK != EnOceanGetSearchLearnDataBy4BS(pRadio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if ( RADIO_CHOICE_1BS == pRadio->Telegram.raw.u8RORG )
    {
        if ( OK != EnOceanGetSearchLearnDataBy1BS(pRadio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if ( RADIO_CHOICE_UTE == pRadio->Telegram.raw.u8RORG )
    {
        if (pRadio->Param.p_rx.u32DestinationId != u32EnOceanChipID)
        {
            return eLEARN_STATUS_IDLE;
        }

        if ( OK != EnOceanGetSearchDataByUTEOrVLDTelRadio(pRadio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else
    {
        return eLEARN_STATUS_IDLE;
    }    

    return EnOceanManualLearnDev2Tab(&Search);
}

/**
  * @brief  Enocean无源无线开关左侧数据处理
  * @param
  * @retval None
  */
uint8_t EnOceanRPSLeftData(ID_SEARCH_TYPE const *pSearchIn,ID_SEARCH_TYPE *pSearchOut)
{

    if (1 == Dev.u8PowerOnFlag)
    {
        CurtainRun.eRunState = eCURTAINRUN_SETTRIP_START;
        Dev.u8PowerOnFlag = 0;
        return OK;
    }

    if (pSearchIn->entry.LrnDev.RPS.u3Key == 0x01 || pSearchIn->entry.LrnDev.RPS.u3Key == 0x05)
    {

        //if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_OFF )
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_ON )
        {
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINSTOP; //停止窗帘
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_MID; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_STOP;
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_ON; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_ON;
            /*
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINOFF; //打开窗帘
            CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_OFF; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_OFF;
            */
            return OK;
        }
    }
    else if (pSearchIn->entry.LrnDev.RPS.u3Key == 0x03 || pSearchIn->entry.LrnDev.RPS.u3Key == 0x07)
    {
     
        //if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_ON )
        if ( CurtainRun.eCurtainRunSteta == eCURTAIN_RUN_OFF )
        {
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINSTOP; //停止窗帘
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_MID; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_STOP;
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_OFF; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_OFF;
            /*
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINON; //关闭窗帘
            CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
            CurtainRun.eCurtainRunSteta = eCURTAIN_RUN_ON; 
            CurtainRun.eEnoceanControl = eENOCEAN_CONTROL_ON;
            */
            return OK;
        }
    }
    else
    {
        return !OK;
    }
}
/**
  * @brief  Enocean无源无线开关右侧数据处理
  * @param
  * @retval None
  */
uint8_t EnOceanRPSRightData(ID_SEARCH_TYPE *pSearch)
{
    if (pSearch->entry.LrnDev.RPS.u3Key == 0x01)
    {
        if (CurtainData.Query.u8MotorState != 0x00)
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP; //停止窗帘
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINON; //打开窗帘
            return OK;
        }
    }
    else if (pSearch->entry.LrnDev.RPS.u3Key == 0x03)
    {
        if (CurtainData.Query.u8MotorState != 0x00)
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP; //停止窗帘
            return OK;
        }
        else
        {
            CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF; //关闭窗帘
            return OK;
        }
    }
    return !OK;
}
/**
  * @brief  Enocean左侧无源无线开关
  * @param
  * @retval None
  */
uint8_t EnOceanRPSLeftOnOffData(Radio_Typedef *pRadio)
{
    
    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO  LearnInfo;


    if ( PTM2XX_ROCK_PRESSED_STATUS == (pRadio->Telegram.raw.u8Status&PTM2XX_ROCK_PRESSED_STATUS) )
    {
        LearnInfo.u8Channel= 0;
        LearnInfo.u8Enable = RADIO_SERACH;
        LearnInfo.u8Key    = RPS_HIGH_4BIT;
        LearnInfo.u8Type   = LRN_MANUAL;

        if ( OK == EnOceanGetSearchLearnDataByRPSLeft(pRadio,&SearchIn,&LearnInfo) )
        {
            if (ID_SUCCESS == EnOceanSearchLearnTab(&SearchIn,&SearchOut))
            {
                EnOceanRPSLeftData(&SearchIn,&SearchOut);
                return OK;
            }
        }

    }
    return !OK;
}
/**
  * @brief  Enocean右侧无源无线开关
  * @param
  * @retval None
  */
uint8_t EnOceanRPSRightOnOffData(Radio_Typedef *pRadio)
{
    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO  LearnInfo;


    if ( PTM2XX_ROCK_PRESSED_STATUS == (pRadio->Telegram.raw.u8Status&PTM2XX_ROCK_PRESSED_STATUS) )
    {
        LearnInfo.u8Channel= 0;
        LearnInfo.u8Enable = LRN_SERACH;
        LearnInfo.u8Key    = RPS_HIGH_4BIT;
        LearnInfo.u8Type   = LRN_MANUAL;

        if (OK == EnOceanGetSearchLearnDataByRPSRight(pRadio, &SearchIn, &LearnInfo))
        {
            if (ID_SUCCESS == EnOceanSearchLearnTab(&SearchIn,&SearchOut))
            {
                EnOceanRPSRightData(&SearchIn);
                return OK;
            }
        }
    }
    return !OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanCurtain(Radio_Typedef *pRadio)
{

 

    if (RADIO_CHOICE_RPS == pRadio->Telegram.raw.u8RORG)
    {
        //Dev.u32EnOceanRPSRxCount++;

        if (OK == EnOceanSearchDevLearnStatusBySrcID(pRadio->Param.ReMan.u32SourceId))
        {
            if (Dev.u8PassiveSwitchSetModeFalg != 1)
            {
                EnOceanRPSSetButton();
            }
            else
            {
                EnOceanManualSet();
                return OK;
            }
        }        
        if (OK == EnOceanRPSLeftOnOffData(pRadio))
        {
            return OK;
        }
    }
    else if (RADIO_CHOICE_MSC == pRadio->Telegram.raw.u8RORG)
    {
        //Dev.u32EnOceanMSCRxCount++;
        return EnOceanRadioMSC(pRadio);
    }
    else if (RADIO_CHOICE_VLD == pRadio->Telegram.raw.u8RORG)
    {
        //Dev.u32EnOceanVLDRxCount++;
        return EEPD20502_ReceiveAndResponse(pRadio);
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanHandler(uint8_t u8SendIntervalPeriodSet)
{   
    uint8_t u8Status;

    /* Get and process EnOcean ESP3's data from receive queue  */
    u8Status = EnOceanESP3ReceivePacketParse(&Radio, PACKET_RESERVED);

    if (0 == u8Status)
    {
        //ENOCEAN_HARDWARE_RST_DISABLE();   //
        //EnOceanRun.u8SendPeriod = u8SendIntervalPeriodSet;
    }
    else if (1 == u8Status)
    {
        /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
        EnOceanModuleInit();
    }
    else if (2 == u8Status)
    {
        if ( OK == EnOceanCurtain(&Radio) )
        {    
            EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,&Radio);    
        }

        EnOceanManualLearn(&Radio);
    }
    else if (3 == u8Status)
    {
        if (RM_SUCCESS == EnOceanReman(&Radio))
        {
            EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM, &Radio);
        }
    }

    /*
    if ( 0x01 == Dev.u8RemoteControlLreanFlag &&  CurtainData.Set.u8SetLearnState != 0x00 )
    {
        Dev.u8RemoteControlLreanFlag = 0x00;
        EnoceanRemanMotorLearnDev_333(&Radio);
        EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM, &Radio);
    }
    */

    /* */
    if (OK != EnOceanESP3SendStateProcess())
    {
        EnOcean_HardwareReset();
    }

    if (OK == EnOceanGetSendReady())
    {
        if (OK == EnOcean_GetSendQueuePopID())
        {
            EnOceanPopQueueSendData();

            EnOceanSetSendPeriod(u8SendIntervalPeriodSet);
        }
    }
    ClearAllFlag();

    EnOceanLearnSend();

}
#if 0
/**
 * @brief：窗帘学习表
 * @param
 * @retval None
 */
eENOCEAN_LEARN_STATUS_TYPE CurtainManualLearnSensor(uint8_t u8LearnChannel,uint8_t u8LearnCmd)
{
    ID_SEARCH_TYPE Search;
    ID_LEARN_INFO  LearnInfo;

    uint32_t u32EnOceanChipID;

    EnOceanGetHWChipID  ( &u32EnOceanChipID );

    Search.u8Start = 0;

    LearnInfo.u8Channel = u8LearnChannel;
    LearnInfo.u8Cmd     = u8LearnCmd;
    LearnInfo.u8Enable  = LRN_SERACH;
    LearnInfo.u8Type    = LRN_MANUAL;

    if ( RADIO_CHOICE_RPS == Radio.Telegram.raw.u8RORG )
    {                
        if ( OK != EnOceanGetSearchLearnDataByRPSLeft(&Radio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }      
    }
    else if ( RADIO_CHOICE_4BS == Radio.Telegram.raw.u8RORG )
    {
        if ( OK != EnOceanGetSearchLearnDataBy4BS(&Radio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if ( RADIO_CHOICE_1BS == Radio.Telegram.raw.u8RORG )
    {
        if ( OK != EnOceanGetSearchLearnDataBy1BS(&Radio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if ( RADIO_CHOICE_UTE == Radio.Telegram.raw.u8RORG )
    {
        if (Radio.Param.p_rx.u32DestinationId != u32EnOceanChipID)            
        {
            return eLEARN_STATUS_IDLE;
        }

        if ( OK != EnOceanGetSearchDataByUTEOrVLDTelRadio(&Radio,&Search,&LearnInfo) )
        {
            return eLEARN_STATUS_IDLE;
        }   
    }
    else
    {
        return eLEARN_STATUS_IDLE;
    }

    if ( eCMD_MANUAL_LEARN_ADD == u8LearnCmd )
    {            
        return EnOceanManualAddDev2LearnTab(&Search) ;
    }
    else if ( eCMD_MANUAL_LEARN_DEL == u8LearnCmd )
    {
        return EnOceanManualDeleteDev2LearnTab(&Search) ;
    }
    else if ( eCMD_MANUAL_LEARN_AUTO_LIGHT == u8LearnCmd )
    {
        return EnOceanManualLearnDev2Tab(&Search);
    }

    return eLEARN_STATUS_IDLE;
}
#endif

/**
  * @brief：Enocen报文类型验证
  * @param
  * @retval None
  */
uint8_t EnOceanRadio(void)
{
#ifdef HW_DEBUG
    /*
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_RPS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanRPSID))
    {
        Dev.u32EnOceanRPSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_1BS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOcean1BSID))
    {
        Dev.u32EnOcean1BSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_4BS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOcean4BSID))
    {
        Dev.u32EnOcean4BSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_VLD) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanVLDID))
    {
        Dev.u32EnOceanVLDRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_MSC) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanMSCID))
    {
        Dev.u32EnOceanMSCRxCount++;
    }
    if (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanRxID)
    {
        Dev.u32EnOceanRxCount++;
    }
    */
#endif

    /*
    if ( RADIO_CHOICE_MSC == Radio.Telegram.raw.u8RORG )
    {
        if(OK == EnOceanRadioMSC(&Radio))
        {
            return !OK;
        }
    } 
    */
    return OK;
}


//!用户定义的远程功能
const uint16_t  u16gRpc[] =
{
    
    RM_FN_UNLOCK                     , //!<Unlock command.
    RM_DEFAULTMANID                  ,
    RM_FN_LOCK                       , //!<Lock command.
    RM_DEFAULTMANID                  ,
    RM_FN_SET_CODE                   , //!<Set security command.
    RM_DEFAULTMANID                  ,
    RM_FN_QUERY_ID                   , //!<Query ID command.
    RM_DEFAULTMANID                  ,
    RM_FN_ACTION_COMMAND             , //!<Test command.
    RM_DEFAULTMANID                  ,
    RM_FN_PING_COMMAND               , //!<Ping command.
    RM_DEFAULTMANID                  ,
    RM_FN_QUERY_FUNCTION_COMMAND     , //!<Query supported RPC functions command.
    RM_DEFAULTMANID                  ,
    RM_FN_QUERY_STATUS               , //!<Query debug status of remote manager.
    RM_DEFAULTMANID                  ,

    RM_RPC_RESET_ALL          , // 0 0x300
    ENOCEAN_MENRED_MAN_ID     , // 1
    RM_RPC_READ_IDS           , // 6 0x303
    ENOCEAN_MENRED_MAN_ID     , // 7
    RM_RPC_CLEAR_IDS          , // 8 0x304
    ENOCEAN_MENRED_MAN_ID     , // 9
    RM_RPC_ADD_ONE            , // 10 0x305
    ENOCEAN_MENRED_MAN_ID     , // 11
    RM_RPC_DEL_ONE            , // 12 0x306
    ENOCEAN_MENRED_MAN_ID     , // 13
    RM_RPC_READ_ONE           , // 14 0x307
    ENOCEAN_MENRED_MAN_ID     , // 15
    RM_RPC_READ_ONE_BY_ONE    , // 16 0x308
    ENOCEAN_MENRED_MAN_ID     , // 17
    RM_RPC_TEST_CHANNEL       , // 18 0x309
    ENOCEAN_MENRED_MAN_ID     , // 19
    RM_RPC_READ_BASEID        ,
    ENOCEAN_MENRED_MAN_ID     , // 19
    RM_RPC_WRITE_BASEID       ,
    ENOCEAN_MENRED_MAN_ID     , // 19
    RM_RPC_QUERY_ALL_BASEID_DEV,
    ENOCEAN_MENRED_MAN_ID     , // 19
    RM_RPC_READ_LIGHT_NUMS    ,
    ENOCEAN_MENRED_MAN_ID     , // 19
    RM_RPC_READ_LIGHT_TYPE    ,
    ENOCEAN_MENRED_MAN_ID     , // 19
    
    RM_RPC_ADD_LEARN_ADVANCED ,
    ENOCEAN_MENRED_MAN_ID     ,
    RM_RPC_DEL_LEARN_ADVANCED ,
    ENOCEAN_MENRED_MAN_ID     ,

};

/**
  * @brief  远程管理命令处理函数
  * @param
  * @retval None 
  */
RM_RETURN_TYPE EnOceanReman(Radio_Typedef *pRadio)
{   
    uint8_t u8Channel;
    uint8_t u8ChannelMax;
    uint16_t u16RemanFN;
    uint8_t u8Mask;
    
    uint32_t u32EnOceanBaseID;

    //uint8_t u8CmdMax;

    EnOceanGetHWBaseID  ( &u32EnOceanBaseID );
    EnOceanSetDstID(pRadio->Param.ReMan.u32SourceId);
    u16RemanFN   = pRadio->Telegram.ReMan.u16FnNum;

    u8ChannelMax = 1;  //通道数量默认为1
    u8Channel    = 0;  //通道默认为0

    /* Ping need not remotemangement password */
    if (RM_FN_PING_COMMAND == u16RemanFN) // PING 0x06
    {
        EnOceanReManPingCommand(CURTAIN_EEP,pRadio);
        return RM_SUCCESS;
    }

    /* Must unlock the devices, can use more function */
    if ( RM_SUCCESS != EnOceanReManSecurityProcess(pRadio) )
    {
        return RM_NO_SUCCESS;
    }

    if ( RM_FN_QUERY_ID == u16RemanFN )//0x04
    {        
        return EnOceanReManGateWayResponseQueryID(CURTAIN_EEP,pRadio);   
    }

    if (EnOceanReManCheckDestID(&pRadio->Param) == RM_NO_SUCCESS)
    {
        return RM_COMMAND_FLASH_READ_NO_SUCCESS;
    } 

    // Depending on the remote telegram command received a certain action is performed
    switch(u16RemanFN)
    {
    // Perform a visual signalisation on the I/O pins.
    // query infomation
    case RM_FN_QUERY_FUNCTION_COMMAND: //0x07 

        u8Mask = sizeof(u16gRpc)/sizeof(u16gRpc[0]);
        return EnOceanReManQueryFunctionCommand(pRadio,u16gRpc,u8Mask);
        
    case RM_FN_QUERY_STATUS://0x08

        return EnOceanReManQueryStatus(pRadio);

    case RM_FN_ACTION_COMMAND://0x05
        
        //LED_Fast_Blink(&LED,100);
        //CurtainRun.eRunState = eCURTAINRUN_CURTAINON;

        if ( RM_SUCCESS == EnOceanReManActive(pRadio,1) )
        {
            CurtainRun.eRunState = eCURTAINRUN_HWTEST_FORWARD;
            return RM_SUCCESS;
        }
        return RM_NO_SUCCESS;
        
    // rpc command for menred products
    case RM_RPC_RESET_ALL://0->0x300   //回复出厂设置

        if ( RM_SUCCESS == EnOceanReManResetDevAll(pRadio) )
        {
            ResetDefaultData();
            ResetDefaultEnable();      
            FLASHRUN.u8LearnUpdateFlag = 1;   //更新Flash中的学习表      
            FLASHRUN.u8CfgUpdateFlag   = 1;   //更新Flash中的数据部分
            return RM_SUCCESS;
        }
        break;

    case RM_RPC_READ_IDS://3->0x303   //读取学习条目

        return EnOceanReManReadLearnIds_303(pRadio);

    case RM_RPC_CLEAR_IDS://4->0x304

        if ( RM_SUCCESS == EnOceanReManClearLearnIds(pRadio) )
        {
            return EnOceanSaveLearnTabEvent();
        }
        break;
        
    case RM_RPC_ADD_ONE://5->0x305

        FLASHRUN.u8LearnUpdateFlag = 1;   //更新Flash中的学习表
        return EnOceanReManAddLearnDev2Tab(pRadio,u8ChannelMax,u8Channel);    
        break;

    case RM_RPC_DEL_ONE://6->0x306

        FLASHRUN.u8LearnUpdateFlag = 1;   //更新Flash中的学习表
        return EnOceanReManDelLearnDev(pRadio,u8ChannelMax,u8Channel);        
        break;

    case RM_RPC_READ_ONE://7->0x307
    
        return EnOceanReManReadDevByLearnIds(pRadio);
        break;
        
    case RM_RPC_READ_ONE_BY_ONE://8->0x308  

        return EnOceanReManReadDevAllLearnInfoByTabIds(pRadio);
        break;
        
    case RM_RPC_TEST_CHANNEL://9->0x309

        if (RM_SUCCESS == EnOceanReManTestDevChannel_309(pRadio))
        {
            CurtainRun.eRunState = eCURTAINRUN_HWTEST_FORWARD;
            return RM_SUCCESS;
        }
        break;

    case RM_RPC_READ_BASEID          ://0x30A
    case RM_RPC_WRITE_BASEID         ://0x30B  
    case RM_RPC_READ_CURTAIN_NUMS    ://0x30F

        return EnOceanReManResponseQueryChannelMax(pRadio,u8ChannelMax);
        break;
        
    case RM_RPC_READ_CURTAIN_TYPE    ://0x310

        return EnOceanReManResponseQueryChannelType(pRadio,u8Channel,u8ChannelMax,0);
        break;

    case RM_RPC_ADD_LEARN_ADVANCED   ://0x330

        LED_Fast_Blink(&LED,3);
        FLASHRUN.u8LearnUpdateFlag = 1;   //更新Flash中的学习表
        return EnOceanReManAddLearnDev2Tab_330(pRadio,u8ChannelMax,u8Channel,0);
        break;

    case RM_RPC_DEL_LEARN_ADVANCED   ://0x331

        LED_Fast_Blink(&LED,3);
        FLASHRUN.u8LearnUpdateFlag = 1;   //更新Flash中的学习表
        return EnOceanReManDelLearnDev_331(pRadio,u8ChannelMax,u8Channel,0);
        break;

    case RM_RPC_OPEN_CURTAIN_LEARN ://0x333

        //Dev.u8RemoteControlLreanFlag  = 0x01;
        Dev.u32RemoteControlLreanTime = 300 * 1000;        // 5分钟
        CurtainRun.eRunState = eCURTAINRUN_SET_LEARNSTATE; //设置学习模式
        return RM_SUCCESS;
        //return EnoceanRemanMotorLearnDev_333(pRadio);
        break;

        // Here it could be received a remote telegram that does not decode. Do nothing.
    default:
        return RM_NO_SUCCESS;

    }
    
    return RM_NO_SUCCESS;
}

/**
  * @brief
  * @param
  * @retval None
  * 333 打开触发电机学习专用遥控器命令
  */
RM_RETURN_TYPE EnoceanRemanMotorLearnDev_333(Radio_Typedef *pRadio)
{
    uint8_t u8Status;



    u8Status = 0x01;

    pRadio->Telegram.ReMan.u16FnNum             = RM_RPC_OPEN_CURTAIN_LEARN_ANS;
    pRadio->Telegram.ReMan.u16ManId             = ENOCEAN_MENRED_MAN_ID;
    pRadio->Param.ReMan.u32DestinationId        = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId             = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable   = REMAN_RANDOM_DISABLE;

    pRadio->Telegram.ReMan.u8Length     = 4;
    pRadio->Telegram.ReMan.u8Data[0]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[1]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[2]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[3]    = u8Status;

    return RM_SUCCESS;
}

/**
  * @brief  EnOcean 303
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadLearnIds_303(Radio_Typedef *pRadio)
{
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;
    //pRadio->Telegram.ReMan.u16FnNum = RM_RPC_READ_IDS_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;
    pRadio->Telegram.ReMan.u8Data[0]= 0x00;
    pRadio->Telegram.ReMan.u8Data[1]= 0x00;
    pRadio->Telegram.ReMan.u8Data[2]= 0x00;
    pRadio->Telegram.ReMan.u8Data[3]= LearnInfoTab.u8nrIDs;
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief  EnOcean 309
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManTestDevChannel_309(Radio_Typedef *pRadio)
{
  
    pRadio->Telegram.ReMan.u16FnNum  = RM_RPC_TEST_CHANNEL_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;
    pRadio->Telegram.ReMan.u8Data[0]= 0x00;
    pRadio->Telegram.ReMan.u8Data[1]= 0x00;
    pRadio->Telegram.ReMan.u8Data[2]= 0x00;
    pRadio->Telegram.ReMan.u8Data[3]= 0x01;
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}


/* End of file */