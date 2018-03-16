#pragma once

#ifndef		__GTSD_COM_DLL_DEFINE__
#define		__GTSD_COM_DLL_DEFINE__

#include "Basetype_def.h"
typedef enum com_error
{
	COM_OK,
	COM_ARM_OUT_TIME = 23,
	COM_NET_ERROR = 25,
	COM_NOT_FINISH = 27
}COM_ERROR;

typedef enum _servoTaskMode
{
	SERTASKMODE_IDLE = 0,
	SERTASKMODE_ADC = 1,
	SERTASKMODE_INIT_POSADJ = 2,
	SERTASKMODE_MOTOR_PAM_IDENTIFICATION = 3,
	SERTASKMODE_VOL_OPEN = 4,
	SERTASKMODE_CURRENT_CLOSE = 5,
	SERTASKMODE_VEL_CLOSE = 6,
	SERTASKMODE_VEL_PROFILE = 7,
	SERTASKMODE_VEL_SYNC = 8,
	SERTASKMODE_POS_FIXED = 9,
	SERTASKMODE_POS_SYNC = 10,
	SERTASKMODE_DB_BRAKE = 11,
	SERTASKMODE_CURRENT_SYNC = 12,

	SERTASKMODE_COUNT
}ServoTaskMode;

//////////////////////////////////////////////////////////////////////////
const int32						MAX_WAVE_PLOT_NUM = 16;

/************************************************************************/
/* 定义通信类型                                                        */
/************************************************************************/
typedef enum com_type
{
	GTSD_COM_TYPE_NET,			//裸机网口
	GTSD_COM_TYPE_RNNET,		//等环网
	GTSD_COM_TYPE_TCPIP,		//TCP/IP协议网口
	GTSD_COM_TYPE_USB2UART,		//usb转串口
	GTSD_COM_TYPE_VIRTUAL,		//虚拟设备
	GTSD_COM_TYPE_RINGNET,		//等环网
	GTSD_COM_TYPE_MAX			//最大值
}COM_TYPE;

typedef enum
{
	SERVO_EN_COMM = 0,																// MpiServoEnable()	----------> ID|0
	SERVO_TASK_COMM = 1,															// MpiServoTaskMode() -----------> ID|1
	MIX_MODE_COMM = 2,																// MpiMixMode()
	WR_16BIT_COMM = 3,																// MpiWr16BitByAdr
	WR_32BIT_COMM = 4,																// MpiWr32BitByAdr
	WR_64BIT_COMM = 5,																// MpiWr64BitByAdr
	ID_REF_WR_COMM = 6,																// id reference read/write
	IQ_REF_WR_COMM = 7,																// iq reference read/write
	SPD_REF_WR_COMM = 8,															// speed reference read/write
	PRE_REF_WR_COMM = 9,
	UD_REF_WR_COMM = 10,															// d axis voltage reference read/write
	UQ_REF_WR_COMM = 11,															// q axis voltage reference read/write
	UA_REF_WR_COMM = 12,															// a phase voltage reference read/write	
	UB_REF_WR_COMM = 13,															// b phase voltage reference read/write
	UC_REF_WR_COMM = 14,															// c phase voltage reference read/write
	POS_ADJ_IREF_COMM = 15,															// motor position adjust reference read/write
	POS_REF_WR_COMM = 16,															// position reference read/write 
	FND_CURR_WR_COMM = 17,															// d axis fn value set in current loop
	FNQ_CURR_WR_COMM = 18,															// q axis fn value set in current loop
	TID_CURR_WR_COMM = 19,															// d axis integrate time constant set	
	TIQ_CURR_WR_COMM = 20,															// q axis integrate time constant set	
	FN_VEL_WR_COMM = 21,															// velocity loop fn value set
	TI_VEL_WR_COMM = 22,															// velocity loop integrate time constant set
	ABS_LIM_VEL_WR_COMM = 23,														// absolute saturate limit rate of of velocity loop output 			
	POS_LIM_VEL_WR_COMM = 24,														// positive saturate limit rate of of velocity loop output 
	NEG_LIM_VEL_WR_COMM = 25,														// negative saturate limit rate of of velocity loop output
	FN_POS_WR_COMM = 26,															// fn value of position loop 
	ABS_LIM_POS_WR_COMM = 27,														// absolute limit rate value of position loop output
	POS_LIM_POS_WR_COMM = 28,														// positive limit rate value of position loop output
	NEG_LIM_POS_WR_COMM = 29,														// negative limit rate velue of position loop output
	KGA_FF_POS_WR_COMM = 30,														// kga value of accelerate feedforward 	
	KGV_FF_POS_WR_COMM = 31,														// kgv value of velocity feedforward
	TFA_FF_POS_WR_COMM = 32,														// tfa value of accelerate feedforward		
	TFV_FF_POS_WR_COMM = 33,														// tfv value of accelerate feedforward	
	WAVE_BUF_SET_WR_COMM = 34,														//设置曲线		
	WR_FRAM_16BIT_COMM = 35,														// MpiFramWr16BitByAdr
	WR_FRAM_32BIT_COMM = 36,														// MpiFramWr32BitByAdr
	WR_FRAM_64BIT_COMM = 37,														// MpiFramWr64BitByAdr
	WR_SPI_FLASH_COMM = 38,	                                                        // burn spi flash 
	SPI_ERASE_FLASH_COMM = 39,                                                      // erase all flash
	INTERRUPT_SWITCH_COMM = 40,														// interrupt enable and disable 
	GET_DRV_VAR_INFO_COMM = 41,                                                     // get var information according to the id 
	RESET_SYSTEM_COMM = 42,                                                         // reset system to reset isr routine
	CHECK_RESET_FINISH_COMM = 43,													// check reset finish
	RD_PROCESSOR_VER_COMM = 44,														// read processor version
	ALARM_CLEAR_COMM = 45,															// clear alarm
	RD_ALARM_LOG_CODE_COM = 46,                                                     // read alarm log code ,just log ten recently
	RD_ALARM_LOG_TIMES_COM = 47,                                                    // read different kind of alarm times 
	TUNNING_MESSAGE_MAX=4095
}tTuningMessageId;


