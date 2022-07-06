
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
/* User App */
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "Debug.h"
//#include "HWTest.h"

#include "SysError.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 


/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/




/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/




/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrorInit(void)
{


    RS485_GetConfigParameter();
    RS485MB_UsartInit(&RS485Modbus);

    #ifdef _DALI_ENABLE_
        RS485EX_UsartInit(&RS485Expand);
    #endif

    
    GPIO_Light_Init();        
    NVM_GetLightPowerOn();
    LightParameterInit(IORun,IOProfile,&AC);


    
    /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
    EnOceanModuleInit();

}


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysytemError(void)
{
    // EnOceanRun.u8Error
    // panel plug out 
    // Can't detect TCM310,CY8CMBR3,SHT30
    // Can't detect CY8CMBR3
    // Can't detect TCM310
    //uint8_t u8i;

    uint32_t u32EnOceanChipID;
    uint32_t u32EnOceanBaseID;
       
    
    
    static uint8_t u8EnOceanError;
    
    static uint8_t u8InitFlag;
    
    static uint8_t u8HotPlug;
    


    if ( u8EnOceanError != (EnOceanRun.u8Error & ENOCEAN_CAN_NOT_GET_ID_ERROR) )
    {
        if ( 0 == (EnOceanRun.u8Error & ENOCEAN_CAN_NOT_GET_ID_ERROR) )
        {
            
        }
        u8EnOceanError = (EnOceanRun.u8Error & ENOCEAN_CAN_NOT_GET_ID_ERROR);
    }

    if ( u8HotPlug == 1 )
    {
        u8HotPlug = 0;
        
    }  

    if ( ( Dev.u32Error&SYS_PANNEL_HOST_PLUG_MASK) != SYS_PANNEL_HOST_PLUG_MASK )
    {
        EnOceanGetHWChipID  ( &u32EnOceanChipID );
    
        EnOceanGetHWBaseID  ( &u32EnOceanBaseID );

        if ( u32EnOceanChipID != Dev.Cfg.u32EnOceanChipID )
        {
            //if ( ( Dev.u16PowerOnCount > 1 )&&(0 != Dev.Cfg.u32EnOceanChipID ) )
            if ( EnOceanRun.u8Error & ENOCEAN_GET_WRONG_CHIPID_ERROR )
            {               
                Dev.u32Error |= SYS_ENOCEAN_HW_CHIPID_ERR_MASK;
            }
            else
            {
                Dev.Cfg.u32EnOceanChipID         = u32EnOceanChipID;
                //NVM_ChannelUpdate(DEV_CHANNEL);
            }
        }

        if ( u32EnOceanBaseID != Dev.Cfg.u32EnOceanBaseID )
        {
            //if ( ( Dev.u16PowerOnCount > 1 )&&(0 != Dev.Cfg.u32EnOceanBaseID ) )
            if ( EnOceanRun.u8Error & ENOCEAN_GET_WRONG_BASEID_ERROR ) 
            {
                Dev.u32Error |= SYS_ENOCEAN_HW_BASEID_ERR_MASK;
            }
            else
            {
                Dev.Cfg.u32EnOceanBaseID         = u32EnOceanBaseID;
                //NVM_ChannelUpdate(DEV_CHANNEL);
            }
        }
    }

    /* Panel not pair the relay moudle */          

    if ( (EnOceanRun.u8Error & ENOCEAN_GET_WRONG_CHIPID_ERROR)
         || (EnOceanRun.u8Error & ENOCEAN_GET_WRONG_BASEID_ERROR)
         || (EnOceanRun.u8Error & ENOCEAN_CAN_NOT_GET_ID_ERROR) )
    {
        Dev.u32Error |= SYS_TCM310_ERR;
    }
    else
    {
        Dev.u32Error &= ~SYS_TCM310_ERR;
    } 
    
    if ( Dev.u32Error )
    {
        if ( 0 == Dev.u8ErrorSendTime )
        {
            Dev.u8ErrorSendTime = 50;

            //EnOceanMSCSendAddQueue(DEV_CHANNEL, MB_INPUT_ERROR);           
        }
    } 

    if ( 1 == u8InitFlag )
    {
        if ( Dev.u32Error & SYS_PANNEL_HOST_PLUG_MASK )
        {
            u8InitFlag = 2;
            Dev.u16CleanErrorFlagTime = 1800;
        }
        else
        {
            u8InitFlag = 0;
        }
    }
    else if ( 2 == u8InitFlag )
    {
        if ( !Dev.u16CleanErrorFlagTime )
        {
            u8InitFlag = 0;
            Dev.u32Error &= ~SYS_PANNEL_HOST_PLUG_MASK;
        }
    }


}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorTime_1000ms(void)
{
    if ( Dev.u16CleanErrorFlagTime )
    {
        Dev.u16CleanErrorFlagTime --;
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorNeedManualClear(void)
{
    if ( Dev.u32Error&SYS_RUN_FAULT_MASK )
    {
        return !OK;
    }
    return OK;
        
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorManualClearID(void)
{
    if ( Dev.u32Error & SYS_PANNEL_HOST_PLUG_MASK )
    {
        return 2;
    }
    else if ( Dev.u32Error & SYS_PANEL_NOT_MATCH_ERR_MASK )
    {
        return 0;
    }
    else if ( Dev.u32Error & SYS_PANNEL_CHANGE_ERR_MASK )
    {
        return 1;
    }
    else if ( Dev.u32Error & SYS_ENOCEAN_HW_CHIPID_ERR_MASK )
    {
        return 3;
    }
    else if ( Dev.u32Error & SYS_ENOCEAN_HW_BASEID_ERR_MASK )
    {
        return 4;
    }
    
    return 0;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorManualClear(void)
{
    Dev.u32Error &= ~(SYS_PANNEL_CHANGE_ERR_MASK|SYS_ENOCEAN_HW_CHIPID_ERR_MASK|SYS_ENOCEAN_HW_BASEID_ERR_MASK);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
