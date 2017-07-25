#include "stdafx.h"
#include "RnDriverPlot.h"


CRnDriverPlot::CRnDriverPlot()
{
	m_pWaveList = NULL;
	m_wave_num = 0;
}

CRnDriverPlot::~CRnDriverPlot()
{
	if(m_pWaveList)
		delete []m_pWaveList;

	m_pWaveList = NULL;
	m_wave_num = 0;
}

int16 CRnDriverPlot::PW_CreateDspWave(Uint16 wave_num, Uint16* dsp_id_list)
{
	if (m_pWaveList)
		delete[]m_pWaveList;

	m_pWaveList = NULL;
	m_wave_num = wave_num;

	if (wave_num == 0)
	{
		return RTN_SUCCESS;
	}

	if (dsp_id_list == NULL)
	{
		return RTN_PARAM_ERR;
	}

	m_pWaveList = new CRnDriverWave[m_wave_num];
	if (m_pWaveList == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	for (int i = 0; i < wave_num; i++)
	{
		m_pWaveList[i].m_dsp_id = dsp_id_list[i];
	}
	return RTN_SUCCESS;
}
short CRnDriverPlot::ParseDspWaveData(StUserPacket* packet)
{
	if (packet == NULL)
	{
		return RTN_NULL_POINT;
	}
	Uint16 des_id = (packet->src_id) << 8 | (packet->src_ch);
	for (int i = 0; i < m_wave_num; i++)
	{
		if (des_id == m_pWaveList[i].m_dsp_id)
		{
			return m_pWaveList[i].ParseDspWaveData(des_id, packet->length, packet->pData);
		}
	}
	return RTN_OBJECT_UNCREATED;
}

int16 CRnDriverPlot::PW_PcGetDspWaveData(Uint16 dsp_station_id, double** data, Uint32& number)
{
	for (int i = 0; i < m_wave_num; i++)
	{
		if (dsp_station_id == m_pWaveList[i].m_dsp_id)
		{
			return m_pWaveList[i].PW_PcGetDspWaveData(data, number);
		}
	}
	return RTN_OBJECT_UNCREATED;
}

int16 CRnDriverPlot::PW_StartDspPlot(Uint16 dsp_station_id, Uint16 wave_num, Uint16 *wave_byte_size_list)
{
	for (int i = 0; i < m_wave_num; i++)
	{
		if (dsp_station_id == m_pWaveList[i].m_dsp_id)
		{
			return m_pWaveList[i].InitDspWaveVar(wave_num, wave_byte_size_list);
		}
	}
	return RTN_OBJECT_UNCREATED;
}

int16 CRnDriverPlot::PW_StopDspPlot(Uint16 dsp_station_id)
{
	for (int i = 0; i < m_wave_num; i++)
	{
		if (dsp_station_id == m_pWaveList[i].m_dsp_id)
		{
			return m_pWaveList[i].CloseDspWave();
		}
	}
	return RTN_OBJECT_UNCREATED;
}
