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

/*============================ INCLUDES ======================================*/

#include "..\BaselibInclude.h"


/*============================ MACROS ========================================*/
#define M24CXX_IIC_DEMOTEST                     (0) 
#define M24CXX_IIC_CMD_WRITE                    IIC_CMD_WRITE
#define M24CXX_IIC_CMD_READ                     IIC_CMD_READ

#define M24CXX_WRITE_OVER_PAGE_MAX_ENABLE        (1)              


#define M24CXX_PHY_ADDRESS_ID         (0xA0)

#define M24C128_PAGE_MAX              (128) 
#define M24C256_PAGE_MAX              (128) 
#define M24C512_PAGE_MAX              (128) 
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
 

/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_ReadBytes(I2C_Bus_Typedef *pM24CXX)
{
    uint16_t i=0; 
    uint8_t u8Data;
    
    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }
        
    u8Data = pM24CXX->u8PhyAddress + M24CXX_PHY_ADDRESS_ID;
    u8Data <<= 1;
    I2C_start(pM24CXX);    
    I2C_send_byte(pM24CXX, u8Data);

    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   

    I2C_send_byte(pM24CXX, pM24CXX->u16DataAddress>>8);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
    }

    I2C_send_byte(pM24CXX, pM24CXX->u16DataAddress&0xFF);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }
    u8Data = pM24CXX->u8PhyAddress + M24CXX_PHY_ADDRESS_ID;
    u8Data <<= 1;    
    u8Data  |= M24CXX_IIC_CMD_READ;
    I2C_start(pM24CXX);
    I2C_send_byte(pM24CXX, u8Data);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_READ_DATA_WRITE_PHY_NO_ACK;
    }

    for (i = 0;i < pM24CXX->u16DataLength;i++)
    {        
        pM24CXX->p8Data[i] = I2C_receive_byte(pM24CXX); 

        if ( i != (pM24CXX->u16DataLength-1) )
        {    
            I2C_ack(pM24CXX); 
        }
    }     
    I2C_no_ack(pM24CXX);
    I2C_stop(pM24CXX);
    return eM24CXX_OK; 
}
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WriteBytes(I2C_Bus_Typedef *pM24CXX)
{        
    uint16_t i=0;
    uint8_t u8Data;
    
    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }
        
    u8Data = pM24CXX->u8PhyAddress + M24CXX_PHY_ADDRESS_ID;
    u8Data <<= 1;

    I2C_start(pM24CXX);
    
    I2C_send_byte(pM24CXX, u8Data);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   

    I2C_send_byte(pM24CXX, pM24CXX->u16DataAddress>>8);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
    }

    I2C_send_byte(pM24CXX, pM24CXX->u16DataAddress&0xFF);
    if ( !OK == I2C_wait_ack(pM24CXX) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }

    for( i = 0; i < pM24CXX->u16DataLength;i++)
    {
        I2C_send_byte(pM24CXX, pM24CXX->p8Data[i]);

        if ( !OK == I2C_wait_ack(pM24CXX) )
        {
            I2C_stop(pM24CXX);
            return eM24CXX_ERR_WRITE_DATA_NO_ACK;
        }        
    }	    

    I2C_stop(pM24CXX);

    return eM24CXX_OK; 
}
/**
   * @brief 
   * @param 
   * @retval 
   */
