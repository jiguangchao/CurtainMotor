/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H__
#define __BUTTON_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

//按键事件
typedef enum
{
	eButton_IDLE = 0,      //按键空闲状态
	eButton_SHORT_PRESS,   //按键短按
	eButton_LONG_PRESS_2S, //按键长按2S  
	eButton_LONG_PRESS_10S,//按键长按10S

} eButtonEvent_t;

//按键运行
typedef enum
{
    eBUTTON_NONE = 0,       //没有按键按下
    eBUTTON_PRESS,          //按键按下
    eBUTTON_COUNT,          //按键计时
	  eBUTTON_LONG_PRESS_TIME,//按键长按计时
    eBUTTON_END,            //按键结束 

} eButtonRun_t;



//硬件测试
typedef enum
{
    eHWTESTMODE_No  = 0, //非硬件测试模式
    eHWTESTMODE_YES = 1, //硬件测试模式
} eHWtest_t;

typedef struct
{
	eButtonRun_t         eButtonRun;   
	eButtonEvent_t       eButtonEvent;
	eHWtest_t            eHWtest;

  uint8_t              u8ResrtFlag;       //恢复出厂设置标志

	uint8_t              u8ButtonValue;      //按键值 
  uint8_t              u8ButtonValuePro;   //记录上一个按键值 

	uint8_t              u8ButtonTimerFlag;  //按键计时标记
	uint8_t              u8ButtonShortCount; //按键短按计数
	uint8_t              u8ButtonLongCount;  //按键长按计数  

  uint32_t             u32ButtonTimer;   //按键计时
	uint32_t             u32ButtonTiming;  //按键定时


} eButton_Typedef;


extern eButton_Typedef Button;


/**
  * @brief
  * @param
  * @retval None     
  */
void Button_Tick1ms(eButton_Typedef *pButton); //Key定时器
/**
  * @brief 
  * @param
  * @retval None     
  */
eButtonEvent_t Button_SetState(eButton_Typedef *pButton);



#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
