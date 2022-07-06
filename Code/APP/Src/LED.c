
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

#include "Dataconfigure.h"
#include "LED.h"


/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

LED_Typedef LED;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief
  * @param
  * @retval None     
  */
void LED_Tick1ms(LED_Typedef *pLED) //LED定时器
{

    if (pLED->u32LedRunTimer)
    {
        pLED->u32LedRunTimer--;
    }
    if (pLED->u32LedWorkTimer)
    {
        pLED->u32LedWorkTimer--;
    }
}
/**
  * @brief  LED快速闪烁
  * @param
  * @retval None     
  */
void LED_Fast_Blink(LED_Typedef *pLED, uint8_t u8Count)
{
    pLED->u32BlinkTime = 50;

    if (pLED->eRunMode != eLEDRUN_STANDBY)
    {
        pLED->u32RunBlinkCount = pLED->u32RunBlinkCount + u8Count;
    }
    else
    {
        pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
        pLED->u32RunBlinkCount = u8Count;
    }
}
/**
  * @brief  LED慢速闪烁
  * @param
  * @retval None     
  */
void LED_Slow_Blink(LED_Typedef *pLED, uint8_t u8Count)
{
    pLED->u32BlinkTime = 500;

    if (pLED->eRunMode != eLEDRUN_STANDBY)
    {
        pLED->u32RunBlinkCount = pLED->u32RunBlinkCount + u8Count;
    }
    else
    {
        pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
        pLED->u32RunBlinkCount = u8Count;
    }
}

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_runmode(LED_Typedef *pLED) //LED运行模式状态机
{


    switch (pLED->eRunMode)
    {
    case eLEDRUN_STANDBY: //待机状态
    
        
        break;
    
    
    //闪烁模式控制
    case eLEDRUN_BLINKMODE_INIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        //if (pLED->u32BlinkONTime < pLED->u32BlinkTime)
        {
            pLED->u32BlinkONTime = pLED->u32BlinkTime;
        }
        //if (pLED->u32BlinkOFFTime < pLED->u32BlinkTime)
        {
            pLED->u32BlinkOFFTime = pLED->u32BlinkTime;
        }
        BSP_LEDON_RED();
        pLED->u32LedRunTimer = pLED->u32BlinkONTime;
        pLED->eRunMode = eLEDRUN_BLINKMODE_ON;
        break;
    }
    case eLEDRUN_BLINKMODE_ON:
    {
        if (0 == pLED->u32LedRunTimer)
        {
            BSP_LEDOFF_RED();
            pLED->u32LedRunTimer = pLED->u32BlinkOFFTime;
            pLED->eRunMode = eLEDRUN_BLINKMODE_OFF;
        }
        break;
    }
    case eLEDRUN_BLINKMODE_OFF:
    {
        if (0 == pLED->u32LedRunTimer)
        {
            if (pLED->u32RunBlinkCount > 0)
            {
                //LEDLight(pLED->eLedID);
                pLED->u32RunBlinkCount--;
                pLED->u32LedRunTimer = pLED->u32BlinkONTime;
                pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
            }
            else
            {
                pLED->u32RunBlinkCount = 0;
                pLED->eRunMode = eLEDRUN_END;
            }
        }
        break;
    }

    //常亮模式控制
    case eLEDRUN_LIGHTMODE_INIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32LightONTime < LED_Light_ON_TIME)
        {
            pLED->u32LightONTime = LED_Light_ON_TIME;
        }
        if (pLED->u32LightOFFTime < LED_Light_OFF_TIME)
        {
            pLED->u32LightOFFTime = LED_Light_OFF_TIME;
        }
        BSP_LEDON_RED();
        pLED->u32LedRunTimer = pLED->u32LightONTime;
        pLED->eRunMode = eLEDRUN_LIGHTMODE_WAIT;
        break;
    }
    case eLEDRUN_LIGHTMODE_WAIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        
        BSP_LEDOFF_RED();
        pLED->u32LedRunTimer = pLED->u32LightOFFTime;
        pLED->eRunMode = eLEDRUN_LIGHTMODE_END;
        break;
    }
    case eLEDRUN_LIGHTMODE_END:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32RunBlinkCount > 0)
        {
            //LEDLight(pLED->eLedID);
            pLED->u32RunBlinkCount--;
            pLED->u32LedRunTimer = pLED->u32LightONTime;
            pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
        }
        else
        {
            pLED->u32RunBlinkCount = 0;
            pLED->eRunMode = eLEDRUN_END;
        }
        // pLED->eRunMode = eLEDRUN_STANDBY;
        break;
    }

    case eLEDRUN_END:

        BSP_LEDOFF_RED();
        pLED->eRunMode = eLEDRUN_STANDBY;
        break;

    default:
        pLED->eRunMode = eLEDRUN_STANDBY;
        break;
    }
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_WorkMode(LED_Typedef *pLED) //LED工作模式状态机
{
     
}




