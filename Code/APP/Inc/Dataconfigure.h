

#ifndef _DATA_CONFIGURE_H_
#define _DATA_CONFIGURE_H_

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"



/**********************************************************************************************************************/
#define CURTAIN_SOFT_VERSION                                       (0x0001)

#define CURTAIN_HW_VERSION                                            (0x10)
#define CURTAIN_FW_VERSION                                            (0x10)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*************************************** FLASH *************************************************************************/
/**********************************************************************************************************************/

#define FLASH_PAGE_NUM                                                  (4)


/**********************************************************************************************************************/
    #define OUT_CHANNEL_NUMS                                            (1)
    /* EEP: D201XX channel is from 0 to 30 */
    /* Use Chip ID */
    #define PAGE_MSC_LIGHT_START                                        (0x01)
    #define PAGE_MSC_LIGHT_END                                          (0x04)
    /* 30 Channels like the EEP */                                                                            
    #define MODBUS_LIGHT_CHANNLE_START                                  (0x0100)// 0x01 00 -- 0x00 FF
    #define MODBUS_LIGHT_CHANNLE_END                                    (0x0300)// 0x1D 00 -- 0x00 FF
    #define LIGHT_CHANNEL_0                                             (1)
    #define LIGHT_CHANNEL_1                                             (2)
    #define LIGHT_CHANNEL_2                                             (3)
    #define LIGHT_CHANNEL_3                                             (4)


#define DEV_CHANNEL                                                 (0)


#define INVALID_PAGE_VALUE                                          (0xFF)
/**********************************************************************************************************************/
/********************* Data reg permission mask *******************************************/
/**********************************************************************************************************************/
#define REG_PERMISSION_N                                            (0x00)
#define REG_PERMISSION_X                                            (0x04)
#define REG_PERMISSION_R                                            (0x02)
#define REG_PERMISSION_W                                            (0x01)
#define REG_VALUE_RANGE_ENABLE                                      (1)
#define REG_VALUE_RANGE_DISABLE                                     (0)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* 0 -- 255 dev have max 256 parameter */

#define MB_INPUT_BASE                                               (0x00)
#define MB_HOLD_BASE                                                (0x00)

#define MB_EQUIPMENT_BASE                                           (0x00)  
#define MB_SENSOR_BASE                                              (0x00)   

#if 0
/* dev read */
/* dev run can only read */
/*          只读寄存器             */
#define MB_INPUT_SOFT_VERSION                                       (MB_EQUIPMENT_BASE+0x01)  //软件版本号
#define MB_INPUT_HARD_VERSION                                       (MB_EQUIPMENT_BASE+0x02)  //硬件版本号
#define MB_INPUT_SIGNAL_STRENGTH                                    (MB_EQUIPMENT_BASE+0x03)  //信号强度
#define MB_INPUT_LASTTIME_GATEWAY_RSSI                              (MB_EQUIPMENT_BASE+0x04)  //上次接收网关 RSSI值
#define MB_INPUT_LASTTIME_SWITCH_RSSI                               (MB_EQUIPMENT_BASE+0x05)  //上次接收开关 RSSI值
#define MB_INPUT_RUN_TIME                                           (MB_EQUIPMENT_BASE+0x06)  //运行时间
#define MB_INPUT_RESET_PASSWORD                                     (MB_EQUIPMENT_BASE+0x07)  //复位密码（保留）
#define MB_INPUT_ERROR_STATUS                                       (MB_EQUIPMENT_BASE+0x08)  //错误状态
#define MB_INPUT_PERCENTAGE                                         (MB_EQUIPMENT_BASE+0x09)  //百分比位置

#define MB_INPUT_REAl_LIMIT                                         (MB_EQUIPMENT_BASE+0x10)  //实时位置
#define MB_INPUT_REAl_LIMIT_HIGH                                    (MB_EQUIPMENT_BASE+0x10)  //实时位置高16位
#define MB_INPUT_REAl_LIMIT_LOW                                     (MB_EQUIPMENT_BASE+0x11)  //实时位置低16位

#define MB_INPUT_UP_LIMIT                                           (MB_EQUIPMENT_BASE+0x12)  //上限位值
#define MB_INPUT_UP_LIMIT_HIGH                                      (MB_EQUIPMENT_BASE+0x12)  //上限位值高16位
#define MB_INPUT_UP_LIMIT_LOW                                       (MB_EQUIPMENT_BASE+0x13)  //上限位值低16位

