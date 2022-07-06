/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "BaselibInclude.h"
#include "stm32g0xx_it.h"

//#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"

#include "CurtainInterface.h"
#include "SysError.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    if (Dev.Log.u32SoftFaultCount < 0xFFFFFFFF)
    {
        Dev.Log.u32SoftFaultCount++;
    }
    FLASHRUN.u8LogUpdateFlag = 1;
    NVIC_SystemReset();
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}


/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
     * @brief This function handles EXTI line 4 to 15 interrupts.
     */
void EXTI4_15_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI4_15_IRQn 0 */

    /* USER CODE END EXTI4_15_IRQn 0 */
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_10) != RESET)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_10);
        /* USER CODE BEGIN LL_EXTI_LINE_10_RISING */
        
        /* USER CODE END LL_EXTI_LINE_10_RISING */
    }
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_11) != RESET)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_11);
        /* USER CODE BEGIN LL_EXTI_LINE_11_RISING */
        
        /* USER CODE END LL_EXTI_LINE_11_RISING */
    }
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_12) != RESET)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_12);
        /* USER CODE BEGIN LL_EXTI_LINE_12_RISING */
        
        /* USER CODE END LL_EXTI_LINE_12_RISING */
    }
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_13) != RESET)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_13);
        /* USER CODE BEGIN LL_EXTI_LINE_13_RISING */
        
        /* USER CODE END LL_EXTI_LINE_13_RISING */
    }
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_14) != RESET)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_14);
        /* USER CODE BEGIN LL_EXTI_LINE_14_RISING */
        
        /* USER CODE END LL_EXTI_LINE_14_RISING */
    }
    /* USER CODE BEGIN EXTI4_15_IRQn 1 */

    /* USER CODE END EXTI4_15_IRQn 1 */
}


/**
     * @brief This function handles TIM3 global interrupt.
     */
void TIM3_IRQHandler(void)
{
    /* USER CODE BEGIN TIM3_IRQn 0 */
    if (LL_TIM_IsActiveFlag_UPDATE(TIM3) == 1)
    {
        /* Clear the update interrupt flag*/
        LL_TIM_ClearFlag_UPDATE(TIM3);

        TIM3_Interrupt_100us();
    }
    /* USER CODE END TIM3_IRQn 0 */
    /* USER CODE BEGIN TIM3_IRQn 1 */

    /* USER CODE END TIM3_IRQn 1 */
}

/**
     * @brief This function handles TIM14 global interrupt.
     */
void TIM14_IRQHandler(void)
{
    /* USER CODE BEGIN TIM14_IRQn 0 */
    if (LL_TIM_IsActiveFlag_UPDATE(TIM14) == 1)
    {
        /* Clear the update interrupt flag*/
        LL_TIM_ClearFlag_UPDATE(TIM14);

        TIM14_Interrupt_1ms();
    }
    /* USER CODE END TIM14_IRQn 0 */
    /* USER CODE BEGIN TIM14_IRQn 1 */

    /* USER CODE END TIM14_IRQn 1 */
}

/**
     * @brief This function handles DMA1 channel 1 interrupt.
     */
void DMA1_Channel1_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
    if ( 1 == LL_DMA_IsActiveFlag_TE1(DMA1) )
    {
        LL_DMA_ClearFlag_TE1(DMA1);

        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC1(DMA1) )
    {
        LL_DMA_ClearFlag_TC1(DMA1);                      
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
    }

    /* USER CODE END DMA1_Channel1_IRQn 0 */
    
    /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

    /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
     * @brief This function handles DMA1 channel 2 and channel 3 interrupts.
     */
void DMA1_Channel2_3_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */
    if ( 1 == LL_DMA_IsActiveFlag_TE2(DMA1) )
    {
        LL_DMA_ClearFlag_TE2(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC2(DMA1) )
    {
        LL_DMA_ClearFlag_TC2(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    }
    
    if ( 1 == LL_DMA_IsActiveFlag_TE3(DMA1) )
    {
        LL_DMA_ClearFlag_TE3(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC3(DMA1) )
    {
        LL_DMA_ClearFlag_TC3(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);

        EnOcean_SendOK();
    }

    /* USER CODE END DMA1_Channel2_3_IRQn 0 */
    
    /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

    /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}
/**
     * @brief This function handles DMA1 channel 4, channel 5, channel 6, channel 7 and DMAMUX1 interrupts.
     */
void DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Ch4_7_DMAMUX1_OVR_IRQn 0 */
    if ( 1 == LL_DMA_IsActiveFlag_TE4(DMA1) )
    {
        LL_DMA_ClearFlag_TE4(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC4(DMA1) )
    {
        LL_DMA_ClearFlag_TC4(DMA1);           
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);

    }

    if ( 1 == LL_DMA_IsActiveFlag_TE5(DMA1) )
    {
        LL_DMA_ClearFlag_TE5(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC5(DMA1) )
    {
        LL_DMA_ClearFlag_TC5(DMA1);     
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);                              
    }
/*
    if ( 1 == LL_DMA_IsActiveFlag_TE6(DMA1) )
    {
        LL_DMA_ClearFlag_TE6(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC6(DMA1) )
    {
        LL_DMA_ClearFlag_TC6(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);

    }

    if ( 1 == LL_DMA_IsActiveFlag_TE7(DMA1) )
    {
        LL_DMA_ClearFlag_TE7(DMA1);
        
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);
    }

    if ( 1 == LL_DMA_IsActiveFlag_TC7(DMA1) )
    {
        LL_DMA_ClearFlag_TC7(DMA1);                       

        
    }
*/
    /* USER CODE END DMA1_Ch4_7_DMAMUX1_OVR_IRQn 0 */
    
    /* USER CODE BEGIN DMA1_Ch4_7_DMAMUX1_OVR_IRQn 1 */

    /* USER CODE END DMA1_Ch4_7_DMAMUX1_OVR_IRQn 1 */
}    

/**
     * @brief  Function called in case of error detected in USART IT Handler
     * @param  None
     * @retval None
     */
void USART1_Error_Callback(void)
{
    if ( LL_USART_IsActiveFlag_PE(USART1) )
    {
        LL_USART_ClearFlag_PE(USART1);
    }

    if ( LL_USART_IsActiveFlag_FE(USART1) )
    {
        LL_USART_ClearFlag_FE(USART1);
    }

    if ( LL_USART_IsActiveFlag_NE(USART1) )
    {
        LL_USART_ClearFlag_NE(USART1);
    }
    
    if ( LL_USART_IsActiveFlag_ORE(USART1) )
    {
        LL_USART_ClearFlag_ORE(USART1);
    }    
}
/**
     * @brief  Function called in case of error detected in USART IT Handler
     * @param  None
     * @retval None
     */
void USART1_IRQHandler(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1))
    {
        /* RXNE flag will be cleared by reading of RDR register (done in call) */
        /* Call function in charge of handling Character reception */
        Esp3Rx.u8RegData = LL_USART_ReceiveData8(USART1);
        EnOcean_ReceiveUsartDataPushQueue(Esp3Rx.u8RegData);
    }
    
    /***************************************************************************/
    /********************************USART1*************************************/
    /***************************************************************************/
    /* Check RXNE flag value in ISR register */
