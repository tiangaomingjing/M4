#pragma once
#include "GTCmdCtrl.h"
#include "SPLine.h"
#include "MotionCtrlCom.h"
#include "driver_command.h"

#ifndef GT_DRIVER_DEF_
#define GT_DRIVER_DEF_

#define	MAX_PROFILE			3
#define	MAX_AXIS					3


#define	KTY84_TEMPER		(4709)			//KTY84的零温度DSP数值
#define	KTY84_RMP			(41.5)			//KTY84的温度上升斜率

#define INBOARDFPGA_WR_SAME  (0x8000)
#define INBOARDFPGA_RD_SAME  (0x0000)
#define INBOARDFPGA_MAX_WORD  (25)

typedef struct DRIVERMESSAGE
{
	float motor_temper;						//电机温度
	float motor_current_rms;				//电机电流有效值
	float motor_brake_time;					//制动时间
	float motor_brake_number;				//制动次数
}drivermessage;

typedef struct FRIMWAREVERSION
{
	short dsp_ver_year;
	short dsp_ver_md;
	short fpga_ver_year;
	short fpga_ver_md;
	short cpld_ver_year;
	short cpld_ver_md;
}firmwareversion;


// liang.jj 20131104 注塑机工艺相关
#define MC_ERULER                       25
#define MC_ENCODER                      23

typedef struct InjectPara
{
	double endPos;                                          // 目标位置
	short  maxP;                                            // 最大压力，即运动过程中的压力值
	short  maxQ;                                            // 最大流量，相当于梯形规划中的目标速度
	short  minQ;                                            // 最小流量，未到位前最小速度输出指令
	short  maxQAcc;                                         // 最大流量变化率
	long   valveDo;                                         // 运动过程中打开的DO，有效位为低8位，运动结束都输出取反并经过valveDoMask掩码后的valveDo值
	long   valveDoMask;                                     // 与ValveDo配合控制到位时需要关闭的DO，DoMask中非0的位代表该DO需要输出
	long   valveShutTime;                                   // 阀关闭的时间点
	long   deltaDecPos;										// 减速位置偏置量
	short  adjustType;										// 1 手动调整，2自动调整，0 锁定调整后的减速位置偏置
	double adjustCoeff;										// 调整系数。
	long   deltaPosInMinQ;                                  // 读取以最小流量运动的位移。
	long   posOffsetInMinQ;                                 // 设置最小流量运动的固定位移。
	double qKp;												// 兼容以前版本保留变量。
} TInjectPara;

typedef struct FeedbackPara
{
	short  fbType;                                          // 反馈通道，可选电子尺MC_ERULER或编码器MC_ENCODER
	short  fbIndex;                                         // 反馈通道的索引(0-5)
	short  fbFilterPara1;                                   // 反馈滤波系数1
	short  fbFilterPara2;                                   // 反馈滤波系数2
} TFeedbackPara;


#define MC_NONE                         -1

#define MC_LIMIT_POSITIVE               0
#define MC_LIMIT_NEGATIVE               1
#define MC_ALARM                        2
#define MC_HOME                         3
#define MC_GPI                          4
#define MC_ARRIVE                       5
#define MC_EGPI0                        6
#define MC_EGPI1                        7
#define MC_EGPI2                        8

#define MC_ENABLE                       10
#define MC_CLEAR                        11
#define MC_GPO                          12
#define MC_EGPO0                        13
#define MC_EGPO1                        14

#define MC_DAC                          20
#define MC_STEP                         21
#define MC_PULSE                        22
#define MC_ENCODER                      23
#define MC_ADC                          24

//Add 2014.01.02 by wu.jr
#define MC_AXIS                         30
#define MC_PROFILE                      31
#define MC_CONTROL                      32


#define MC_FULL_CLOSE_MODE              40
#define MC_SEMI_CLOSE_MODE              41
#define MC_HYBRID_CLOSE_MODE			42

// 捕获
#define CAPTURE_HOME                    1
#define CAPTURE_INDEX                   2
#define CAPTURE_PROBE                   3
#define CAPTURE_HSIO0                   6
#define CAPTURE_HSIO1                   7
#define CAPTURE_SOFT_PROBE0             8
#define CAPTURE_SOFT_PROBE1             9

#define PULSE_COUNT						10
#define ENCODER_COUNT					11

typedef struct JogPrm
{
	double acc;
	double dec;
	double smooth;
} TJogPrm;

typedef struct TrapPrm
{
	double acc;
	double dec;
	double velStart;
	short  smoothTime;
} TTrapPrm;

typedef struct Pid
{
	double kp;
	double ki;
	double kd;
	double kvff;
	double kaff;
	long   integralLimit;
	long   derivativeLimit;
	short  limit;
} TPid;

