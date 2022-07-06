/*******************************************************************
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/

#include "..\..\BSP_Include.h"



/*!
*****************************************************************
						$Name$
						$Revision: 27601 $
						$Date: 2010-06-18 16:20:57 +0200 (Fr, 18 Jun 2010) $
	\file 				id_mod.c
	\brief 				ID management related functions
	\author 			EnOcean

	<b>Processor:</b>\n	EO3000I\n\n
	<b>Company:</b>\n	EnOcean GmbH\n
****************************************************************
*/

#include "platform.h"
#include "BaselibInclude.h"
#include "BSP_Button.h"



/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Button_ReadPin(void)
{
    return LL_GPIO_IsInputPinSet(KEY_LRN1_GPIO,KEY_LRN1_PIN);
}

/**
  * @brief   //按键扫描
  * @param
  * @retval None
  */
uint8_t Button_Scan(void)
{
    uint8_t u8ButtonPin;
	uint8_t u8ButtonValue;

    u8ButtonPin = 0;
    u8ButtonValue = eNONE_DOWN_VALUE;

    if (0 == LL_GPIO_IsInputPinSet(KEY_LRN1_GPIO,KEY_LRN1_PIN))
    {
        u8ButtonPin |= 0x01;
    }
    /*
    if (0 == LL_GPIO_IsInputPinSet(KEY_LRN2_GPIO,KEY_LRN2_PIN))
    {
        u8ButtonPin |= 0x02;
    }
    if (0 == LL_GPIO_IsInputPinSet(KEY_SET_GPIO,KEY_SET_PIN))
    {
        u8ButtonPin |= 0x04;
    }
    */
    u8ButtonValue = u8ButtonPin;

	return u8ButtonValue;
}

/**
  * @brief  //按键消抖
  * @param
  * @retval None
  */
uint8_t Button_ReadPinStatus(uint8_t *pu8Button)
{
    uint8_t u8Pin;
    static uint8_t u8PinCount;
    static uint8_t u8PinPre;

    u8Pin = Button_Scan();

    if ( u8PinPre != u8Pin )
    {
        u8PinCount = 0;
    }
    else
    {
        if ( u8PinCount < 0xFF )
        {
            u8PinCount++;
        }
    }

    u8PinPre = u8Pin;

	if (u8PinCount < 50)
	{
        u8Pin = 0;
	}
    else
    {
        //u8Pin |= 0x80;
        //u8PinCount = 0;
        *pu8Button = u8Pin;
        return OK;
    }
	return !OK;
}






/* End of file */

