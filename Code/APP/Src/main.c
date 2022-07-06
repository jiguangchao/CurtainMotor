
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
#include "DataReport.h"
#include "BSP.h"
#include "main.h"

#include "EnOceanTelegram.h"
#include "EnOceanMSC.h"

#include "CurtainProtocol.h"
#include "CurtainInterface.h"
#include "CurtainQueue.h"

#include "SysError.h"
#include "Button.h"
#include "LED.h"
#include "HWTest.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 
Timer_Flag_Typedef TimerFlag;
/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RamInit(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_1000ms(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_100ms(void);

/* Private function prototypes -----------------------------------------------*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RamInit(void)
{                     
    /* !!! Must attention !!!*/
    /* EnOcean reman function must be used the Dev.u32RemanCode */
    ResetDefaultData();

    //EnOceanHardware.u8DOMaxNums = 0;
    //EnOceanHardware.pu8Reapter = &Dev.Cfg.u8Repeater;
    //EnOceanHardware.pu32RemanCode = &Dev.Cfg.u32RemanCode;

    EnOceanRun.u16SendPeriod = 100; //RADIO_SEND_MIN_INTERVAl_DEFAULT;
    EnOceanRun.u8Lock = RM_UNLOCK;
    EnOceanRun.u16LockCount = RM_AUTO_LOCK_TIME;
    EnOceanInit();

    Dev.u16HWVersion = CURTAIN_HW_VERSION;
    Dev.u16FWVersion = CURTAIN_FW_VERSION;

    //Key.pDev                      = &Dev;
    /* Init the ram var ,then read from the NVM area */
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void CURTIAN_GetConfigParameter(void)
{
    /* Modbus */
    CURTAIN_UART.Frame.pu8PhyAddress           = NULL;
    CURTAIN_UART.Frame.eParity                 = ePARITY_NONE;
    CURTAIN_UART.Frame.eBaudID                 = eBAUD_115200_ID;
    CURTAIN_UART.Frame.eStop                   = eSTOP_1;
}
/**
  * @brief
  * @param
  * @retval None
  */
void WISTAR_Init(void)
{
    RamInit();
    BuildComplierDateTime(&Dev.u32BuildYYMMDD, &Dev.u32BuildHHMMSS);
    

    CURTIAN_GetConfigParameter();

    BSP_DMA_ChannelEnable();

    CURTAIN_Init(&CURTAIN_UART);


    FLASH_Write_FactorySettings();
    FLASH_ReadWrite_LOG();    
    FLASH_ReadWrite_Learn();
    Dev.Log.u32PowerOnCount++;

    EnOceanModuleInit();
    EnOceanGetHWChipID(&Dev.Cfg.u32EnOceanChipID);
    EnOceanGetHWBaseID(&Dev.Cfg.u32EnOceanBaseID);

} 

uint16_t u16SendFlag;
/**
  * @brief  The application entry point.
  * 
  * @retval None
  */
int main(void)
{
    /* Initialize all configured peripherals */
    /* MCU Configuration------------------*/

    /* Configure the system clock */
    SystemClock_Config();
    //BSP_Clock_Init();
    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_TIM14_Init();
    
    //FLASH_Remove_Page(FLASH_CFG_ADD);
    //FLASH_Remove_Page(FLASH_LOG_ADD);
    //FLASH_Remove_Page(FLASH_LEARN_ADD1);

    /*       在读取flash之前，先进行数据初始化      */
    WISTAR_Init();

    Dev.u8PowerOnFlag = 1;
    //CurtainRun.eRunState = eCURTAINRUN_SET_DELETETRIP;
    BSP_LEDOFF_RED();
    
    HardwareSelfTest(&HWTest);
    

#ifndef HW_DEBUG
    MX_IWDG_Init();
#endif
    while (1)
    {
    #ifndef HW_DEBUG
        IWDG_Reload();   //喂狗
    #endif  

        SystemTimeTick_10ms();
        SystemTimeTick_100ms();
        SystemTimeTick_1000ms();    

        FLASH_Write_Cfg();
        FLASH_Write_Log();
        FLASH_Write_Learn();

        LED_runmode(&LED);
        Button_SetState(&Button);

        EnOceanHandler(Dev.Cfg.u8RadioInterval);
        EnOcean_ProactiveReport(&ReportedData);

        CurtainQueueRun(); 
        USART_StateMachineHandler(&CURTAIN_UART);
        ManualSetMode_Scan(&CurtainRun);

        //Curtain_SetState_Test(&CurtainRun);
        Curtain_SetState(&CurtainRun);
        Curtain_ControlState(&CurtainRun);
            

    }
    /* USER CODE END 3 */
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_1000ms(void)
{   
    if ( 1 == TimerFlag.u8Timer_1s )
    {
        TimerFlag.u8Timer_1s = 0;

        NVM_DevRunSave();
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_100ms(void)
{    
    if ( TimerFlag.u8Timer_100ms )
    {
        TimerFlag.u8Timer_100ms = 0;

        EnOceanTime_100ms();

        if (Dev.u8LearnSuccessTime)
        {
            Dev.u8LearnSuccessTime--;
        }

        if (Dev.u8LearnAutoSendEEPTime)
        {
            Dev.u8LearnAutoSendEEPTime--;
        }        

    } 
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_10ms(void)
{   
    if (TimerFlag.u8Timer_10ms)
    {
        TimerFlag.u8Timer_10ms = 0;
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void MotorFeedback(void)
{
}
/* USER CODE BEGIN 4 */
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM14_Interrupt_1ms(void)
{
    TimerFlag.u8Timer_1ms = 1;

    USART_Time_1ms(&CURTAIN_UART);
    CurtainRun_Tick1ms(&CurtainRun);
    EnOceanTime_1ms();
    EnoceanPassiveSwitchSetTime_1ms();

    EnoceanSend_Tick1ms(&ReportedData);
    HardwareSelfTest_Tick1ms(&HWTest);
    LED_Tick1ms(&LED);
    Button_Tick1ms(&Button);

    CurtainQueue_Tick1ms();
    
    TimerFlag.u8Cnt_1ms++;
    if (TimerFlag.u8Cnt_1ms >= 10)
    {
        TimerFlag.u8Cnt_1ms = 0;

        TimerFlag.u8Timer_10ms = 1;
        
        SystemTimeTick_10ms();
                    
        TimerFlag.u8Cnt_10ms++;
        if (TimerFlag.u8Cnt_10ms >= 10)
        {
            TimerFlag.u8Cnt_10ms = 0;

            TimerFlag.u8Timer_100ms = 1;

            TimerFlag.u8Cnt_100ms++;

            if (TimerFlag.u8Cnt_100ms >= 10)
            {
                TimerFlag.u8Cnt_100ms = 0;
                TimerFlag.u8Timer_1s = 1;
            }
        }
    }
    //EnOceanTime_100us();
}
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM3_Interrupt_100us(void)
{    
    TimerFlag.u8Timer_100us = 1;

    EnOceanTime_100us();
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


