#ifndef _BSP_IO_MAP_H_
#define _BSP_IO_MAP_H_

#ifdef  G_PORT_MAP_MODULE
#define G_PORT_MAP_EXT
#else
#define G_PORT_MAP_EXT extern
#endif


#define FCLK                                      (64000000)//64MHz



/*############################################################################################################*/
/*############################################################################################################*/
/*                                                                                                            */
/*                                           STM32G030xx                                                      */
/*                                                                                                            */
/*############################################################################################################*/
/*############################################################################################################*/


/******************************************************************************/
/* USART DMA TRANSFORM */
/******************************************************************************/
#define CURTAIN_USART_DMA_CHANNEL_RX                 (LL_DMA_CHANNEL_1)
#define CURTAIN_USART_DMA_CHANNEL_TX                 (LL_DMA_CHANNEL_2)
   
#define ENOCEAN_DMA_CHANNEL_TX                       (LL_DMA_CHANNEL_3)
   
#define ENOCEAN_USART                                (USART1)
#define ENOCEAN_USART_IRQ                            (USART1_IRQn)
#define ENOCEAN_USART_DMA_TX_REQ                     LL_DMAMUX_REQ_USART1_TX  

#define CURTAIN_USART                                (USART2)    
#define CURTAIN_USART_IRQ                            (USART2_IRQn)    
#define CURTAIN_USART_DMA_TX_REQ                     LL_DMAMUX_REQ_USART2_TX
#define CURTAIN_USART_DMA_RX_REQ                     LL_DMAMUX_REQ_USART2_RX
#define CURTAIN_TX_BUFF                              (32)
#define CURTAIN_RX_BUFF                              (32)
   


/******************************************************************************/
/* KEY PIN IN MCU */
/******************************************************************************/
#define KEY_LRN1_GPIO                                (GPIOA)
#define KEY_LRN1_PIN                                 (LL_GPIO_PIN_1)

/******************************************************************************/
/* LED PIN OUT MCU */
/******************************************************************************/
#define LED_RED_GPIO                                (GPIOA)
#define LED_RED_PIN                                 (LL_GPIO_PIN_0)

/******************************************************************************/
/* TCM_310  -- uart1  RX->PB7 TX->PB6 RST->PB5 */
/******************************************************************************/  
#define ENOCEAN_RX_PIN                              (LL_GPIO_PIN_7)
#define ENOCEAN_RX_GPIO                             (GPIOB)        

#define ENOCEAN_TX_PIN                              (LL_GPIO_PIN_6)
#define ENOCEAN_TX_GPIO                             (GPIOB)        

#define ENOCEAN_RST_PIN                             (LL_GPIO_PIN_12)
#define ENOCEAN_RST_GPIO                            (GPIOB)
                                                                                                   
#define ENOCEAN_HARDWARE_RST_DISABLE()              LL_GPIO_ResetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN)  
#define ENOCEAN_HARDWARE_RST_ENABLE()               LL_GPIO_SetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN) 
/******************************************************************************/
/*   CURTAIN  -- uart2  RX->PA3 TX->PA2  */
/******************************************************************************/   
#define CURTAIN_UART_RX_PIN                        (LL_GPIO_PIN_3)
#define CURTAIN_UART_RX_GPIO                       (GPIOA)

#define CURTAIN_UART_TX_PIN                        (LL_GPIO_PIN_2)
#define CURTAIN_UART_TX_GPIO                       (GPIOA)





                    
#endif
/* End of file */
