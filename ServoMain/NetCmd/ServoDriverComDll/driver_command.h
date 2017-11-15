// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DRIVER_DLL_20130507_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DRIVER_DLL_20130507_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


#ifndef DRIVER_COMMAND_
#define  DRIVER_COMMAND_


// 资源
#define	RES_ENCODER						(3)
#define PROFILE_MAX                     (2)
#define CONTROL_MAX                     (1)

//wang bin 2013.04.07

#define DRV_GET_MODULEPARAM             (0x6917)
#define DRV_SET_MODULEPARAM				(0x6918)

//wang bin 2013.05.06

#define DRV_GET_FLASHPARAMINDEX         (0x6919)
#define DRV_SET_FLASHPARAMINDEX			(0x691A)

// wangbin 2013-06-24

#define DRV_GET_RAMINDEX16				(0x691B)
#define DRV_GET_RAMINDEX32				(0x691C)


#define DRV_SET_RAMINDEX16				(0x691D)
#define DRV_SET_RAMINDEX32				(0x691E)

//add wangbin 2013-06-26

#define	DRV_GET_BUF_DATA				(0x6741)


//add wangbin 2013-07-18

//#define DRV_SETBUF_VARIABLE				(0x691F)

//add wangbin2013-07-25

#define	DRV_SetDrvCmd					(0x6920)
#define	DRV_GetDrvInf					(0x6921)

//add wangbin2013-10-21

//#define	DRV_GetVersionDriver			(0x6925) //原来是6921
#define DRV_GET_FPGAADDR				(0x6922)
#define DRV_SET_FPGAADDR				(0x6923)

#define	DRV_INFBOARD_FPGA				(0x6924)

#define	DRV_NET_SYNC_TEST_TIME			(0x6925)
#define	DRV_NET_SYNC_TEST_PRFPOS		(0x6926)
#define	DRV_NET_SYNC_TEST_FDPOS			(0x6927)
#define	DRV_NET_SYNC_TEST_FOLLOWERROR	(0x6928)

//add wb 20141127
#define FLASH_TO_SDRAM				    (0x1190)
#define SDRAM_TO_FLASH_2				(0x1192)
#define CHECK_FLASH_PASSWORD            (0x11c1)
#define SET_MEMORY					    (0x1180)


//add liang.jj 2013-11-04
#define SET_INJECT_PARA                 (0x6930)
#define SET_FEEDBACK_PARA               (0x6931)
#define START_INJECT                    (0x6932)
#define SET_VALVE_DO_VALUE              (0x6933)
#define GET_VALVE_DO_VALUE              (0x6934)
#define GET_INJECT_ENC_POS              (0x6935)
#define GET_INJECT_PARA                 (0x6936)

#define  DRV_SET_VEL_PID                (0x6700)
#define  DRV_GET_VEL_PID                (0x6701)
// add 2014.01.02 by wu.jr
#define ALARM_ENABLE                    (0x1011)
#define LMT_ENABLE                      (0x1012)

#define ENC_SNS                         (0x101a)
#define SET_POS_ERR                     (0x101c)
#define GET_POS_ERR                     (0x101d)
#define SET_STOP_DEC                    (0x101e)
#define GET_STOP_DEC                    (0x101f)

#define CTRL_MODE						(0x1021)

#define SET_CONTROL_ENCODER             (0x1030)
#define GET_CONTROL_ENCODER             (0x1031)
#define SET_CONTROL_VALUE               (0x1032)
#define GET_CONTROL_VALUE               (0x1033)
#define SET_CONTROL_MODE				(0x1034)
#define GET_CONTROL_MODE				(0x1035)


#define SET_LOOP_MODE					(0x1036)
#define GET_LOOP_MODE					(0x1037)
#define SET_LOOP_SWITCH					(0x1038)
#define GET_LOOP_SWITCH					(0x1039)
#define SET_ENCODER_EQUIVALANT			(0x1041)

#define GET_DO                          (0x1100)
#define GET_DI                          (0x1110)


