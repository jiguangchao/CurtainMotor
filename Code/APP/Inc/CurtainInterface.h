#ifndef _CURTAIN_INTERFACE_H_
#define _CURTAIN_INTERFACE_H_


#define CURTAIN_CONFIG_RPS_KEY                              (0x17)

#define LED_FAST_FLASH_TIME                                 (500)   //快速闪烁时间
#define LED_SLOW_FLASH_TIME                                 (1000)  //慢速闪烁时间


#define CURTAIN_RUN_TEST_TIME                               (100)  //1s


/**********************************************************************************/
/*                     数据存储                                                   */
/******************************************************************* **************/
typedef struct
{
    uint32_t u32UpLimit;         //上限位值
    uint32_t u32DownLimit;       //下限位值
    uint32_t u32ThirdLimt;       //第三限位值
    uint32_t u32RealtimeLimt;    //实时位置
    uint32_t u32SoftwareVersion; //软件版本号

    uint8_t u8MotorState;        //电机状态
    uint8_t u8MotorDirection;    //电机方向
    uint8_t u8HighVoltageMode;   //强电模式
    uint8_t u8LowVoltageMode;    //弱电模式
    uint8_t u8CurtainPercentage; //窗帘百分比位置
    uint8_t u8CurtainType;       //窗帘类型
    uint8_t u8BatteryPower;      //电池电量  

} CurtainData_QUERY_Typedef;

typedef struct
{
    uint8_t u8Percentage; //百分比
    uint8_t u8Jog;        //点动

} CurtainData_CONYROL_Typedef;

typedef struct
{
    uint8_t u8SetUpLimit;         //设置上限位
    uint8_t u8SetDownLimit;       //设置下限位
    uint8_t u8SetThirdLimit;      //设置第三限位
    uint8_t u8SetMotorDirection;  //设置电机方向
    uint8_t u8SetHighVoltageMode; //设置强电模式
    uint8_t u8SetLowVoltageMode;  //设置弱电模式
    uint8_t u8SetManualMode;      //设置手拉模式
    uint8_t u8SetLndicatorLED;    //设置指示灯
    uint8_t u8SetLearnState;      //设置学习状态
    uint8_t u8SetDeleteTrip;      //删除行程
    uint8_t u8SetCurtainType;     //设置窗帘类型

} CurtainData_SET_Typedef;

typedef struct
{
    CurtainData_QUERY_Typedef    Query;
    CurtainData_CONYROL_Typedef  Conyrol;
    CurtainData_SET_Typedef      Set; 

} CurtainData_Typedef;


/**********************************************************************************/
/*                     窗帘电机运行                                                   */
/******************************************************************* **************/
typedef enum //故障码
{
    eCURTAINRUN_NORMAL            = 0x00,     //通信正常
    eCURTAINRUN_ABNORMAL_DATA     = 0x01,     //数据异常
    eCURTAINRUN_EXCEPTION_MESSAGE = 0x02,     //通信异常
    eCURTAINRUN_EQUIPMENT_DROPS   = 0x03,     //通信掉线

} eCurtainRun_FaultCode;

