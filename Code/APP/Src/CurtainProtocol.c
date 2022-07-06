

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

/*******************************************************************************************/
/********************************     串口发送    *******************************************/
/*******************************************************************************************/


/*******************************查询-0x01-CURTAIN_CMD_READ**********************************/
/**
  * @brief:查询上限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitUp(Serial_Typedef *pSerial) 
{   
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x01;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询下限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitDown(Serial_Typedef *pSerial) 
{   
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x02;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitThrid(Serial_Typedef *pSerial) 
{   
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x03;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询实时限位位置  
  * @param
  * @retval None
  */
void CurtainSendQueryRunLimit(Serial_Typedef *pSerial) 
{   
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x04;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询电机状态  
  * @param
  * @retval None
  */
void CurtainSendQueryRunState(Serial_Typedef *pSerial) 
{   
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x05;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询方向  
  * @param
  * @retval None
  */
void CurtainSendQueryDirect(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x06;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询强电模式  
  * @param
  * @retval None
  */
void CurtainSendQueryHighPowerMode(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x07;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询弱电模式  
  * @param
  * @retval None
  */
void CurtainSendQuerySmallPowerMode(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x08;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询窗帘百分比位置  
  * @param
  * @retval None
  */
void CurtainSendQueryLocation(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x09;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询窗帘类型  
  * @param
  * @retval None
  */
void CurtainSendQueryCurtainType(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x0A;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询软件版本号  
  * @param
  * @retval None
  */
void CurtainSendQuerySoftVersion(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x17;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:查询电池电量  
  * @param
  * @retval None
  */
void CurtainSendQueryBattery(Serial_Typedef *pSerial) 
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_READ;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x18;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}


/****************************控制命令-CURTAIN_CMD_CTRL-0x02*******************************/
/**
  * @brief:控制上运行  
  * @param
  * @retval None
  */
void CurtainSendControlOn(Serial_Typedef *pSerial)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_CTRL;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x09;
    u8Crc              = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:控制下运行  
  * @param
  * @retval None
  */
void CurtainSendControlOff(Serial_Typedef *pSerial)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_CTRL;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x0A;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:控制停止运行  
  * @param
  * @retval None
  */
void CurtainSendControlStop(Serial_Typedef *pSerial)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_CTRL;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x0B;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief：控制百分比  
  * @param
  * @retval None
  */
void CurtainSendControlSetPercent(Serial_Typedef *pSerial,uint8_t u8SetPercent)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_CTRL;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x0C;
    pSerial->pu8Send[7] = u8SetPercent;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief：控制点动  
  * @param
  * @retval None
  */
void CurtainSendControlJoy(Serial_Typedef *pSerial,uint8_t u8Joy)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_CTRL;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x18;
    pSerial->pu8Send[7] = u8Joy;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}

/**********************设置命令-CURTAIN_CMD_SET-0x03***************************/
/**
  * @brief:设置上限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitUp(Serial_Typedef *pSerial,uint8_t u8SetLimitUp)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x0D;
    pSerial->pu8Send[7] = u8SetLimitUp;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置下限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitDown(Serial_Typedef *pSerial,uint8_t u8SetLimitDown)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x0E;
    pSerial->pu8Send[7] = u8SetLimitDown;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置第三点限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitThird(Serial_Typedef *pSerial,uint8_t u8SetLimitThird)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x0F;
    pSerial->pu8Send[7] = u8SetLimitThird;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置换向
  * @param
  * @retval None
  */
void CurtainSendSetDirect(Serial_Typedef *pSerial,uint8_t u8SetDirect)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x10;
    pSerial->pu8Send[7] = u8SetDirect;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置强电模式
  * @param
  * @retval None
  */
void CurtainSendSetHighPowerMode(Serial_Typedef *pSerial,uint8_t u8SetHighPowerMode)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x11;
    pSerial->pu8Send[7] = u8SetHighPowerMode;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置弱电模式
  * @param
  * @retval None
  */
void CurtainSendSetSmallPowerMode(Serial_Typedef *pSerial,uint8_t u8SmallPowerMode)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x12;
    pSerial->pu8Send[7] = u8SmallPowerMode;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置手拉开关
  * @param
  * @retval None
  */
void CurtainSendSetHandOnOff(Serial_Typedef *pSerial,uint8_t u8SetHandOnOff)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x13;
    pSerial->pu8Send[7] = u8SetHandOnOff;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置指示灯
  * @param
  * @retval None
  */
void CurtainSendSetLED(Serial_Typedef *pSerial,uint32_t u32SetLED)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x05;
    pSerial->pu8Send[6] = 0x14;
    pSerial->pu8Send[7] = u32SetLED>>24 ;
    pSerial->pu8Send[8] = u32SetLED>>16 ;
    pSerial->pu8Send[9] = u32SetLED>>8 ;
    pSerial->pu8Send[10] = u32SetLED ;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,11);
    pSerial->pu8Send[11] = u8Crc;
    pSerial->u16SendBytesMax = 12;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置电机进入学习状态
  * @param
  * @retval None
  */
void CurtainSendSetMotorLearn(Serial_Typedef *pSerial)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x15;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,7);
    pSerial->pu8Send[7] = u8Crc;
    pSerial->u16SendBytesMax = 8;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置删除行程
  * @param
  * @retval None
  */
void CurtainSendSetDeleteRoute(Serial_Typedef *pSerial,uint8_t u8SetDeleteRoute)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x02;
    pSerial->pu8Send[6] = 0x16;
    pSerial->pu8Send[7] = u8SetDeleteRoute;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}
/**
  * @brief:设置窗帘类型
  * @param
  * @retval None
  */
void CurtainSendSetCurtainType(Serial_Typedef *pSerial,uint8_t u8SetCurtainType)
{
    uint8_t u8Crc;
    pSerial->pu8Send[0] = 0x5A; 
    pSerial->pu8Send[1] = 0xA5;
    pSerial->pu8Send[2] = 0x5A;
    pSerial->pu8Send[3] = 0xA5;
    pSerial->pu8Send[4] = CURTAIN_CMD_SET;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x17;
    pSerial->pu8Send[7] = u8SetCurtainType;
    u8Crc               = CRC8Maxim_Check (pSerial->pu8Send,8);
    pSerial->pu8Send[8] = u8Crc;
    pSerial->u16SendBytesMax = 9;
    pSerial->u8RetransCnt = 1;
}


/*******************************************************************************************/
/********************************     队列串口发送    *******************************************/
/*******************************************************************************************/


/*******************************查询-0x01-CURTAIN_CMD_READ**********************************/
/**
  * @brief:查询上限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitUp(void) 
{   
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x01;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询下限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitDown(void) 
{   
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x02;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
     
}
/**
  * @brief:查询第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitThrid(void) 
{   
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x03;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询实时限位位置  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryRunLimit(void) 
{   
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x04;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询电机状态  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryRunState(void) 
{   
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x05;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询方向  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryDirect(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x06;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询强电模式  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryHighPowerMode(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x07;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询弱电模式  
  * @param
  * @retval None
  */
void CurtainSendQueueQuerySmallPowerMode(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x08;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询窗帘百分比位置  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLocation(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x09;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询窗帘类型  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryCurtainType(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0A;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询软件版本号  
  * @param
  * @retval None
  */
void CurtainSendQueueQuerySoftVersion(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x17;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:查询电池电量  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryBattery(void) 
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_READ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x18;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}

/****************************控制命令-CURTAIN_CMD_CTRL-0x02*******************************/
/**
  * @brief:控制上运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlOn(void)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x09;
    u8Crc              = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:控制下运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlOff(void)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0A;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:控制停止运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlStop(void)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0B;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief：控制百分比  
  * @param
  * @retval None
  */
void CurtainSendQueueControlSetPercent(uint8_t u8SetPercent)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0C;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetPercent;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief：控制点动  
  * @param
  * @retval None
  */
void CurtainSendQueueControlJoy(uint8_t u8Joy)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_CTRL;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x18;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Joy;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**********************设置命令-CURTAIN_CMD_SET-0x03***************************/
/**
  * @brief:设置上限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitUp(uint8_t u8SetLimitUp)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0D;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetLimitUp;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置下限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitDown(uint8_t u8SetLimitDown)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0E;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetLimitDown;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitThird(uint8_t u8SetLimitThird)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x0F;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetLimitThird;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置换向
  * @param
  * @retval None
  */
void CurtainSendQueueSetDirect(uint8_t u8SetDirect)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x10;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetDirect;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置强电模式
  * @param
  * @retval None
  */
void CurtainSendQueueSetHighPowerMode(uint8_t u8SetHighPowerMode)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x11;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetHighPowerMode;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置弱电模式
  * @param
  * @retval None
  */
void CurtainSendQueueSetSmallPowerMode(uint8_t u8SmallPowerMode)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x12;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SmallPowerMode;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置手拉开关
  * @param
  * @retval None
  */
void CurtainSendQueueSetHandOnOff(uint8_t u8SetHandOnOff)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x13;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetHandOnOff;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置指示灯
  * @param
  * @retval None
  */
void CurtainSendQueueSetLED(uint32_t u32SetLED)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x05;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x14;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u32SetLED>>24 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u32SetLED>>16 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[9] = u32SetLED>>8 ;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[10] = u32SetLED ;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,11);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[11] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 12;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置电机进入学习状态
  * @param
  * @retval None
  */
void CurtainSendQueueSetMotorLearn(void)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x15;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,7);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 8;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置删除行程
  * @param
  * @retval None
  */
void CurtainSendQueueSetDeleteRoute(uint8_t u8SetDeleteRoute)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x02;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x16;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetDeleteRoute;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}
/**
  * @brief:设置窗帘类型
  * @param
  * @retval None
  */
void CurtainSendQueueSetCurtainType(uint8_t u8SetCurtainType)
{
    uint8_t u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[0] = 0x5A; 
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[1] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[2] = 0x5A;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[3] = 0xA5;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[4] = CURTAIN_CMD_SET;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[5] = 0x01;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[6] = 0x17;
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[7] = u8SetCurtainType;
    u8Crc               = CRC8Maxim_Check (CurtainSend.u8Data[CurtainSend.u8End].u8Byte,8);
    CurtainSend.u8Data[CurtainSend.u8End].u8Byte[8] = u8Crc;
    CurtainSend.u8Data[CurtainSend.u8End].u8ByteMax = 9;
    CurtainSendQueue_IntoQueue();
}







/*****************************END OF FILE****/
