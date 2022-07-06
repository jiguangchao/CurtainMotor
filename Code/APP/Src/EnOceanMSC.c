
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "EnOceanMSC.h"

#include "CurtainProtocol.h"
#include "CurtainInterface.h"


/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetRegPermission(uint8_t u8GetRegSize, RegTab_Typedef const *pu32DataTab, uint8_t u8Cmd, uint8_t u8RegIndex, uint32_t u32Data);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetRegPermission(uint8_t u8GetRegSize, RegTab_Typedef const *pu32DataTab, uint8_t u8Cmd, uint8_t u8RegIndex, uint32_t u32Data)
{

    return !OK;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetChannelAndRegPermission(uint8_t u8Cmd, uint8_t u8Channel, uint8_t u8RegIndex, uint32_t u32Data)
{
    if (0 == u8Channel) //
    {
        return EnOceanMSCGetRegPermission(Dev_GetRegTabSize(), DevRegTab, u8Cmd, u8RegIndex, u32Data);
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteSettings(Radio_Typedef *pRadio)
{
    uint8_t u8Cmd;
    //uint8_t u8BuffChannel;
    uint8_t u8MSCChannel;
    uint8_t u8Register;
    uint32_t u32Data;

    u8Cmd = pRadio->Telegram.raw.bytes[1] & 0x0F;

    u8MSCChannel = pRadio->Telegram.raw.bytes[2];

    u8Register = pRadio->Telegram.raw.bytes[3];
    u32Data = pRadio->Telegram.raw.bytes[4] << 24 | pRadio->Telegram.raw.bytes[5] << 16 | pRadio->Telegram.raw.bytes[6] << 8 | pRadio->Telegram.raw.bytes[7];
    if (eMSC_CMD_WRITE != u8Cmd)
    {
        return !OK;
    }

    if (EnOceanMSCGetChannelAndRegPermission(eMSC_CMD_WRITE, u8MSCChannel, u8Register, u32Data))
    {
        return !OK;
    }
    //if (EnOceanRadioMapChannel(u8MSCChannel, &u8BuffChannel, 0))
    {
        return !OK;
    }
    //u32Data = (uint32_t)pRadioTel->raw.bytes[4]<<24 | (uint32_t)pRadioTel->raw.bytes[5]<<16 | (uint32_t)pRadioTel->raw.bytes[6]<<8 | (uint32_t)pRadioTel->raw.bytes[7];
    /* Use chip id */
    /*
    if (0 == u8MSCChannel) //
    {
        if (EnOceanMSCWriteDevtings(u8Register, u32Data, &Dev))
        {
            return !OK;
        }
        pRadio->u16DataLength = 14;
    }
    else
    {
        return !OK;
    }

    return OK;
    */
}
/**
  * @brief
  * @param
  * @retval None
  */

uint8_t EnOceanMSCResponse(Radio_Typedef *pRadio, Dev_Typedef *pDev)
{


    Radio.Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    Radio.Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    /* Must use "<=", because the MSC telegram relay channel is from 1 to 3 */
    /* Dev channel use the ID is tcm310's ChipID */

    if (0x00 == pRadio->Telegram.raw.bytes[2])
    {
        EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
        EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
    }
    else if (1 == pRadio->Telegram.raw.bytes[2])
    {
        EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
        EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
    }
    return !OK;
}

/**
  * @brief
  * @param
  * @retval None
  */

uint8_t EnOceanMSCWrite(Radio_Typedef *pRadio, Dev_Typedef *pDev)
{

    uint32_t u32Data;
    uint8_t  u8Channel;

    u8Channel = pRadio->Telegram.raw.bytes[2];
    u32Data = (uint32_t)pRadio->Telegram.raw.bytes[4] << 24 | (uint32_t)pRadio->Telegram.raw.bytes[5] << 16 | (uint32_t)pRadio->Telegram.raw.bytes[6] << 8 | (uint32_t)pRadio->Telegram.raw.bytes[7];
    EnOceanMSCWriteDevtings(pRadio->Telegram.raw.bytes[3], u32Data, pDev);

    Radio.Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    Radio.Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    Radio.Telegram.raw.bytes[2] = u8Channel;    

    EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */

void EnOceanMSCSend(Radio_Typedef *pRadio, Dev_Typedef *pDev, uint8_t u8RegH, uint8_t u8RegL)
{

    Radio.Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    Radio.Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    pRadio->Telegram.raw.bytes[2] = u8RegH;

    pRadio->Telegram.raw.bytes[3] = u8RegL;

    EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);

    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanMSCSend32Data(Radio_Typedef *pRadio, Dev_Typedef *pDev, uint8_t u8RegH, uint8_t u8RegL,uint32_t u32Data)
{

    Radio.Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    Radio.Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    pRadio->Telegram.raw.bytes[2] = u8RegH;

    pRadio->Telegram.raw.bytes[3] = u8RegL;

    pRadio->Telegram.raw.bytes[4] = (uint8_t)(u32Data >> 24);
    pRadio->Telegram.raw.bytes[5] = (uint8_t)(u32Data >> 16);
    pRadio->Telegram.raw.bytes[6] = (uint8_t)(u32Data >> 8);
    pRadio->Telegram.raw.bytes[7] = (uint8_t)(u32Data >> 0);

    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
}


/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanMSCSendTest(Radio_Typedef *pRadio)
{

    pRadio->Telegram.raw.bytes[0] = 0x55;

    pRadio->Telegram.raw.bytes[1] = 0x66;

    pRadio->Telegram.raw.bytes[2] = 0x77;

    pRadio->Telegram.raw.bytes[3] =  0x88;

    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteDevtings(uint8_t u8RegID, uint32_t u32Data, Dev_Typedef *pDev)
{
    uint16_t u16RegValue;
    switch (u8RegID)
    {
    case MB_HOLD_ENOCEAN_REAPTER      ://Enocean Reapter
    case MB_HOLD_RESET_INITIALIZE     ://恢复出厂参数 
    case MB_HOLD_CURTAIN_PERCENTAGE_CONTROL ://百分比控制窗帘
    case MB_HOLD_MOTOR_ACTION_CMD     ://电机动作命令
    case MB_HOLD_MOTOR_TRIP_SET       ://电机行程设置
    case MB_HOLD_TOUCH_SET            ://轻触设置
    case MB_HOLD_COMMUTATION_SET      ://电机换向设置
    case MB_HOLD_CLEAR_TRIP_SET       ://清除行程设置
    case MB_HOLD_MANUAL_SET_BORDAR    ://手动设置边界
    case MB_HOLD_MANUAL_SET_BORDAR_ON ://打开手动设置边界
    case MB_HOLD_MANUAL_SET_BORDAR_OFF://关闭手动设置边界
    case MB_HOLD_MAX_TRIP_SET         ://设置最大行程
    case MB_HOLD_MIN_TRIP_SET         ://设置最小行程
                
    default:
        u16RegValue = (uint16_t)(u32Data & 0xFFFF);
        if (OK == Dev_HoldRegUpdateDataSetting(u8RegID, u16RegValue))
        {
            return OK;
        }
        break;
    }
    
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCResponseDevtings(uint8_t *p8Data, Dev_Typedef *pDev)
{
    p8Data[4] = 0;
    p8Data[5] = 0;
    p8Data[6] = 0;
    p8Data[7] = 0;
    switch(p8Data[3])
    {
    case MB_INPUT_SOFT_VERSION         ://软件版本号  
    case MB_INPUT_SIGNAL_STRENGTH      ://信号强度  
    case MB_INPUT_ERROR_STATUS         ://错误状态  
    //case MB_INPUT_LASTTIME_GATEWAY_RSSI://上次接收网关 RSSI值  
    //case MB_INPUT_LASTTIME_SWITCH_RSSI ://上次接收开关 RSSI值  
    case MB_INPUT_RESET_PASSWORD       ://复位密码  
    case MB_INPUT_RUN_TIME             ://运行时间  
    case MB_INPUT_PERCENTAGE           ://百分比位置
        Dev_ReadRegInput(p8Data, 3, p8Data[3]);
        break;

    case MB_INPUT_REAl_LIMIT           ://实时位置      
    case MB_INPUT_UP_LIMIT             ://上限位值高16位 
    case MB_INPUT_DOWN_LIMIT           ://下限位值高16位
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;

    case MB_HOLD_CURTAIN_PERCENTAGE_CONTROL ://百分比控制窗帘
    case MB_HOLD_ENOCEAN_REAPTER       ://Enocean Reapter
    case MB_HOLD_RESET_INITIALIZE      ://恢复出厂参数
    case MB_HOLD_MOTOR_ACTION_CMD      ://电机动作命令
    case MB_HOLD_MOTOR_TRIP_SET        ://电机行程设置
    case MB_HOLD_TOUCH_SET             ://轻触设置
    case MB_HOLD_COMMUTATION_SET       ://电机换向设置
    case MB_HOLD_CLEAR_TRIP_SET        ://清除行程设置
    case MB_HOLD_MANUAL_SET_BORDAR     ://手动设置边界
    case MB_HOLD_MANUAL_SET_BORDAR_ON  ://打开手动设置边界
    case MB_HOLD_MANUAL_SET_BORDAR_OFF ://关闭手动设置边界
    case MB_HOLD_MAX_TRIP_SET          ://设置最大行程
    case MB_HOLD_MIN_TRIP_SET          ://设置最小行程
        Dev_ReadRegHold(p8Data, 3, p8Data[3]);
        break;
    default:
        return Dev_ReadRegHold(p8Data, 3, p8Data[3]);
        break;
    }
    return OK;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Dev_HoldRegUpdateDataSetting(uint16_t u16RegID, uint16_t u16RegValue)
{
    switch (u16RegID)
    {

    case MB_HOLD_ENOCEAN_REAPTER       ://Enocean Reapter
    
        Dev.Cfg.u8Repeater = u16RegValue;
        /* Must update the tcm310 */
        EnOcean_InitGetInfo(&Radio);
        FLASHRUN.u8CfgUpdateFlag = 0x01;
        return OK;
        break;


    case MB_HOLD_RESET_INITIALIZE      ://恢复出厂参数

        if (u16RegValue == 1)
        {
            ResetDefaultData();
            FLASHRUN.u8CfgUpdateFlag = 0x01;
            FLASHRUN.u8LearnUpdateFlag = 0x01;
        }
        return OK;
        break;

    case MB_HOLD_CURTAIN_PERCENTAGE_CONTROL ://百分比控制窗帘

        if ( u16RegValue > 0x64 )
        {
            CurtainRun.u8CurtainPercentage =  0x64;
        }
        else
        {
            CurtainRun.u8CurtainPercentage =  u16RegValue;
        }
        CurtainRun.eControlState =  eCURTAINRUN_CURTAINPERCENTAGE;
        return OK;
        break;

    case MB_HOLD_MOTOR_ACTION_CMD      ://电机动作命令

        if (u16RegValue == 0)
        {
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINSTOP ;
            CurtainRun.eControlState = eCURTAINRUN_CURTAINSTOP;
        }
        else if (u16RegValue == 1)
        {
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINON ;
            CurtainRun.eControlState = eCURTAINRUN_CURTAINON;
        }
        else if (u16RegValue == 2)
        {
            //CurtainRun.eRunState = eCURTAINRUN_CURTAINOFF ;
            CurtainRun.eControlState = eCURTAINRUN_CURTAINOFF;
        }   
        return OK;
        break;
        
    case MB_HOLD_MOTOR_TRIP_SET        ://电机行程设置

        if (u16RegValue == 1)
        {
            CurtainRun.eRunState = eCURTAINRUN_SETTRIP_START ;
        }
        return OK;
        break;

    case MB_HOLD_TOUCH_SET: //轻触设置

        CurtainData.Set.u8SetManualMode = u16RegValue;
        CurtainRun.eRunState = eCURTAINRUN_SET_MANUALMODE;
        return OK;
        break;

    case MB_HOLD_COMMUTATION_SET       ://电机换向设置

        CurtainData.Set.u8SetMotorDirection = u16RegValue;
        CurtainRun.eRunState = eCURTAINRUN_SET_DIRECTION;
        return OK;
        break;

    case MB_HOLD_CLEAR_TRIP_SET        ://清除行程设置

        CurtainData.Set.u8SetDeleteTrip = 0x00;
        CurtainRun.eRunState = eCURTAINRUN_SET_DELETETRIP;
        return OK;
        break;

    case MB_HOLD_MANUAL_SET_BORDAR     ://手动设置边界

        return OK;
        break;
    case MB_HOLD_MANUAL_SET_BORDAR_ON  ://打开手动设置边界

        return OK;
        break;
    case MB_HOLD_MANUAL_SET_BORDAR_OFF ://关闭手动设置边界

        return OK;
        break;
    case MB_HOLD_MAX_TRIP_SET          ://设置最大行程

        CurtainData.Set.u8SetUpLimit =  u16RegValue;
        CurtainRun.eRunState = eCURTAINRUN_SET_UPLIMIT;
        return OK;
        break;

    case MB_HOLD_MIN_TRIP_SET          ://设置最小行程

        CurtainData.Set.u8SetDownLimit =  u16RegValue;
        CurtainRun.eRunState = eCURTAINRUN_SET_DOWNLIMIT;
        return OK;
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
uint8_t Dev_ReadRegHold(uint8_t *pu8SendBuff, uint16_t u16RegBuffID, uint16_t u16RegID)
{
    pu8SendBuff[u16RegBuffID*2]     = 0x00;
    pu8SendBuff[u16RegBuffID*2+1]   = 0x00;

    switch( u16RegID )
    {
    case MB_HOLD_ENOCEAN_REAPTER      ://Enocean Reapter

        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u8Repeater  >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u8Repeater & 0xFF;
        return OK;
        break;  

    case MB_HOLD_RESET_INITIALIZE     ://恢复出厂参数

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = 0x01;
        return OK;
        break;  

    case MB_HOLD_CURTAIN_PERCENTAGE_CONTROL ://百分比窗帘控制

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = 0x64 - CurtainData.Query.u8CurtainPercentage;
        return OK;
        break;   


    case MB_HOLD_MOTOR_ACTION_CMD     ://电机动作命令

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = 0x01;
        return OK;
        break;  
    case MB_HOLD_MOTOR_TRIP_SET       ://电机行程设置

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = 0x01;
        return OK;
        break;  
    case MB_HOLD_TOUCH_SET            ://轻触设置

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = CurtainData.Set.u8SetManualMode;
        return OK;
        break;  
 
    case MB_HOLD_COMMUTATION_SET      ://电机换向设置

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = CurtainData.Set.u8SetMotorDirection;
        return OK;
        break;  
    case MB_HOLD_CLEAR_TRIP_SET       ://清除行程设置

        pu8SendBuff[u16RegBuffID*2]     = 0x00;
        pu8SendBuff[u16RegBuffID*2+1]   = 0x01;
        return OK;
        break;  
    case MB_HOLD_MANUAL_SET_BORDAR    ://手动设置边界

        return OK;
        break;  
    case MB_HOLD_MANUAL_SET_BORDAR_ON ://打开手动设置边界

        return OK;
        break;  
    case MB_HOLD_MANUAL_SET_BORDAR_OFF://关闭手动设置边界

        return OK;
        break;  
    case MB_HOLD_MAX_TRIP_SET         ://设置最大行程
 
        pu8SendBuff[u16RegBuffID*2+1]   = CurtainData.Set.u8SetUpLimit;
        return OK;
        break;  
    case MB_HOLD_MIN_TRIP_SET         ://设置最小行程

        pu8SendBuff[u16RegBuffID*2+1]   = CurtainData.Set.u8SetDownLimit;
        return OK;
        break;          
    }
    return OK;
}
/**
   * @brief
   * @param
   * @retval
   */
uint8_t Dev_ReadRegInput(uint8_t *pu8SendBuff,uint16_t u16RegBuffID,uint16_t u16RegID)
{
    pu8SendBuff[u16RegBuffID*2]     = 0x00;
    pu8SendBuff[u16RegBuffID*2+1]   = 0x00;

    switch ( u16RegID )
    {
    case MB_INPUT_SOFT_VERSION         ://软件版本号

        pu8SendBuff[u16RegBuffID*2]       = Dev.u16HWVersion >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16HWVersion & 0xFF;
        break;

    case MB_INPUT_HARD_VERSION         ://硬件版本号

        pu8SendBuff[u16RegBuffID*2]       = Dev.u16FWVersion >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16FWVersion & 0xFF;
        break;          

    case MB_INPUT_SIGNAL_STRENGTH      ://信号强度

        pu8SendBuff[u16RegBuffID * 2]     = EnOceanRun.u8LatestReceiveRssi  >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = EnOceanRun.u8LatestReceiveRssi & 0xFF;
        break;

    case MB_INPUT_ERROR_STATUS         ://错误状态

        if (CurtainRun.eFaultCode != eCURTAINRUN_NORMAL)
        {
            pu8SendBuff[u16RegBuffID * 2]     = 0x00;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
            break;
        }
        else
        {
            pu8SendBuff[u16RegBuffID * 2]     = 0x00;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;            
            break;    
        }
    /*
    case MB_INPUT_LASTTIME_GATEWAY_RSSI://上次接收网关 RSSI值

        break;

    case MB_INPUT_LASTTIME_SWITCH_RSSI ://上次接收开关 RSSI值

        break;
    */
    case MB_INPUT_RESET_PASSWORD       ://复位密码

        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u32ResetPassword >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u32ResetPassword & 0xFF;
        break;

    case MB_INPUT_RUN_TIME             ://运行时间

        pu8SendBuff[u16RegBuffID * 2]     = Dev.Log.u32RunTime >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Log.u32RunTime & 0xFF;
        break;

    case MB_INPUT_PERCENTAGE           ://百分比位置

        pu8SendBuff[u16RegBuffID * 2]     = CurtainData.Query.u8CurtainPercentage >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = CurtainData.Query.u8CurtainPercentage & 0xFF;        
        break;

    case MB_INPUT_REAl_LIMIT_HIGH           ://实时位置高16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32RealtimeLimt >> 24);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32RealtimeLimt >> 16);        
        break;

    case MB_INPUT_REAl_LIMIT_LOW           ://实时位置低16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32RealtimeLimt >> 8);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32RealtimeLimt >> 0);        
        break;

    case MB_INPUT_UP_LIMIT_HIGH           ://上限位值高16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32UpLimit >> 24);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32UpLimit >> 16);        
        break;

    case MB_INPUT_UP_LIMIT_LOW           ://上限位值低16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32UpLimit >> 8);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32UpLimit >> 0);        
        break;

    case MB_INPUT_DOWN_LIMIT_HIGH           ://下限位值高16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32DownLimit >> 24);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32DownLimit >> 16);        
        break;

    case MB_INPUT_DOWN_LIMIT_LOW           ://下限位值低16位

        pu8SendBuff[u16RegBuffID * 2]     = (uint8_t)(CurtainData.Query.u32DownLimit >> 8);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(CurtainData.Query.u32DownLimit >> 0);        
        break;


    default:
        return !OK;
        break;         
    }
    return OK;
}


/* End of file */
