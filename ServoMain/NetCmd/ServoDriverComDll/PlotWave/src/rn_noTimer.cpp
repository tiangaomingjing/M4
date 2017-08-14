//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	RN no timer						 							//
//	file				:	rn_notimer.cpp												//
//	Description			:	rn can sent data automatic ,has callback thread to receive  //
//							data  so do not need another thread							//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2017/1/15	|	googoltech		|		2017 - 2020			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gdef.h"
#include "PlotWave.h"
#include "rn_noTimer.h"

CRn_NoTimer::CRn_NoTimer(void)
{

}

CRn_NoTimer::~CRn_NoTimer(void)
{

}

void CRn_NoTimer::StartNoTimer( int32 dspNo )
{
	//初始化cs
	if (dspNo < MAX_DSP_WAVE) InitializeCriticalSection(&g_cs_dsp[dspNo]);

// 	if (dspNo == GTSD_DSP_A)
// 	{
// 		//初始化cs
// 		InitializeCriticalSection(&g_cs_dspA);
// 	}
// 	else if (dspNo == GTSD_DSP_B)
// 	{
// 		//初始化cs
// 		InitializeCriticalSection(&g_cs_dspB);
// 	}
// 	else
// 	{ }
}

void CRn_NoTimer::StopNoTimer(int32 dspNo)
{
	if (dspNo < MAX_DSP_WAVE) DeleteCriticalSection(&g_cs_dsp[dspNo]);
	//删除关键区
// 	if (dspNo == GTSD_DSP_A)
// 	{
// 		DeleteCriticalSection(&g_cs_dspA);
// 	}
// 	else if (dspNo == GTSD_DSP_B)
// 	{
// 		DeleteCriticalSection(&g_cs_dspB);
// 	}
// 	else
// 	{ 
// 	}
}

void CRn_NoTimer::GetPlotWaveDataFromRn(int16 dsp_Number)
{
	if (dsp_Number < MAX_DSP_WAVE)
	{
		if (g_dsp_wave_prm[dsp_Number].cmd.bit.ENP)
		{
			g_plotWave->ReadPlotWaveDataFromFPGA(dsp_Number, g_dsp_wave_prm[dsp_Number], g_plotWave->m_comType);
		}
	}

// 	if (g_dspA_wave_prm.cmd.bit.ENP || g_dspB_wave_prm.cmd.bit.ENP)
// 	{		
// 		if (dsp_Number == GTSD_DSP_A)
// 		{
// 			//假如dspA画图使能
// 			if (g_dspA_wave_prm.cmd.bit.ENP)
// 			{
// 				g_plotWave->ReadPlotWaveDataFromFPGA(dsp_Number, g_dspA_wave_prm,g_plotWave->m_comType);
// 			}
// 		}
// 		else if (dsp_Number == GTSD_DSP_B)
// 		{
// 			//假如dspB画图使能
// 			if (g_dspB_wave_prm.cmd.bit.ENP)
// 			{
// 				g_plotWave->ReadPlotWaveDataFromFPGA(dsp_Number, g_dspB_wave_prm, g_plotWave->m_comType);
// 			}	
// 		}
// 		else
// 		{
// 
// 		}
// 	}
}