typedef struct TPressPid
{
	double kp;
	double ki;
	double kd;
	double kvff;
	double kaff;
	double piConvertPara;
	long integralLimit;
	long derivativeLimit;
	short limitMax;
	short limitMin;
} TPressPid;

#define WATCH_LIST_MAX                  8
#define WATCH_LENGTH_MAX                32
#define WATCH_FIFO_SIZE                 0x1E0       // 480 word

#define WATCH_ADDRESS_TYPE_PRF_POS      (0)                           // 规划器规划位置,32.16
#define WATCH_ADDRESS_TYPE_PRF_VEL      (1)                           // 规划器规划速度,16.16
#define WATCH_ADDRESS_TYPE_ENC_POS      (2)                           // 编码器位置,32.0
#define WATCH_ADDRESS_TYPE_ENC_VEL      (3)                           // 编码器速度,16.16
#define WATCH_ADDRESS_TYPE_AXIS_PRF_POS (4)                           // axis规划位置,32.16
#define WATCH_ADDRESS_TYPE_AXIS_PRF_VEL (5)                           // axis规划速度,16.16
#define WATCH_ADDRESS_TYPE_AXIS_ENC_POS (6)                           // axis编码器位置,32.16
#define WATCH_ADDRESS_TYPE_AXIS_ENC_VEL (7)                           // axis编码器速度,16.16
#define WATCH_ADDRESS_TYPE_DAC          (8)                           // DAC输出,16.0
#define WATCH_ADDRESS_TYPE_LMT_POS      (9)                           // 正限位,16.0
#define WATCH_ADDRESS_TYPE_LMT_NEG      (10)                          // 负限位,16.0
#define WATCH_ADDRESS_TYPE_ALARM        (11)                          // 报警信号,16.0
#define WATCH_ADDRESS_TYPE_HOME         (12)                          // HOME信号,16.0
#define WATCH_ADDRESS_TYPE_GPI          (13)                          // 通用数字量输入,16.0
#define WATCH_ADDRESS_TYPE_ENABLE       (14)                          // 使能信号,16.0
#define WATCH_ADDRESS_TYPE_CLEAR        (15)                          // 报警清除信号,16.0
#define WATCH_ADDRESS_TYPE_GPO          (16)                          // 通用数字量输出,16.0
#define WATCH_ADDRESS_TYPE_CLOCK        (17)                          // 时钟,32.0
#define WATCH_ADDRESS_TYPE_FLASH_BUFFER (18)
#define WATCH_ADDRESS_TYPE_CRD_VEL      (19)                          // 坐标系合成规划速度,16.16
#define WATCH_ADDRESS_TYPE_ARRIVE       (20)                          // 电机到位信号,16.0
#define WATCH_ADDRESS_TYPE_POS_LOOP_ERROR (21)                        // 位置环跟随误差,32.16
#define WATCH_ADDRESS_TYPE_POS_LOOP_OUTPUT (22)                       // 位置环输出,32.16
#define WATCH_ADDRESS_TYPE_POS_LOOP_INTERGRAL (23)                    // 位置环积分值,32.16
#define WATCH_ADDRESS_TYPE_VEL_LOOP_ERROR (24)                        // 速度环跟随误差,32.16
#define WATCH_ADDRESS_TYPE_VEL_LOOP_INTERGRAL (25)                    // 速度环积分值,32.16
#define WATCH_ADDRESS_TYPE_SPRING_OFFSET (26)                         // 弹簧力补偿值,32.16
#define WATCH_ADDRESS_TYPE_BEFORE_SPRING (27)                         // 弹簧力补偿前控制量,32.16
#define WATCH_ADDRESS_TYPE_AFTER_SPRING (28)                          // 弹簧力补偿后控制量,32.16
#define WATCH_ADDRESS_TYPE_OBSERVER_LOWPASS_OUTPUT (29)               // 观测器低通滤波输出值,32.16
#define WATCH_ADDRESS_TYPE_OBSERVER_OUTPUT_PRE (30)                   // 观测器上一次输出值,32.32
#define WATCH_ADDRESS_TYPE_OBSERVER_TORQUE_CMD_PRE (31)               // 观测器扭矩输入上一次值,32.16
#define WATCH_ADDRESS_TYPE_OBSERVER_VEL_FEEDBACK_INTERGRAL (32)       // 观测器速度反馈积分值,32.32
#define WATCH_ADDRESS_TYPE_OBSERVER_VEL_ERR_FEEDBACK_INTERGRAL (33)   // 观测器速度偏差积分值,32.32

#define WATCH_ADDRESS_TYPE_POS_LOOP_REF_POS			(34)			  // 32.16