typedef enum //窗帘电机运行状态
{
    eCURTAINRUN_IDLE               = 0x00,  //闲置状态

    eCURTAINRUN_POLL_QUERY         = 0x01,  //轮询查询
    eCURTAINRUN_POLL_QUERY_WAIT    = 0x02,  //轮询查询等待


    /*     设置命令        */
    eCURTAINRUN_SET_UPLIMIT        = 0x10,  //设置上限位
    eCURTAINRUN_SET_DOWNLIMIT      = 0x11,  //设置下限位
    eCURTAINRUN_SET_THIRDLIMIT     = 0x12,  //设置第三限位
    eCURTAINRUN_SET_DIRECTION      = 0x13,  //设置电机运转方向
    eCURTAINRUN_SET_HIGHMODE       = 0x14,  //设置强电模式
    eCURTAINRUN_SET_LOWMODE        = 0x15,  //设置弱电模式
    eCURTAINRUN_SET_MANUALMODE     = 0x16,  //设置手拉模式
    eCURTAINRUN_SET_LEARNSTATE     = 0x17,  //设置学习模式
    eCURTAINRUN_SET_DELETETRIP     = 0x18,  //设置删除行程
    eCURTAINRUN_SET_CURTAINTYPE    = 0x19,  //设置窗帘类型

    eCURTAINRUN_SET_WAIT           = 0x1F,  //设置命令等待

    /*      控制命令              */
    /*
    eCURTAINRUN_CURTAINON          = 0x20, //窗帘打开
    eCURTAINRUN_CURTAINON_WAIT     = 0x21, //窗帘打开等待

    eCURTAINRUN_CURTAINOFF         = 0x22, //窗帘关闭
    eCURTAINRUN_CURTAINOFF_WAIT    = 0x23, //窗帘关闭等待

    eCURTAINRUN_CURTAINPERCENTAGE      = 0x24, //窗帘百分比控制percentage
    eCURTAINRUN_CURTAINPERCENTAGE_WAIT = 0x25, //窗帘百分比控制等待     

    eCURTAINRUN_CURTAINSTOP        = 0x26, //窗帘停止
    eCURTAINRUN_CURTAINSTOP_WAIT   = 0x27, //窗帘停止等待 
    
    eCURTAINRUN_CURTAIN_QUERYA     = 0x28, //查询电机状态 
    eCURTAINRUN_CURTAIN_QUERYA_WAIT= 0x29, //查询等待 
    */
    eCURTAINRUN_CURTAIN_QUERYB     = 0x2A, //查询电机百分比位置 
    eCURTAINRUN_CURTAIN_QUERYB_WAIT= 0x2B, //查询等待 
    /*
    eCURTAINRUN_APP_CURTAINON          = 0x2C, //窗帘APP打开
    eCURTAINRUN_APP_CURTAINON_WAIT     = 0x2D, //窗帘APP打开等待

    eCURTAINRUN_APP_CURTAINOFF         = 0x2E, //窗帘APP关闭
    eCURTAINRUN_APP_CURTAINOFF_WAIT    = 0x2F, //窗帘APP关闭等待
    */

    /*      设置行程命令            */
    eCURTAINRUN_SETTRIP_START      = 0x30, //设置行程开始
    eCURTAINRUN_SETTRIP_START_WAIT = 0x31, //设置行程开始等待
    eCURTAINRUN_SETTRIP_DOWN       = 0x32, //设置行程下行
    eCURTAINRUN_SETTRIP_DOWN_WAIT  = 0x33, //设置行程下行等待    
    eCURTAINRUN_SETTRIP_UP         = 0x34, //设置行程上行
    eCURTAINRUN_SETTRIP_UP_WAIT    = 0x35, //设置行程上行等待
    

    /*       出厂自检测试电机          */
    eCURTAINRUN_HWTEST_FORWARD           = 0x40, //出厂测试电机正转
    eCURTAINRUN_HWTEST_FORWARD_WAIT      = 0x41, //出厂测试电机正转等待
    eCURTAINRUN_HWTEST_FORWARD_STOP      = 0x42, //出厂测试电机正转停止
    eCURTAINRUN_HWTEST_FORWARD_STOP_WAIT = 0x43, //出厂测试电机正转停止等待
    eCURTAINRUN_HWTEST_REVERSE           = 0x44, //出厂测试电机反转
    eCURTAINRUN_HWTEST_REVERSE_WAIT      = 0x45, //出厂测试电机反转等待
    eCURTAINRUN_HWTEST_REVERSE_STOP      = 0x46, //出厂测试电机停止
    eCURTAINRUN_HWTEST_REVERSE_STOP_WAIT = 0x47, //出厂测试电机停止等待    


    eCURTAINRUN_END                      = 0x99, //窗帘运行结束 

} eCurtainRun_TYPE;

