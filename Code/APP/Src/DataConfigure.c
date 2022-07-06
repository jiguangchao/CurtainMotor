
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
#include "EnOceanlibInclude.h"
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "EnOceanTelegram.h"
#include "CurtainInterface.h"





#pragma pack(1)
/* Clover Dev Setting */
const RegTab_Typedef DevRegTab[]=
{
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_SOFT_VERSION                ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_SIGNAL_STRENGTH             ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ERROR_STATUS                ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_RESET_PASSWORD              ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_RUN_TIME                    ,    0,     0xFFFF,                     },


    
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_ENOCEAN_REAPTER              ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RESET_INITIALIZE             ,    0,     0xFFFF,                     },


    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_MOTOR_ACTION_CMD             ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MOTOR_TRIP_SET               ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_TOUCH_SET                    ,    0,     0xFFFF,                     },
                                                                                                                                 

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_COMMUTATION_SET              ,    0,     0xFFFF,                     },

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_CLEAR_TRIP_SET               ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MANUAL_SET_BORDAR            ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MANUAL_SET_BORDAR_ON         ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MANUAL_SET_BORDAR_OFF        ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MAX_TRIP_SET                 ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_MIN_TRIP_SET                 ,    0,     0xFFFF,                     },    
        

#ifdef HW_DEBUG
    
#endif

};
#pragma pack()

Dev_Typedef Dev;
eFLASH_RunTypedef         FLASHRUN;


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
uint8_t Dev_GetRegTabSize(void)
{
    return sizeof(DevRegTab) / sizeof(DevRegTab[0]);
}
/**
  * @brief
  * @param
  * @retval None
  */
//static uint8_t NVM_ReadLearnInfoDataCheck(void);
/*============================ IMPLEMENTATION ================================*/

/**
  * @brief  运行时间
  * @param
  * @retval None
  */
void NVM_DevRunSave(void)
{
    TimerFlag._u8Second180++;
    
    if(FLASHRUN.u32FlashWriteTime != 0)
    {
        FLASHRUN.u32FlashWriteTime--;
    }

    if (TimerFlag._u8Second180 >= 3600)
    {
        TimerFlag._u8Second180 = 0;
        Dev.Log.u32RunTime++; //运行时间1小时+1

        FLASHRUN.u8LogUpdateFlag = 1;
    }     
}

/**
  * @brief  //开机默认设置
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void)
{    
    Dev.Cfg.u32RemanCode                    = RM_DEFAULT_REMAN_CODE;
          
    Dev.Cfg.u32ResetPassword                = 0x12345678;
    Dev.Cfg.u8Repeater                      = 0;
}
/**
  * @brief  清除学习表的全部内容
  * @param
  * @retval None
  */
void EnOceanClearLearnListAll(void)
{
    uint8_t i;

    LearnInfoTab.u8nrIDs    = 0x00;
    LearnInfoTab.u8Reserve0 = 0x00;
    LearnInfoTab.u8Reserve1 = 0x00;
    LearnInfoTab.u8Reserve2 = 0x00;

    for (i = 0; i < 20; i++)
    {
        LearnInfoTab.entry[i].u32SrcId  = 0x00;
        LearnInfoTab.entry[i].u8EepFun  = 0x00;
        LearnInfoTab.entry[i].u8EepRorg = 0x00;
        LearnInfoTab.entry[i].u8EepType = 0x00;

        LearnInfoTab.entry[i].LrnDev.u16Data         = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u1LrnType   = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u2KeyState  = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u3Cmd       = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u3Key       = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u3OutMode   = 0x00;
        LearnInfoTab.entry[i].LrnDev.RPS.u5Channel   = 0x00;
    }
}
/**
  * @brief 重置默认数据 
  * @param
  * @retval None
  */
void ResetDefaultData(void)
{
    DevLoadDefaultSettings();
    EnOceanClearLearnListAll();
}
/**
  * @brief  
  * @param
  * @retval None
  */