#define SET_COUNT_POS				    (0x1140)
#define GET_COUNT_INFO				    (0x1150)
#define	COUNT_INFO_ENCODER_POS			(1)
#define	COUNT_INFO_ENCODER_VEL			(2)

#define GET_ADC_VALUE                   (0x1161)
#define SET_ADC_FILTER_EX               (0x1162)
#define GET_ADC_FILTER_EX               (0x1163)


#define SET_CAPTURE_MODE			    (0x1170)
#define GET_CAPTURE_MODE			    (0x1171)
#define GET_CAPTURE_STATUS				(0x1172)
#define SET_CAPTURE_SENSE				(0x1174)


#define GET_MEMORY					    (0x1181)

#define GET_CLOCK                       (0x1202)
#define GET_CLOCK_HIGH_PRECISION        (0x1203)
#define CLEAR_TIME						(0x1210)
#define GET_TIME						(0x1211)

#define GET_STS                         (0x1300)
#define CLR_STS                         (0x1301)
#define AXIS_ENABLE						(0x1302)
#define STOP							(0x1303)
#define SET_PRF_POS                     (0x1304)
#define SYNCH_AXIS_POS                  (0x1305)
#define ZERO_POS						(0x1306)

#define SYNCH_PRF_POS_TO_ENC			(0x1310)

#define GET_DRIVER_ALARM				(0x1320)

#define SET_MOVE_DISTANCE				(0x1330)
#define GET_MOVE_DISTANCE				(0x1331)

#define SET_STOP_OFFSET					(0x1360)
#define GET_STOP_OFFSET					(0x1361)

#define GET_PROFILE_INFO                (0x1380)
#define	PROFILE_INFO_POS				(1)
#define	PROFILE_INFO_VEL				(2)

#define GET_AXIS_INFO                   (0x1381)
#define	AXIS_INFO_PRF_POS				(1)
#define	AXIS_INFO_PRF_VEL				(2)
#define	AXIS_INFO_PRF_ACC				(3)
#define	AXIS_INFO_ENC_POS				(4)
#define	AXIS_INFO_ENC_VEL				(5)
#define	AXIS_INFO_ENC_ACC				(6)
#define	AXIS_INFO_ERROR					(7)


#define ENABLE_TORQUE_STOP              (0x13a0)    // 使能力矩急停
#define ENABLE_PRESS_STOP               (0x13a1)    // 使能压力急停
#define SET_PRESS_STOP                  (0x13a2)    // 设置压力急停参数
#define GET_PRESS_STOP                  (0x13a3)    // 读取压力急停参数
#define SET_TORQUE_STOP                 (0x13a4)    // 设置力矩急停参数
#define GET_TORQUE_STOP                 (0x13a5)    // 读取力矩急停参数

#define SET_PRESS_RANGE                 (0x13a6)    // 设置力矩模式工作区间
#define GET_PRESS_RANGE                 (0x13a7)    // 读取力矩模式工作区间
#define SET_PRESS_CROSS                 (0x13a8)    // 设置力矩模式穿越位置
#define GET_PRESS_CROSS                 (0x13a9)    // 读取力矩模式穿越位置
#define SET_TORQUE_LIMIT                (0x13aa)    // 设置电流环饱和值
#define GET_TORQUE_LIMIT                (0x13ab)    // 读取电流环饱和值

#define SET_PRESS_PID				    (0x13ac)    // 设置压力传感器闭环PID参数
#define GET_PRESS_PID		            (0x13ad)    // 读取压力传感器闭环PID参数

#define SET_PRESS_FILTER                (0x13b0)    // 设置力矩模式滤波参数
#define GET_PRESS_FILTER                (0x13b1)    // 读取力矩模式滤波参数

