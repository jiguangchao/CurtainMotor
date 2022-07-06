/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com> 
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to 
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1  
*         Data: 
*          
*     V1.0  
*         Data:2015.1.26
*         Official release
****************************************************************************/

#ifndef __M24CXX_H__
#define __M24CXX_H__

#include "..\..\MCU\platform.h"

typedef enum
{
	eM24C01_PAGE = 16,
	eM24C02_PAGE = 32,
	eM24C04_PAGE = 32,
	eM24C08_PAGE = 64,
	eM24C16_PAGE = 128,	
}eM24CXX_PAGE_MAX;

typedef enum
{
	eM24C01_PAGE_BYTES_MAX = 16,
	eM24C02_PAGE_BYTES_MAX = 32,
	eM24C04_PAGE_BYTES_MAX = 32,
	eM24C08_PAGE_BYTES_MAX = 64,
	eM24C16_PAGE_BYTES_MAX = 128,
	
}eM24CXX_PAGE_BYTES_MAX;

typedef enum
{
    eM24CXX_OK = 0,
    eM24CXX_ERR_WRITE_PHY_NO_ACK,
    eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK,
    eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK,
    eM24CXX_ERR_WRITE_DATA_NO_ACK,
    eM24CXX_ERR_READ_DATA_WRITE_PHY_NO_ACK,

    eM24CXX_ERR_INPUT_PHY_ADDRESS,
    eM24CXX_ERR_INPUT_PAGE,
    
}eM24CXX_RETURN_TYPE;


typedef struct
{    
    uint16_t u16ReadPeriod;
    uint8_t  u8ReadWait;

    uint16_t u16Status;
    uint8_t  u8ErrorCount;
    uint8_t  u8Error;

    uint8_t *p8Data;
    
    I2C_Bus_Typedef I2C;
}M24CXX_Typedef;

extern M24CXX_Typedef M24CXX;

/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_ReadBytes(I2C_Bus_Typedef *pM24CXX);
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WriteBytes(I2C_Bus_Typedef *pM24CXX);
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_RWDemo(void);

#endif
/* EOF */
