

#include "..\BaselibInclude.h"

stTM1617_Typedef stTM1617;

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
void TM1617_ReadKey(uint8_t *ucKeydata)
{
    uint8_t u8KeyRegister;
				
	TM1617_WriteCmd(CMD_DATA|CMD_DATA_READ_KEY);
	
	TM1617_DATAIN();
		
	Nop_Delay(TM1617_DELAY_COUNT);
	Nop_Delay(TM1617_DELAY_COUNT);
			
	/* Read Data */
	for (u8KeyRegister = 0; u8KeyRegister < 5; u8KeyRegister++)
	{
		ucKeydata[u8KeyRegister] = TM1617_ReadByte();
	}	
	
	Nop_Delay(TM1617_DELAY_COUNT);
	
	TM1617_DATAOUT();
	
	Nop_Delay(TM1617_DELAY_COUNT);	
	TM1617_CLK_SET();	

	TM1617_DATA_SET();
	
	TM1617_STB_SET();
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
void TM1617_LEDControl(uint8_t *u8WriteDisplayData, uint8_t u8DisplayControlCmd)
{		   
	/* Set display mode */
    TM1617_WriteCmd(CMD_DISPLAY | CMD_DISPLAY_MODE_2_8);
	/* Set data cmd */
	TM1617_WriteCmd(CMD_DATA | CMD_DATA_WRITE_TO_REGISTER | CMD_DATA_ADD_AUTO_INCREASE);	
	/* Set display address */
	TM1617_WriteCmd(CMD_ADDRESS);
	
	/* Write data to display address */	
	TM1617_WriteDataAutoIncrease(u8WriteDisplayData);	
		
	/* Set display control cmd */
	TM1617_WriteCmd(CMD_DISPLAY_CONTROL | CMD_DUTY_14_16 | u8DisplayControlCmd);
	
	TM1617_STB_SET();	
	TM1617_CLK_SET();	
	TM1617_DATA_SET();	
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
	
	ucReadKeyFG = 0;
	
	if (( stTM1617.ReadKeyCycle >= 5)&&(stTM1617.DisplayCycle < 10)) // 2012.08.02
	{
        stTM1617.ReadKeyCycle = 0;
		TM1617_ReadKey(stTM1617.Key);	
		
		ucReadKeyFG = 1;
		//stTM1617.DisplayCycle = 0;//2012.08.02
		//stTM1617.DispLaterRead++;
		stTM1617.DisplayCycle++;
	}
	
	if (ucReadKeyFG == 0)
	{
		if ((stTM1617.DisplayCycle >= 10)&&(stTM1617.ReadKeyCycle >= 5)) // 2012.08.02
		{
			stTM1617.DisplayCycle = 0;
			

			//if (stLed_Key.KeyDownCoun)
			{
				TM1617_LEDControl(stTM1617.LedBuff,0x8B);	
			}
			//else
			{
				TM1617_LEDControl(stTM1617.LedBuff,0x88);
			}
			
			stTM1617.ReadKeyCycle = 0;	  //2012.08.02
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