#define GET_PRESS_STATUS	            (0x13b8)    // 读取压力急停、力矩环状态
#define GET_PRF_PRESS		            (0x13b9)	// 读取压力规划值
#define GET_ATL_PRESS		            (0x13ba)	// 读取压力规划值
#define GET_PRF_SPEED		            (0x13bb)	// 读取速度环规划值
#define GET_ATL_SPEED		            (0x13bc)	// 读取速度环反馈值
#define GET_PRF_TORQUE					(0x13bd)    // 读取压力规划
#define GET_ATL_TORQUE					(0x13be)    // 读取压力反馈

#define SET_PRESS_PRM                   (0x13c0)    // 设置压力规划参数
#define GET_PRESS_PRM                   (0x13c1)    // 读取压力规划参数


#define SET_PRESS                       (0x13c2)    // 设置压力目标值
#define GET_PRESS                       (0x13c3)    // 读取压力目标值

#define SET_PRESS_ARRAY                 (0x13c8)    // 设置一组压力目标值
#define GET_PRESS_ARRAY                 (0x13c9)    // 读取一组压力目标值
/**/
#define PRESS_TABLE_DATA				(0x13d8)
#define PRESS_TABLE_CLEAR				(0x13d9)
#define PRESS_TABLE_START				(0x13da)
#define PRESS_TABLE_SELECT				(0x13db)
#define SET_PRESS_TABLE_LOOP			(0x13dc)
#define GET_PRESS_TABLE_LOOP			(0x13dd)
#define GET_PRESS_TABLE_STATUS			(0x13de)
/**/

#define GET_CONTROL_INFO				(0x1410)
#define GET_DEBUG_INFO				    (0x1411)

#define SET_PID							(0x1440)
#define GET_PID							(0x1441)

#define UPDATE							(0x2000)
#define SET_POS			                (0x2002)
#define GET_POS							(0x2003)
#define SET_VEL							(0x2004)
#define GET_VEL							(0x2005)

#define PRF_TRAP                        (0x2100)
#define SET_TRAP_PRM		            (0x2101)
#define GET_TRAP_PRM	                (0x2102)

#define SET_WATCH						(0x1500)
#define START_WATCH						(0x1501)
#define GET_WATCH_FIFO                  (0x1502)
#define GET_WATCH_ADDRESS               (0x1503)

#define GET_WATCH_STS					(0x1504)
#define GET_WATCH_DATA					(0x1505)

/*-----------------------------------------------------------*/
/*                    0x2200  - 0x22ff                       */
/*-----------------------------------------------------------*/
#define PRF_JOG                         0x2200
#define SET_JOG_PRM		                0x2201
#define GET_JOG_PRM			            0x2202

/*-----------------------------------------------------------*/
/*                    0x2300 -- 0x23ff                       */
/*-----------------------------------------------------------*/
#define PRF_PT                          (0x2300)
#define SET_PT_LOOP                     (0x2301)
#define GET_PT_LOOP                     (0x2302)
#define PT_SPACE                        (0x2303)
#define PT_DATA                         (0x2304)
#define PT_CLEAR                        (0x2305)
#define PT_START                        (0x2306)
#define SET_PT_MEMORY                   (0x2307)
#define GET_PT_MEMORY                   (0x2308)
#define PT_DATA_WN                      (0x2309)
#define PT_GET_SEG_NUM                  (0x230a)

#define PRF_PVT                         0x2340
#define SET_PVT_LOOP                    0x2341
#define GET_PVT_LOOP                    0x2342
#define PVT_STATUS						0x2343
#define PVT_TABLE_DATA                  0x2344
#define PVT_TABLE_CLEAR                 0x2345
#define PVT_START                       0x2346
#define PVT_TABLE_SELECT                0x2347

