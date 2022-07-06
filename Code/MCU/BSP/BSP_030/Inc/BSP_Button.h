#ifndef _BSP_BUTTON_H_
#define _BSP_BUTTON_H_


typedef enum
{
    eNONE_DOWN_VALUE = 0,
    eLRN1_KEY_VALUE,
    eLRN2_KEY_VALUE,    
    eREPEAT_KEY_VALUE,
    eSET_KEY_VALUE,

}eKEY_VALUE_TYPE;



/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Button_ReadPin(void);
/**
  * @brief   //按键消抖
  * @param
  * @retval None
  */
uint8_t Button_Scan(void);
/**
  * @brief  //按键消抖
  * @param
  * @retval None
  */
uint8_t Button_ReadPinStatus(uint8_t *pu8Button);


#endif
/* End of file */
