

#ifndef _EnOceanTELEGRAM_H_
#define _EnOceanTELEGRAM_H_


#include "EnOceanlibInclude.h"


/**
  * @brief 
  * @param
  * @retval None
  */
void EnoceanPassiveSwitchSetTime_1ms(void);
/**
  * @brief
  * @param
  * @retval None
  * 清理各个标记位
  */
void ClearAllFlag(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanHandler(uint8_t u8SendIntervalPeriodSet);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanLearnSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanCurtain(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanOled(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadio(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMSC(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_ReceiveAndResponse(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_GotoPositionandAngle_01(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD20502_ReplyPositionandAngle_04(Radio_Typedef *pRadio);
/**
  * @brief  Enocean手动学习
  * @param
  * @retval None
  */
void EnOceanManualLearn(Radio_Typedef *pRadio);
/**
  * @brief  Enocean学习处理函数
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanLearnSensor(Radio_Typedef *pRadio,uint8_t u8LearnChannel, uint8_t u8LearnOutMode);
/**
  * @brief  Enocean手动清除
  * @param
  * @retval None
  */
void EnOceanManualClear(void);
/**
  * @brief  Enocean设置按键
  * @param
  * @retval None
  */
void EnOceanRPSSetButton(void);
/**
  * @brief  Enocean手动设置
  * @param
  * @retval None
  */
void EnOceanManualSet(void);
/**
  * @brief  Enocean接收数据处理
  * @param
  * @retval None
  */
uint8_t EnOceanRPSOnOffData(void);


/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE CurtainManualLearnSensor(uint8_t u8LearnChannel, uint8_t u8LearnCmd);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetAirBoxByMSC(Radio_Typedef *pRadio,uint16_t *pu16T,uint8_t *pu8T,uint16_t *pu16CO2,uint16_t *pu16C2HO,uint16_t *pu16PM25);
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE Oled_ManualLearnSensor(ID_SEARCH_TYPE *pSearch);
/**
  * @brief  
  * @param
  * @retval None 
  */
//#pragma location = "IPECODE16"
RM_RETURN_TYPE EnOceanReman(Radio_Typedef *pRadio);
 /**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMapChannel(uint8_t u8MapChannel, uint8_t *pu8IOChannel, uint8_t u8CascadeAdd);
/**
  * @brief
  * @param
  * @retval None
  * 333 打开触发电机学习专用遥控器命令
  */
RM_RETURN_TYPE EnoceanRemanMotorLearnDev_333(Radio_Typedef *pRadio);
/**
  * @brief  EnOcean 303
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadLearnIds_303(Radio_Typedef *pRadio);
/**
  * @brief  EnOcean 309
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManTestDevChannel_309(Radio_Typedef *pRadio);

#endif

