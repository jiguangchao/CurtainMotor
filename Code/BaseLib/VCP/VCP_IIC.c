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
//#define IIC_NOTE       (0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_init(I2C_Bus_Typedef *pI2C)
{
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pSetSdaHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_start(I2C_Bus_Typedef *pI2C)
{
    pI2C->HwPort.pSetSdaOutput();
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);

    pI2C->HwPort.pSetSdaHigh();    
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSdaLow();

    pI2C->HwPort.pSetSdaLow();    
    pI2C->HwPort.pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_stop(I2C_Bus_Typedef *pI2C)
{
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);

    pI2C->HwPort.pSetSdaLow();
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSdaHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_ack(I2C_Bus_Typedef *pI2C)
{
    pI2C->HwPort.pSetSdaOutput();

    pI2C->HwPort.pSetSdaLow();    
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSclLow(); 
    pI2C->HwPort.pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_no_ack(I2C_Bus_Typedef *pI2C)
{
    pI2C->HwPort.pSetSdaHigh();

    pI2C->HwPort.pSetSdaOutput();
       
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSclLow();
    pI2C->HwPort.pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_wait_ack(I2C_Bus_Typedef *pI2C)
{      
    uint16_t u16WaitNop;
      
    pI2C->HwPort.pSetSdaHigh();   
    pI2C->HwPort.pSetSdaInput();
  
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);     
    
    u16WaitNop = 250;
        
    while(u16WaitNop)
    {
        u16WaitNop--;
        if(pI2C->HwPort.pGetSdaGpio())
        {
            if (!u16WaitNop)
            {
                pI2C->HwPort.pSetSclLow();             
                /* 在进入该函数前获取SDA引脚状态时就已经把SDA引脚配置为了输入，所以这里如果获取失败就配置为输出20181206 */
                pI2C->HwPort.pSetSdaOutput();
                return !OK;
            }
            pI2C->HwPort.pWait(IIC_N_DELAY);
        }
        else
        {
            break;
        }
    }
    pI2C->HwPort.pSetSdaOutput();
    pI2C->HwPort.pSetSclLow();    
    return OK;

}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_send_byte(I2C_Bus_Typedef *pI2C,uint8_t sendData)
{ 
    uint8_t u8DisplayRegister;
    
    u8DisplayRegister = 8;
    pI2C->HwPort.pSetSclLow();
    while (u8DisplayRegister --)
    {       
        if (sendData&0x80)
        {
            pI2C->HwPort.pSetSdaHigh();
        }
        else
        { 
            pI2C->HwPort.pSetSdaLow(); 
        }
        
        sendData<<=1;

        pI2C->HwPort.pSetSclHigh();
        pI2C->HwPort.pWait(IIC_N_DELAY);

        pI2C->HwPort.pSetSclLow();

    }
    //pI2C->HwPort.pSetSclLow();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_receive_byte(I2C_Bus_Typedef *pI2C)
{   

    uint8_t i=0x80;
    uint8_t ReceiveByte=0;
    /* Before IIC SDA pin change to input mode,SDA should out high logic 
    that prevent the pin from being pulled low by VSS -- 20210113*/
    pI2C->HwPort.pSetSdaHigh();
    pI2C->HwPort.pSetSdaInput();
    pI2C->HwPort.pWait(IIC_N_DELAY);
    while(i)
    {
        pI2C->HwPort.pSetSclHigh();
        pI2C->HwPort.pWait(IIC_N_DELAY);
        if (pI2C->HwPort.pGetSdaGpio())
        {
            ReceiveByte |= i;
        }
        pI2C->HwPort.pSetSclLow();
        pI2C->HwPort.pWait(IIC_N_DELAY);
        i >>= 1;
    }   

    return ReceiveByte;

}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_InterfaceReset(I2C_Bus_Typedef *pI2C)
{   
    uint8_t u8Count;

    /* IIC start */ 
    pI2C->HwPort.pSetSdaHigh();
    pI2C->HwPort.pSetSclHigh();
    pI2C->HwPort.pWait(IIC_N_DELAY);
    pI2C->HwPort.pSetSdaLow();

    u8Count = 100;

    while (u8Count) 
    {
        u8Count--;
        
        pI2C->HwPort.pWait(IIC_N_DELAY);
        
        pI2C->HwPort.pSetSclHigh();
        
        pI2C->HwPort.pWait(IIC_N_DELAY);
        
        pI2C->HwPort.pSetSclLow();
        
        pI2C->HwPort.pWait(IIC_N_DELAY);
    }
    pI2C->HwPort.pSetSdaHigh();
    pI2C->HwPort.pSetSclHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_WriteAddress(uint8_t u8Cmd,uint8_t u8PhyAdd,I2C_Bus_Typedef *pI2C)
{   
    uint8_t u8WrData;

    u8WrData = u8Cmd|(u8PhyAdd<<1);
    
    I2C_send_byte(pI2C,u8WrData);

    if(I2C_wait_ack(pI2C))
    {
        I2C_stop (pI2C);
        return !OK;
    }
    
    return OK;
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_WriteDataWaitAck(uint8_t u8Data,I2C_Bus_Typedef *pI2C)
{      
    I2C_send_byte(pI2C,u8Data);

    if ( I2C_wait_ack(pI2C) )
    {
        I2C_stop (pI2C);
        return !OK;
    }
    
    return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_ReadDataWithAck(I2C_Bus_Typedef *pI2C)
{   
    uint8_t u8Data;

    u8Data = I2C_receive_byte(pI2C);  
          
    I2C_ack(pI2C);   

    return u8Data;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_ReadDataWithNoAck(I2C_Bus_Typedef *pI2C)
{   
    uint8_t u8Data;

    u8Data = I2C_receive_byte(pI2C);     
       
    I2C_no_ack(pI2C);   

    return u8Data;
}
/* EOF */