#if M24CXX_IIC_DEMOTEST > 0

    static uint8_t u8ReadBuff[256];
    static uint8_t u8WriteBuff[256];

    eM24CXX_RETURN_TYPE M24CXX_RWDemo(void)
    {
        uint16_t u16i;
        uint16_t u16j;   

        uint32_t u32Delay;
        
        
        I2C_Bus_Typedef M24Driver;

        M24Driver.p8Data          = u8ReadBuff;
        
        M24Driver.u16DataLength   = 128;
        M24Driver.u16PageMax      = 128;
        M24Driver.u8PhyAddress    = 0x00;

        for (u16i = 0; u16i < 256; u16i ++) 
        {
            u8WriteBuff[u16i] = u16i;
            u8ReadBuff[u16i]  = 0x00;
        }
        /* Test write one byte */
        
        M24Driver.u16DataLength   = 1;
        M24Driver.u8PhyAddress    = 0;
        for (u16i = 0; u16i < 256; )
        {
            M24Driver.u16DataAddress  =  u16i+128;
            M24Driver.p8Data          = &u8WriteBuff[u16i];
            if ( eM24CXX_OK == M24CXX_WriteBytes(&M24Driver) )
            {
                u16i++;
            }
            u32Delay = 1000;
            while (u32Delay) 
            {
                u32Delay--;
                M24CXX_IIC_NOP();
            }
        }
        u32Delay = 6000;
        while (u32Delay) 
        {
            u32Delay--;
            M24CXX_IIC_NOP();
        }
        /* Test Read one byte */
        
        M24Driver.u16DataLength   = 1;
        for (u16i = 0; u16i < 256; )
        {        
            M24Driver.u16DataAddress  =  u16i+128;
            M24Driver.p8Data          = &u8ReadBuff[u16i];
            if ( eM24CXX_OK == M24CXX_ReadBytes(&M24Driver) )
            {
                u16i++;
            }
            
        }


        for (u16j = 0; u16j < 256; u16j++)
        {
            u8ReadBuff[u16j]  = 0x00;
        }
        /* Test Write one Page */
        M24Driver.p8Data = u8WriteBuff;
        M24Driver.u16DataLength   = 128;
        for (u16i = 0; u16i < 512; )
        {       
            M24Driver.u16DataAddress =  u16i*128;
            if ( eM24CXX_OK == M24CXX_WriteBytes(&M24Driver) )        
            {
                u16i++;
            }
            u32Delay = 1000;
            while (u32Delay) 
            {
                u32Delay--;
                M24CXX_IIC_NOP();
            }
            
        }
        u32Delay = 6000;
        while (u32Delay) 
        {
            u32Delay--;
            M24CXX_IIC_NOP();
        }
        /* Test Read one Page */
        M24Driver.p8Data = u8ReadBuff;
        M24Driver.u16DataLength   = 128;
        for (u16i = 0; u16i < 512; )
        {   
            M24Driver.u16DataAddress =  u16i*128;     
            if ( eM24CXX_OK == M24CXX_ReadBytes(&M24Driver) )
            {
                u16i++;
            }

            for (u16j = 0; u16j < 256; u16j++)
            {
                u8ReadBuff[u16j]  = 0x00;
            }
        }
        return eM24CXX_OK;
    }
    #endif

/**
   * @brief 
   * @param 
   * @retval 
   */
/*
void m24512_driver_init(M24512_Device_t *me,M24512_init_t init_Struct)
{
    me->i2cPort  = init_Struct.i2cPort;
    me->pageWriteWait = init_Struct.pageWriteWait;
    I2C_init((VCP_IICInterface_Typedef*)me);
}
*/
#if 0
/**
   * @brief 
   * @param 
   * @retval 
   */
bool m24512_driver_write_page(M24512_Device_t *me,uint16_t address,\
                          uint16_t length,uint8_t *data)
{
    uint16_t i=0;
    bool result = FALSE;
    result = M24512_write_address(me,address); 
    if(result)
    {
       for(i=0;i<length;i++)
       {
          I2C_send_byte((VCP_IICInterface_Typedef*)me,data[i]);		 
          result = I2C_wait_ack((VCP_IICInterface_Typedef*)me);             
          if(!result)
          {
             I2C_stop((VCP_IICInterface_Typedef*)me); 
             return FALSE;
          }

          address++;
          if((address&0x0000007f)==0)
          {
              I2C_stop((VCP_IICInterface_Typedef*)me);
              me->pageWriteWait(); 
              result = M24512_write_address(me,address);
          }
       }	
       I2C_stop((VCP_IICInterface_Typedef*)me);
       return TRUE;
    }
    else
    {
       I2C_stop((VCP_IICInterface_Typedef*)me);
       return FALSE;
    }
}
/**
   * @brief 
   * @param 
   * @retval 
   */
static uint8_t M24CXX_WriteAddress(uint8_t u8PhyAddress,uint16_t u16DataAddress)
{    
    uint8_t result = FALSE;     
 
    if ( u8PhyAddress > 7)
    {
        return FALSE;
    }
    u8PhyAddress <<= 1;
    u8PhyAddress  |= M24CXX_PHY_ADDRESS_ID|M24CXX_IIC_CMD_WRITE;
    M24CXX_IIC_Start();
    
    M24CXX_IIC_SendByte(u8PhyAddress);

    if ( FALSE == M24CXX_IIC_WaitAck() )
    {

    }   

    M24CXX_IIC_SendByte(u16DataAddress>>8);

    if ( FALSE == M24CXX_IIC_WaitAck() )
    {

    }

    M24CXX_IIC_SendByte(u16DataAddress&0xFF);

    if ( FALSE == M24CXX_IIC_WaitAck() )
    {

    }

    

    return TRUE;
}
#endif
/* EOF */
