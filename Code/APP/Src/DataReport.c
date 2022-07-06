
/*!
*****************************************************************
$Name$
$Revision: 
$Date: 
\file 
\brief  
\author zhoujinbang


<b>Company:</b>\nmenred automation\n
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
#include "BSP.h"
/* User App */
#include "Dataconfigure.h"

#include "..\..\BSP_Include.h"

#include "main.h"
#include "BSP.h"
#include "DataReport.h"
#include "EnOceanTelegram.h"
#include "EnOceanMSC.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
ReportedData_Typedef ReportedData;

/* Private function prototypes -----------------------------------------------*/


/**
   * @brief
   * @param
   * @retval
   */
void EnoceanSend_Tick1ms(ReportedData_Typedef *pReportedData)
{
    if (pReportedData->u32SendWait)
    {
        pReportedData->u32SendWait--;
    }
    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t Enocean_ReportFlag(ReportedData_Typedef *pReportedData)
{
    //if (pReportedData->u8RecordFaultCode != CurtainRun.eFaultCode )
    if ( CurtainRun.eFaultCode != eCURTAINRUN_NORMAL )
    {
        pReportedData->u8ReportedFaultCodeFlag = 0x01;
        pReportedData->u8RecordFaultCode = CurtainRun.eFaultCode; 
        return OK;
    }
    else if (pReportedData->u8RecordPercentage != CurtainData.Query.u8CurtainPercentage )
    {
        pReportedData->u8ReportedPercentageFlag = 0x01;
        pReportedData->u8RecordPercentage = CurtainData.Query.u8CurtainPercentage;
        return OK;
    }
    else if (pReportedData->u8RecordMotorDirection != CurtainData.Query.u8MotorDirection)
    {
        pReportedData->u8ReportedMotorDirectionFlag = 0x01;
        pReportedData->u8RecordMotorDirection = CurtainData.Query.u8MotorDirection;
        return OK;
    }
    else if (pReportedData->u32RecordRealLocation != CurtainData.Query.u32RealtimeLimt)
    {
        pReportedData->u8ReportedRealLocationFlag = 0x01;
        pReportedData->u32RecordRealLocation = CurtainData.Query.u32RealtimeLimt;
        return OK;
    }
    else if (pReportedData->u32RecordUpLimit != CurtainData.Query.u32UpLimit)
    {
        pReportedData->u8ReportedUpLimitFlag = 0x01;
        pReportedData->u32RecordUpLimit = CurtainData.Query.u32UpLimit;
        return OK;
    }
    else if (pReportedData->u32RecordDownLimit != CurtainData.Query.u32DownLimit)
    {
        pReportedData->u8ReportedDownLimitFlag = 0x01;
        pReportedData->u32RecordDownLimit = CurtainData.Query.u32DownLimit;
        return OK;
    }
    else
    {
        pReportedData->u8ReportedFaultCodeFlag      = 0x00;
        pReportedData->u8ReportedPercentageFlag     = 0x00;
        pReportedData->u8ReportedMotorDirectionFlag = 0x00;
        pReportedData->u8ReportedRealLocationFlag   = 0x00;
        pReportedData->u8ReportedUpLimitFlag        = 0x00;
        pReportedData->u8ReportedDownLimitFlag      = 0x00;
        return OK;
    }
    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t EnOcean_ReportSelect(ReportedData_Typedef *pReportedData)
{
    if (pReportedData->u8ReportedFaultCodeFlag == 0x01)
    {
        pReportedData->eRunState = Enocean_Send_FaultCode;
        pReportedData->u8ReportedFaultCodeFlag = 0x00;
        pReportedData->u32SendWait = 5*1000;
        return OK;
    }
    else if (pReportedData->u8ReportedPercentageFlag == 0x01)
    {
        pReportedData->eRunState = eENOCEAN_SEND_PERCENTAGE;
        pReportedData->u8ReportedPercentageFlag = 0x00;
        pReportedData->u32SendWait = 200;
        return OK;
    }
    else if (pReportedData->u8ReportedRealLocationFlag == 0x01)
    {
        //pReportedData->eRunState = eENOCEAN_SEND_REALLOCATION;
        pReportedData->u8ReportedRealLocationFlag = 0x00;
        pReportedData->u32SendWait = 200;
        return OK;
    }
    else if (pReportedData->u8ReportedUpLimitFlag == 0x01)
    {
        pReportedData->eRunState = eENOCEAN_SEND_UPLIMIT;
        pReportedData->u8ReportedUpLimitFlag = 0x00;
        pReportedData->u32SendWait = 200;
        return OK;
    }
    else if (pReportedData->u8ReportedDownLimitFlag == 0x01)
    {
        pReportedData->eRunState = eENOCEAN_SEND_DOWNLIMIT;
        pReportedData->u8ReportedDownLimitFlag = 0x00;
        pReportedData->u32SendWait = 200;
        return OK;
    }
    else if (pReportedData->u8ReportedMotorDirectionFlag == 0x01)
    {
        pReportedData->eRunState = eENOCEAN_SEND_MOTORDIRECTION;
        pReportedData->u8ReportedMotorDirectionFlag = 0x00;
        pReportedData->u32SendWait = 200;
        return OK;
    }
    else
    {
        //pReportedData->eRunState = eENOCEAN_SEND_PERCENTAGE;
        //pReportedData->u32SendWait = 1000;        
        return !OK;
    }
    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOcean_ProactiveReport(ReportedData_Typedef *pReportedData)
{

    
    switch (pReportedData->eRunState)
    {
    case eENOCEAN_SEND_IDLE:

        Enocean_ReportFlag(pReportedData);
        EnOcean_ReportSelect(pReportedData);
        //pReportedData->u32SendWait = 200;
        break;

    case Enocean_Send_FaultCode: //故障上报

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x00, MB_INPUT_ERROR_STATUS);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;

    case eENOCEAN_SEND_PERCENTAGE://上报百分比位置

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        if ( CurtainData.Query.u32UpLimit == 0x00FFFF00  ||  CurtainData.Query.u32DownLimit == 0xFF000000 )
        {
            break;
        }
        EEPD20502_ReplyPositionandAngle_04(&Radio);
        //EnOceanMSCSend(&Radio, &Dev, 0x00, MB_HOLD_CURTAIN_PERCENTAGE_CONTROL);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break; 
    /*
    case eENOCEAN_SEND_REALLOCATION://上报实时位置

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        EnOceanMSCSend32Data(&Radio, &Dev, 0x00, MB_INPUT_REAl_LIMIT,CurtainData.Query.u32RealtimeLimt);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;
    */
    case eENOCEAN_SEND_UPLIMIT:  //上报上限位值

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        EnOceanMSCSend32Data(&Radio, &Dev, 0x00, MB_INPUT_UP_LIMIT,CurtainData.Query.u32UpLimit);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;

    case eENOCEAN_SEND_DOWNLIMIT: //上报下限位值

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        EnOceanMSCSend32Data(&Radio, &Dev, 0x00, MB_INPUT_DOWN_LIMIT,CurtainData.Query.u32DownLimit);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;

    case eENOCEAN_SEND_MOTORDIRECTION: //上报电机方向

        if (pReportedData->u32SendWait != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x00, MB_HOLD_COMMUTATION_SET);
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;

 

    default:
        pReportedData->eRunState = eENOCEAN_SEND_IDLE;
        break;
    }
}