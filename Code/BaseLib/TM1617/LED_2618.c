

#include "..\BaselibInclude.h"


stLED2618_Typedef stLED2618;
/***********************************************************
*Function Name: LED2618_WriteByte
*
*Parameters:    ucWdata: 
*
*Description:   None
*
*Returns:       None
*
***********************************************************/
void LED2618_WriteByte(uint8_t ucWdata)
{
	uint8_t ucData;		
		
	for (ucData = 0x01; ucData != 0x00; ucData<<=1) 
	{	
		LED2618_CLK_CLR();
		
		//LED2618_DELAY();
		
		Soft_Delay(LED2618_DELAY_COUN);
				
		if (ucWdata&ucData) 
		{
			LED2618_DATA_SET();
		}
		else
		{
			LED2618_DATA_CLR();
		}
		//LED2618_DELAY();
		Soft_Delay(LED2618_DELAY_COUN);
		LED2618_CLK_SET();		
		
		//LED2618_DELAY();
		Soft_Delay(LED2618_DELAY_COUN);
	}
}
/***********************************************************
*Function Name: LED2618_ReadByte
*
*Parameters:    None
*
*Description:
*
*Returns:
*
***********************************************************/
uint8_t LED2618_ReadByte(void)
{
	uint8_t ucData;
	uint8_t ucReadData;
	
	ucReadData = 0x00;				
		
	for (ucData = 0x01; ucData != 0x00; ucData <<= 1) 
	{
		
		LED2618_CLK_CLR();	
		
		//LED2618_DELAY();
		//LED2618_DELAY();
		Soft_Delay(LED2618_DELAY_COUN);
		Soft_Delay(LED2618_DELAY_COUN);
		if (LED2618_DATAREAD()) 
		{			
			ucReadData |= ucData;
		}	
        //LED2618_DELAY();
		LED2618_CLK_SET();
			
		//LED2618_DELAY();
		Soft_Delay(LED2618_DELAY_COUN);
		
	}
		
	
	return ucReadData;
}
/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
void LED2618_WriteCmd(uint8_t ucCmd)
{		
    
	LED2618_STB_SET();	
	Soft_Delay(LED2618_DELAY_COUN);
	
	LED2618_STB_CLR();
	Soft_Delay(LED2618_DELAY_COUN);
	
		
	/* Write Command */
	LED2618_WriteByte(ucCmd); 
		
}
/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
void LED2618_WriteData(uint8_t *ucData)
{
    uint8_t ucI;
	
	
	/* Write Data */
	for (ucI = 0; ucI < 14; ucI++)//
	{
		LED2618_WriteByte(ucData[ucI]);
	}
	
	//LED2618_DELAY();
	
}
/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
void LED2618_WriteBytes(uint8_t *ucWdata,uint8_t ucDisCmd)
{		
    
	/* Mode cmd */
	LED2618_WriteCmd(CMD_MODE_COM4_SEG13);
	/* Data write or read cmd */
	LED2618_WriteCmd(CMD_DATA|CMD_DATA_W|CMD_DATA_ADD_INC);	
	/* Write Command */
	LED2618_WriteCmd(CMD_ADD);
	
	/* Write Data */	
	LED2618_WriteData(ucWdata);	
		
	/* Write Display Command */
	LED2618_WriteCmd(ucDisCmd);
	
	LED2618_STB_SET();	
	LED2618_CLK_SET();	
	LED2618_DATA_SET();	
}

/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
void LED2618_ReadKey(uint8_t *ucKeydata)
{
    uint8_t ucI;
				
	
	
	LED2618_WriteCmd(CMD_DATA|CMD_DATA_RKEY);
	
	LED2618_DATAIN();
	
	
	
	Soft_Delay(LED2618_DELAY_COUN);
			
	/* Read Data */
	for (ucI = 0; ucI < 5; ucI++)
	{
		ucKeydata[ucI] = LED2618_ReadByte();
	}	
	
	//LED2618_DELAY();
	Soft_Delay(LED2618_DELAY_COUN);
	LED2618_DATAOUT();
	
	//LED2618_DELAY();
	Soft_Delay(LED2618_DELAY_COUN);	
	LED2618_CLK_SET();	

	LED2618_DATA_SET();
	
	LED2618_STB_SET();
}
/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
void LED2618_Opearte(void)//
{
    uint8_t ucReadKeyFG;
	uint8_t ucI;
	
	ucReadKeyFG = 0;
	
	
	if (( stLED2618.ReadKeyCycle >= 5)&&(stLED2618.DisplayCycle < 10)) // 2012.08.02
	{
        stLED2618.ReadKeyCycle = 0;
		LED2618_ReadKey(stLED2618.Key);	
		
		ucReadKeyFG = 1;
		//stLED2618.DisplayCycle = 0;//2012.08.02
		//stLED2618.DispLaterRead++;
		stLED2618.DisplayCycle++;
	}
	
	if (ucReadKeyFG == 0)
	{
		if ((stLED2618.DisplayCycle >= 10)&&(stLED2618.ReadKeyCycle >= 5)) // 2012.08.02
		{
			stLED2618.DisplayCycle = 0;
			

			if (stLed_Key.KeyDownCoun)
			{
				LED2618_WriteBytes(stLED2618.SegBuff,0x8B);	
			}
			else
			{
				LED2618_WriteBytes(stLED2618.SegBuff,0x88);
			}
			
			stLED2618.ReadKeyCycle = 0;	  //2012.08.02
		}
	}
	
}
/***********************************************************
*Function Name: 
*
*Parameters:    
*
*Description:
*
*Returns:
*
***********************************************************/