/*-----------------------------------------------------------*/
/* 电子凸轮，0x3100 -- 0x31ff                                */
/*-----------------------------------------------------------*/
#define PRF_FOLLOW                      0x3100
#define SET_FOLLOW_MASTER               0x3101
#define GET_FOLLOW_MASTER               0x3102
#define SET_FOLLOW_LOOP                 0x3103
#define GET_FOLLOW_LOOP                 0x3104
#define SET_FOLLOW_EVENT                0x3105
#define GET_FOLLOW_EVENT                0x3106
#define FOLLOW_SPACE                    0x3107
#define FOLLOW_DATA                     0x3108
#define FOLLOW_CLEAR                    0x3109
#define FOLLOW_START                    0x310a
#define FOLLOW_SWITCH                   0x310b
#define SET_FOLLOW_MEMORY               0x310c
#define GET_FOLLOW_MEMORY               0x310d
#define GET_FOLLOW_STATUS               0x310e
#define SET_FOLLOW_PHASING              0x310f
#define GET_FOLLOW_PHASING              0x3110
#define SET_FOLLOW_REGIST				0x3111
#define GET_FOLLOW_REGIST				0x3112
#define GET_FOLLOW_REGIST_COUNT			0x3113
#define SET_FOLLOW_VIRTUAL_SEG          0x3114
#define GET_FOLLOW_VIRTUAL_SEG          0x3115
#define GET_FOLLOW_VIRTUAL_ERR          0x3116
#define CLEAR_FOLLOW_VIRTUAL_ERR        0x3117
/*-----------------------------------------------------------*/
/* 电子凸轮升级，0x3200 -- 0x32ff                            */
/*-----------------------------------------------------------*/
#define PRF_FOLLOW_EX                      0x3200
#define SET_FOLLOW_MASTER_EX               0x3201
#define GET_FOLLOW_MASTER_EX               0x3202
#define SET_FOLLOW_LOOP_EX                 0x3203
#define GET_FOLLOW_LOOP_EX                 0x3204
#define SET_FOLLOW_EVENT_EX                0x3205
#define GET_FOLLOW_EVENT_EX                0x3206
#define FOLLOW_SPACE_EX                    0x3207
#define FOLLOW_DATA_PERCENT_EX             0x3208
#define FOLLOW_CLEAR_EX                    0x3209
#define FOLLOW_START_EX                    0x320a
#define FOLLOW_SWITCH_EX                   0x320b
#define SET_FOLLOW_MEMORY_EX               0x320c
#define GET_FOLLOW_MEMORY_EX               0x320d
#define GET_FOLLOW_STATUS_EX               0x320e
#define SET_FOLLOW_PHASING_EX              0x320f
#define GET_FOLLOW_PHASING_EX              0x3210
#define SET_FOLLOW_REGIST_EX			   0x3211
#define GET_FOLLOW_REGIST_EX			   0x3212
#define GET_FOLLOW_REGIST_COUNT_EX		   0x3213
#define SET_FOLLOW_VIRTUAL_SEG_EX          0x3214
#define GET_FOLLOW_VIRTUAL_SEG_EX          0x3215
#define GET_FOLLOW_VIRTUAL_ERR_EX          0x3216
#define CLEAR_FOLLOW_VIRTUAL_ERR_EX        0x3217

#define FOLLOW_DATA_PERCENT2_EX            0x3220
#define GET_FOLLOW_DATA_PERCENT2_EX        0x3221

/*-----------------------------------------------------------*/
/* 新增加软探针捕获											 */
/*-----------------------------------------------------------*/
#define TRIGGER_SOFT_PROBE					(0x3230)
#define SET_CAPTURE_TYPE					(0x3231)


//IO used 
///////////////////////////////////////////////////////////////////
//0X6000 --0X6100
#define		IO_SET_MESSAGE					(0x6000)
#define		IO_GET_MESSAGE					(0x6001)
//////////////////////////////////////////////////////////////////


//APP used 
//--------------------------------------------------------
//0x8000-0x8100 used for punch app

#define		APP_PUNCH_GET_ZEROPOS			(0x7000)

//0x7100 kesai
#define		APP_KESAI_SET_LED_MESSAGE		(0x7100)
#define		APP_KESAI_GET_LED_MESSAGE		(0x7101)
#define		APP_KESAI_PT_PROCESS			(0x7102)
//
//--------------------------------------------------------
#endif // !DRIVER_COMMAND_