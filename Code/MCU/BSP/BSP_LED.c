
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
#include "BSP_LED.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/*Set输出高电平  Reset输出低电平 */     
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDON_RED(void)
{
    //LL_GPIO_SetOutputPin(LED_RED_GPIO, LED_RED_PIN) ;
    LL_GPIO_ResetOutputPin(LED_RED_GPIO, LED_RED_PIN);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDOFF_RED(void)
{
    //LL_GPIO_ResetOutputPin(LED_RED_GPIO, LED_RED_PIN);
    LL_GPIO_SetOutputPin(LED_RED_GPIO, LED_RED_PIN) ;
}
/**
 * @brief
 * @param
 * @retval None
 */








