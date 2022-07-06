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
/* User App */
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"

#include "CurtainInterface.h"
#include "LED.h"
#include "Button.h"
#include "CurtainProtocol.h"
#include "DataReport.h"

#include "EnOceanTelegram.h"
#include "EnOceanMSC.h"

#include "HWTest.h"
#include "SysError.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 



/*============================ LOCAL VARIABLES ===============================*/


/*============================ PROTOTYPES ====================================*/

HWTest_Typedef HWTest;
HWTest_LedRunMode_t HWTestLed;
HWTest_CurtainRun_TYPE HWTestCurtain;
/*============================ IMPLEMENTATION ================================*/

/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTest_Tick1ms(HWTest_Typedef *pHWTest)
{
    if (pHWTest->u8SelfTestState==1)
    {
        pHWTest->u32HWTestCount++;
    }
    if (pHWTest->u16HWTestTimer !=0)
    {
        pHWTest->u16HWTestTimer--;
    }

    if (pHWTest->u32LedRunTimer !=0)
    {
        pHWTest->u32LedRunTimer--;
    }
    if (pHWTest->u32BlinkTime !=0)
    {
        pHWTest->u32BlinkTime--;
    }    
    
    if (pHWTest->u32CurtainRunWait !=0)
    {
        pHWTest->u32CurtainRunWait--;
    }

}

/**
  * @brief
  * @param
  * @retval None     
  */
void HWTest_LED(HWTest_Typedef *pHWTest) //出厂自检LED运行
{

    switch (pHWTest->eHWTestLed)
    {
    case eHWTestLEDRUN_STANDBY: //待机状态

        break;
    
    //闪烁模式控制
    case eHWTestLEDRUN_BLINKMODE_INIT:
    {
        if (pHWTest->u32LedRunTimer != 0)
        {
            break;
        }
        if (pHWTest->u32BlinkONTime < pHWTest->u32BlinkTime)
        {
            pHWTest->u32BlinkONTime = pHWTest->u32BlinkTime;
        }
        if (pHWTest->u32BlinkOFFTime < pHWTest->u32BlinkTime)
        {
            pHWTest->u32BlinkOFFTime = pHWTest->u32BlinkTime;
        }
        BSP_LEDON_RED();
        pHWTest->u32LedRunTimer = pHWTest->u32BlinkONTime;
        pHWTest->eHWTestLed = eHWTestLEDRUN_BLINKMODE_ON;
        break;
    }
    case eHWTestLEDRUN_BLINKMODE_ON:
    {
        if (0 == pHWTest->u32LedRunTimer)
        {
            BSP_LEDOFF_RED();
            pHWTest->u32LedRunTimer = pHWTest->u32BlinkOFFTime;
            pHWTest->eHWTestLed = eHWTestLEDRUN_BLINKMODE_OFF;
        }
        break;
    }
    case eHWTestLEDRUN_BLINKMODE_OFF:
    {
        if (0 == pHWTest->u32LedRunTimer)
        {
            if (pHWTest->u32RunBlinkCount > 0)
            {
                //LEDLight(pHWTest->eLedID);
                pHWTest->u32RunBlinkCount--;
                pHWTest->u32LedRunTimer = pHWTest->u32BlinkONTime;
                pHWTest->eHWTestLed = eHWTestLEDRUN_BLINKMODE_INIT;
            }
            else
            {
                pHWTest->u32RunBlinkCount = 0;
                pHWTest->eHWTestLed = eHWTestLEDRUN_END;
            }
        }
        break;
    }


    case eHWTestLEDRUN_END:

        BSP_LEDOFF_RED();
        pHWTest->eHWTestLed = eHWTestLEDRUN_STANDBY;
        break;

    default:
        pHWTest->eHWTestLed = eHWTestLEDRUN_STANDBY;
        break;
    }
}
/**
  * @brief  LED快速闪烁
  * @param
  * @retval None     
  */
void HWTest_LED_Fast_Blink(HWTest_Typedef *pHWTest, uint8_t u8Count)
{
    pHWTest->eHWTestLed = eHWTestLEDRUN_BLINKMODE_INIT;
    pHWTest->u32BlinkTime = 100;
    pHWTest->u32RunBlinkCount = u8Count;
}
/**
  * @brief  LED慢速闪烁
  * @param
  * @retval None     
  */
void HWTest_LED_Slow_Blink(HWTest_Typedef *pHWTest, uint8_t u8Count)
{
    pHWTest->eHWTestLed = eHWTestLEDRUN_BLINKMODE_INIT;
    pHWTest->u32BlinkTime = 500;
    pHWTest->u32RunBlinkCount = u8Count;
}
/**
 * @brief    窗帘运行状态机
 * @param
 * @retval   
 */