typedef enum //窗帘电机控制状态
{
    eCURTAINCONTROL_IDLE               = 0x00,  //闲置状态
    /*      控制命令              */
    eCURTAINRUN_CURTAINON          = 0x20, //窗帘打开
    eCURTAINRUN_CURTAINON_WAIT     = 0x21, //窗帘打开等待

    eCURTAINRUN_CURTAINOFF         = 0x22, //窗帘关闭
    eCURTAINRUN_CURTAINOFF_WAIT    = 0x23, //窗帘关闭等待

    eCURTAINRUN_CURTAINPERCENTAGE      = 0x24, //窗帘百分比控制percentage
    eCURTAINRUN_CURTAINPERCENTAGE_WAIT = 0x25, //窗帘百分比控制等待     

    eCURTAINRUN_CURTAINSTOP        = 0x26, //窗帘停止
    eCURTAINRUN_CURTAINSTOP_WAIT   = 0x27, //窗帘停止等待 
    /*
    eCURTAINRUN_CURTAIN_QUERYA     = 0x28, //查询电机状态 
    eCURTAINRUN_CURTAIN_QUERYA_WAIT= 0x29, //查询等待 

    eCURTAINRUN_CURTAIN_QUERYB     = 0x2A, //查询电机百分比位置 
    eCURTAINRUN_CURTAIN_QUERYB_WAIT= 0x2B, //查询等待 
    */

} eCurtainControl_TYPE; //control

typedef enum //窗帘电机运行测试状态
{
    eCURTAINRUN_TEST_IDLE = 0x00,
    /*      控制命令              */
    eCURTAINRUN_TEST_CURTAINON          , //窗帘打开
    eCURTAINRUN_TEST_CURTAINON_WAIT     , //窗帘打开等待

    eCURTAINRUN_TEST_CURTAINOFF        , //窗帘关闭
    eCURTAINRUN_TEST_CURTAINOFF_WAIT    , //窗帘关闭等待  

    eCURTAINRUN_TEST_CURTAINSTOP_A        , //窗帘停止
    eCURTAINRUN_TEST_CURTAINSTOP_WAIT_A   , //窗帘停止等待 

    eCURTAINRUN_TEST_CURTAINSTOP_B        , //窗帘停止
    eCURTAINRUN_TEST_CURTAINSTOP_WAIT_B   , //窗帘停止等待 
 

} eCurtainRunTest_TYPE;


//窗帘运行状态
typedef enum
{
    eCURTAIN_RUN_UP   = 1,       //窗帘电机在上端点
    eCURTAIN_RUN_DOWN    ,       //窗帘电机在下端点
    eCURTAIN_RUN_MID     ,       //窗帘电机在中间
	eCURTAIN_RUN_ON      ,       //窗帘电机在打开
    eCURTAIN_RUN_OFF     ,       //窗帘电机在关闭

} eCurtainRunSteta_t;

// Enocean控制窗帘
typedef enum
{
    eENOCEAN_CONTROL_IDLE = 0x00, //Enocean控制待机状态

    eENOCEAN_CONTROL_ON  ,         //Enocean控制打开窗帘
    eENOCEAN_CONTROL_OFF ,         //Enocean控制闭合窗帘
    eENOCEAN_CONTROL_STOP,         //Enocean控制停止窗帘
    eENOCEAN_CONTROL_PERCENTAGE,   //Enocean控制停止窗帘percentage

} eEnoceanControl_t;



//按键手动设置
typedef enum
{
    eMANUAL_SET_NONE = 0,       //没有按键按下
    eMANUAL_SET_MOTORDIRECTION, //电机换向设置
    eMANUAL_SET_MANUALMODE,     //手拉设置
	eMANUAL_SET_SETTRIP,        //行程设置 

} eManualSet_t;


