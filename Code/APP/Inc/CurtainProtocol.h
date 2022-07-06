/*!
*****************************************************************
	\file 				
	\brief 				Curtain code
	\author 			xuyixin

    <b>Company:</b>\n	menred automation\n
修改记录
*****************************************************************/

#ifndef _CURTAIN_PROTOCOL_H_
#define _CURTAIN_PROTOCOL_H_

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "BSP.h"

#include "main.h"
#include "CurtainProtocol.h"

/*============================ MACROS ========================================*/
//#define IIC_NOTE       (0)

#define CURTAIN_MESSAGE_HEAD                     (0x5AA55AA5)    //message  head

/*============================ IMPLEMENTATION ================================*/
/******************************************************************************/
#define CURTAIN_CMD_READ                         (0x01)
#define CURTAIN_CMD_REPLY_READ                   (0x81)
#define CURTAIN_CMD_CTRL                         (0x02)
#define CURTAIN_CMD_REPLY_CTRL                   (0x82)
#define CURTAIN_CMD_SET                          (0x03)
#define CURTAIN_CMD_REPLY_SET                    (0x83)

#define CURTAIN_CMD_REPORT                       (0x04)



/*******************************查询-0x01-CURTAIN_CMD_READ**********************************/
/**
  * @brief:查询上限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitUp(Serial_Typedef *pSerial);
/**
  * @brief:查询下限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitDown(Serial_Typedef *pSerial); 
/**
  * @brief:查询第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueryLimitThrid(Serial_Typedef *pSerial); 
/**
  * @brief:查询实时限位位置  
  * @param
  * @retval None
  */
void CurtainSendQueryRunLimit(Serial_Typedef *pSerial); 
/**
  * @brief:查询电机状态  
  * @param
  * @retval None
  */
void CurtainSendQueryRunState(Serial_Typedef *pSerial); 
/**
  * @brief:查询方向  
  * @param
  * @retval None
  */
void CurtainSendQueryDirect(Serial_Typedef *pSerial); 
/**
  * @brief:查询强电模式  
  * @param
  * @retval None
  */
void CurtainSendQueryHighPowerMode(Serial_Typedef *pSerial);
/**
  * @brief:查询弱电模式  
  * @param
  * @retval None
  */
void CurtainSendQuerySmallPowerMode(Serial_Typedef *pSerial); 
/**
  * @brief:查询窗帘百分比位置  
  * @param
  * @retval None
  */
void CurtainSendQueryLocation(Serial_Typedef *pSerial); 
/**
  * @brief:查询窗帘类型  
  * @param
  * @retval None
  */
void CurtainSendQueryCurtainType(Serial_Typedef *pSerial); 
/**
  * @brief:查询软件版本号  
  * @param
  * @retval None
  */
void CurtainSendQuerySoftVersion(Serial_Typedef *pSerial); 
/**
  * @brief:查询电池电量  
  * @param
  * @retval None
  */
void CurtainSendQueryBattery(Serial_Typedef *pSerial);


/****************************控制命令-CURTAIN_CMD_CTRL-0x02*******************************/
/**
  * @brief:控制上运行  
  * @param
  * @retval None
  */
void CurtainSendControlOn(Serial_Typedef *pSerial);
/**
  * @brief:控制下运行  
  * @param
  * @retval None
  */
void CurtainSendControlOff(Serial_Typedef *pSerial);
/**
  * @brief:控制停止运行  
  * @param
  * @retval None
  */
void CurtainSendControlStop(Serial_Typedef *pSerial);
/**
  * @brief：控制百分比  
  * @param
  * @retval None
  */
void CurtainSendControlSetPercent(Serial_Typedef *pSerial,uint8_t u8Joy);
/**
  * @brief：控制点动  
  * @param
  * @retval None
  */
void CurtainSendControlJoy(Serial_Typedef *pSerial,uint8_t u8SetPercent);

/**********************设置命令-CURTAIN_CMD_SET-0x03***************************/
/**
  * @brief:设置上限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitUp(Serial_Typedef *pSerial,uint8_t u8SetLimitUp);
/**
  * @brief:设置下限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitDown(Serial_Typedef *pSerial,uint8_t u8SetLimitDown);
/**
  * @brief:设置第三点限位
  * @param
  * @retval None
  */
void CurtainSendSetLimitThird(Serial_Typedef *pSerial,uint8_t u8SetLimitThird);
/**
  * @brief:设置换向
  * @param
  * @retval None
  */
void CurtainSendSetDirect(Serial_Typedef *pSerial,uint8_t u8SetDirect);
/**
  * @brief:设置强电模式
  * @param
  * @retval None
  */
