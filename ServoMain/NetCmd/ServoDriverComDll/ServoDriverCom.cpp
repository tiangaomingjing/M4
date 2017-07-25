#include "stdafx.h"
#include "ServoDriverCom.h"

CServoDriverCom::CServoDriverCom()
{
	m_pDriver = NULL;
	m_pPlot = NULL;
	m_pMapping = NULL;
	
}


CServoDriverCom::~CServoDriverCom()
{
	if (m_pPlot)
	{
		delete m_pPlot;
		m_pPlot = NULL;
	}
	if (m_pMapping)
	{
		delete m_pMapping;
	}
}

short CServoDriverCom::Initial(CRingNetInterface* pDriver)
{
	if (pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (m_pMapping == NULL)
	{
		m_pMapping = new CRnServoAxiMapping;
		if (m_pMapping == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
	}
	m_pDriver = pDriver;
	short rtn = m_pMapping->InitialMapping(pDriver);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}

	if (m_pPlot == NULL)
	{
		m_pPlot = new CRnDriverPlot;
		if (m_pPlot == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
		Uint16 dsp_list[3] = {0xF001, 0xF002, 0xF003};
		for (int i = 0; i < 3; i++)
		{
			dsp_list[i] = m_pMapping->ConvertDspToStationId(i);
		}
		
		short rtn = m_pPlot->PW_CreateDspWave(3, dsp_list);
		if (rtn != RTN_SUCCESS)
		{
			return rtn;
		}
		m_pDriver->m_pUserHandleRespFunctionDriver = m_pPlot;
	}
	return RTN_SUCCESS;
}

// 
// int16 Cmd_PlotDataBuffer[10000] = { 0 };


static const int32			FPGA_MODE_RD = 0x0;							//FPGA读操作
static const int32			FPGA_MODE_WR = 0x1;							//FPGA写操作
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//将命令ID和轴号合并成一个short，其中bit[0-11]为命令ID, bit[12 - 15]为轴号
int16 CServoDriverCom::GetCmdIDAndAxisNum(short cmdID, short motorNum)
{
	short ret;
	ret = cmdID;
	ret += (motorNum << 12);
	return ret;
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////打开命令通道
//int16 CServoDriverCom::GTSD_CMD_ST_OPEN(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress, int16 comType)
//{
//	void* ptr = ptrv;
//	//定义对象
//	if (g_AbsCom == NULL)
//	{
//		g_AbsCom = new CAbsCom;
//	}
//	else
//	{
//		return RTN_SUCCESS;//如果设备已经打开，直接返回
//	}
//	if (g_AbsCom == NULL)
//	{
//		return Net_Rt_CreateObj_Err;
//	}
//	//百分比进度
//	progress = 10;
//	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);
//
//	int16 rtn;
//	//调用open函数
//	rtn = g_AbsCom->GTSD_Com_Open(tpfUpdataProgressPt, ptr, progress, comType);
//	return rtn;
//}
////////////////////////////////////////////////////////////////////////////
////关闭命令通道
//int16 CServoDriverCom::GTSD_CMD_CLOSE(int16 comType)
//{
//	//假如已经关闭了就直接退出
//	if (g_AbsCom == NULL)
//	{
//		return RTN_SUCCESS;
//	}
//
//	int16 rtn;
//	//调用close函数
//	rtn = g_AbsCom->GTSD_Com_Close(comType);
//	if (g_AbsCom != NULL)
//	{
//		delete g_AbsCom;
//	}
//	g_AbsCom = NULL;
//
//	return rtn;
//}
//////////////////////////////////////////////////////////////////////////
//上伺服
//参数：轴号
int16 CServoDriverCom::GTSD_CMD_SetServoOn(int16 axis)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis);			//转换至站号和通道
	

	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;						//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SERVO_EN_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = 1;												//伺服使能							

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);

	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//下伺服
//参数：轴号
int16 CServoDriverCom::GTSD_CMD_SetServoOff(int16 axis)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}		


	int16 cmd_id = SERVO_EN_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = 0;												//伺服off							

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取伺服状态
//参数：轴号
//伺服状态结构体指针
int16 CServoDriverCom::GTSD_CMD_GetServoState(int16 axis, SERVO_STATE* serv)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SERVO_EN_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;									//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);

	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		serv->act_on_tmp = dspdata[0];
		serv->act_on = dspdata[1];
		serv->sec_on = dspdata[2];
		serv->sof_st_on = dspdata[3];
		serv->serv_ready = dspdata[4];
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置伺服任务模式
//参数：轴号
//参数：模式
int16 CServoDriverCom::GTSD_CMD_SetServoTaskMode(int16 axis, int16 mode)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SERVO_TASK_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = mode;												//设置模式							

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取伺服任务模式
//参数：轴号
//参数：模式
int16 CServoDriverCom::GTSD_CMD_GetServoTaskMode(int16 axis, SERVO_MODE* mode)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SERVO_TASK_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		mode->usr_mode = dspdata[0];
		mode->cmd_id = dspdata[1];
		mode->curr_id = dspdata[2];
		mode->curr_state = dspdata[3];

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个16bit的值到处理器
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Write16BitByAdr(int16 axis, int16 ofst, int16 value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}
	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	int16 cmd_id = WR_16BIT_COMM;							//cmd id		
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_WRITE);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_WRITE | (val[0] << 1));												//写命令	
	}
	dspdata[2] = 0;												//返回值											
	dspdata[3] = ofst;												//设置ofst
	dspdata[4] = value;											//设置value


	int16 dsp_comNum = 5;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从处理器读取一个16bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Read16BitByAdr(int16 axis, int16 ofst, int16* value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}
	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = WR_16BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_READ);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_READ | (val[0] << 1));												//读命令	
	}
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		*value = dspdata[1];
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个32bit的值到处理器
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Write32BitByAdr(int16 axis, int16 ofst, int32 value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}
	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = WR_32BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_WRITE);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_WRITE | (val[0] << 1));												//写命令	
	}
	dspdata[2] = 0;												//返回值											
	dspdata[3] = ofst;												//设置ofst
	dspdata[4] = (value & 0xffff);									//设置value,先设置低16bit
	dspdata[5] = ((value >> 16) & 0xffff);							//设置value,再设置高16bit

	int16 dsp_comNum = 6;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从处理器读取一个32bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Read32BitByAdr(int16 axis, int16 ofst, int32* value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}
	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = WR_32BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_READ);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_READ | (val[0] << 1));												//读命令	
	}
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		*value = (((dspdata[1]) & 0x0000ffff) | ((dspdata[2] << 16) & 0xffff0000));								//高位在后
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个64bit的值到处理器
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Write64BitByAdr(int16 axis, int16 ofst, int64 value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}
	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = WR_64BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_WRITE);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_WRITE | (val[0] << 1));												//写命令	
	}
	dspdata[2] = 0;												//返回值											
	dspdata[3] = ofst;												//设置ofst
	dspdata[4] = (value & 0xffff);									//设置value,先设置低16bit
	dspdata[5] = ((value >> 16) & 0xffff);							//设置value,再设置  16bit
	dspdata[6] = ((value >> 32) & 0xffff);							//设置value,再设置  16bit
	dspdata[7] = (((value >> 32) >> 16) & 0xffff);					//设置value,再设置高16bit

	int16 dsp_comNum = 8;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从处理器读取一个64bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Read64BitByAdr(int16 axis, int16 ofst, int64* value, void* ptr)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	int16* val = NULL;
	if (ptr != NULL)
	{
		val = (int16*)ptr;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = WR_64BIT_COMM;									//cmd id

	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	if (val == NULL)
	{
		dspdata[1] = (GTSD_DSP_READ);
	}
	else
	{
		dspdata[1] = (GTSD_DSP_READ | (val[0] << 1));												//读命令	
	}
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		int64 tmp, tmp1;
		tmp = (((int64)dspdata[4]) << 32);
		tmp1 = ((tmp << 16) & 0xffff000000000000);
		*value = (((int64)(dspdata[1]) & 0x000000000000ffff) | ((((int64)dspdata[2]) << 16) & 0x00000000ffff0000) | ((((int64)dspdata[3]) << 32) & 0x0000ffff00000000) | tmp1);								//高位在后
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置id指令
//参数：轴号
//参数：id指令参考值
int16 CServoDriverCom::GTSD_CMD_SetIdRef(int16 axis, double id_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = ID_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值	
	int32 tmp;
	tmp = (int32)((id_ref) / 100.0*((double)(MAX_CUR_SCALE)) + 0.5);
	if ((tmp>32767) || (tmp<-32768))
	{
		tmp = (int32)(0.05*((double)(MAX_CUR_SCALE)) + 0.5);
	}
	dspdata[3] = (int16)tmp;											//设置id_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取id指令
//参数：轴号
//参数：id指令参考值
int16 CServoDriverCom::GTSD_CMD_GetIdRef(int16 axis, ID_STATE* id_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = ID_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		id_ref->chd_idr_tmp = (((double)dspdata[0]) / ((double)MAX_CUR_SCALE) * 100.0);
		id_ref->tsk_id_ref = (((double)dspdata[1]) / ((double)MAX_CUR_SCALE) * 100.0);
		id_ref->ctl_id_ref = (((double)dspdata[2]) / ((double)MAX_CUR_SCALE) * 100.0);
		id_ref->ctl_id = (((double)dspdata[3]) / ((double)MAX_CUR_SCALE) * 100.0);
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置iq指令
//参数：轴号
//参数：id指令参考值
int16 CServoDriverCom::GTSD_CMD_SetIqRef(int16 axis, double iq_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = IQ_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)((iq_ref) / 100.0*((double)(MAX_CUR_SCALE)) + 0.5);
	if ((tmp > 32767) || (tmp < -32768))
	{
		tmp = (int32)(0.05*((double)(MAX_CUR_SCALE)) + 0.5);
	}
	dspdata[3] = (int16)tmp;										//设置iq_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取iq指令
//参数：轴号
//参数：iq指令参考值
int16 CServoDriverCom::GTSD_CMD_GetIqRef(int16 axis, IQ_STATE* iq_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = IQ_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		iq_ref->chd_iqr_tmp = (((double)dspdata[0]) / ((double)MAX_CUR_SCALE) * 100.0);
		iq_ref->tsk_iq_ref = (((double)dspdata[1]) / ((double)MAX_CUR_SCALE) * 100.0);
		iq_ref->ctl_iq_ref = (((double)dspdata[2]) / ((double)MAX_CUR_SCALE) * 100.0);
		iq_ref->ctl_iq = (((double)dspdata[3]) / ((double)MAX_CUR_SCALE) * 100.0);
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置速度指令
//参数：轴号
//参数：速度指令参考值比率
int16 CServoDriverCom::GTSD_CMD_SetSpdRef(int16 axis, double spd_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SPD_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int64 tmp;
	tmp = (int64)(spd_ref / 100.0*((double)MAX_SPD_SCALE) + 0.5);
	if ((tmp>0x7fffffff) || (tmp<-0x7fffffff))
	{
		tmp = (int64)(0.05*((double)MAX_SPD_SCALE) + 0.5);
	}
	int32 tmp1;
	tmp1 = (int32)tmp;
	dspdata[3] = (tmp1 & 0xffff);									//设置spd_ref低16位
	dspdata[4] = ((tmp1 >> 16) & 0xffff);								//设置spd_ref高16位

	int16 dsp_comNum = 5;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取速度指令
//参数：轴号
//参数：速度指令参考值比率
int16 CServoDriverCom::GTSD_CMD_GetSpdRef(int16 axis, SPD_STATE* spd_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = SPD_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		spd_ref->chd_spd_tmp = ((double)(((dspdata[0] & 0x0000ffff) | ((dspdata[1] << 16) & 0xffff0000)))) / ((double)MAX_SPD_SCALE)*100.0;
		spd_ref->tsk_spd_ref = ((double)(((dspdata[2] & 0x0000ffff) | ((dspdata[3] << 16) & 0xffff0000)))) / ((double)MAX_SPD_SCALE)*100.0;
		spd_ref->ctl_spd_ref = ((double)(((dspdata[4] & 0x0000ffff) | ((dspdata[5] << 16) & 0xffff0000)))) / ((double)MAX_SPD_SCALE)*100.0;
		spd_ref->ctl_spd_fd = ((double)(((dspdata[6] & 0x0000ffff) | ((dspdata[7] << 16) & 0xffff0000)))) / ((double)MAX_SPD_SCALE)*100.0;
		spd_ref->rsv_mot_spd = ((double)(((dspdata[8] & 0x0000ffff) | ((dspdata[9] << 16) & 0xffff0000)))) / ((double)MAX_SPD_SCALE)*100.0;
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置udref指令
//参数：轴号
//参数：ud指令参考值
int16 CServoDriverCom::GTSD_CMD_SetUdRef(int16 axis, double ud_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UD_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)(ud_ref / 100.0*((double)MAX_VOL_SCALE) + 0.5);
	if ((tmp>16384) || (tmp<-16384))
	{
		tmp = (int32)(0.05*((double)MAX_VOL_SCALE));
	}
	dspdata[3] = (int16)tmp;											//设置ud_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取udref指令
//参数：轴号
//参数：ud指令参考值
int16 CServoDriverCom::GTSD_CMD_GetUdRef(int16 axis, UD_STATE* ud_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UD_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		ud_ref->chd_ud_tmp = ((double)(dspdata[0])) / ((double)MAX_VOL_SCALE)*100.0;
		ud_ref->tsk_ud_ref = ((double)(dspdata[1])) / ((double)MAX_VOL_SCALE)*100.0;
		ud_ref->cur_ud = ((double)(dspdata[2])) / ((double)MAX_VOL_SCALE)*100.0;

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置uqref指令
//参数：轴号
//参数：uq指令参考值
int16 CServoDriverCom::GTSD_CMD_SetUqRef(int16 axis, double uq_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UQ_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)(uq_ref / 100.0*((double)MAX_VOL_SCALE) + 0.5);
	if ((tmp > 16384) || (tmp < -16384))
	{
		tmp = (int32)(0.05*((double)MAX_VOL_SCALE));
	}
	dspdata[3] = (int16)tmp;											//设置uq_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取uqref指令
//参数：轴号
//参数：uq指令参考值
int16 CServoDriverCom::GTSD_CMD_GetUqRef(int16 axis, UQ_STATE* uq_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UQ_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		uq_ref->chd_uq_tmp = ((double)(dspdata[0])) / ((double)MAX_VOL_SCALE)*100.0;
		uq_ref->tsk_uq_ref = ((double)(dspdata[1])) / ((double)MAX_VOL_SCALE)*100.0;
		uq_ref->cur_uq = ((double)(dspdata[2])) / ((double)MAX_VOL_SCALE)*100.0;

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置uaref指令
//参数：轴号
//参数：ua指令参考值
int16 CServoDriverCom::GTSD_CMD_SetUaRef(int16 axis, double ua_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UA_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)(ua_ref / 100.0*((double)MAX_VOL_SCALE) + 0.5);
	if ((tmp > 16384) || (tmp < -16384))
	{
		tmp = (int32)(0.05*((double)MAX_VOL_SCALE));
	}
	dspdata[3] = (int16)tmp;											//设置ua_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取uaref指令
//参数：轴号
//参数：ua指令参考值
int16 CServoDriverCom::GTSD_CMD_GetUaRef(int16 axis, UA_STATE* ua_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UA_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		ua_ref->chd_ua_tmp = ((double)(dspdata[0])) / ((double)MAX_VOL_SCALE)*100.0;
		ua_ref->tsk_ua_ref = ((double)(dspdata[1])) / ((double)MAX_VOL_SCALE)*100.0;
		ua_ref->cur_ua = ((double)(dspdata[2])) / ((double)MAX_VOL_SCALE)*100.0;

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置ubref指令
//参数：轴号
//参数：ub指令参考值
int16 CServoDriverCom::GTSD_CMD_SetUbRef(int16 axis, double ub_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UB_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值	
	int32 tmp;
	tmp = (int32)(ub_ref / 100.0*((double)MAX_VOL_SCALE) + 0.5);
	if ((tmp > 16384) || (tmp < -16384))
	{
		tmp = (int32)(0.05*((double)MAX_VOL_SCALE));
	}
	dspdata[3] = (int16)tmp;										//设置ub_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取ubref指令
//参数：轴号
//参数：ub指令参考值
int16 CServoDriverCom::GTSD_CMD_GetUbRef(int16 axis, UB_STATE* ub_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UB_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		ub_ref->chd_ub_tmp = ((double)(dspdata[0])) / ((double)MAX_VOL_SCALE)*100.0;
		ub_ref->tsk_ub_ref = ((double)(dspdata[1])) / ((double)MAX_VOL_SCALE)*100.0;
		ub_ref->cur_ub = ((double)(dspdata[2])) / ((double)MAX_VOL_SCALE)*100.0;

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置ucref指令
//参数：轴号
//参数：uc指令参考值
int16 CServoDriverCom::GTSD_CMD_SetUcRef(int16 axis, double uc_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UC_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)(uc_ref / 100.0*((double)MAX_VOL_SCALE) + 0.5);
	if ((tmp > 16384) || (tmp < -16384))
	{
		tmp = (int32)(0.05*((double)MAX_VOL_SCALE));
	}
	dspdata[3] = (int16)tmp;											//设置uc_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取ucref指令
//参数：轴号
//参数：uc指令参考值
int16 CServoDriverCom::GTSD_CMD_GetUcRef(int16 axis, UC_STATE* uc_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = UC_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		uc_ref->chd_uc_tmp = ((double)(dspdata[0])) / ((double)MAX_VOL_SCALE)*100.0;
		uc_ref->tsk_uc_ref = ((double)(dspdata[1])) / ((double)MAX_VOL_SCALE)*100.0;
		uc_ref->cur_uc = ((double)(dspdata[2])) / ((double)MAX_VOL_SCALE)*100.0;

		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置PosAdjref指令
//参数：轴号
//参数：PosAdj指令参考值
int16 CServoDriverCom::GTSD_CMD_SetPosAdjRef(int16 axis, double PosAdj_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = POS_ADJ_IREF_COMM;								//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值
	int32 tmp;
	tmp = (int32)(PosAdj_ref / 100.0*((double)MAX_CUR_SCALE) + 0.5);
	if ((tmp > 16384) || (tmp < -16384))
	{
		tmp = (int32)(0.05*((double)MAX_CUR_SCALE));
	}
	dspdata[3] = (int16)tmp;										//设置PosAdj_ref

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取PosAdjref指令
//参数：轴号
//参数：PosAdj指令参考值
int16 CServoDriverCom::GTSD_CMD_GetPosAdjRef(int16 axis, POS_ADJ_STATE* pos_adj_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = POS_ADJ_IREF_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		pos_adj_ref->chd_pos_adj_tmp = ((double)(dspdata[0])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->tsk_pos_adj_ref = ((double)(dspdata[1])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->ctl_id_ref = ((double)(dspdata[2])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->ctl_id = ((double)(dspdata[3])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->ctl_iq_ref = ((double)(dspdata[4])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->ctl_iq = ((double)(dspdata[5])) / ((double)MAX_CUR_SCALE)*100.0;
		pos_adj_ref->rsv_pos_elec = (dspdata[6]);
		pos_adj_ref->rsv_pos = ((dspdata[7] & 0x0000ffff) | ((dspdata[8] << 16) & 0xffff0000));
		pos_adj_ref->rsv_pos_in = ((dspdata[9] & 0x0000ffff) | ((dspdata[10] << 16) & 0xffff0000));
		pos_adj_ref->mfj_pos_adj_flag = (dspdata[11]);
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//设置Posref指令
//参数：轴号
//参数：Pos指令参考值
int16 CServoDriverCom::GTSD_CMD_SetPosRef(int16 axis, int32 Pos_ref)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = POS_REF_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = (Pos_ref & 0xffff);									//设置Pos_ref 低16bit
	dspdata[4] = ((Pos_ref >> 16) & 0xffff);							//设置Pos_ref 高16bit

	int16 dsp_comNum = 5;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

/////////////////////////////////com vs fpga/////////////////////////////////////////
int16 CServoDriverCom::GTSD_CMD_Set16bitFPGAByAddr(int16 dsp_number, int16 com_addr, int16 value)
{
	//输入是byte地址，pcdebug操作需要short地址，而等环网操作需要byte地址，

	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);
	int16 comAddr = m_pMapping->ConvertFpgaByteAddrByDspId(dsp_number, com_addr);
	int16 comNum = 1;

	return m_pDriver->RnNetCom_FPGA_ComHandler(GTSD_COM_MODE_WRITE, comAddr, &value, comNum, station_id >> 8);
}
//////////////////////////////////////////////////////////////////////////
//通过地址读取16bit的fpga
int16 CServoDriverCom::GTSD_CMD_Get16bitFPGAByAddr(int16 dsp_number, int16 com_addr, int16* pvalue)
{
	//输入是byte地址，pcdebug操作需要short地址，而等环网操作需要byte地址，
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);
	int16 comAddr = m_pMapping->ConvertFpgaByteAddrByDspId(dsp_number, com_addr);
	int16 comNum = 1;
	return m_pDriver->RnNetCom_FPGA_ComHandler(GTSD_COM_MODE_READ, comAddr, pvalue, comNum, station_id >> 8);
}
//////////////////////////////////////////////////////////////////////////
//通过地址设置32bit的fpga
int16 CServoDriverCom::GTSD_CMD_Set32bitFPGAByAddr(int16 dsp_number, int16 com_addr, int32 value)
{
	//输入是byte地址，pcdebug操作需要short地址，而等环网操作需要byte地址，
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);
	int16 comAddr = m_pMapping->ConvertFpgaByteAddrByDspId(dsp_number, com_addr);
	int16 comNum = 2;

	return m_pDriver->RnNetCom_FPGA_ComHandler(GTSD_COM_MODE_WRITE, comAddr, (int16*)&value, comNum, station_id >> 8);
}
//////////////////////////////////////////////////////////////////////////
//通过地址读取32bit的fpga
int16 CServoDriverCom::GTSD_CMD_Get32bitFPGAByAddr(int16 dsp_number, int16 com_addr, int32* pvalue)
{
	//输入是byte地址，pcdebug操作需要short地址，而等环网操作需要byte地址，
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);
	int16 comAddr = m_pMapping->ConvertFpgaByteAddrByDspId(dsp_number, com_addr);
	int16 comNum = 2;
	return m_pDriver->RnNetCom_FPGA_ComHandler(GTSD_COM_MODE_READ, comAddr, (int16*)pvalue, comNum, station_id >> 8);
}
//////////////////////////////////////////////////////////////////////////
//设置曲线配置
int16 CServoDriverCom::GTSD_CMD_SetWaveBuf(int16 dsp_number, WAVE_BUF_PRM wave)
{
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);

	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;						//地址
	int16 dspdata[64] = { 0 };											//通信数组
	int16 Axis = 0;												//轴号都设置为0即可，因为每个dsp有两个轴，设置哪个都一样

	int16 cmd_id = WAVE_BUF_SET_WR_COMM;								//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, 0);					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = (wave.cmd.all);									//设置controlword
	int16 j = 4;

	if (wave.cmd.bit.NUM >MAX_WAVE_PLOT_NUM)
	{
		return RTN_PARAM_OVERFLOW;
	}

	for (int16 i = 0; i < wave.cmd.bit.NUM; ++i)
	{
		dspdata[j] = wave.inf[i].bytes;
		dspdata[j + 1] = wave.inf[i].ofst;
		dspdata[j + 2] = wave.inf[i].base;
		j += 3;
	}

	int16 dsp_comNum = j;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//读取曲线配置
int16 CServoDriverCom::GTSD_CMD_GetWaveBuf(int16 dsp_number, tWaveBufCmd* ctrlword)
{
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
		//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	Uint16 station_id = m_pMapping->ConvertDspToStationId(dsp_number);
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址

	int16 dspdata[16] = { 0 };											//通信数组
	int16 Axis = 0;												//轴号

	int16 cmd_id = WAVE_BUF_SET_WR_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, 0);					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		ctrlword->all = (dspdata[0]);
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据配置获取曲线数据
int16 CServoDriverCom::GTSD_CMD_GetWaveData(int16 dsp_number, int16* read_num, int16** data)
{
	return RTN_OBJECT_UNCREATED;
}
//////////////////////////////////////////////////////////////////////////
//清除fpga的FIFO
int16 CServoDriverCom::GTSD_CMD_ClearFpgaFifo(int16 dsp_number)
{
	return RTN_OBJECT_UNCREATED;
}

/////////////////////////////////com vs dsp/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个16bit的值到FRAM
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Write16BitByAdr(int16 axis, int16 ofst, int16 value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };												//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_16BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 						//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;										//写命令	
	dspdata[2] = 0;														//返回值											
	dspdata[3] = ofst;													//设置ofst
	dspdata[4] = value;													//设置value

	int16 dsp_comNum = 5;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从FRAM读取一个16bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Read16BitByAdr(int16 axis, int16 ofst, int16* value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_16BIT_COMM;								//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;									//读命令	
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		*value = dspdata[1];
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个32bit的值到FRAM
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Write32BitByAdr(int16 axis, int16 ofst, int32 value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_32BIT_COMM;								//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = ofst;												//设置ofst
	dspdata[4] = (value & 0xffff);									//设置value,先设置低16bit
	dspdata[5] = ((value >> 16) & 0xffff);							//设置value,再设置高16bit

	int16 dsp_comNum = 6;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从FRAM读取一个32bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Read32BitByAdr(int16 axis, int16 ofst, int32* value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_32BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		*value = (((dspdata[1]) & 0x0000ffff) | ((dspdata[2] << 16) & 0xffff0000));								//高位在后
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置设置一个64bit的值到FRAM
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Write64BitByAdr(int16 axis, int16 ofst, int64 value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_64BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = ofst;												//设置ofst
	dspdata[4] = (value & 0xffff);									//设置value,先设置低16bit
	dspdata[5] = ((value >> 16) & 0xffff);							//设置value,再设置  16bit
	dspdata[6] = ((value >> 32) & 0xffff);							//设置value,再设置  16bit
	dspdata[7] = (((value >> 32) >> 16) & 0xffff);					//设置value,再设置高16bit

	int16 dsp_comNum = 8;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
//根据偏置从FRAM读取一个64bit的值
//参数：轴号
//参数：偏置
//参数：值
int16 CServoDriverCom::GTSD_CMD_Fram_Read64BitByAdr(int16 axis, int16 ofst, int64* value)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 			//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;						//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_FRAM_64BIT_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis)); 					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = ofst;												//设置ofst

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		int64 tmp, tmp1;
		tmp = (((int64)dspdata[4]) << 32);
		tmp1 = ((tmp << 16) & 0xffff000000000000);
		*value = (((int64)(dspdata[1]) & 0x000000000000ffff) | ((((int64)dspdata[2]) << 16) & 0x00000000ffff0000) | ((((int64)dspdata[3]) << 32) & 0x0000ffff00000000) | tmp1);								//高位在后
		return RTN_SUCCESS;
	}
}

///////////////////////////////plot wave///////////////////////////////////////////
int16 CServoDriverCom::GTSD_CMD_StartPlot(int16 axis, WAVE_BUF_PRM& wave)
{
	if (m_pPlot == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	Uint16 *wave_size = new Uint16[wave.cmd.bit.NUM];
	if (wave_size == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	for (int i = 0; i < wave.cmd.bit.NUM; i++)
	{
		wave_size[i] = wave.inf[i].bytes;
	}
	wave.cmd.bit.ENP = 1;
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 			//轴号
	short rtn = m_pPlot->PW_StartDspPlot(station_id, wave.cmd.bit.NUM, wave_size);
	delete wave_size;
	if (rtn != RTN_SUCCESS)
		return rtn;
	Uint16 dsp_id = m_pMapping->ConvertAxiToDspId(axis);
	rtn = GTSD_CMD_SetWaveBuf(dsp_id, wave);
	return rtn;

}
int16 CServoDriverCom::GTSD_CMD_StopPlot(int16 axis, WAVE_BUF_PRM& wave)
{
	if (m_pPlot == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	//停止dspA向FPGA的FIFO中写数据
	wave.cmd.bit.ENP = 0;
	Uint16 dsp_id = m_pMapping->ConvertAxiToDspId(axis);
	short rtn = GTSD_CMD_SetWaveBuf(dsp_id, wave);
	if (rtn)
		return rtn;
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 			//轴号
	return m_pPlot->PW_StopDspPlot(station_id);
}
int16 CServoDriverCom::GTSD_CMD_PcGetWaveData(int16 axis, double** data, int32& number)
{
	Uint32 read_number;
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 			//轴号
	short rtn = m_pPlot->PW_PcGetDspWaveData(station_id, data, read_number);
	number = read_number;
	return rtn;
}
bool CServoDriverCom::GTSD_CMD_CheckPlotState(int16 axis)
{
	return false;
}
/////////////////////////Dsp FLash Operate/////////////////////////////////////////////////
int16 CServoDriverCom::GTSD_CMD_FlashWrite(int16 axis, INTEL_HEX_FRAME* packet)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[100] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_SPI_FLASH_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;												//写命令	
	dspdata[2] = 0;												//返回值											
	dspdata[3] = packet->lenth;
	dspdata[4] = ((packet->addr >> 16) & 0xffff);
	dspdata[5] = (packet->addr & 0xffff);
	dspdata[6] = (packet->type);
	for (int16 i = 0; i < packet->lenth; ++i)
	{
		dspdata[7 + i] = packet->data[i];
	}
	dspdata[7 + packet->lenth] = packet->checksum;

	int16 dsp_comNum = 8 + packet->lenth;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_FlashRead(int16 axis, INTEL_HEX_FRAME* packet_w, INTEL_HEX_FRAME* packet_r)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[200] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = WR_SPI_FLASH_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));				//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		
	dspdata[3] = packet_w->lenth;
	dspdata[4] = ((packet_w->addr >> 16) & 0xffff);
	dspdata[5] = (packet_w->addr & 0xffff);
	int16 dsp_comNum = 8 + packet_w->lenth;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		packet_r->lenth = (Uint8)dspdata[0];
		packet_r->addr = ((Uint32)((Uint16)dspdata[1] << 16) | (Uint16)(dspdata[2]));
		for (int16 i = 0; i < packet_r->lenth; ++i)
		{
			packet_r->data[i] = (Uint8)dspdata[3 + i];
		}

		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_FlashErase(int16 axis, int16 blockNum)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = SPI_ERASE_FLASH_COMM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));			//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;													//返回值	
	dspdata[3] = blockNum;											//需要擦出的block number

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_InterruptSwitch(int16 axis, int16 int_switch)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = INTERRUPT_SWITCH_COMM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));				//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;													//返回值											
	dspdata[3] = int_switch;											//中断开关							

	int16 dsp_comNum = 4;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_ProcessorGeneralFunc(int16 axis, GENERALFUNCTION* gefunc)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	if ((gefunc->data == NULL))
	{
		return RTN_PARAM_OVERFLOW;
	}
	if (gefunc->dataLenth == 0)
	{
		return RTN_PARAM_OVERFLOW;
	}
	if (gefunc->mode > 1)
	{
		return RTN_PARAM_OVERFLOW;
	}
	if (gefunc->cmd > TUNNING_MESSAGE_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 														//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;												//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
															//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}
	gefunc->data[0] = GetCmdIDAndAxisNum(gefunc->cmd, m_pMapping->ConvertAxiToSubAxiId(axis));						//合并轴号和命令id
	gefunc->data[1] = gefunc->mode;												//命令模式	写：0 读1
	gefunc->data[2] = 0;															//返回值	

	int16 dsp_comNum = gefunc->dataLenth;											//数据长度是包含回来的总长度

	int rtn = m_pDriver->RnNetCom_DSP_ComHandler((1 - gefunc->mode), dsp_comAddr, gefunc->data, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	return RTN_SUCCESS;

}

int16 CServoDriverCom::GTSD_CMD_ResetSystem(int16 axis)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = RESET_SYSTEM_COMM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));				//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;													//返回值											

	int16 dsp_comNum = 3;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_CheckResetFinish(int16 axis, bool& flag_finish)
{
	flag_finish = 0;

	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = CHECK_RESET_FINISH_COMM;									//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		
	int32 value1, value2;
	int16 dsp_comNum = 15;
	//读取第一次
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		value1 = (((dspdata[0]) & 0x0000ffff) | ((dspdata[1] << 16) & 0xffff0000));								//高位在后
	}
	Sleep(1);
	//读取第二次
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));				//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;
	rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		value2 = (((dspdata[0]) & 0x0000ffff) | ((dspdata[1] << 16) & 0xffff0000));								//高位在后
	}

	if ((value2 > value1) && (value1 != 0) && (value2 != 0))
	{
		flag_finish = true;
	}
	else
	{
		flag_finish = false;
	}
	return RTN_SUCCESS;
}

int16 CServoDriverCom::GTSD_CMD_ReadProcessorVersion(int16 axis, Uint16& ver)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 												//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = RD_PROCESSOR_VER_COMM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 15;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		ver = dspdata[0];
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_ReadFirmwareVersion(int16 axis, Uint16& ver)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}												//轴号
	int16 dsp_id = m_pMapping->ConvertAxiToDspId(axis);;
	int16 com_addr = (int16)FPGA_VERSION;

	int16 rtn = GTSD_CMD_Get16bitFPGAByAddr(dsp_id, com_addr, (int16*)(&ver));
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_ClrAlarm(int16 axis)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[16] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
													//如果是2，那么是另一个dsp，但是需将轴号更改为0
	}

	int16 cmd_id = ALARM_CLEAR_COMM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_WRITE;									//写命令	
	dspdata[2] = 0;													//返回值											

	int16 dsp_comNum = 3;
	short rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_WRITE, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		return RTN_SUCCESS;
	}
}
//////////////////////////////////////////////////////////////////////////
// int16 CServoDriverCom::GTSD_CMD_OpenSerialPort(int16 axis, int32 baudRate)
// {
// 	short rtn;
// 	rtn = m_pSerial->open(axis, baudRate);
// 
// 	if (rtn == RTN_SUCCESS)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return rtn;
// 	}
// 
// }
// 
// int16 CServoDriverCom::GTSD_CMD_CloseSerialPort(int16 axis)
// {
// 	bool rtn;
// 	rtn = m_pSerial->close(axis);
// 
// 	if (rtn == true)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return Net_Rt_SerialPort_Err;
// 	}
// }
// 
// int16 CServoDriverCom::GTSD_CMD_ReadSerialPort(int16 axis, Uint8 *buf, int32 length, int32 *length_read)
// {
// 	bool rtn;
// 	rtn = m_pSerial->read(axis, buf, length, length_read);
// 
// 	if (rtn == true)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return Net_Rt_SerialPort_Err;
// 	}
// }
// 
// int16 CServoDriverCom::GTSD_CMD_WriteSerialPort(int16 axis, Uint8 *buf, int32 length, int32 *length_written)
// {
// 	bool rtn;
// 	rtn = m_pSerial->write(axis, buf, length, length_written);
// 
// 	if (rtn == true)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return Net_Rt_SerialPort_Err;
// 	}
// }

int16 CServoDriverCom::GTSD_CMD_ReadLogAlarmCode(int16 axis, Uint32* alarmCode, Uint16& lenth)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[64] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = RD_ALARM_LOG_CODE_COM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));				//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	Uint16 cur_index = 0;
	Uint16 bit32lenth = 0;
	int16 dsp_comNum = 40;
	int rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		//第一个数据是当前的index
		cur_index = dspdata[0];
		//假如读到的报警index是-1，那么就说明还没有报警，正常的时候会将他们初始化为0
		if (((int16)cur_index) < 0)
		{
			cur_index = 0;
		}

		//第二个数据是32bit数据的长度
		bit32lenth = dspdata[1];

		//根据当前index和总的数据长度进行排序，将最近的报警排在最前面。
		for (int16 i = 0; i < lenth; ++i)
		{
			alarmCode[i] = (((dspdata[(2 + 2 * cur_index)] << 16) & 0xffff0000) | (dspdata[(2 + 2 * cur_index + 1)] & 0x0000ffff));
			cur_index++;
			if ((cur_index) >= bit32lenth)
			{
				cur_index = 0;
			}
		}

		return RTN_SUCCESS;
	}
}

int16 CServoDriverCom::GTSD_CMD_ReadLogAlarmTimes(int16 axis, Uint16* alarmTimes, Uint16& lenth)
{
	if (axis >= COM_AXIS_MAX)
	{
		return RTN_PARAM_OVERFLOW;
	}

	int16 dspdata[64] = { 0 };											//通信数组
	Uint16 station_id = m_pMapping->ConvertAxiToStationId(axis); 													//轴号
	int16 dsp_comAddr = RN_USER_PROTOCOL_DRIVER;										//地址
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}

	int16 cmd_id = RD_ALARM_LOG_TIMES_COM;							//cmd id
	dspdata[0] = GetCmdIDAndAxisNum(cmd_id, m_pMapping->ConvertAxiToSubAxiId(axis));					//合并轴号和命令id
	dspdata[1] = GTSD_DSP_READ;												//读命令	
	dspdata[2] = 0;												//返回值																		

	int16 dsp_comNum = 40;
	int rtn = m_pDriver->RnNetCom_DSP_ComHandler(GTSD_COM_MODE_READ, dsp_comAddr, dspdata, dsp_comNum, station_id >> 8, station_id & 0xFF);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	else
	{
		for (int16 i = 0; i < lenth; ++i)
		{
			alarmTimes[i] = dspdata[i];
		}
		return RTN_SUCCESS;
	}
}