typedef struct
{
    eCurtainRun_TYPE       eRunState;           //运行状态  
    eCurtainControl_TYPE   eControlState;       //控制状态

    eCurtainRunSteta_t     eCurtainRunSteta;    //窗帘电机运行状态
    eManualSet_t           eManualSetRun;       //手动设置
    eCurtainRun_FaultCode  eFaultCode;          //故障
    eEnoceanControl_t      eEnoceanControl;     //Enocean控制窗帘

    eCurtainRunTest_TYPE   eRunStateTest;       //测试运行状态  

    uint8_t u8CurtainDropFlag;         //掉线标记
    uint8_t u8CurtainDropCount;        //掉线计数
    uint32_t u32CurtainDropTime;       //掉线计时

    uint8_t u8ConfigFlag;

    uint8_t u8RecordCurtainLocation;      //记录当前窗帘的位置
    uint8_t u8RecordLastCurtainLocation;  //记录上一个窗帘的位置
    uint32_t u32RecordCurtainLocation;      //记录当前窗帘的位置
    uint32_t u32RecordLastCurtainLocation;  //记录上一个窗帘的位置



    uint8_t u8CurtainPercentage;         //窗帘百分比控制      

    uint8_t u8CRCteat;                 //CRC测试
    uint8_t u8PowerONPollCount;        //上电轮询计数
  
    uint8_t u8CurtainButtonFlag;       //窗帘电机按键按键状态标记
    uint8_t u8CurtainButtonTime;       //窗帘电机按键计时
  
    uint8_t u8LEDFlashCount;           //LED闪烁计数
    uint8_t u8LEDFlashFlag;            //LED闪烁标记
    uint8_t u8LEDFlashNum;             //LED闪烁次数
  
    uint8_t u8ButtonFlag;              //按键按下标记

    uint8_t u8MotorStateFlag;          //电机状态标志

    uint8_t u8DeleteTripFlag;          //删除行程设置delete trip

    uint8_t u8SanCurtainRunStateFlag;  //扫描窗帘运行状态标志
    uint32_t u32SanCurtainRunStateTime;//扫描窗帘运行状态时间
  
    uint32_t u32LEDFlashTime;          //LED闪烁时间
    uint32_t u32CurtainRunWait;        //电机运行等待
    

} CurtainRun_Typedef;

extern CurtainRun_Typedef   CurtainRun;
extern CurtainData_Typedef  CurtainData;

extern USART_Function_Typedef CURTAIN_UART;
/**************************************************************************************/
/*                   窗帘串口初始化                                                   */
/*********************************************************************** **************/
/**
 * @brief
 * @param
 * @retval
 */
uint8_t CURTAIN_Init(USART_Function_Typedef *pUSART);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINSendOK(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINReset(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINDevError(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CURTAINReceiveOK(Serial_Typedef *pSerial);
/**
   * @brief
   * @param
   * @retval
   */
void CurtainRun_Tick1ms(CurtainRun_Typedef *pCurtainRun);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Curtain_CRC8(uint8_t *ptr, uint8_t len);
/**************************************************************************************/
/*                   窗帘接收函数                                                   */
/*********************************************************************** **************/
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Read_Unpack(uint8_t *p8ReceiveBuff);   //接收拆包
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Report(uint8_t *p8ReceiveBuff); //接收回复查询数据
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Query(uint8_t *p8ReceiveBuff); //接收回复查询数据
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Conyrol(uint8_t *p8ReceiveBuff); //接收回复控制数据
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Curtain_Reply_Set(uint8_t *p8ReceiveBuff);   //接收回复设置数据
/**************************************************************************************/
/*                   窗帘运行函数                                                   */
/*********************************************************************** **************/
/**
 * @brief    窗帘运行测试状态机
 * @param
 * @retval   
 */
void Curtain_SetState_Test(CurtainRun_Typedef *pCurtainRun);
/**
 * @brief    窗帘控制状态机
 * @param
 * @retval   
 */
uint8_t Curtain_ControlState(CurtainRun_Typedef *pCurtainRun);
/**
 * @brief
 * @param
 * @retval   窗帘运行状态机
 */
void Curtain_SetState(CurtainRun_Typedef *pCurtainRun);
/**
 * @brief
 * @param
 * @retval
 */
void Curtain_PowerON_Poll(CurtainRun_Typedef *pCurtainRun); 

/**
  * @brief   手动设置模式扫描
  * @param
  * @retval None     
  */
void ManualSetMode_Scan(CurtainRun_Typedef *pCurtainRun);

/**
 * @brief   掉线故障处理
 * @param
 * @retval
 */
uint8_t DropFault_Deal(void);
/**
 * @brief   窗帘电机串口发送
 * @param
 * @retval
 */
void CurtainUsart_Send(void);
/**
 * @brief   判断窗帘是否运行到端点
 * @param
 * @retval
 */
uint8_t CurtainRunLimit(void);
/**
 * @brief    计算窗帘百分比percentage
 * @param
 * @retval
 */
void CountCurtainPercentage(void);
/**
 * @brief    判断窗帘的运行状态judge
 * @param
 * @retval
 */
uint8_t JudgeCurtainRunState(void);
/**
 * @brief    判断Enceoan控制没有生效后补发数据
 * @param
 * @retval
 */
uint8_t JudgeEnoceanControl(void);



#endif


