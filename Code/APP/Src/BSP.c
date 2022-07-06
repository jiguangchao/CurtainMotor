

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


/*============================ MACROS ========================================*/
//#define IIC_NOTE       (0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
#include "platform.h"
#include "BaselibInclude.h"
/* Includes ------------------------------------------------------------------*/
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"



Radio_Typedef               Radio={0};
/**
* @brief  per CPU Cycle = 12 OS Cyscles = 0.75us (16MHz System Clock frequency)
* @param
* @retval None
*/   
void EnOcean_HardwareReset(void)
{
    volatile unsigned int num;

    ENOCEAN_HARDWARE_RST_ENABLE();
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    //HAL_Delay(2);

    ENOCEAN_HARDWARE_RST_DISABLE();
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    //HAL_Delay(1);
}


/**
 * @brief  
 * @param
 * @retval None
 */
void EnOceanModuleInit(void)
{

    EnOceanRun.pu8Reapter = &Dev.Cfg.u8Repeater;
    EnOceanRun.pu32RemanCode = &Dev.Cfg.u32RemanCode;

    EnOceanInit();

    EnOceanRun.pStart = BSP_EnOceanSendStart;
    EnOceanRun.pStop = BSP_EnOceanSendStop;
    EnOceanRun.pEnOceanReset = EnOcean_HardwareReset;
    EnOceanRun.pEnOceanError = EnOceanModuleError;

    EnOcean_HardwareReset();
    BSP_EnOceanUsartDMA_Init(Esp3Tx.u8Buff);
    BSP_EnOceanUSART_Init(57600, LL_USART_STOPBITS_1, LL_USART_PARITY_NONE);
    EnOcean_InitGetInfo(&Radio);
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanModuleError(uint16_t u16Err)
{
    static uint8_t u8ErrorCnt;
    
    if ( u16Err )
    {
        if (u8ErrorCnt > 2)
        {
            u8ErrorCnt = 0;

            return ;
        }
    }
    u8ErrorCnt = 0;

    #ifndef HW_DEBUG
        IWDG_Reload();
    #endif
    //return OK;
}

/*****************************END OF FILE****/
