//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Communicaiton cmd layer Define		 						//
//	file				:	ServoDriverComDll.cpp										//
//	Description			:	use for cmd define											//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2016/1/20	|	googoltech		|		2016 - 2019			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <conio.h>
#include "BaseReturn_def.h"
// #include "PlotWave.h"
// #include "ParseHex.h"
#include "FPGAUpdate.h"
// #include "hex2ldr.h"
// #include "serialport.h"
// #include "eepromOpt.h"
// #include "ServoDriverComDll.h"
// #include "RnDriverPlot.h"
// #include "RingNetInterface.h"
#include "MotionControlComDll.h"
#include "MotionCtrlCom.h"

//为了获取网卡连接的状态和速率，因为等环网不支持百兆，现在只支持千兆，如果是百兆，
#include <winsock2.h>
#include <ws2tcpip.h>

extern HANDLE GTSD_Event;
int16 TryLock(void);
int16 Unlock(int16 error);

CMotionCtrlCom* g_RnMotionCom = NULL;
extern CRingNetInterface* g_RnInterface;

//////////////////////////////////////////////////////////////////////////
//多线程保护
SERVODRIVERCOMDLL_API int16 GT_RN_Open(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv)
{
	int16 progress;
	void* ptr = ptrv;
	//百分比进度
	progress = 0;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);
	////////////////////////if use the ring net way//////////////////////////////////////////////////
	short rtn;
	if (Net_Rt_Lock_Err == TryLock())
	{
		return Net_Rt_Lock_Err;
	}
	if (g_RnInterface == NULL)
	{
		g_RnInterface = new CRingNetInterface;
		if (g_RnInterface == NULL)
		{
			return Unlock(RTN_MALLOC_FAIL);
		}
		rtn = g_RnInterface->RnNetCom_Open(tpfUpdataProgressPt, ptrv, progress);
		if (rtn != RTN_SUCCESS)
		{
			return Unlock(rtn);
		}
	}

	progress = 100;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);
	if (g_RnMotionCom == NULL)
	{
		g_RnMotionCom = new CMotionCtrlCom;
		if (g_RnMotionCom == NULL)
		{
			return Unlock(RTN_MALLOC_FAIL);
		}
		rtn = g_RnMotionCom->Initial(g_RnInterface);
		if (rtn != RTN_SUCCESS)
		{
			return Unlock(rtn);
		}
	}

	return Unlock(RTN_SUCCESS);
}
SERVODRIVERCOMDLL_API int16 GT_RN_Close()
{

	if (Net_Rt_Lock_Err == TryLock())
	{
		return Net_Rt_Lock_Err;
	}
	if (g_RnMotionCom)
	{
		delete g_RnMotionCom;
		g_RnMotionCom = NULL;
	}
	if (g_RnInterface)
	{
		delete g_RnInterface;
		g_RnInterface = NULL;
	}

	return Unlock(RTN_SUCCESS);
}

SERVODRIVERCOMDLL_API short GT_RN_PostPci(void* gPci, Uint8 station_id)
{
	if (g_RnMotionCom)
	{
		return g_RnMotionCom->PostPci((TPci*)gPci, station_id);
	}
	return RTN_OBJECT_UNCREATED;
}
SERVODRIVERCOMDLL_API short GT_RN_SendPci(void* gPci, Uint8 station_id)
{
	if (g_RnMotionCom)
	{
		return g_RnMotionCom->SendPci((TPci*)gPci, station_id);
	}
	return RTN_OBJECT_UNCREATED;
}

SERVODRIVERCOMDLL_API short  RN_ComHandler(Uint8 mode, Uint8 cmd, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id,
	Uint8 des_c, Uint8 needReq /*= TRUE*/, Uint8 addr_mod /*= 1*/, Uint8 wait_level /*= RN_OP_WAIT_DEFAULT*/, Uint8 dsitance /*= 0xf0*/)
{

	if (g_RnMotionCom)
	{
		return (g_RnInterface->RnNetCom(mode, cmd, byte_addr, pData, word_num, des_id, des_c, needReq, addr_mod, wait_level, dsitance));
	}
	return RTN_OBJECT_UNCREATED;
}

SERVODRIVERCOMDLL_API short  RN_GetCns(COMMON_NET_STATUS* pCns, Uint8 dsitance)
{
	if (g_RnMotionCom)
	{
		return (g_RnInterface->RnNetGetCns(pCns, dsitance));
	}
	return RTN_OBJECT_UNCREATED;
}

SERVODRIVERCOMDLL_API short RN_FpgaUpate(char* filePath, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16 stationId /*= 0xf0*/)
{
	int16 progress;
	void* ptr = ptrv;
// 	g_RnInterface = new CRingNetInterface;
// 	CComBase* pData = g_RnInterface;
// 	pData->ComRdFpgaHandle(0, &progress, 1, 0, NULL);

	if (Net_Rt_Lock_Err == TryLock())
	{
		return Net_Rt_Lock_Err;
	}
	CFPGAUpdate firmware;
	if (g_RnInterface == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	CComBase* pComBase = g_RnInterface;
	firmware.m_pCom = &pComBase;
	firmware.m_des_id = stationId;
	//百分比进度
	progress = 0;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);

	int16 rtn = 0;
	//复位变量

	//百分比进度
	progress = 5;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);

	rtn = firmware.WriteFPGAFileToFlash(filePath, tpfUpdataProgressPt, ptr, progress);

	if (rtn != 0)
	{
		return Unlock(rtn);
	}

	//百分比进度
	progress = 100;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptr, &progress);

	return Unlock(rtn);
}