#define WATCH_ADDRESS_TYPE_ADC						(40)			  // 模拟量通道0的值 16.0
#define WATCH_ADDRESS_TYPE_POS_LOOP_REF_VEL			(41)			  // control的规划速度,16.16
#define WATCH_ADDRESS_TYPE_PRF_PRESS		   		(42)			  // 规划压力 16.0
#define WATCH_ADDRESS_TYPE_ATL_PRESS			   	(43)			  // 反馈压力 16.0
#define WATCH_ADDRESS_TYPE_PRF_SPEED		   		(44)			  // 速度环指令 16.0 
#define WATCH_ADDRESS_TYPE_ATL_SPEED			   	(45)			  // 速度环速度反馈 16.0
#define WATCH_ADDRESS_TYPE_PRF_TORQUE          		(46)			  // 电流环指令 16.0 
#define WATCH_ADDRESS_TYPE_ATL_TORQUE              	(47)			  // 电流环反馈 16.0 

#define WATCH_ADDRESS_TYPE_PROFILE_LOOP             (50)			  // 规划周期数 16.0 驱控一体
/*驱动相关 watch 数据*/
#define WATCH_ADDRESS_TYPE_DRV_PRESS_REF				(1000)
#define WATCH_ADDRESS_TYPE_DRV_PRESS_FB					(1001)
#define WATCH_ADDRESS_TYPE_DRV_SPEED_REF				(1002)
#define WATCH_ADDRESS_TYPE_DRV_SPEED_FB					(1003)

typedef struct Watch
{
	short count;
	short interval;
	unsigned long address[WATCH_LIST_MAX];
	short length[WATCH_LIST_MAX];
	unsigned long threshold;
} TWatch;


#define LOOP_MODE_POSITION               (0)
#define LOOP_MODE_PRESS                  (1)
#define LOOP_MODE_NONE                   (2)

typedef struct
{
	short loopMode;
	short pressProfileMode;
} TLoopMode;

//----------------------------------------------------------
// PT模式相关函数
//----------------------------------------------------------
#define PT_MODE_STATIC                  (0)
#define PT_MODE_DYNAMIC                 (1)

#define PT_SEGMENT_NORMAL               (0)
#define PT_SEGMENT_EVEN                 (1)
#define PT_SEGMENT_STOP                 (2)


#define FOLLOW_MASTER_ENCODER           1
#define FOLLOW_MASTER_PROFILE           2
#define FOLLOW_MASTER_AXIS              3

#define FOLLOW_EVENT_START              1
#define FOLLOW_EVENT_PASS               2
#define FOLLOW_EVENT_HOME				3
#define	FOLLOW_EVENT_INDEX				4

#define FOLLOW_SEGMENT_NORMAL           0
#define FOLLOW_SEGMENT_EVEN             1
#define FOLLOW_SEGMENT_STOP             2
#define FOLLOW_SEGMENT_CONTINUE         3

typedef struct
{
	double k;
	short ignoreBit;
} TAdcFilter;


#define PRESS_PROFILE_NONE                  (0)
#define PRESS_PROFILE_TARGET                (1)
#define PRESS_PROFILE_ARRAY                 (2)

#define PRESS_DIR_NONE                      (0)
#define PRESS_DIR_CROSS_POSITIVE            (1)
#define PRESS_DIR_CROSS_NEGATIVE            (2)
#define PRESS_DIR_CROSS_BOTH                (3)
#define PRESS_DIR_GE                        (4)
#define PRESS_DIR_LE                        (5)


#define PRESS_STOP_GREATER_THAN_LIMIT             (0)
#define PRESS_STOP_LESS_THAN_LIMIT                (1) 

typedef struct
{
	short limit1;
	short limit2;
	short time;
	short triggerCondition;        // 压力急停触发条件，PRESS_GREATER_THAN_LIMIT,PRESS_LESS_THAN_LIMIT,
} TPressStop;

typedef struct
{
	double dec;
} TLoopSwitch;

typedef struct
{
	long t;
	double k;
} TPressFilter;

typedef struct
{
	double acc;				// 力矩加速度
	double dec;				// 力矩减速度
} TPressPrm;

typedef struct
{
	double pressTarget;
	long pressTime;
	double pressAcc;
} TPressArrayData;

typedef struct
{
	short count;
	TPressArrayData buffer[4];
	short exit;
} TPressArray;

typedef struct ControlInfo
{
	double refPos;
	double refPosFilter;
	double refPosFilter2;
	double cntPos;
	double cntPosFilter;

	double error;
	double refVel;
	double refAcc;

	short value;
	short valueFilter;

	short offset;
} TControlInfo;


typedef struct DebugInfo
{
	long cntPos_Debug;
	long prfPos_Debug;
	long error_Debug;
	short encoder_Debug;

} TDebugInfo;


#define MOVE_DISTANCE_NONE                  (0)
#define MOVE_DISTANCE_PRESS                 (1)

typedef struct
{
	short enable;
	double value;
	long distance;
} TMoveDistancePress;


typedef struct
{
	long distance;
	double vel;
	double acc;
} TStopOffset;