#if 0
    if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1))
    {
        /* RXNE flag will be cleared by reading of RDR register (done in call) */
        /* Call function in charge of handling Character reception */            
    }
#endif
    /* TXE */
    if (LL_USART_IsEnabledIT_TXE(USART1) && LL_USART_IsActiveFlag_TXE(USART1))
    {
        /* Clear TXE flag */
        LL_USART_ClearFlag_TXFE(USART1);
    }
    /* TC */
    if (LL_USART_IsEnabledIT_TC(USART1) && LL_USART_IsActiveFlag_TC(USART1))
    {
        /* Clear TC flag */
        LL_USART_ClearFlag_TC(USART1);
        /* Disable TC interrupt */
        //LL_USART_DisableIT_TC(USART1);
    }


    /* Call Error function */
    USART1_Error_Callback();

}
/**
     * @brief  Function called in case of error detected in USART IT Handler
     * @param  None
     * @retval None
     */
void USART2_Error_Callback(void)
{
    if ( LL_USART_IsActiveFlag_PE(USART2) )
    {
        LL_USART_ClearFlag_PE(USART2);
    }

    if ( LL_USART_IsActiveFlag_FE(USART2) )
    {
        LL_USART_ClearFlag_FE(USART2);
    }

    if ( LL_USART_IsActiveFlag_NE(USART2) )
    {
        LL_USART_ClearFlag_NE(USART2);
    }
    if ( LL_USART_IsActiveFlag_ORE(USART2) )
    {
        LL_USART_ClearFlag_ORE(USART2);
    }
    /*
    if ( LL_USART_IsActiveFlag_IDLE(USART2) )
    {
        LL_USART_ClearFlag_IDLE(USART2);
    }       
    */
}
/**
     * @brief  Function called in case of error detected in USART IT Handler
     * @param  None
     * @retval None
     */
void USART2_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */

    if(LL_USART_IsActiveFlag_IDLE(USART2) && LL_USART_IsEnabledIT_IDLE(USART2))
    {
        LL_USART_ClearFlag_IDLE(USART2);
        
        /* USER CODE BEGIN USART1_4_IRQn 0 */
        LL_DMA_DisableChannel(DMA1, CURTAIN_USART_DMA_CHANNEL_RX);

        /* Copy the receive buff to the process buff */
        CURTAIN_UART.Frame.u16ReceiveBytesMax = CURTAIN_UART.Frame.u16ReceiveBuffMax - LL_DMA_GetDataLength(DMA1, CURTAIN_USART_DMA_CHANNEL_RX);
        USART_IdleInterruptGetDMABuff(&CURTAIN_UART.Frame);
        
        /* Reset the dma count */
        LL_DMA_SetDataLength(DMA1, CURTAIN_USART_DMA_CHANNEL_RX, CURTAIN_UART.Frame.u16ReceiveBuffMax);
        LL_DMA_EnableChannel(DMA1, CURTAIN_USART_DMA_CHANNEL_RX);
    }


    /* TXE */
    if (LL_USART_IsEnabledIT_TXE(USART2) && LL_USART_IsActiveFlag_TXE(USART2))
    {
        /* Clear TXE flag */
        //LL_USART_ClearFlag_TXFE(USART1);
    }
    /* TC */
    if (LL_USART_IsEnabledIT_TC(USART2) && LL_USART_IsActiveFlag_TC(USART2))
    {
        /* Clear TC flag */
        //LL_USART_ClearFlag_TC(USART1);
        /* Disable TC interrupt */
        //LL_USART_DisableIT_TC(USART1);
    }

    /* Call Error function */
    USART2_Error_Callback();

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
