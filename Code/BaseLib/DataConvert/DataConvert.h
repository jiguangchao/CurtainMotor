

#ifndef _DATA_CONVERT_H_
#define _DATA_CONVERT_H_


extern const uint8_t HexCode[];

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
//void NumericalVariable2String_Dec(char *str,uint32_t u32Num);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
//void NumericalVariable2String_Hex(char *str,uint32_t u32Num);
/**
  * @brief
  * @param
  * @retval None
  */
void HSVtoRGB(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t h, uint16_t s, uint16_t v);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ClearBuff(char *p,uint8_t u8Size);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBlinkBuff(char *p8Buff,uint8_t u8BuffSize,uint32_t u32Input);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBuff(char *p8Buff,int32_t i32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Version2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void YYMMDD2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HHMMSS2HexBuff(char *p8Buff,uint32_t u32Data);


#endif

/* End of file */