void ResetDefaultDataByReset(void)
{    
    DevLoadDefaultSettingsByReset();
    EnOceanClearLearnListAll();
}

/**
  * @brief 开发人员通过重置加载默认设置 
  * @param
  * @retval None
  */
void DevLoadDefaultSettingsByReset(void)
{    
    
}

/**
   * @brief
   * @param
   * @retval
   */
uint8_t NVM_ChannelUpdate(uint8_t u8Channel)
{
    if (0 == u8Channel)
    {
        if ( Dev.u8DataUpdate < 0xFF )
        {
            Dev.u8DataUpdate ++;
        }
        return OK;
    }
    
    return !OK; 
}
/**
  * @brief  重置默认使能
  * @param
  * @retval None
  */
void ResetDefaultEnable(void)
{
    EnOceanSaveLearnTabEvent();

    NVM_ChannelUpdate(DEV_CHANNEL);    
}





/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Erase(void)
{
    if (Dev.u8EraseFlag == 1)
    {
        if (Dev.Cfg.u8CfgBlockCnt != 0)
        {
            FLASH_Remove_Page(FLASH_CFG_ADD);
            Dev.u8EraseFlag = 0;
        }
    }

    if(Dev.Cfg.u8CfgBlockCnt > FLASH_PAGE_NUM-1)
    {
        Dev.Cfg.u8CfgBlockCnt = 0;
    }
}
/****************************************************************************************************************/
/********************************          Cfg Flash        ***************************************************/
/*****************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_FactorySettings(void) //FLASHRUN 写入出厂设置参数
{
    uint8_t i;
    volatile uint8_t u8BlockFlag;

    u8BlockFlag = FLASH_PAGE_NUM;
    

    while (u8BlockFlag)
    {
        u8BlockFlag--;
        Dev.Cfg.u8CfgBlockCnt = u8BlockFlag;
        FLASH_Read_32Bit((FLASH_CFG_ADD + (u8BlockFlag * 0x200)), FLASH_CFG_READ_BUFF, sizeof(FLASH_CFG_READ_BUFF)/sizeof(uint32_t));

        if (0xFFFFFFFF != FLASH_CFG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_CfgDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Cfg.u32Words[i] = FLASH_CFG_READ_BUFF[i + 1];  
                }
                Dev.Log.u16FlashReadSuccessCount++;
                return;
            }
            else
            {
                Dev.Log.u16FlashReadFailCount++;
            }
        }

        FLASH_Read_32Bit((FLASH_CFG_ADD + (u8BlockFlag * 0x200 + 0x100)), FLASH_CFG_READ_BUFF, sizeof(FLASH_CFG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_CFG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_CfgDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Cfg.u32Words[i] = FLASH_CFG_READ_BUFF[i + 1];
                }
                Dev.Log.u16FlashReadSuccessCount++;
                return;
            }
            else
            {
                Dev.Log.u16FlashReadFailCount++;
            }
        }

    }

    if (0 == u8BlockFlag)
    {
        Dev.Cfg.u8CfgBlockCnt = 0;

        FLASH_Write_CfgDeal();
        if (OK != FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8CfgBlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, sizeof(FLASH_CFG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
        if (OK != FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8CfgBlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, sizeof(FLASH_CFG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_CfgDeal(void)
{
    uint8_t i;
    //uint32_t u32Header;
    uint32_t u32Check;

    Dev.Log.u16FlashWriteSuccessCount++;
    FLASH_CFG_WRITE_BUFF [0] =  0xAA5555AA; 

    for (i = 0 ; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t) ; i++)
    {
        FLASH_CFG_WRITE_BUFF[i+1] = Dev.Cfg.u32Words[i];
    }

    u32Check = FLASH_CRC32(FLASH_CFG_WRITE_BUFF,(sizeof(HWCfg_Typedef)/sizeof(uint32_t)+1));

    FLASH_CFG_WRITE_BUFF [sizeof(HWCfg_Typedef)/sizeof(uint32_t)+2] = u32Check;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Cfg(void)
{
    if (FLASHRUN.u8CfgUpdateFlag == 1)
    {    
        if (Dev.u8EraseFlag == 1)
        {
            if (Dev.Cfg.u8CfgBlockCnt != 0 || Dev.u8EraseFlag == 1)
            {
                FLASH_Remove_Page(FLASH_CFG_ADD);
                Dev.u8EraseFlag = 0;
            }
            
        }
        
        Dev.Cfg.u8CfgBlockCnt++;

        if (Dev.Cfg.u8CfgBlockCnt > FLASH_PAGE_NUM - 1)
        {
            Dev.Cfg.u8CfgBlockCnt = 0;
        }


        FLASH_Write_CfgDeal();

        FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8CfgBlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
        //FLASH_JustWrite_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
        FLASHRUN.u8CfgUpdateFlag = 2;
        FLASHRUN.u32FlashWriteTime = 2;
    }

    else if (FLASHRUN.u8CfgUpdateFlag == 2)
    {
        if (FLASHRUN.u32FlashWriteTime == 0)
        {
            FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8CfgBlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
            //FLASH_JustWrite_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
            FLASHRUN.u8CfgUpdateFlag = 0;
            FLASHRUN.u32FlashWriteTime = 0;
        }
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_CfgDeal(void)
{
    //uint8_t  i;
    uint32_t u32Check;

    u32Check = FLASH_CRC32(FLASH_CFG_READ_BUFF, (sizeof(HWCfg_Typedef)/sizeof(uint32_t)+1));
    //FLASHRUN.u32CRCTest = u32Check;
    if( 0xAA5555AA == FLASH_CFG_READ_BUFF[0])
    {
        if( u32Check == FLASH_CFG_READ_BUFF[(sizeof(HWCfg_Typedef)/sizeof(uint32_t)+2)] )
        {
            return OK;   
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWCfg(uint32_t u32add)
{
    HWCfg_Typedef HWCfg;
  

    if (OK == FLASH_ReadNBytes(u32add, HWCfg.u32Words, sizeof(HWCfg_Typedef) / sizeof(uint32_t)))
    {

            Dev.Cfg.u32RemanCode = HWCfg.u32RemanCode;
            Dev.Cfg.u32ResetPassword = HWCfg.u32ResetPassword;
            Dev.Cfg.u32EnOceanChipID = HWCfg.u32EnOceanChipID;
            Dev.Cfg.u32EnOceanBaseID = HWCfg.u32EnOceanBaseID;

            Dev.Cfg.u8Repeater      = HWCfg.u8Repeater;
            Dev.Cfg.u8Repeater0     = HWCfg.u8Repeater0;
            Dev.Cfg.u8Repeater1     = HWCfg.u8Repeater1;
            Dev.Cfg.u8Repeater2     = HWCfg.u8Repeater2;
            Dev.Cfg.u8RadioInterval = HWCfg.u8RadioInterval;

            Dev.Cfg.u8CfgBlockCnt      = HWCfg.u8CfgBlockCnt  ;
            Dev.Cfg.u8LogBlockCnt      = HWCfg.u8LogBlockCnt  ;
            Dev.Cfg.u8LearnBlockCnt    = HWCfg.u8LearnBlockCnt;


        
    }
}

/****************************************************************************************************************/
/********************************          Log Flash        ***************************************************/
/*****************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_LOG(void) //FLASH读写日志
{
    uint8_t i;
    volatile uint8_t u8BlockFlag;

    u8BlockFlag = FLASH_PAGE_NUM;
    
    //Dev.Log.u32PowerOnCount++;

    //DevLoadDefaultSettingsByReset();

    while (u8BlockFlag)
    {
        u8BlockFlag--;
        Dev.Cfg.u8LogBlockCnt = u8BlockFlag;
        FLASH_Read_32Bit(FLASH_LOG_ADD + u8BlockFlag * 0x200, FLASH_LOG_READ_BUFF,  sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LOG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LogDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWLogInfo_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Log.u32Words[i] = FLASH_LOG_READ_BUFF[i + 1];  
                }
                Dev.Log.u16FlashReadSuccessCount++;
                return;
            }

        }

        FLASH_Read_32Bit(FLASH_LOG_ADD + u8BlockFlag * 0x200 + 0x100, FLASH_LOG_READ_BUFF, sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LOG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LogDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWLogInfo_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Log.u32Words[i] = FLASH_LOG_READ_BUFF[i + 1];  
                }
                Dev.Log.u16FlashReadSuccessCount++;
                return;
            }
        }

    }

    if (0 == u8BlockFlag)
    {
        Dev.Cfg.u8LogBlockCnt = 0;

        FLASH_Write_LogDeal();
        if (OK != FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8LogBlockCnt * 0x200)), FLASH_LOG_WRITE_BUFF, sizeof(FLASH_LOG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
        if (OK != FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8LogBlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, sizeof(FLASH_LOG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LogDeal(void)
{
    uint8_t i;
    //uint32_t u32Header;
    uint32_t u32Check;

    //Dev.Log.u16FlashWriteSuccessCount++;
    FLASH_LOG_WRITE_BUFF [0] =  0xBB5555BB; 

    for (i = 0 ; i < (sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)) ; i++)
    {
        FLASH_LOG_WRITE_BUFF[i+1] = Dev.Log.u32Words[i];
    }

    u32Check = FLASH_CRC32(FLASH_LOG_WRITE_BUFF,(sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)+1));

    FLASH_LOG_WRITE_BUFF [(sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)+2)] = u32Check;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Log(void)
{
    if (FLASHRUN.u8LogUpdateFlag == 1)
    {
        if (Dev.u8EraseFlag == 1)
        {
            if (Dev.Cfg.u8LogBlockCnt != 0)
            {
                FLASH_Remove_Page(FLASH_LOG_ADD);
            }
            Dev.u8EraseFlag = 0;
        }

        Dev.Cfg.u8LogBlockCnt++;
        Dev.Log.u16FlashWriteSuccessCount++;

        if (Dev.Cfg.u8LogBlockCnt > FLASH_PAGE_NUM - 1)
        {
            Dev.Cfg.u8LogBlockCnt = 0;
        }

        FLASH_Write_LogDeal();
        FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8LogBlockCnt * 0x200)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
        //FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
        FLASHRUN.u8LogUpdateFlag = 2;
        FLASHRUN.u32FlashWriteTime = 2;
    }
    else if (FLASHRUN.u8LogUpdateFlag == 2)
    {
        if (FLASHRUN.u32FlashWriteTime == 0)
        {
            FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8LogBlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
            FLASHRUN.u8LogUpdateFlag = 0;
            FLASHRUN.u32FlashWriteTime = 0;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LogDeal(void)
{
  
    uint32_t u32Check;
    uint32_t u32Num;

    u32Num = sizeof(Dev.Log.u32Words)/sizeof(uint32_t);

    u32Check = FLASH_CRC32(FLASH_LOG_READ_BUFF,  (u32Num+1));
 
    if( 0xBB5555BB == FLASH_LOG_READ_BUFF[0])
    {
        if( FLASH_LOG_READ_BUFF[u32Num+2] == u32Check   )
        {
            return OK;   
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLog(uint32_t u32add)
{
    HWLogInfo_Typedef HWLog;

    if ( OK == FLASH_ReadNBytes(u32add, HWLog.u32Words, sizeof(HWLogInfo_Typedef) / sizeof(uint32_t)) )
    {        

        Dev.Log.u32RunTime          = HWLog.u32RunTime;
        Dev.Log.u32PowerOnCount     = HWLog.u32PowerOnCount;       
        Dev.Log.u32SoftFaultCount   = HWLog.u32SoftFaultCount;       
                
    }
 
}

/****************************************************************************************************************/
/********************************          Learn Flash        ***************************************************/
/*****************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_Learn(void) //FLASHRUN 读写学习表
{
    uint16_t i;
    volatile uint8_t u8BlockFlag;

    u8BlockFlag = FLASH_PAGE_NUM;

    while (u8BlockFlag)
    {
        u8BlockFlag--;
        Dev.Cfg.u8LearnBlockCnt = u8BlockFlag;

        FLASH_Read_32Bit((FLASH_LEARN_ADD1 + (u8BlockFlag * 0x200)), FLASH_LEARN_READ_BUFF, sizeof(FLASH_LEARN_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LEARN_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LearnDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t); i++)
                {
                    LearnInfoTab.u32Words[i] = FLASH_LEARN_READ_BUFF[i + 1];  
                }
                Dev.Log.u16FlashReadSuccessCount++; 
                return ;              
            }
            else
            {
                Dev.Log.u16FlashReadFailCount++;
            }
        }
        
        FLASH_Read_32Bit((FLASH_LEARN_ADD1 + (u8BlockFlag * 0x200 + 0x100)), FLASH_LEARN_READ_BUFF, sizeof(FLASH_LEARN_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LEARN_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LearnDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t); i++)
                {
                    LearnInfoTab.u32Words[i] = FLASH_LEARN_READ_BUFF[i + 1]; 
                }
                Dev.Log.u16FlashReadSuccessCount++;
                return ;
            }
            else
            {
                Dev.Log.u16FlashReadFailCount++;
            }
        }
        
    }

    if (0 == u8BlockFlag)
    {
        Dev.Cfg.u8LearnBlockCnt = 0;
        
        FLASH_Write_LearnDeal();
        
        if (OK != FLASH_Write_32Bit((FLASH_LEARN_ADD1 + (Dev.Cfg.u8LearnBlockCnt * 0x200)), FLASH_LEARN_WRITE_BUFF, sizeof(FLASH_LEARN_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
        if (OK != FLASH_Write_32Bit((FLASH_LEARN_ADD1 + (Dev.Cfg.u8LearnBlockCnt * 0x200 + 0x100)), FLASH_LEARN_WRITE_BUFF, sizeof(FLASH_LEARN_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Log.u16FlashWriteFailCount++;
        }
        
    }
    
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LearnDeal(void)
{
    uint16_t i;
    uint32_t u32Check;

    FLASH_LEARN_WRITE_BUFF[0] =  0xBB5555BB; 

    for (i = 0 ; i < (sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t)) ; i++)
    {
        FLASH_LEARN_WRITE_BUFF[i+1] = LearnInfoTab.u32Words[i];
    }

    u32Check = FLASH_CRC32(FLASH_LEARN_WRITE_BUFF,(sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t)+1));

    FLASH_LEARN_WRITE_BUFF[(sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t)+2)] = u32Check;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Learn(void)
{
    if (FLASHRUN.u8LearnUpdateFlag == 1)
    {
        if (Dev.u8EraseFlag == 1)
        {
            if (Dev.Cfg.u8LearnBlockCnt != 0)
            {
                FLASH_Remove_Page(FLASH_LEARN_ADD1);
            }
            Dev.u8EraseFlag = 0;
        }

        Dev.Cfg.u8LearnBlockCnt++;
        Dev.Log.u16FlashWriteSuccessCount++;

        if (Dev.Cfg.u8LearnBlockCnt > FLASH_PAGE_NUM - 1)
        {
            Dev.Cfg.u8LearnBlockCnt = 0;
        }

        FLASH_Write_LearnDeal();
        FLASH_Write_32Bit((FLASH_LEARN_ADD1 + (Dev.Cfg.u8LearnBlockCnt * 0x200)), FLASH_LEARN_WRITE_BUFF, (sizeof(FLASH_LEARN_WRITE_BUFF) / sizeof(uint32_t)));
        //FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
        FLASHRUN.u8LearnUpdateFlag = 2;
        FLASHRUN.u32FlashWriteTime = 2;
    }
    else if (FLASHRUN.u8LearnUpdateFlag == 2)
    {
        if (FLASHRUN.u32FlashWriteTime == 0)
        {
            FLASH_Write_32Bit((FLASH_LEARN_ADD1 + (Dev.Cfg.u8LearnBlockCnt * 0x200 + 0x100)), FLASH_LEARN_WRITE_BUFF, (sizeof(FLASH_LEARN_WRITE_BUFF) / sizeof(uint32_t)));
            FLASHRUN.u8LearnUpdateFlag = 0;
            FLASHRUN.u32FlashWriteTime = 0;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LearnDeal(void)
{
  
    uint32_t u32Check;
    uint32_t u32Num;

    u32Num = sizeof(LearnInfoTab.u32Words)/sizeof(uint32_t);

    u32Check = FLASH_CRC32(FLASH_LEARN_READ_BUFF,  (u32Num+1));
 
    if( 0xBB5555BB == FLASH_LEARN_READ_BUFF[0])
    {
        if( FLASH_LEARN_READ_BUFF[u32Num+2] == u32Check   )
        {
            return OK;   
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLearn(uint32_t u32add)
{
    
    LearnID_TYPE   HWLearn;
    uint8_t  u8entry;
    uint8_t  i; 

    u8entry = LearnInfoTab.u8nrIDs;

    if (OK == FLASH_ReadNBytes(u32add, HWLearn.u32Words, sizeof(LearnInfoTab.u32Words) / sizeof(uint32_t)))
    {
        //LearnInfoTab.u8Bytes = HWLearn.u8Bytes;
        LearnInfoTab.u8nrIDs    = HWLearn.u8nrIDs;
        LearnInfoTab.u8Reserve0 = HWLearn.u8Reserve0;
        LearnInfoTab.u8Reserve1 = HWLearn.u8Reserve1;
        LearnInfoTab.u8Reserve2 = HWLearn.u8Reserve2;

        for (i = u8entry; i > 0; i--)
        {
            LearnInfoTab.entry[i-1].u32SrcId  = HWLearn.entry[i-1].u32SrcId;
            LearnInfoTab.entry[i-1].u8EepFun  = HWLearn.entry[i-1].u8EepFun;
            LearnInfoTab.entry[i-1].u8EepRorg = HWLearn.entry[i-1].u8EepRorg;
            LearnInfoTab.entry[i-1].u8EepType = HWLearn.entry[i-1].u8EepType;

            LearnInfoTab.entry[i-1].LrnDev.RPS.u1LrnType  = HWLearn.entry[i-1].LrnDev.RPS.u1LrnType;
            LearnInfoTab.entry[i-1].LrnDev.RPS.u2KeyState = HWLearn.entry[i-1].LrnDev.RPS.u2KeyState;
            LearnInfoTab.entry[i-1].LrnDev.RPS.u3Cmd      = HWLearn.entry[i-1].LrnDev.RPS.u3Cmd;
            LearnInfoTab.entry[i-1].LrnDev.RPS.u3Key      = HWLearn.entry[i-1].LrnDev.RPS.u3Key;
            LearnInfoTab.entry[i-1].LrnDev.RPS.u3OutMode  = HWLearn.entry[i-1].LrnDev.RPS.u3OutMode;
            LearnInfoTab.entry[i-1].LrnDev.RPS.u5Channel  = HWLearn.entry[i-1].LrnDev.RPS.u5Channel;
        } 
    }
}

/* End of file */