void CurtainSendSetHighPowerMode(Serial_Typedef *pSerial,uint8_t u8SetHighPowerMode);
/**
  * @brief:设置弱电模式
  * @param
  * @retval None
  */
void CurtainSendSetSmallPowerMode(Serial_Typedef *pSerial,uint8_t u8SmallPowerMode);
/**
  * @brief:设置手拉开关
  * @param
  * @retval None
  */
void CurtainSendSetHandOnOff(Serial_Typedef *pSerial,uint8_t u8SetHandOnOff);
/**
  * @brief:设置指示灯
  * @param
  * @retval None
  */
void CurtainSendSetLED(Serial_Typedef *pSerial,uint32_t u32SetLED);
/**
  * @brief:设置电机进入学习状态
  * @param
  * @retval None
  */
void CurtainSendSetMotorLearn(Serial_Typedef *pSerial);
/**
  * @brief:设置删除行程
  * @param
  * @retval None
  */
void CurtainSendSetDeleteRoute(Serial_Typedef *pSerial,uint8_t u8SetDeleteRoute);
/**
  * @brief:设置窗帘类型
  * @param
  * @retval None
  */
void CurtainSendSetCurtainType(Serial_Typedef *pSerial,uint8_t u8SetCurtainType);


/*******************************************************************************************/
/********************************     队列串口发送    *******************************************/
/*******************************************************************************************/


/*******************************查询-0x01-CURTAIN_CMD_READ**********************************/
/**
  * @brief:查询上限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitUp(void);
/**
  * @brief:查询下限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitDown(void);
/**
  * @brief:查询第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLimitThrid(void);
/**
  * @brief:查询实时限位位置  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryRunLimit(void);
/**
  * @brief:查询电机状态  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryRunState(void);
/**
  * @brief:查询方向  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryDirect(void);
/**
  * @brief:查询强电模式  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryHighPowerMode(void);
/**
  * @brief:查询弱电模式  
  * @param
  * @retval None
  */
void CurtainSendQueueQuerySmallPowerMode(void);
/**
  * @brief:查询窗帘百分比位置  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryLocation(void);
/**
  * @brief:查询窗帘类型  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryCurtainType(void);
/**
  * @brief:查询软件版本号  
  * @param
  * @retval None
  */
void CurtainSendQueueQuerySoftVersion(void);
/**
  * @brief:查询电池电量  
  * @param
  * @retval None
  */
void CurtainSendQueueQueryBattery(void);

/****************************控制命令-CURTAIN_CMD_CTRL-0x02*******************************/
/**
  * @brief:控制上运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlOn(void);
/**
  * @brief:控制下运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlOff(void);
/**
  * @brief:控制停止运行  
  * @param
  * @retval None
  */
void CurtainSendQueueControlStop(void);
/**
  * @brief：控制百分比  
  * @param
  * @retval None
  */
void CurtainSendQueueControlSetPercent(uint8_t u8SetPercent);
/**
  * @brief：控制点动  
  * @param
  * @retval None
  */
void CurtainSendQueueControlJoy(uint8_t u8Joy);

/**********************设置命令-CURTAIN_CMD_SET-0x03***************************/
/**
  * @brief:设置上限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitUp(uint8_t u8SetLimitUp); 
/**
  * @brief:设置下限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitDown(uint8_t u8SetLimitDown);
/**
  * @brief:设置第三点限位
  * @param
  * @retval None
  */
void CurtainSendQueueSetLimitThird(uint8_t u8SetLimitThird);
/**
  * @brief:设置换向
  * @param
  * @retval None
  */
void CurtainSendQueueSetDirect(uint8_t u8SetDirect);
/**
  * @brief:设置强电模式
  * @param
  * @retval None
  */
void CurtainSendQueueSetHighPowerMode(uint8_t u8SetHighPowerMode);
/**
  * @brief:设置弱电模式
  * @param
  * @retval None
  */
void CurtainSendQueueSetSmallPowerMode(uint8_t u8SmallPowerMode);
/**
  * @brief:设置手拉开关
  * @param
  * @retval None
  */
void CurtainSendQueueSetHandOnOff(uint8_t u8SetHandOnOff);
/**
  * @brief:设置指示灯
  * @param
  * @retval None
  */
void CurtainSendQueueSetLED(uint32_t u32SetLED);
/**
  * @brief:设置电机进入学习状态
  * @param
  * @retval None
  */
void CurtainSendQueueSetMotorLearn(void);
/**
  * @brief:设置删除行程
  * @param
  * @retval None
  */
void CurtainSendQueueSetDeleteRoute(uint8_t u8SetDeleteRoute);
/**
  * @brief:设置窗帘类型
  * @param
  * @retval None
  */
void CurtainSendQueueSetCurtainType(uint8_t u8SetCurtainType);




#endif
