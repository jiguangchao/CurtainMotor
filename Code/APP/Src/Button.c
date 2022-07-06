
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
#include "BSP.h"
#include "main.h"
#include "Button.h"
#include "LED.h"

#include "CurtainInterface.h"
#include "CurtainProtocol.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 



/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/




/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */
eButton_Typedef Button;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief
  * @param
  * @retval None     
  */
void Button_Tick1ms(eButton_Typedef *pButton) //Key定时器
{
    if ( Button.u8ButtonShortCount < 0xFF )
    {
        Button.u8ButtonShortCount++;
    }
    if (pButton->u8ButtonTimerFlag)
    {
        pButton->u32ButtonTimer++;
    }
}

/**
  * @brief 
  * @param
  * @retval None     
  */
eButtonEvent_t Button_StateShort(void)
{
    if ( eButton_IDLE == Button.eButtonEvent)
    {
        Button.u8ButtonShortCount++;
        Dev.u8State = 0x01;
        CurtainRun.eRunState = eCURTAINRUN_HWTEST_FORWARD;//电机运动
        return eButton_SHORT_PRESS;
    }

    return eButton_IDLE;
}
/**
  * @brief 
  * @param
  * @retval None     
  */
eButtonEvent_t Button_StateLong(void)
{
    //if ( Button.u8ButtonShortCount >= 20 && Button.u32ButtonTiming == 0 )
    if ( Button.u8ButtonShortCount >= 20 &&  Button.u32ButtonTimer % 1000 == 0 )
    {
        Button.u8ButtonShortCount = 0;
        Button.u8ButtonLongCount += 1;
        Button.u32ButtonTimer     = 0;
    }
    
    if ( Button.u8ButtonLongCount < 10 &&  Button.u8ButtonLongCount > 6 )
    {
        LED.eRunMode = eLEDRUN_END;
        return eButton_LONG_PRESS_2S;
    }
        
    
    if ( Button.u8ButtonLongCount >= 10  )
    {
        //if ( LED.eRunMode == eLEDRUN_STANDBY  && LED.u8LEDButtonFalg == 2 )
        if ( LED.eRunMode == eLEDRUN_STANDBY)
        {
            LED_Fast_Blink(&LED, 20); //快闪10次
            //LED.u8LEDButtonFalg = 0x01;
        }  
        ResetDefaultData();

        if (Button.u8ResrtFlag == 0)
        {
            FLASHRUN.u8CfgUpdateFlag = 0x01;
            FLASHRUN.u8LearnUpdateFlag = 0x01;
            Dev.u8ManualLearnState = 0x00;
            Button.u8ResrtFlag = 1;
        }

        //Button.u8ButtonLongCount = 10;
        return eButton_LONG_PRESS_10S;
    }
    else if ( Button.u8ButtonLongCount > 2 )
    {
        //if ( LED.eRunMode == eLEDRUN_STANDBY && LED.u8LEDButtonFalg == 1 )
        if ( LED.eRunMode == eLEDRUN_STANDBY)
        {
            LED_Slow_Blink(&LED, 3);   //慢闪3次
            //LED.u8LEDButtonFalg = 0x01;
        }
        Dev.u8ManualLearnState    = 0x01;
        Dev.u32ManualLearnTiming  = 30*1000;//5分钟
        return eButton_LONG_PRESS_2S;
    }

    return eButton_IDLE;
    
}
/**
  * @brief 
  * @param
  * @retval None     
  */