void HWTestCurtain_SetState(HWTest_Typedef *pHWTest) 
{
    switch (pHWTest->eHWTestCurtain)
    {
    case eHWTestCURTAINRUN_IDLE:
        
        break;     

    /*       出厂自检测试电机          */
    case eHWTestCURTAINRUN_HWTEST_FORWARD:

        CurtainSendControlOn(&CURTAIN_UART.Frame);
        CurtainUsart_Send();
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_FORWARD_WAIT;
        pHWTest->u32CurtainRunWait = 2000;
        break;

    case eHWTestCURTAINRUN_HWTEST_FORWARD_WAIT:

        if (pHWTest->u32CurtainRunWait != 0)
        {
            break;
        }
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_STOPA;
        break;    

    case eHWTestCURTAINRUN_HWTEST_STOPA:

        CurtainSendControlStop(&CURTAIN_UART.Frame);
        CurtainUsart_Send();
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_STOP_WAITA;
        pHWTest->u32CurtainRunWait = 100;
        break;

    case eHWTestCURTAINRUN_HWTEST_STOP_WAITA:

        if (pHWTest->u32CurtainRunWait != 0)
        {
            break;
        }
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_REVERSE;
        break;   

    case eHWTestCURTAINRUN_HWTEST_REVERSE:

        CurtainSendControlOff(&CURTAIN_UART.Frame);
        CurtainUsart_Send();
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_REVERSE_WAIT;
        pHWTest->u32CurtainRunWait = 1500;
        break;

    case eHWTestCURTAINRUN_HWTEST_REVERSE_WAIT:

        if (pHWTest->u32CurtainRunWait != 0)
        {
            break;
        }
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_STOP_WAITB;
        break;      

    case eHWTestCURTAINRUN_HWTEST_STOPB:

        CurtainSendControlStop(&CURTAIN_UART.Frame);
        CurtainUsart_Send();
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_STOP_WAITB;
        pHWTest->u32CurtainRunWait = 100;
        break;

    case eHWTestCURTAINRUN_HWTEST_STOP_WAITB:

        if (pHWTest->u32CurtainRunWait != 0)
        {
            break;
        }
        pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_IDLE;
        break;           

    default:
        break;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void HWTest_EnOceanHandler(uint8_t u8SendIntervalPeriodSet)
{   
    uint8_t u8Status;

    /* Get and process EnOcean ESP3's data from receive queue  */
    u8Status = EnOceanESP3ReceivePacketParse(&Radio, PACKET_RESERVED);

    if (0 == u8Status)
    {
        
        //ENOCEAN_HARDWARE_RST_DISABLE();   //
        //EnOceanRun.u8SendPeriod = u8SendIntervalPeriodSet;
    }
    else if (1 == u8Status)
    {
        /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
        EnOceanModuleInit();
    }
    else if (2 == u8Status)
    {
        if ( Radio.Telegram.raw.u8RORG == RADIO_CHOICE_RPS )
        {
            LL_GPIO_TogglePin(LED_RED_GPIO,LED_RED_PIN);
        }
    }
    else if (3 == u8Status)
    {
        if (RM_SUCCESS == EnOceanReman(&Radio))
        {
            EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM, &Radio);
        }
    }

    /* */
    if (OK != EnOceanESP3SendStateProcess())
    {
        EnOcean_HardwareReset();
    }

    if (OK == EnOceanGetSendReady())
    {
        if (OK == EnOcean_GetSendQueuePopID())
        {
            EnOceanPopQueueSendData();

            EnOceanSetSendPeriod(u8SendIntervalPeriodSet);
        }
    }

    EnOceanLearnSend();

}
/*! \note   //出厂自检项目轮询
*  \param  
*  \retval  
*  \retval  
*/
void SelfTest_Poll(HWTest_Typedef *pHWTest)
{
    switch (pHWTest->eHWTestPoll)
    {
    case eHWTEST_STANDBY:

        pHWTest->eHWTestPoll = eHWTEST_LEDDETECT;
        break;

    case eHWTEST_LEDDETECT:
        
        HWTest_LED_Slow_Blink(pHWTest,15);
        pHWTest->eHWTestPoll = eHWTEST_MOTORDETECT;
        break;

    case eHWTEST_MOTORDETECT:
        
        if (CurtainRun.u8ButtonFlag == 1)
        {
            pHWTest->eHWTestCurtain = eHWTestCURTAINRUN_HWTEST_FORWARD;
            pHWTest->u16HWTestTimer = 3000;
            pHWTest->eHWTestPoll = eHWTEST_EnoceanDETECT;
        }
        break;

    case eHWTEST_EnoceanDETECT:

        if (pHWTest->u16HWTestTimer != 0 )
        {
            break;
        }
        break;        

    default:
        break;
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardwareSelfTest(HWTest_Typedef *pHWTest)
{   
   
    uint32_t u32EnOceanBaseID;       

    EnOceanGetHWBaseID ( &u32EnOceanBaseID );

    pHWTest->u8SelfTestState = 0;

    if (1 != Button_ReadPin() )
    {
        pHWTest->u8SelfTestState = 1;
    }

    while (pHWTest->u8SelfTestState)
    {

        SystemTimeTick_10ms();
        SystemTimeTick_100ms();
        SystemTimeTick_1000ms();

        USART_StateMachineHandler(&CURTAIN_UART);   
        HWTest_EnOceanHandler(Dev.Cfg.u8RadioInterval);

        HWTest_LED(pHWTest);
        HWTestCurtain_SetState(pHWTest);
        SelfTest_Poll(pHWTest);
        //按下LRN按键会退出出厂自检模式
        if (pHWTest->u32HWTestCount > (300 * 1000) )//5分钟
        {
            pHWTest->u8SelfTestState = 0;
        }
        

    }
}




