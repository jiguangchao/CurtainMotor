#ifndef __HW_TEST_H__
#define __HW_TEST_H__


/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"


typedef enum
{
    eHWTEST_STANDBY = 0,   // 待机状态

    eHWTEST_LEDDETECT,     //LED检测
    eHWTEST_MOTORDETECT,   //电机检测
    eHWTEST_EnoceanDETECT, //Enocean检测


} HWTest_t; //


typedef enum
{
    eHWTestLEDRUN_STANDBY = 1, // 待机状态

    //闪烁模式
    eHWTestLEDRUN_BLINKMODE_INIT,  //闪烁模式开始
    eHWTestLEDRUN_BLINKMODE_ON,    //闪烁模式开状态
    eHWTestLEDRUN_BLINKMODE_OFF,   //闪烁模式关状态 

    eHWTestLEDRUN_END , // 结束状态

} HWTest_LedRunMode_t; //LED运行状态

typedef enum //窗帘电机运行状态
{
    eHWTestCURTAINRUN_IDLE                = 0x00, //闲置状态
    
    /*       出厂自检测试电机          */
    eHWTestCURTAINRUN_HWTEST_FORWARD      = 0x40, //出厂测试电机正转
    eHWTestCURTAINRUN_HWTEST_FORWARD_WAIT = 0x41, //出厂测试电机正转等待
    eHWTestCURTAINRUN_HWTEST_STOPA        = 0x42, //出厂测试电机停止
    eHWTestCURTAINRUN_HWTEST_STOP_WAITA   = 0x43, //出厂测试电机停止等待    
    eHWTestCURTAINRUN_HWTEST_REVERSE      = 0x44, //出厂测试电机反转
    eHWTestCURTAINRUN_HWTEST_REVERSE_WAIT = 0x45, //出厂测试电机反转等待
    eHWTestCURTAINRUN_HWTEST_STOPB        = 0x46, //出厂测试电机停止
    eHWTestCURTAINRUN_HWTEST_STOP_WAITB   = 0x47, //出厂测试电机停止等待    

} HWTest_CurtainRun_TYPE;


typedef struct
{
    HWTest_t eHWTestPoll;    //自检运行模式
 
    HWTest_LedRunMode_t eHWTestLed;         //自检Led运行
    HWTest_CurtainRun_TYPE eHWTestCurtain;  //出厂自检窗帘

    uint32_t u32LedRunTimer;    
    uint32_t u32RunBlinkCount;
    
    uint32_t u32BlinkONTime;    // 闪烁时开启时间
    uint32_t u32BlinkOFFTime;   // 闪烁时关闭启时间
    uint32_t u32BlinkTime;      // 闪烁时间

    uint32_t u32CurtainRunWait;  //窗帘运行等待

    uint8_t u8SelfTestState;     //自检进入标记
    uint16_t u16HWTestTimer;     //自检LED定时器
    uint32_t u32HWTestCount;     //自检定时计数

    uint32_t u32HWTestEnoceanSendCout;   //Enocean发送计数

} HWTest_Typedef;

extern HWTest_LedRunMode_t HWTestLed;
extern HWTest_Typedef HWTest;
extern HWTest_CurtainRun_TYPE HWTestCurtain;

/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTest_Tick1ms(HWTest_Typedef *pHWTest);
/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTestLed(HWTest_Typedef *pHWTest);


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardwareSelfTest(HWTest_Typedef *pHWTest);

#endif
