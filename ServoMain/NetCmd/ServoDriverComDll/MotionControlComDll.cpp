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
// #include "FirmwareDl.h"
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
