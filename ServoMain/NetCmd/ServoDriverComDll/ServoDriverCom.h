#pragma once
#include "Basetype_def.h"
#include "RingNetInterface.h"
#include "RnServoAxiMapping.h"
#include "RnDriverPlot.h"
#include "ServoDriverComDef.h"
#include "Eeprom.h"
#include<vector>  
using namespace std;

class CServoDriverCom
{
public:
	CServoDriverCom();
	virtual ~CServoDriverCom();
protected:
	CRingNetInterface * m_pDriver;
	CRnServoAxiMapping*	m_pMapping;
	CRnDriverPlot*		m_pPlot;
	CEeprom* m_pEeprom;
public:
	//add by luo.mj 20180328
	Uint16 m_station_id;
	short SetStationId(Uint16 station_id);
	short GetStationIdList(vector<int16>& stationIdList);
	short GetStationAxisNum(int16* axisNum);
	/////////////////////////////////////////////
	short Initial(CRingNetInterface* pDriver);
	short InitialEeprom(CEeprom* pEeprom);
	Uint16 ConvertAxiToStationId(int16 axi_id){ return m_pMapping->ConvertAxiToStationId(axi_id); };
private:
	 const int32	 OUTPUT_LIMIT_SCALE = 4096;
	 const int32	 MAX_CUR_SCALE = 15000;
	 const int32	 MAX_SPD_SCALE = 16777216;   //2^24
	 const int32	 MAX_VOL_SCALE = 16384;
protected:
	const int16						GTSD_DSP_WRITE = 0;					  //dsp定义的读写	
	const int16						GTSD_DSP_READ = 1;

	const int16						COM_AXIS_MAX = 240;					//轴最大个数为4	

  const Uint16					FPGA_VERSION = (0xFF00 + (0x0001<<1));
	const Uint16					FPGA_YEAR		= (0xFF00 + (0x0003 << 1));
	const Uint16					FPGA_MD			= (0xFF00 + (0x0004 << 1));
	const Uint16					FPGA_ADD_A	= (0xFF00 + (0x0006 << 1));
	const Uint16					FPGA_ADD_B		= (0xFF00 + (0x0006 << 1));
protected:
	int16 GetCmdIDAndAxisNum(short cmdID, short motorNum);////将命令ID和轴号合并成一个short，其中bit[0-11]为命令ID, bit[12 - 15]为轴号
public:
	/////////////////////////////////com vs dsp/////////////////////////////////////////
	int16 GTSD_CMD_SetServoOn(int16 axis);
	int16 GTSD_CMD_SetServoOff(int16 axis);
	int16 GTSD_CMD_GetServoState(int16 axis, SERVO_STATE* serv);
	int16 GTSD_CMD_SetServoTaskMode(int16 axis, int16 mode);
	int16 GTSD_CMD_GetServoTaskMode(int16 axis, SERVO_MODE* mode);
	int16 GTSD_CMD_Write16BitByAdr(int16 axis, int16 ofst, int16 value, void* ptr);
	int16 GTSD_CMD_Read16BitByAdr(int16 axis, int16 ofst, int16* value, void* ptr);
	int16 GTSD_CMD_Write32BitByAdr(int16 axis, int16 ofst, int32 value, void* ptr);
	int16 GTSD_CMD_Read32BitByAdr(int16 axis, int16 ofst, int32* value, void* ptr);
	int16 GTSD_CMD_Write64BitByAdr(int16 axis, int16 ofst, int64 value, void* ptr);
	int16 GTSD_CMD_Read64BitByAdr(int16 axis, int16 ofst, int64* value, void* ptr);
	int16 GTSD_CMD_SetIdRef(int16 axis, double id_ref);
	int16 GTSD_CMD_GetIdRef(int16 axis, ID_STATE* id_ref);
	int16 GTSD_CMD_SetIqRef(int16 axis, double iq_ref);
	int16 GTSD_CMD_GetIqRef(int16 axis, IQ_STATE* iq_ref);
	int16 GTSD_CMD_SetSpdRef(int16 axis, double spd_ref);
	int16 GTSD_CMD_GetSpdRef(int16 axis, SPD_STATE* spd_ref);
	int16 GTSD_CMD_SetUdRef(int16 axis, double ud_ref);
	int16 GTSD_CMD_GetUdRef(int16 axis, UD_STATE* ud_ref);
	int16 GTSD_CMD_SetUqRef(int16 axis, double uq_ref);
	int16 GTSD_CMD_GetUqRef(int16 axis, UQ_STATE* uq_ref);
	int16 GTSD_CMD_SetUaRef(int16 axis, double ua_ref);
	int16 GTSD_CMD_GetUaRef(int16 axis, UA_STATE* ua_ref);
	int16 GTSD_CMD_SetUbRef(int16 axis, double ub_ref);
	int16 GTSD_CMD_GetUbRef(int16 axis, UB_STATE* ub_ref);
	int16 GTSD_CMD_SetUcRef(int16 axis, double uc_ref);
	int16 GTSD_CMD_GetUcRef(int16 axis, UC_STATE* uc_ref);
	int16 GTSD_CMD_SetPosAdjRef(int16 axis, double PosAdj_ref);
	int16 GTSD_CMD_GetPosAdjRef(int16 axis, POS_ADJ_STATE* pos_adj_ref);
	int16 GTSD_CMD_SetPosRef(int16 axis, int32 Pos_ref);
	/*
	int16 GTSD_CMD_SetFndCurr(int16 axis, int16 fnd, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetFndCurr(int16 axis, int16* fnd, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetFnqCurr(int16 axis, int16 fnq, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetFnqCurr(int16 axis, int16* fnq, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetTidCurr(int16 axis, int32 tid, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetTidCurr(int16 axis, int32* tid, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetTiqCurr(int16 axis, int32 tiq, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetTiqCurr(int16 axis, int32* tiq, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetFnVel(int16 axis, int16 fnvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetFnVel(int16 axis, int16* fnvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetTiVel(int16 axis, double tivel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetTiVel(int16 axis, double* tivel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetAbsLimVel(int16 axis, int16 abslimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetAbsLimVel(int16 axis, int16* abslimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetPosLimVel(int16 axis, int16 poslimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetPosLimVel(int16 axis, int16* poslimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetNegLimVel(int16 axis, int16 neglimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetNegLimVel(int16 axis, int16* neglimvel, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetFnPos(int16 axis, double fnpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetFnPos(int16 axis, double* fnpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetAbsLimPos(int16 axis, int16 abslimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetAbsLimPos(int16 axis, int16* abslimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetPosLimPos(int16 axis, int16 poslimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetPosLimPos(int16 axis, int16* poslimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetNegLimPos(int16 axis, int16 neglimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetNegLimPos(int16 axis, int16* neglimpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetKgaFfdPos(int16 axis, int16 kgaffdpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetKgaFfdPos(int16 axis, int16* kgaffdpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_SetKgvFfdPos(int16 axis, int16 kgvffdpos, int16 com_type = GTSD_COM_TYPE_NET);
	int16 GTSD_CMD_GetKgvFfdPos(int16 axis, int16* kgvffdpos, int16 com_type = GTSD_COM_TYPE_NET);
	*/