#define MB_INPUT_DOWN_LIMIT                                         (MB_EQUIPMENT_BASE+0x14)  //下限位值
#define MB_INPUT_DOWN_LIMIT_HIGH                                    (MB_EQUIPMENT_BASE+0x14)  //下限位值高16位
#define MB_INPUT_DOWN_LIMIT_LOW                                     (MB_EQUIPMENT_BASE+0x15)  //下限位值低16位

/*          读写寄存器               */
#define MB_HOLD_CURTAIN_PERCENTAGE_CONTROL                          (MB_EQUIPMENT_BASE + 0x49)  //百分比控制窗帘
#define MB_HOLD_MOTOR_ACTION_CMD                                    (MB_EQUIPMENT_BASE + 0x50)  //电机动作命令
#define MB_HOLD_MOTOR_TRIP_SET                                      (MB_EQUIPMENT_BASE + 0x51)  //电机行程设置
#define MB_HOLD_TOUCH_SET                                           (MB_EQUIPMENT_BASE + 0x52)  //轻触设置
#define MB_HOLD_COMMUTATION_SET                                     (MB_EQUIPMENT_BASE + 0x53)  //电机换向设置
#define MB_HOLD_CLEAR_TRIP_SET                                      (MB_EQUIPMENT_BASE + 0x54)  //清除行程设置

#define MB_HOLD_MANUAL_SET_BORDAR                                   (MB_EQUIPMENT_BASE + 0x55)  //手动设置边界
#define MB_HOLD_MANUAL_SET_BORDAR_ON                                (MB_EQUIPMENT_BASE + 0x56)  //打开手动设置边界
#define MB_HOLD_MANUAL_SET_BORDAR_OFF                               (MB_EQUIPMENT_BASE + 0x57)  //关闭手动设置边界
#define MB_HOLD_MAX_TRIP_SET                                        (MB_EQUIPMENT_BASE + 0x58)  //设置最大行程
#define MB_HOLD_MIN_TRIP_SET                                        (MB_EQUIPMENT_BASE + 0x59)  //设置最小行程

#define MB_HOLD_ENOCEAN_REAPTER                                     (MB_EQUIPMENT_BASE + 0x60)  //Enocean Reapter
#define MB_HOLD_RESET_INITIALIZE                                    (MB_EQUIPMENT_BASE + 0x61)  //恢复出厂参数

/*
#define MB_HOLD_LEARN_ENABLE                                        (MB_EQUIPMENT_BASE + 0x14)  //学习使能
#define MB_HOLD_WORK_MODE_SET                                       (MB_EQUIPMENT_BASE + 0x41)  //工作模式设置
*/
#endif
/* dev read */
/* dev run can only read */
/*          只读寄存器             */
#define MB_INPUT_SIGNAL_STRENGTH                                    (MB_EQUIPMENT_BASE+0x01)  //信号强度
#define MB_INPUT_RATE_RXTX                                          (MB_EQUIPMENT_BASE+0x02)  //通讯成功率
#define MB_INPUT_ONLINE                                             (MB_EQUIPMENT_BASE+0x03)  //在线状态
#define MB_INPUT_ERROR_STATUS                                       (MB_EQUIPMENT_BASE+0x04)  //错误状态
#define MB_INPUT_SOFT_VERSION                                       (MB_EQUIPMENT_BASE+0x05)  //软件版本号
#define MB_INPUT_HARD_VERSION                                       (MB_EQUIPMENT_BASE+0x06)  //硬件版本号
#define MB_INPUT_RUN_TIME                                           (MB_EQUIPMENT_BASE+0x07)  //运行时间（保留）

#define MB_INPUT_OUTPUT_NUM                                         (MB_EQUIPMENT_BASE+0x20)  //输出动作次数（保留）
#define MB_INPUT_PERCENTAGE                                         (MB_EQUIPMENT_BASE+0x21)  //百分比位置
#define MB_INPUT_REAl_LIMIT                                         (MB_EQUIPMENT_BASE+0x22)  //实时位置
#define MB_INPUT_REAl_LIMIT_HIGH                                    (MB_EQUIPMENT_BASE+0x22)  //实时位置高16位
#define MB_INPUT_REAl_LIMIT_LOW                                     (MB_EQUIPMENT_BASE+0x23)  //实时位置低16位

#define MB_INPUT_UP_LIMIT                                           (MB_EQUIPMENT_BASE+0x24)  //上限位值
#define MB_INPUT_UP_LIMIT_HIGH                                      (MB_EQUIPMENT_BASE+0x24)  //上限位值高16位
#define MB_INPUT_UP_LIMIT_LOW                                       (MB_EQUIPMENT_BASE+0x25)  //上限位值低16位

