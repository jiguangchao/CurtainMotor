
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DATA_REPORT_H_
#define __DATA_REPORT_H_

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"

typedef enum
{
    eENOCEAN_SEND_IDLE = 0x00, //闲置状态
    Enocean_Send_FaultCode, //发送故障码

    eENOCEAN_SEND_PERCENTAGE,     //上报百分比位置
    eENOCEAN_SEND_REALLOCATION,   //上报实时位置
    eENOCEAN_SEND_UPLIMIT,        //上报上限位值
    eENOCEAN_SEND_DOWNLIMIT,      //上报下限位值
    eENOCEAN_SEND_MOTORDIRECTION, //上报电机方向
    

} eEnoceanState_TYPE;

typedef struct
{
	eEnoceanState_TYPE  eRunState;
    

	uint32_t u32SendWait;

    uint8_t u8RecordFaultCode;             //记录故障码
    uint8_t u8RecordPercentage;            //记录百分比位置
    uint8_t u8RecordMotorDirection;        //记录电机方向
    uint32_t u32RecordRealLocation;        //记录实时位置
    uint32_t u32RecordUpLimit;             //记录上限位
    uint32_t u32RecordDownLimit;           //记录下限位

    uint8_t u8ReportedFaultCodeFlag;       //故障码上报标记
    uint8_t u8ReportedPercentageFlag;      //上报百分比位置标记
    uint8_t u8ReportedRealLocationFlag;    //上报实时位置标记
    uint8_t u8ReportedUpLimitFlag;         //上报上限位值标记
    uint8_t u8ReportedDownLimitFlag;       //上报下限位值标记
    uint8_t u8ReportedMotorDirectionFlag;  //上报电机方向标记

    
}ReportedData_Typedef;


extern ReportedData_Typedef ReportedData;


/**
   * @brief
   * @param
   * @retval
   */
void EnoceanSend_Tick1ms(ReportedData_Typedef *pReportedData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t Enocean_ReportFlag(ReportedData_Typedef *pReportedData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t EnOcean_ReportSelect(ReportedData_Typedef *pReportedData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOcean_ProactiveReport(ReportedData_Typedef *pReportedData);




#endif