	/////////////////////////////////com vs fpga/////////////////////////////////////////
public:
	int16 GTSD_CMD_Set16bitFPGAByAddr(int16 dsp_number, int16 com_addr, int16 value);
	int16 GTSD_CMD_Get16bitFPGAByAddr(int16 dsp_number, int16 com_addr, int16* pvalue);
	int16 GTSD_CMD_Set32bitFPGAByAddr(int16 dsp_number, int16 com_addr, int32 value);
	int16 GTSD_CMD_Get32bitFPGAByAddr(int16 dsp_number, int16 com_addr, int32* pvalue);

	int16 GTSD_CMD_SetWaveBuf(int16 dsp_number, WAVE_BUF_PRM wave);
	int16 GTSD_CMD_GetWaveBuf(int16 dsp_number, tWaveBufCmd* ctrlword);

	int16 GTSD_CMD_GetWaveData(int16 dsp_number, int16* read_num, int16** data);
	int16 GTSD_CMD_ClearFpgaFifo(int16 dsp_number);

	/////////////////////////////////com vs dsp/////////////////////////////////////////
	int16 GTSD_CMD_Fram_Write16BitByAdr(int16 axis, int16 ofst, int16 value);
	int16 GTSD_CMD_Fram_Read16BitByAdr(int16 axis, int16 ofst, int16* value);
	int16 GTSD_CMD_Fram_Write32BitByAdr(int16 axis, int16 ofst, int32 value);
	int16 GTSD_CMD_Fram_Read32BitByAdr(int16 axis, int16 ofst, int32* value);
	int16 GTSD_CMD_Fram_Write64BitByAdr(int16 axis, int16 ofst, int64 value);
	int16 GTSD_CMD_Fram_Read64BitByAdr(int16 axis, int16 ofst, int64* value);