eButtonEvent_t Button_SetState(eButton_Typedef *pButton)
{
    eButtonEvent_t ButtonEvent = eButton_IDLE;

    if (OK != Button_ReadPinStatus(&Button.u8ButtonValue))
    {
        ButtonEvent = eButton_IDLE;
        return ButtonEvent;
    }

    if ( eNONE_DOWN_VALUE !=  Button.u8ButtonValue )
    {
        Button.u8ButtonTimerFlag = 1;
        if ( Button.u8ButtonValuePro != Button.u8ButtonValue  )
        {
            Button.u8ButtonShortCount = 0;
            Button.u8ButtonLongCount  = 0;
            ButtonEvent = Button_StateShort();
        }
        else
        {
            ButtonEvent = Button_StateLong();
        }
        
    }
    else
    {
        Button.u8ButtonShortCount = 0;
        Button.u8ButtonLongCount  = 0;
        Button.u8ButtonTimerFlag  = 0;
    }

    Button.u8ButtonValuePro = Button.u8ButtonValue;

    Button.eButtonEvent = ButtonEvent;
    /*
    if ( Button.eButtonEvent == eButton_IDLE )
    {
        LED.u8LEDButtonFalg = 0;
    }
    else if ( Button.eButtonEvent == eButton_LONG_PRESS_2S )
    {
        LED.u8LEDButtonFalg = 1;
    }
    else if (Button.eButtonEvent == eButton_LONG_PRESS_10S )
    {
        LED.u8LEDButtonFalg = 2;
    }
    */

    return ButtonEvent;

}



#if 0
/**
  * @brief 
  * @param
  * @retval None     
  */
 void Button_SetState(eButton_Typedef *pButton)
 {
    Button_Scan();   
    
     pButton->u8ButtonState = BSP_Button.u32PinValue;

     switch (pButton->eButtonRun)
     {
     case eBUTTON_NONE:

        if (pButton->u8ButtonState == 1)
        {
            pButton->eButtonRun = eBUTTON_PRESS;
        }
        break;

    case eBUTTON_PRESS:

        if (pButton->u8ButtonState == 1)
        {
            pButton->u8ButtonTimerFlag = 1;  
        }
        else
        {
            pButton->u8ButtonTimerFlag = 0;
            pButton->eButtonRun = eBUTTON_COUNT;
        }
        
        break;    

     case eBUTTON_COUNT:

        if (pButton->u32ButtonTimer < 1500)//1.5s
        {
            Dev.u8State = 1;

            pButton->eButtonEvent = eButton_SHORT_PRESS;
            pButton->u8ButtonShortCount++;
            pButton->u32ButtonTimer = 0;
            pButton->eButtonRun = eBUTTON_NONE;

            if ( pButton->u8ButtonShortCount >= 3)
            {
                LED_Slow_Blink(&LED, 3);
            }
        }
        else if (pButton->u32ButtonTimer > 5000)
        {
            pButton->eButtonEvent = eButton_LONG_PRESS_10S;
            pButton->u32ButtonTimer = 0;
            pButton->eButtonRun = eBUTTON_NONE;
            pButton->u8ButtonShortCount = 0;

            LED_Slow_Blink(&LED, 5);
            ResetDefaultData();
            FLASHRUN.u8CfgUpdateFlag = 0x01;
            FLASHRUN.u8LearnUpdateFlag = 0x01;

        }
        else if (pButton->u32ButtonTimer >= 1500 && pButton->u32ButtonTimer <= 5000 )
        //else if (pButton->u32ButtonTimer >= 2000 )
        {
            pButton->eButtonEvent = eButton_LONG_PRESS_2S;
            pButton->u32ButtonTiming = 30*1000; //定时30S
            pButton->u32ButtonTimer = 0;
            pButton->eButtonRun = eBUTTON_LONG_PRESS_TIME;
            pButton->u8ButtonShortCount = 0;
            LED_Fast_Blink(&LED,10);

        }
        break;

     case eBUTTON_LONG_PRESS_TIME:

        if (pButton->u32ButtonTiming != 0)
        {
            break;
        }
        pButton->eButtonEvent = eButton_IDLE;
        pButton->eButtonRun = eBUTTON_NONE;
        break;

     case eBUTTON_END:

         break;

     default:
         break;
     }
 }
#endif

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* End of file */
