#ifndef _BSP_USART_H_
#define _BSP_USART_H_

/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_DMA_ChannelEnable(void);
/*=============================================================================*/
/*===============================EnOcean  USART1===============================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanUsartDMA_Init(uint8_t *puTxBuff);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_EnOceanUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanSendStart(uint16_t u16SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_EnOceanSendStop(void);
/*=============================================================================*/
/*=============================== CURTAIN USART2================================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_CURTAINUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_CURTAINUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_CURTAINSendStart(uint8_t u8SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CURTAINSendStop(void);
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t BSP_CURTAINStatus(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CURTAINDirectSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CURTAINDirectReceive(void);

#endif
/* End of file */