#define MB_INPUT_DOWN_LIMIT                                         (MB_EQUIPMENT_BASE+0x26)  //下限位值
#define MB_INPUT_DOWN_LIMIT_HIGH                                    (MB_EQUIPMENT_BASE+0x26)  //下限位值高16位
#define MB_INPUT_DOWN_LIMIT_LOW                                     (MB_EQUIPMENT_BASE+0x27)  //下限位值低16位

/*          读写寄存器               */
#define MB_HOLD_ENOCEAN_REAPTER                                     (MB_EQUIPMENT_BASE + 0x10)  //Enocean Reapter
#define MB_INPUT_RESET_PASSWORD                                     (MB_EQUIPMENT_BASE + 0x11)  //复位密码（保留）
#define MB_HOLD_RESET_INITIALIZE                                    (MB_EQUIPMENT_BASE + 0x12)  //恢复出厂参数

#define MB_HOLD_MOTOR_ACTION_CMD                                    (MB_EQUIPMENT_BASE + 0x30)  //电机动作命令
#define MB_HOLD_CURTAIN_PERCENTAGE_CONTROL                          (MB_EQUIPMENT_BASE + 0x31)  //百分比控制窗帘

#define MB_HOLD_MOTOR_TRIP_SET                                      (MB_EQUIPMENT_BASE + 0x39)  //电机行程设置
#define MB_HOLD_TOUCH_SET                                           (MB_EQUIPMENT_BASE + 0x40)  //轻触设置
#define MB_HOLD_CURTAIN_MODE_SET                                    (MB_EQUIPMENT_BASE + 0x41)  //窗帘模式（保留）
#define MB_HOLD_COMMUTATION_SET                                     (MB_EQUIPMENT_BASE + 0x42)  //电机换向设置
#define MB_HOLD_CLEAR_TRIP_SET                                      (MB_EQUIPMENT_BASE + 0x43)  //清除行程设置

#define MB_HOLD_MANUAL_SET_BORDAR                                   (MB_EQUIPMENT_BASE + 0x55)  //手动设置边界（保留）
#define MB_HOLD_MANUAL_SET_BORDAR_ON                                (MB_EQUIPMENT_BASE + 0x56)  //打开手动设置边界（保留）
#define MB_HOLD_MANUAL_SET_BORDAR_OFF                               (MB_EQUIPMENT_BASE + 0x57)  //关闭手动设置边界（保留）

#define MB_HOLD_MAX_TRIP_SET                                        (MB_EQUIPMENT_BASE + 0x45)  //设置最大行程
#define MB_HOLD_MIN_TRIP_SET                                        (MB_EQUIPMENT_BASE + 0x46)  //设置最小行程


/**********************************************************************************************************************/

/**********************************************************************************************************************/

typedef struct
{
  uint8_t u8FactorySetCount;//出厂设置计数  
  uint8_t u8FactorySetFlag; //出厂设置标记

  uint8_t u8CfgUpdateFlag; //配置更新标记
  uint8_t u8LogUpdateFlag; //日志更新标记
  uint8_t u8LearnUpdateFlag; //学习更新标记
  uint8_t u8SaveCount; //保存计数

  uint32_t u32FlashWriteTime;  //写入等待

  uint32_t u32CRCTest;

}eFLASH_RunTypedef;



typedef union 
{
    struct
    {
        uint32_t                 u32RemanCode;
        uint32_t                 u32ResetPassword;    //复位密码
        uint32_t                 u32EnOceanChipID;
        uint32_t                 u32EnOceanBaseID;

        uint8_t                  u8Repeater;   
        uint8_t                  u8Repeater0;  
        uint8_t                  u8Repeater1; 
        uint8_t                  u8Repeater2; 
        uint8_t                  u8RadioInterval;  

        uint8_t                  u8CfgBlockCnt;              //写入页面计数
        uint8_t                  u8LogBlockCnt;              //写入页面计数
        uint8_t                  u8LearnBlockCnt;            //写入页面计数


    };
    uint32_t u32Words[20];
    
}HWCfg_Typedef;

typedef union 
{
    struct
    {                            
        uint32_t            u32RunTime;
        uint32_t            u32PowerOnCount;
        uint32_t            u32SoftFaultCount;

        uint16_t            u16FlashReadSuccessCount;  //读成功计数
        uint16_t            u16FlashReadFailCount;   //读失败计数

        uint16_t            u16FlashWriteSuccessCount; //写成功计数
        uint16_t            u16FlashWriteFailCount;    //写失败计数
    };

    uint32_t u32Words[20];

}HWLogInfo_Typedef;