	/////////////////////////////////plot  vs dsp/////////////////////////////////////////
	int16 GTSD_CMD_StartPlot(int16 axis, WAVE_BUF_PRM& wave);						//启动ARM画图
	int16 GTSD_CMD_StopPlot(int16 axis, WAVE_BUF_PRM& wave);							//停止ARM画图
	int16 GTSD_CMD_PcGetWaveData(int16 axis, double** data, int32& number);			//从ARM获取数据
	bool GTSD_CMD_CheckPlotState(int16 axis);
	/////////////////////////////////com vs dsp burn the dsp program/////////////////////////////////////////
	int16 GTSD_CMD_ProcessorFlashHandler(int16 axis, wstring& filePath, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv);
	/////////////////////////////////com vs dsp burn the fpga program/////////////////////////////////////////
	int16 GTSD_CMD_FirmwareFlashHandler(int16 axis, wstring& filePath, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv);

	////////////////////////Dsp Flash read and wrtie//////////////////////////////////////////////////
	int16 GTSD_CMD_FlashWrite(int16 axis, INTEL_HEX_FRAME* packet);
	int16 GTSD_CMD_FlashRead(int16 axis, INTEL_HEX_FRAME* packet_w, INTEL_HEX_FRAME* packet_r);
	int16 GTSD_CMD_FlashErase(int16 axis, int16 blockNum);
	int16 GTSD_CMD_InterruptSwitch(int16 axis, int16 int_switch);

	/////////////////////////////////com vs dsp/////////////////////////////////////////
	int16 GTSD_CMD_ProcessorGeneralFunc(int16 axis, GENERALFUNCTION* gefunc);
	int16 GTSD_CMD_ResetSystem(int16 axis);
	int16 GTSD_CMD_CheckResetFinish(int16 axis, bool& flag_finish);

	int16 GTSD_CMD_ReadProcessorVersion(int16 axis, Uint16& ver);
	int16 GTSD_CMD_ReadFirmwareVersion(int16 axis, Uint16& ver);

	///add by luo.mj
	int16 GTSD_CMD_ReadFPGAVersion(int16 axis, VERSION* ver);
	int16 GTSD_CMD_ClrAlarm(int16 axis);

	//----------------------------------------------------------------------------------------------------------------
	int16 GTSD_CMD_ReadLogAlarmCode(int16 axis, Uint32* alarmCode, Uint16& lenth);

	int16 GTSD_CMD_ReadLogAlarmTimes(int16 axis, Uint16* alarmTimes, Uint16& lenth);

	//-----------------------------------------------------------------------------------------------------
// 
// 	//use for uart boot .out 转化为 .ldr
// 	int16 GTSD_CMD_Hex2Ldr(wstring& HexFile, wstring& LdrFile);
// 
// 	//可以使用hex文件或者是.out转化的ldr文件，ldr本身已经是二进制的文件了，hex还需要单独提取二进制信息。
// 	int16 GTSD_CMD_OpenSerialPort(int16 axis, int32 baudRate);
// 	int16 GTSD_CMD_CloseSerialPort(int16 axis);
// 	int16 GTSD_CMD_ReadSerialPort(int16 axis, Uint8 *buf, int32 length, int32 *length_read);
// 	int16 GTSD_CMD_WriteSerialPort(int16 axis, Uint8 *buf, int32 length, int32 *length_written);
// 
// 	/////////////////////////////////com vs fppa uart to burn the dsp/////////////////////////////////////////
// 	int16 GTSD_CMD_ProcessorUartBootHandler(int16 axis, wstring& filePath, int32 baudRate, int16 cmd, string& inputKey, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv);

// 	/////////////////////////////////com vs fppa eeprom/////////////////////////////////////////
// 	//EEPROM 读写,擦除
	int16 GTSD_CMD_ReadEEPROM(int16 axis, Uint16 ofst, Uint8* value, Uint16 num);
	int16 GTSD_CMD_WriteEEPROM(int16 axis, Uint16 ofst, Uint8* value, Uint16 num);
	int16 GTSD_CMD_ReadEEPROMExt(int16 axis, Uint16 ofst, Uint8* value, Uint16 num);
	int16 GTSD_CMD_WriteEEPROMExt(int16 axis, Uint16 ofst, Uint8* value, Uint16 num);
	Uint16 GTSD_CMD_FroceCheckMode(Uint16 mode);
// 	int16 GTSD_CMD_ClearEEPROM(int16 axis);
// 
// 	int16 GTSD_CMD_ResetFPGA(int16 axis);
// 	int16 GTSD_CMD_ConfigEEPROM(int16 com_type = GTSD_COM_TYPE_NET, int16 stationId = 0xf0);
	short GTSD_CMD_XmlWriteFile(int16 axis, char* pFileNameList[], int pFileTypeList[], int file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

	short GTSD_CMD_XmlReadFile(int16 axis, char* pFileNameList[], int pFileTypeList[], int& file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

};

