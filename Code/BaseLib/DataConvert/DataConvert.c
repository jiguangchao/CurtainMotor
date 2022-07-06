

/*============================ INCLUDES ======================================*/
#include "..\BaselibInclude.h"

/*============================ MACROS ========================================*/

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
#if 0
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void NumericalVariable2String_Dec(char *str,uint32_t u32Num)
{
    uint8_t i;
    uint16_t n;

    for ( i = 0; i < 8; i++ )
    {
        str[i] = 0;
    }

    if ( u32Num >= 1000000 )
    {
        return;
    }

    if ( u32Num >= 100000 )
    {
        str[0] = u32Num/100000 + '0';
        n      = u32Num%100000;
        str[1] = n/10000 + '0';
        n      = n%10000;
        str[2] = n/1000 + '0';
        n      = n%1000;
        str[3] = n/100 + '0';
        n      = n%100;
        str[4] = n/10 + '0';
        str[5] = n%10 + '0';
    }
    else if ( u32Num >= 10000 )
    {
        str[0] = u32Num/10000 + '0';
        n      = u32Num%10000;
        str[1] = n/1000 + '0';
        n      = n%1000;
        str[2] = n/100 + '0';
        n      = n%100;
        str[3] = n/10 + '0';
        str[4] = n%10 + '0';
    }
    else if ( u32Num >= 1000 )
    {
        str[0] = u32Num/1000 + '0';
        n      = u32Num%1000;
        str[1] = n/100 + '0';
        n      = n%100;
        str[2] = n/10 + '0';
        str[3] = n%10 + '0';
    }   
    else if ( u32Num >= 100 )
    {
        str[0] = u32Num/100 + '0';
        n      = u32Num%100;
        str[1] = n/10 + '0';
        str[2] = n%10 + '0';
    }
    else if ( u32Num >= 10 )
    {
        str[0] = u32Num/10 + '0';
        str[1] = u32Num%10 + '0';
    }
    else
    {
        str[0] = u32Num + '0';
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void NumericalVariable2String_Hex(char *str,uint32_t u32Num)
{
    uint8_t i;
    uint32_t n;

    for ( i = 0; i < 8; i++ )
    {
        str[i] = 0;
    }

    if ( u32Num >= 0x10000000 )
    {
        if (((u32Num / 0x10000000)) > 9)
        {
            str[0] = (((u32Num / 0x10000000)) + 7) + '0';
        }
        else
        {
            str[0] = ((u32Num / 0x10000000)) + '0';
        }
        n = u32Num % 0x10000000;
        if (((n / 0x1000000)) > 9)
        {
            str[1] = (((n / 0x1000000)) + 7) + '0';
        }
        else
        {
            str[1] = ((n / 0x1000000)) + '0';
        }
        n = u32Num % 0x1000000;
        if (((n / 0x100000)) > 9)
        {
            str[2] = (((n / 0x100000)) + 7) + '0';
        }
        else
        {
            str[2] = ((n / 0x100000)) + '0';
        }
        n = u32Num % 0x100000;
        if (((n / 0x10000)) > 9)
        {
            str[3] = (((n / 0x10000)) + 7) + '0';
        }
        else
        {
            str[3] = ((n / 0x10000)) + '0';
        }
        n = u32Num % 0x10000;
        if (((n / 0x1000)) > 9)
        {
            str[4] = (((n / 0x1000)) + 7) + '0';
        }
        else
        {
            str[4] = ((n / 0x1000)) + '0';
        }
        n = u32Num % 0x1000;
        if (((n / 0x100)) > 9)
        {
            str[5] = (((n / 0x100)) + 7) + '0';
        }
        else
        {
            str[5] = ((n / 0x100)) + '0';
        }
        n = u32Num % 0x100;
        if (((n / 0x10)) > 9)
        {
            str[6] = (((n / 0x10)) + 7) + '0';
        }
        else
        {
            str[6] = ((n / 0x10)) + '0';
        }
        n = u32Num % 0x10;
        if (n > 9)
        {
            str[7] = (n + 7) + '0';
        }
        else
        {
            str[7] = n + '0';
        }
    }
    else if ( u32Num >= 0x100000 )
    {
        if (((u32Num / 0x100000)) > 9)
        {
            str[0] = (((u32Num / 0x100000)) + 7) + '0';
        }
        else
        {
            str[0] = ((u32Num / 0x100000)) + '0';
        }
        n = u32Num % 0x100000;
        if (((n / 0x10000)) > 9)
        {
            str[1] = (((n / 0x10000)) + 7) + '0';
        }
        else
        {
            str[1] = ((n / 0x10000)) + '0';
        }
        n = u32Num % 0x10000;
        if (((n / 0x1000)) > 9)
        {
            str[2] = (((n / 0x1000)) + 7) + '0';
        }
        else
        {
            str[2] = ((n / 0x1000)) + '0';
        }
        n = u32Num % 0x1000;
        if (((n / 0x100)) > 9)
        {
            str[3] = (((n / 0x100)) + 7) + '0';
        }
        else
        {
            str[3] = ((n / 0x100)) + '0';
        }
        n = u32Num % 0x100;
        if (((n / 0x10)) > 9)
        {
            str[4] = (((n / 0x10)) + 7) + '0';
        }
        else
        {
            str[4] = ((n / 0x10)) + '0';
        }
        n = u32Num % 0x10;
        if (n > 9)
        {
            str[5] = (n + 7) + '0';
        }
        else
        {
            str[5] = n + '0';
        }
    }
    else if ( u32Num >= 0x1000 )
    {
        if (((u32Num / 0x1000)) > 9)
        {
            str[0] = (((u32Num / 0x1000)) + 7) + '0';
        }
        else
        {
            str[0] = ((u32Num / 0x1000)) + '0';
        }
        n = u32Num % 0x1000;
        if (((n / 0x100)) > 9)
        {
            str[1] = (((n / 0x100)) + 7) + '0';
        }
        else
        {
            str[1] = ((n / 0x100)) + '0';
        }
        n = u32Num % 0x100;
        if (((n / 0x10)) > 9)
        {
            str[2] = (((n / 0x10)) + 7) + '0';
        }
        else
        {
            str[2] = ((n / 0x10)) + '0';
        }
        n = u32Num % 0x10;
        if (n > 9)
        {
            str[3] = (n + 7) + '0';
        }
        else
        {
            str[3] = n + '0';
        }
    }
    else if ( u32Num >= 0x100 )
    {
        if (((u32Num / 0x100)) > 9)
        {
            str[0] = (((u32Num / 0x100)) + 7) + '0';
        }
        else
        {
            str[0] = ((u32Num / 0x100)) + '0';
        }
        n = u32Num % 0x100;
        if (((n / 0x10)) > 9)
        {
            str[1] = (((n / 0x10)) + 7) + '0';
        }
        else
        {
            str[1] = ((n / 0x10)) + '0';
        }
        n = u32Num % 0x10;
        if (n > 9)
        {
            str[2] = n + 7 + '0';
        }
        else
        {
            str[2] = n + '0';
        }
    }
    else if ( u32Num >= 0x10 )
    {
        if (((u32Num / 0x10)) > 9)
        {
            str[0] = (((u32Num / 0x10)) + 7) + '0';
        }
        else
        {
            str[0] = ((u32Num / 0x10)) + '0';
        }
        n = u32Num % 0x10;
        if (n > 9)
        {
            str[1] = n + 7 + '0';
        }
        else
        {
            str[1] = n + '0';
        }
    }
    else
    {
        if (u32Num > 9)
        {
            str[0] = u32Num + 7 + '0';
        }
        else
        {
            str[0] = u32Num + '0';
        }
    }
}
#endif

/**
  * @brief
  * @param
  * @retval None
  */
void HSVtoRGB(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t h, uint16_t s, uint16_t v)
{
    // R,G,B from 0-255, H from 0-360, S,V from 0-100
    int i;
    float RGB_min, RGB_max;
    RGB_max = v*2.55f;
    RGB_min = RGB_max*(100 - s) / 100.0f;

    i = h / 60;
    int difs = h % 60; // factorial part of h

                       // RGB adjustment amount by hue 
    float RGB_Adj = (RGB_max - RGB_min)*difs / 60.0f;

    switch (i) {
    case 0:
        *r = (uint8_t)RGB_max;
        *g = (uint8_t)(RGB_min + RGB_Adj);
        *b = (uint8_t)RGB_min;
        break;
    case 1:
        *r = (uint8_t)(RGB_max - RGB_Adj);
        *g = (uint8_t)RGB_max;
        *b = (uint8_t)RGB_min;
        break;
    case 2:
        *r = (uint8_t)RGB_min;
        *g = (uint8_t)RGB_max;
        *b = (uint8_t)(RGB_min + RGB_Adj);
        break;
    case 3:
        *r = (uint8_t)RGB_min;
        *g = (uint8_t)(RGB_max - RGB_Adj);
        *b = (uint8_t)RGB_max;
        break;
    case 4:
        *r = (uint8_t)(RGB_min + RGB_Adj);
        *g = (uint8_t)RGB_min;
        *b = (uint8_t)RGB_max;
        break;
    default:// case 5:
        *r = (uint8_t)RGB_max;
        *g = (uint8_t)RGB_min;
        *b = (uint8_t)(RGB_max - RGB_Adj);
        break;
    }
}


const uint8_t HexCode[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ClearBuff(char *p,uint8_t u8Size)
{
    uint8_t i;
    for (i = 0; i < u8Size; i++)
    {
        p[i] = 0x00;
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBlinkBuff(char *p8Buff,uint8_t u8BuffSize,uint32_t u32Input)
{
    uint8_t i;
    uint32_t u32Data;
    uint32_t u32n;

    switch (u8BuffSize)
    {
    case 1:
        u32n = 1;
        break;
    case 2:
        u32n = 10;
        break;
    case 3:
        u32n = 100;
        break;
    case 4:
        u32n = 1000;
        break;
    case 5:
        u32n = 10000;
        break;
    case 6:
        u32n = 100000;
        break;
    case 7:
        u32n = 1000000;
        break;
    case 8:
        u32n = 10000000;
        break;
        /*
    case 9:break;
    case 10:break;
    case 11:break;
    case 12:break;
        */
    }
    u32Data = u32Input;
    //u32n = u32n
    for ( i = 0; i < u8BuffSize; i++)
    {
        p8Buff[i] = HexCode[u32Data/u32n];
        u32Data  %= u32n;
        u32n      = u32n/10;       
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBuff(char *p8Buff,int32_t i32Data)
{
    int32_t i32;
    
    if ( i32Data >= 100000 )
    {
        p8Buff[0] = HexCode[i32Data/100000];
        i32       = i32Data%100000;
        p8Buff[1] = HexCode[i32/10000];
        i32       = i32%10000;
        p8Buff[2] = HexCode[i32/1000];
        i32       = i32%1000;
        p8Buff[3] = HexCode[i32/100];
        i32       = i32%100;
        p8Buff[4] = HexCode[i32/10];
        p8Buff[5] = HexCode[i32%10];
    }
    else if ( i32Data >= 10000 )
    {
        p8Buff[0] = HexCode[i32Data/10000];
        i32       = i32Data%10000;
        p8Buff[1] = HexCode[i32/1000];
        i32       = i32%1000;
        p8Buff[2] = HexCode[i32/100];
        i32       = i32%100;
        p8Buff[3] = HexCode[i32/10];
        p8Buff[4] = HexCode[i32%10];
    }
    else if ( i32Data >= 1000 )
    {
        p8Buff[0] = HexCode[i32Data/1000];
        i32       = i32Data%1000;
        p8Buff[1] = HexCode[i32/100];
        i32       = i32%100;
        p8Buff[2] = HexCode[i32/10];
        p8Buff[3] = HexCode[i32%10];
    }
    else if ( i32Data >= 100 )
    {
        p8Buff[0] = HexCode[i32Data/100];
        i32       = i32Data%100;
        p8Buff[1] = HexCode[i32/10];
        p8Buff[2] = HexCode[i32%10];
    }
    else if ( i32Data >= 10 )
    {
        i32       = i32Data%100;
        p8Buff[0] = HexCode[i32/10];
        p8Buff[1] = HexCode[i32%10];
    }
    else
    {
        p8Buff[0] = HexCode[i32Data];
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2HexBuff(char *p8Buff,uint32_t u32Data)
{
    p8Buff[0] = HexCode[(u32Data>>28)&0x0F];
    p8Buff[1] = HexCode[(u32Data>>24)&0x0F];
    p8Buff[2] = HexCode[(u32Data>>20)&0x0F];
    p8Buff[3] = HexCode[(u32Data>>16)&0x0F];
    p8Buff[4] = HexCode[(u32Data>>12)&0x0F];
    p8Buff[5] = HexCode[(u32Data>> 8)&0x0F];
    p8Buff[6] = HexCode[(u32Data>> 4)&0x0F];
    p8Buff[7] = HexCode[(u32Data>> 0)&0x0F];
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Version2HexBuff(char *p8Buff,uint32_t u32Data)
{
    p8Buff[0] = HexCode[(u32Data>>12)&0x0F];
    p8Buff[1] = HexCode[(u32Data>> 8)&0x0F];
    p8Buff[2] = HexCode[(u32Data>> 4)&0x0F];
    p8Buff[3] = '.';
    p8Buff[4] = HexCode[(u32Data>> 0)&0x0F];
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void YYMMDD2HexBuff(char *p8Buff,uint32_t u32Data)
{
    p8Buff[0] = HexCode[(u32Data>>28)&0x0F];
    p8Buff[1] = HexCode[(u32Data>>24)&0x0F];
    p8Buff[2] = HexCode[(u32Data>>20)&0x0F];
    p8Buff[3] = HexCode[(u32Data>>16)&0x0F];
    p8Buff[4] = '.';

    p8Buff[5] = HexCode[(u32Data>>12)&0x0F];
    p8Buff[6] = HexCode[(u32Data>> 8)&0x0F];
    p8Buff[7] = '.';

    p8Buff[8] = HexCode[(u32Data>> 4)&0x0F];
    p8Buff[9] = HexCode[(u32Data>> 0)&0x0F];
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HHMMSS2HexBuff(char *p8Buff,uint32_t u32Data)
{ 
    p8Buff[0] = HexCode[(u32Data>>20)&0x0F];
    p8Buff[1] = HexCode[(u32Data>>16)&0x0F];
    p8Buff[2] = '.';

    p8Buff[3] = HexCode[(u32Data>>12)&0x0F];
    p8Buff[4] = HexCode[(u32Data>> 8)&0x0F];
    p8Buff[5] = '.';

    p8Buff[6] = HexCode[(u32Data>> 4)&0x0F];
    p8Buff[7] = HexCode[(u32Data>> 0)&0x0F];
}
/* End of file */
