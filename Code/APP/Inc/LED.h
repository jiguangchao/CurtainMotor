
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H_
#define __LED_H_

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"
#include "BSP_LED.h"


//闪烁参数
#define LED_Blink_TIME            (100) //闪烁时间
//常亮参数
#define LED_Light_ON_TIME         (2000) //常量时间3S
#define LED_Light_OFF_TIME        (500) //常量时间3S


typedef enum
{
    eLEDRUN_STANDBY = 1, // 待机状态

    //闪烁模式
    eLEDRUN_BLINKMODE_INIT,    //闪烁模式开始
    eLEDRUN_BLINKMODE_ON,  //闪烁模式开状态
    eLEDRUN_BLINKMODE_OFF, //闪烁模式关状态

    //常亮模式
    eLEDRUN_LIGHTMODE_INIT, //常亮模式开始
    eLEDRUN_LIGHTMODE_WAIT, //常亮模式等待
    eLEDRUN_LIGHTMODE_END,  //常量模式结束    

    eLEDRUN_END , // 结束状态


} LedRunMode_t; //LED运行状态

typedef enum
{
    eLEDWORK_STANDBY = 0, // 待机状态

    eLEDWORK_MANUALSET,       //manual set 手动设置模式
    eLEDWORK_MANUALSET_WAIT,  //manual set 手动设置模式等待

    eLEDWORK_RESET,           //reset 复位模式
    eLEDWORK_RESET_WAIT,      //reset 复位模式等待


} LedWorkMode_t; //LED运行状态


typedef struct
{

    LedRunMode_t eRunMode;   // 运行模式


    uint32_t u32LedRunTimer;  // 计时器
    uint32_t u32LedWorkTimer; // 计时器

    uint8_t u8LEDButtonFalg;   //LED按键标志

    uint32_t u32BlinkONTime;  // 闪烁时开启时间
    uint32_t u32BlinkOFFTime; // 闪烁时关闭启时间
    uint32_t u32BlinkTime;    // 闪烁时间

    uint32_t u32LightONTime;  //常亮时开启时间
    uint32_t u32LightOFFTime;

    uint32_t u32RunBlinkCount;//闪烁次数

    uint8_t u8SelfTestCount; //自检计数
    uint8_t u8LedSwtichFalg; //LED开关标志

    uint8_t u8MarqueeFlag;   //跑马灯标记

} LED_Typedef;

extern LED_Typedef LED;

/**
  * @brief
  * @param
  * @retval None
  */
void LED_Tick1ms(LED_Typedef *pLED);
/**
  * @brief  LED快速闪烁
  * @param
  * @retval None     
  */
void LED_Fast_Blink(LED_Typedef *pLED, uint8_t u8Count);
/**
  * @brief  LED慢速闪烁
  * @param
  * @retval None     
  */
void LED_Slow_Blink(LED_Typedef *pLED, uint8_t u8Count);
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_runmode(LED_Typedef *pLED); //LED运行模式状态机





#endif