typedef struct servo_state
{
	int16 act_on_tmp;
	int16 act_on;
	int16 sec_on;
	int16 sof_st_on;
	int16 serv_ready;
}SERVO_STATE;

typedef struct servo_mode
{
	int16 usr_mode;
	int16 cmd_id;
	int16 curr_id;
	int16 curr_state;
}SERVO_MODE;

typedef struct id_state
{
	double chd_idr_tmp;
	double tsk_id_ref;
	double ctl_id_ref;
	double ctl_id;
}ID_STATE;

typedef struct iq_state
{
	double chd_iqr_tmp;
	double tsk_iq_ref;
	double ctl_iq_ref;
	double ctl_iq;
}IQ_STATE;

typedef struct spd_state
{
	double chd_spd_tmp;
	double tsk_spd_ref;
	double ctl_spd_ref;
	double ctl_spd_fd;
	double rsv_mot_spd;
}SPD_STATE;

typedef struct ud_state
{
	double chd_ud_tmp;
	double tsk_ud_ref;
	double cur_ud;
}UD_STATE;
typedef struct uq_state
{
	double chd_uq_tmp;
	double tsk_uq_ref;
	double cur_uq;
}UQ_STATE;

typedef struct ua_state
{
	double chd_ua_tmp;
	double tsk_ua_ref;
	double cur_ua;
}UA_STATE;
typedef struct ub_state
{
	double chd_ub_tmp;
	double tsk_ub_ref;
	double cur_ub;
}UB_STATE;
typedef struct uc_state
{
	double chd_uc_tmp;
	double tsk_uc_ref;
	double cur_uc;
}UC_STATE;
typedef struct pos_adj_state
{
	double chd_pos_adj_tmp;
	double tsk_pos_adj_ref;
	double ctl_id_ref;
	double ctl_id;
	double ctl_iq_ref;
	double ctl_iq;
	int16 rsv_pos_elec;
	int32 rsv_pos;
	int32 rsv_pos_in;
	int16 mfj_pos_adj_flag;

}POS_ADJ_STATE;


typedef struct		wave_buf_cmd
{
	Uint16		TIM : 8;												// sample times
	Uint16		NUM : 5;												// wave number
	Uint16		ENP : 1;												// wave plot enable bit
	Uint16		res : 2;												// rsvd
}WAVE_BUF_CMD;

typedef	union
{
	Uint16					all;
	WAVE_BUF_CMD			bit;
}tWaveBufCmd;

//-------------------------------------------------------------------------------------
typedef		struct	wave_info
{
	Uint16		bytes;																	// variable storage bytes
	Uint16		ofst;																	// variable storage offset
	Uint16		base;
}WAVE_INFO;



typedef		struct	wave_buf_prm
{
	tWaveBufCmd			cmd;															// wave buffer command information
	WAVE_INFO			inf[MAX_WAVE_PLOT_NUM];											// wave plot variable information
}WAVE_BUF_PRM;

#define INTEL_HEX_FRAME_DAT_LENTH       100


//////////////////////////////////////////////////////////////////////////

//define INTEL HEX struct 
typedef struct intel_hex_frame
{
	Uint16			lenth;									//长度   (unit :byte)   
	Uint32			addr;									//地址      
	Uint16			type;									//记录类型，0－数据，1－终止     
	int16			data[INTEL_HEX_FRAME_DAT_LENTH];		//数据     
	int16			checksum;								//校验和 
}INTEL_HEX_FRAME;


//////////////////////////////////////////////////////////////////////////


typedef struct generalFunction
{
	Uint16			mode;
	Uint16			cmd;
	Uint16			dataLenth;
	int16*			data;
}GENERALFUNCTION;

typedef enum
{
	UART_PROGRAM = 1,
	UART_ERASE = 4
}UARTBOOT;

typedef enum
{
	SEV_SECTION = 0,
	AUX_SECTION = 1
}tRwRamPrm;
//参数，0：sev， 1：aux
typedef struct
{
  Uint16 usDeviceMesg;
  Uint16 usVersion;
  Uint16 usYear;
  Uint16 usMonthDay;
  Uint16 usAddInfA;
  Uint16 usAddInfB;
}VERSION;

#endif