

#ifndef _TM1617_H_
#define _TM1617_H_
 
/*********************************************************************************/

typedef struct 
{
	uint8_t LedBuff[14];
	//uint8_t SegBuffPre[14];
	//uint8_t SegBuffFG;
	
	uint8_t Key[5];
	
	uint8_t ReadKeyCycle;
	uint8_t DisplayCycle;
	//uint8_t DispLaterRead;
    
}stTM1617_Typedef;

extern stTM1617_Typedef   stTM1617;

void TM1617_ReadKey(uint8_t *ucKeydata);
void LED2618_Opearte(void);
void TM1617_LEDControl(uint8_t *u8WriteDisplayData,uint8_t u8DisplayControlCmd);

#endif