typedef struct
{
    uint32_t            u32BuildYYMMDD;
    uint32_t            u32BuildHHMMSS;
    uint16_t            u16HWVersion;
    uint16_t            u16FWVersion;
 
    uint32_t            u32Error;
    uint16_t            u16CleanErrorFlagTime;

    uint8_t             u8ErrorSendTime;
    uint8_t             u8EnOceanError;
    uint8_t             u8EraseFlag;

    uint8_t             u8RunUpdate;
    uint8_t             u8DataUpdate;
    
    uint8_t             u8PowerOnFlag;             //上电标志

    uint8_t             u8CfgUpdate;               //配置更新
    uint8_t             u8LogUpdate;               //日志更新
    uint8_t             u8SaveCount;               //保存计数 
    
    uint8_t             u8PassiveSwitchCount;      //无源开关按键计数

    uint8_t             u8RemoteControlLreanFlag;     //遥控器学习标志
    uint32_t            u32RemoteControlLreanTime;    //remote control 遥控器学习时间

    uint32_t            u32PassiveSwitchSetContinuedTime;  //无源开关按键设置持续时间
    uint32_t            u32PassiveSwitchSetTime;     //无源开关按键设置计时
    uint8_t             u8PassiveSwitchSetCount;     //无源开关按键设置次数
    uint8_t             u8PassiveSwitchSetTimeFalg;  //无源开关按键设置计时标记
    uint8_t             u8PassiveSwitchSetModeFalg;  //无源开关按键设置模式标记



    
}DevRun_Typedef;

typedef struct
{

  uint32_t u32EnOceanRxID;
  uint32_t u32EnOceanRxCount;
  uint32_t u32EnOceanRPSID;
  uint32_t u32EnOceanRPSRxCount;
  uint32_t u32EnOcean4BSID;
  uint32_t u32EnOcean4BSRxCount;
  uint32_t u32EnOcean1BSID;
  uint32_t u32EnOcean1BSRxCount;
  uint32_t u32EnOceanVLDID;
  uint32_t u32EnOceanVLDRxCount;
  uint32_t u32EnOceanMSCID;
  uint32_t u32EnOceanMSCRxCount;

  uint32_t u32TransmitCount[4];
  uint32_t u32TouchPressedID[4];
  uint32_t u32TouchReleaseID[4];
  uint32_t u32TouchRPSCount[4];

} DevDebug_Typedef;

typedef struct
{
    uint8_t             u8State;
    uint8_t             u8ManualLearnState;
    uint8_t             u8LearnState;
    uint8_t             u8LearnChannel;
    uint8_t             u8LearnMode;
    uint8_t             u8LearnSuccessTime;
    uint8_t             u8LearnAutoSendEEPTime;
	  uint8_t             u8LearnSendEvent;
    uint32_t            u32ManualLearnTiming;  //手动学习状态定时

}DevManual_Typedef;

typedef struct
{
    HWCfg_Typedef      Cfg;
    HWLogInfo_Typedef  Log;
    DevRun_Typedef         ;
    DevDebug_Typedef       ;    

    DevManual_Typedef;    


}Dev_Typedef;





/*******************************************************************************/
/*******************************************************************************/
extern Dev_Typedef  Dev;
extern eFLASH_RunTypedef         FLASHRUN;


extern const RegTab_Typedef DevRegTab[];

uint8_t Dev_GetRegTabSize(void);
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_DevRunSave(void);
/**
  * @brief  清除学习表的全部内容
  * @param
  * @retval None
  */
void  EnOceanClearLearnListAll(void);
/**
   * @brief
   * @param
   * @retval
   */
uint8_t NVM_ChannelUpdate(uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t ValueSetValidByBuff(uint8_t u8ValueSet,uint8_t const *pu8Buff,uint8_t u8BuffSize);
/**
  * @brief
  * @param
  * @retval None
  */
void HardWareLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettingsByReset(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultData(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultDataByReset(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultEnable(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_FactorySettings(void); //FLASHRUN 写入出厂设置参数
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_LOG(void);  //FLASH读写日志
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Erase(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_CfgDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Cfg(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_CfgDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LogDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Log(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LogDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLog(uint32_t u32add);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWCfg(uint32_t u32add);
/****************************************************************************************************************/
/********************************          Learn Flash        ***************************************************/
/*****************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_Learn(void); //FLASHRUN 写入学习表
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LearnDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Learn(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LearnDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLearn(uint32_t u32add);

#endif