typedef struct ThreadStatus
{
	short link;
	unsigned long  address;
	short size;
	unsigned long  page;
	short delay;
	short priority;
	short ptr;
	short status;
	short error;
	short result[4];
	short resultType;
	short breakpoint;
	short period;
	short count;
	short function;
} TThreadStatus;

typedef struct VarInfo
{
	short id;
	short dataType;
	char  name[32];
} TVarInfo;

typedef struct CompileInfo
{
	char  *pFileName;
	short *pLineNo;
	char  *pMessage;
} TCompileInfo;

typedef struct ThreadSts
{
	short  run;
	short  error;
	double result;
	short  line;
} TThreadSts;

#endif

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

class SERVODRIVERCOMDLL_API CGTDriverCmd :
	public CGTCmdCtrl, CSPLine
{
public:
	CGTDriverCmd();
	~CGTDriverCmd();

	//luo.mj GTSD13相关函数
	short GTD_ST_Reset(void);
	short GTD_ST_GetSampleSts(short axis, short *pSmpSts);
	short GTD_ST_GetVirtualEnc(short axis, short *pVirtualEnc);
	short GTD_ST_ClrSampleCfg(short axis);
	short GTD_ST_GetPosVirtualEnc(short axis, short *pPosVirtualEnc);
	short GTD_ST_SetFlashStoreMsg(short axis, short pStoreMsg);
	short GTD_ST_GetFlashStoreMsg(short axis, short *pStoreMsg);

	//wang bin 20130407 无用
	short GTD_ST_GetModuleParam(short axis, short fc, short *pData);
	short GTD_ST_SetModuleParam(short axis, short fc, short size, short *pdata);

	//wang bin 20130506
	short GTD_ST_GetFlashParamIndex(short axis, unsigned long adr, short *pData);
	short GTD_ST_SetFlashParamIndex(short axis, unsigned long adr, short *pdata);
	short GTD_ST_GetFlashParamIndexBase(short axis, unsigned long adr, short *pData);
	short GTD_ST_SetFlashParamIndexBase(short axis, unsigned long adr, short *pdata);

	//wang bin 20130624
	short GTD_ST_SetRamIndex16(short axis, short adr, short *pData);
	short GTD_ST_SetRamIndex32(short axis, short adr, long *pData);
	short GTD_ST_GetRamIndex16(short axis, short adr, short *pData);
	short GTD_ST_GetRamIndex32(short axis, short adr, long *pData);

	// wangbin 20130626
	short GTD_ST_GetBufData(short axis, short identify, short *pNum, short *pStatus, short *pData);

	//wangbin 20130718
	//change by wangbin 20130725 下面的命令包含这条命令
	//short GTD_SetBufVarible(short axis,short pNum,short *pData0,short *pData1);

	//wangbin 20130725
	short GTD_ST_SetDrvCmd(short axis, short pNum, short id, short *pData0);
	short GTD_ST_GetDrvInf(short axis, short pNum, short id, short *pData0);


	//wangbin 20130905   封装给cpac层保存flash
	short GTD_ST_AppSaveFlashParam(short axis, short id, unsigned long adr, short *pdata);

	//wangbin 20130905   封装给cpac层读取变量
	short GTD_ST_AppReadVariable(short axis, short id, short adr, short *pData);

	//wangbin 20130918	封装给CPAC层读取程序版本
	//short GTD_AppReadVersion(short axis,short id,short adr,short *pData);

	//wangbin 20131017  封装给cpac读取flash
	short GTD_ST_AppReadFlashParam(short axis, short id, unsigned long adr, short *pdata);

	//wangbin 20131021 读取版本号 dsp fpga cpld

	//short GTD_ST_AppGetVersionDriver(short axis,unsigned long adryear,unsigned long adrmd,short *pdata);
	//wangbin 20141106
	short GTD_ST_GetFpgaAddr(short axis, short adr, short *pData);
	short GTD_ST_SetFpgaAddr(short axis, short adr, short *pData);

	short GTD_ST_InfBoardFpga(short axis, unsigned short num, short* pdata, unsigned short addr, unsigned short ctl);
		//num : word_num; num <= 25
		//addr: bAddr;
		//ctrl : 0x8000 write not increase 0x0 read not increase
		//bit14 1:offset + 1, 0 : offset + 0
	///////////////////////////////////////////////////////////////////////////////////////////
	//add wangbin 20160421
	short GTD_ST_SetStationType(short axis, short Data);
	short GTD_ST_GetStationType(short axis, short* Data);
	short GTD_ST_MotorAdcAdjust(short axis);
	short GTD_ST_MotorInitPosAdjust(short axis);
	short GTD_ST_ServoOff(short axis);
	short GTD_ST_ServoModeSwitch(short axis, short mode);
	short GTD_ST_MotorSpdloop(short axis, short spd, short spdbase);
	short GTD_ST_MotorClrAlarm(short axis);
	short GTD_ST_MotorSaveAdcOffset(short axis);
	short GTD_ST_MotorSavePosOffset(short axis);
	short GTD_ST_GetMotorMessage(short axis, drivermessage* drvmsg);
	short GTD_ST_GetFirmwareVersion(short axis, firmwareversion* fm_ver);
	short GTD_ST_WriteDriverParamFileToFlash(short axis, char*  pFileName);
	///////////////////////////////////////////////////////////////////////////////////////////


	//wangbin 20141127
	short GT_ST_CheckFlashPassword(void);
	short GT_ST_SdramToFlash2(long *pRetry = NULL);
	short GT_ST_FlashToSdram(long *pRetry = NULL);
	short GT_ST_SetMemory(unsigned long address, short count, short *pData);


	short GT_ST_SetInjectPara(short active, TInjectPara *pInjectPara);
	short GT_ST_GetInjectPara(TInjectPara *pInjectPara);
	short GT_ST_SetFbPara(TFeedbackPara *pFeedbackPara);
	short GT_ST_StartInject();
	short GT_ST_SetValveDoValue(long mask);
	short GT_ST_GetValveDoValue(long *mask);
	short GT_ST_GetInjectEncPos(double *fbPos);


	short GT_ST_Update(long mask);
	short GT_ST_SetPos(short profile, long pos);
	short GT_ST_GetPos(short profile, long *pPos);
	short GT_ST_SetVel(short profile, double vel);
	short GT_ST_GetVel(short profile, double *pVel);

	short GT_ST_PrfTrap(short profile);
	short GT_ST_SetTrapPrm(short profile, TTrapPrm *pPrm);
	short GT_ST_GetTrapPrm(short profile, TTrapPrm *pPrm);

	short GT_ST_SetPid(short control, short index, TPid *pPid);
	short GT_ST_GetPid(short control, short index, TPid *pPid);

	short GT_ST_CtrlMode(short axis, short mode);

	short GT_ST_AxisOn(short axis);
	short GT_ST_AxisOff(short axis);
	short GT_ST_Stop(long mask, long option);

	short GT_ST_GetPrfPos(short profile, double *pValue, short count = 1, unsigned long *pClock = NULL);
	short GT_ST_GetPrfVel(short profile, double *pValue, short count = 1, unsigned long *pClock = NULL);
	short GT_ST_GetEncPos(short encoder, double *pValue, short count = 1, unsigned long *pClock = NULL);
	short GT_ST_GetEncVel(short encoder, double *pValue, short count = 1, unsigned long *pClock = NULL);

	short GT_ST_ZeroPos(short axis, short count = 1);
	short GT_ST_GetSts(short axis, long *pSts, short count = 1, unsigned long *pClock = NULL);
	short GT_ST_ClrSts(short axis, short count = 1);
	short GT_ST_AlarmOff(short axis);
	short GT_ST_AlarmOn(short axis);
	short GT_ST_LmtsOn(short axis, short limitType = -1);
	short GT_ST_LmtsOff(short axis, short limitType = -1);

	short GT_ST_SynchPrfPosToEnc(short profile, short encoder);
	short GT_ST_SynchAxisPos(short axis);

	short GT_ST_SetControlEncoder(short axis, short encoder);
	short GT_ST_GetControlEncoder(short axis, short *pEncoder);
	short GT_ST_SetControlValue(short axis, short value);
	short GT_ST_GetControlValue(short axis, short *pValue);


	short GT_ST_SetLoopMode(short axis, TLoopMode *pMode);
	short GT_ST_GetLoopMode(short axis, TLoopMode *pMode);

	short GT_ST_GetWatchAddress(short type, short index, unsigned long *pAddress, short count);
	short GT_ST_GetWatchFifo(short *pFifo);
	short GT_ST_LoadWatchFifo(short fifo, short *pBuf);
	short GT_ST_StopWatch(void);
	short GT_ST_StartWatch(void);
	short GT_ST_SetWatch(TWatch *pWatch);

	//----------------------------------------------------------
	// 静态 Watch 相关函数
	//----------------------------------------------------------
	short GT_ST_AutoSetWatch(long *pWatchInfo, short interval);
	short GT_ST_StartWatchStatic(void);
	short GT_ST_StopWatchStatic(void);
	short GT_ST_GetWatchSts(short *pRun, unsigned long *pCount);
	short GT_ST_GetWatchData(unsigned long offset, short *pData, short count);
	short GT_ST_PrintWatchStaticData(char *pFileName);



	short GT_ST_DrvSetVelPid(short control, short index, TPid *pPid);
	short GT_ST_DrvGetVelPid(short control, short index, TPid *pPid);

	short GT_ST_PrfPt(short profile, short mode);
	short GT_ST_SetPtLoop(short profile, long loop);
	short GT_ST_GetPtLoop(short profile, long *pLoop);
	short GT_ST_PtSpace(short profile, short *pSpace, short fifo = 0);
	short GT_ST_PtData(short profile, double pos, long time, short type, short fifo = 0);
	short GT_ST_PtDataWN(short profile, double pos, long time, short type, long segNum, short fifo = 0);
	short GT_ST_PtGetSegNum(short profile, long *pSegNum);
	short GT_ST_PtClear(short profile, short fifo = 0);
	short GT_ST_PtStart(long mask, long option);
	short GT_ST_SetPtMemory(short profile, short memory);
	short GT_ST_GetPtMemory(short profile, short *pMemory);

	short GT_ST_PrfFollowEx(short profile, short dir = 0);
	short GT_ST_SetFollowMasterEx(short profile, short masterIndex, short masterType = FOLLOW_MASTER_PROFILE, short masterItem = 0);
	short GT_ST_GetFollowMasterEx(short profile, short *pMasterIndex, short *pMasterType = NULL, short *pMasterItem = NULL);
	short GT_ST_SetFollowLoopEx(short profile, long loop);
	short GT_ST_GetFollowLoopEx(short profile, long *pLoop);
	short GT_ST_SetFollowEventEx(short profile, short event, short masterDir, long pos = 0);
	short GT_ST_GetFollowEventEx(short profile, short *pEvent, short *pMasterDir, long *pPos = NULL);
	short GT_ST_FollowSpaceEx(short profile, short *pSpace, short fifo = 0);
	short GT_ST_FollowDataPercentEx(short profile, double masterSegment, double slaveSegment, short type = FOLLOW_SEGMENT_NORMAL, short percent = 0, short fifo = 0);
	short GT_ST_FollowClearEx(short profile, short fifo = 0);
	short GT_ST_FollowStartEx(long mask, long option = 0);
	short GT_ST_FollowSwitchEx(long mask);
	short GT_ST_SetFollowMemoryEx(short profile, short memory);
	short GT_ST_GetFollowMemoryEx(short profile, short *pMemory);
	short GT_ST_GetFollowStatusEx(short profile, short *pFifoNum, short *pSwitchStatus);
	short GT_ST_SetFollowPhasingEx(short profile, short profilePhasing);
	short GT_ST_GetFollowPhasingEx(short profile, short *pProfilePhasing);

	short GT_ST_FollowDataPercent2Ex(short profile, double masterSegment, double slaveSegment, double velBeginRatio, double velEndRatio, short percent = 100, short *pPercent1 = NULL, short fifo = 0);
	short GT_ST_GetFollowDataPercent2Ex(double masterPos, double v1, double v2, double p, double p1, double *pSlavePos);

	short GT_ST_SetDo(short doType, long pValue);

	short GT_ST_GetDi(short diType, long *pValue);
	short GT_ST_SetEncPos(short encoder, long pos);
	short GT_ST_SetPrfPos(short profile, long pos);
	short GT_ST_GetAdcValue(short adc, short *pValue, short count = 1, unsigned long *pClock = NULL);



	short GT_ST_SetAdcFilterEx(short adc, TAdcFilter *pFilter);
	short GT_ST_GetAdcFilterEx(short adc, TAdcFilter *pFilter);


	short GT_ST_PressStopOn(short axis, TLoopMode *pLoopMode);
	short GT_ST_PressStopOff(short axis);
	short GT_ST_SetPressStop(short axis, TPressStop *pPressStop);
	short GT_ST_GetPressStop(short axis, TPressStop *pPressStop);
	short GT_ST_SetLoopSwitch(short axis, TLoopSwitch *pSwitch);
	short GT_ST_GetLoopSwitch(short axis, TLoopSwitch *pSwitch);
	short GT_ST_SetPressRange(short axis, short centerSynch, long range);
	short GT_ST_GetPressRange(short axis, long *pCenterPos, long *pRange);
	short GT_ST_SetPressCross(short axis, short dir, long pos);
	short GT_ST_GetPressCross(short axis, short *pDir, long *pPos);

	short GT_ST_SetPressPid(short axis, TPressPid *pPid);
	short GT_ST_GetPressPid(short axis, TPressPid *pPid);

	short GT_ST_SetPressFilter(short axis, TPressFilter *pPressFilter);
	short GT_ST_GetPressFilter(short axis, TPressFilter *pPressFilter);

	short GT_ST_GetPressStatus(short axis, long *pStatus);
	short GT_ST_GetPrfPress(short axis, double *pValue);
	short GT_ST_GetAtlPress(short axis, double *pValue);
	short GT_ST_GetPrfSpeed(short axis, double *pValue);
	short GT_ST_GetAtlSpeed(short axis, double *pValue);
	short GT_ST_GetPrfTorque(short axis, double *pValue);
	short GT_ST_GetAtlTorque(short axis, double *pValue);


	short GT_ST_SetPressPrm(short axis, TPressPrm *pPressPrm);
	short GT_ST_GetPressPrm(short axis, TPressPrm *pPressPrm);
	short GT_ST_SetPress(short axis, double value);
	short GT_ST_GetPress(short axis, double *pValue);

	short GT_ST_SetPressArray(short axis, TPressArray *pPressArray);
	short GT_ST_GetPressArray(short axis, TPressArray *pPressArray);

	/**/

	void fsin(double A, double w, double x, double &y, double &v);
	void Poly3Coef(double dt, double y1, double y2, double v1, double v2, float k[]);

	short GT_ST_PressTableClear(short table);
	short GT_ST_PressTableData(short table, float t, float k[]);
	short GT_ST_PressTableSin(short table, double A, double T);
	short GT_ST_PressTableSelect(short axis, short table);
	short GT_ST_SetPressTableLoop(short axis, short loop);
	short GT_ST_GetPressTableLoop(short axis, long *pLoopCount, long *pLoop);
	short GT_ST_GetPressTableStatus(short axis, short *pTableId, float *pTime);
	short GT_ST_PressTableStart(short axis, short table);

	/**/

	short GT_ST_SetStopDec(short profile, double decSmoothStop, double decAbruptStop);
	short GT_ST_GetStopDec(short profile, double *pDecSmoothStop, double *pDecAbruptStop);
	short GT_ST_SetPosErr(short control, long error);
	short GT_ST_GetPosErr(short control, long *pError);

	short GT_ST_GetAxisError(short axis, double *pValue, short count = 1, unsigned long *pClock = NULL);


	short GT_ST_GetControlInfo(short control, TControlInfo *pControlInfo);
	short GT_ST_GetDebugInfo(short control, TDebugInfo *pDebugInfo);
	short GT_ST_ClearTime(void);
	short GT_ST_GetTime(long item, unsigned long *pTime, unsigned long *pTimeMax);
	short GT_ST_GetDriverAlarm(short axis, short *pAlarmFlag, short *pAlarmCode);



	short GT_ST_SetMoveDistancePress(short axis, TMoveDistancePress *pPress);
	short GT_ST_GetMoveDistancePress(short axis, TMoveDistancePress *pPress);

	short GT_ST_TorqueStopOn(short axis);
	short GT_ST_TorqueStopOff(short axis);
	short GT_ST_SetTorqueStop(short axis, TPressStop *pPressStop);
	short GT_ST_GetTorqueStop(short axis, TPressStop *pPressStop);

	short GT_ST_SetStopOffset(short axis, TStopOffset *pStopOffset);
	short GT_ST_GetStopOffset(short axis, TStopOffset *pStopOffset);

	short GT_ST_SetTorqueLimit(short axis, short torqueLimit);
	short GT_ST_GetTorqueLimit(short axis, short *pTorqueLimit);

	short GT_ST_EncSns(unsigned short sense);

	short GT_ST_PrfJog(short profile);
	short GT_ST_SetJogPrm(short profile, TJogPrm *pPrm);
	short GT_ST_GetJogPrm(short profile, TJogPrm *pPrm);
	short GT_ST_SetControlMode(short control, short controlMode);
	short GT_ST_GetControlMode(short control, short *pControlMode);
	short GT_ST_SetEncoderEquivalant(short control, double equivalantRatio);
	short GT_ST_SetCaptureMode(short encoder, short mode);
	short GT_ST_GetCaptureMode(short encoder, short *pMode, short count);
	short GT_ST_GetCaptureStatus(short encoder, short *pStatus, long *pValue, short count, unsigned long *pClock);
	short GT_ST_SetCaptureSense(short encoder, short mode, short sense);
	short GT_ST_TriggerSoftProbe(short mode, short state);
	short GT_ST_SetCaptureType(short axis, short type);
	short GT_ST_GetClockHighPrecision(unsigned long *pClock);
	short GT_ST_GetMemory(unsigned long address, short count, short *pData);

	short GT_ST_Compile(char *pFileName, TCompileInfo *pWrongInfo);
	short GT_ST_Download(char *pFileName);

	short GT_ST_GetFunId(char *pFunName, short *pFunId);
	short GT_ST_Bind(short thread, short funId, short page);

	short GT_ST_RunThread(short thread);
	short GT_ST_StopThread(short thread);
	short GT_ST_PauseThread(short thread);

	short GT_ST_GetThreadSts(short thread, TThreadSts *pThreadSts);

	short GT_ST_GetVarId(char *pFunName, char *pVarName, TVarInfo *pVarInfo);
	short GT_ST_SetVarValue(short page, TVarInfo *pVarInfo, double *pValue, short count = 1);
	short GT_ST_GetVarValue(short page, TVarInfo *pVarInfo, double *pValue, short count = 1);

	short GT_ST_PrfPvt(short profile);
	short GT_ST_SetPvtLoop(short profile, long loop);
	short GT_ST_GetPvtLoop(short profile, long *pLoopCount, long *pLoop);
	short GT_ST_PvtStatus(short profile, short *pTableId, double *pTime, short count);
	short GT_ST_PvtStart(long mask);
	short GT_ST_PvtTableSelect(short profile, short tableId);
	short GT_ST_PvtTable(short tableId, long n, double *pTime, double *pPos, double *pVel);
	short GT_ST_PvtTableEx(short tableId, long n, double *pTime, double *pPos, double *pVelBegin, double *pVelEnd);
	short GT_ST_PvtTableComplete(short tableId, long n, double *pTime, double *pPos, double *pA, double *pB, double *pC, double velBegin, double velEnd);
	short GT_ST_PvtTablePercent(short tableId, long n, double *pTime, double *pPos, double *pPercent, double velBegin);
	short GT_ST_PvtPercentCalculate(long n, double *pTime, double *pPos, double *pPercent, double velBegin, double *pVel);
	short GT_ST_PvtTableContinuous(short tableId, long n, double *pPos, double *pVel, double *pPercent, double *pVelMax, double *pAcc, double *pDec, double timeBegin);
	short GT_ST_PvtContinuousCalculate(long n, double *pPos, double *pVel, double *pPercent, double *pVelMax, double *pAcc, double *pDec, double *pTime);

	//////////////////////////////////////////////////////////////////////////
	//FOLLOW MODE 
	//////////////////////////////////////////////////////////////////////////
	short GT_ST_PrfFollow(short profile, short dir);
	short GT_ST_SetFollowMaster(short profile, short masterIndex, short masterType, short masterItem);
	short GT_ST_GetFollowMaster(short profile, short *pMasterIndex, short *pMasterType, short *pMasterItem);
	short GT_ST_SetFollowLoop(short profile, long loop);
	short GT_ST_GetFollowLoop(short profile, long *pLoop);
	short GT_ST_SetFollowEvent(short profile, short event, short masterDir, long pos);
	short GT_ST_GetFollowEvent(short profile, short *pEvent, short *pMasterDir, long *pPos);
	short GT_ST_FollowSpace(short profile, short *pSpace, short fifo);
	short GT_ST_FollowData(short profile, long masterSegment, double slaveSegment, short type, short fifo);
	short GT_ST_FollowClear(short profile, short fifo);
	short GT_ST_FollowStart(long mask, long option);
	short GT_ST_FollowSwitch(long mask);
	short GT_ST_SetFollowMemory(short profile, short memory);
	short GT_ST_GetFollowMemory(short profile, short *pMemory);
	short GT_ST_GetFollowStatus(short profile, short *pFifoNum, short *pSwitchStatus);
	short GT_ST_SetFollowPhasing(short profile, short profilePhasing);
	short GT_ST_GetFollowPhasing(short profile, short *pProfilePhasing);
	short GT_ST_SetFollowVirtualSeg(short profile, short segment, short axis, short fifo);
	short GT_ST_GetFollowVirtualSeg(short profile, short *pSegment, short *pAxis, short fifo);
	short GT_ST_GetFollowVirtualErr(short profile, double *pVirtualErr);
	short GT_ST_ClearFollowVirtualErr(short profile);
	short GT_ST_GetFollowRegist(short profile, short *pSegment, short fifo);
	short GT_ST_GetFollowRegistCount(short profile, unsigned long *pCount);
	short GT_ST_SetFollowRegist(short profile, short segment, short fifo);




	//io
	////////////////////////////////////////////////////////////////////
	short GTD_ST_SetIoBit(short axis, unsigned short bitmask, short data);
	short GTD_ST_GetIoBit(short axis, short* pdata);
	///////////////////////////////////////////////////////////////////

	//app 
	/////////////////////////////////////////////////////////////////////
	short GTD_ST_GetPunchZeroPos(short axis, long* pdata);
	/////////////////////////////////////////////////////////////////////

	//kesai net sync test
	//////////////////////////////////////////////////////////////////////////
	short GTD_ST_GetNetSyncTime(short axis, short part, short *pNum, short* pdata);
	short GTD_ST_GetNetSyncPrfPos(short axis, short part, short *pNum, short* pdata);
	short GTD_ST_GetNetSyncFdPos(short axis, short part, short *pNum, short* pdata);
	short GTD_ST_GetNetFollowError(short axis, short part, short *pNum, short* pdata);
	//////////////////////////////////////////////////////////////////////////

	short GTD_ST_SetLedMessage(short axis, short mode);
	short GTD_ST_GetLedMessage(short axis, short* mode);
};

