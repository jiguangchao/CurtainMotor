
#ifndef _BSP_INCLUDE_H_
#define _BSP_INCLUDE_H_


//#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <intrinsics.h>

#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_rng.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_hal_flash.h"
#include "stm32g0xx_hal_flash_ex.h"



#include "Common.h"
#include ".\BSP_IOMap.h"

#include ".\BSP_030\Inc\BSP_Init.h"
#include ".\BSP_030\Inc\BSP_USART.h"
#include ".\BSP_030\Inc\BSP_Button.h"

#include ".\BSP_Flash.h"

#define NOP() nop()
/*
#ifndef OK
#define OK            (0)
#endif
*/
enum
{
    OK = 0,   
};


typedef struct
{
    uint8_t  u3Permission :3;
    uint8_t  u1RangeEnable:1;

    uint8_t  u8RegID       ;
    uint16_t u16MinValue   ;
    uint16_t u16MaxValue   ;
}RegTab_Typedef;



#endif
