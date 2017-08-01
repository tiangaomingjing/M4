#include "stdafx.h"
#include "RnServoAxiMapping.h"
#include "RingNetDeviceDef.h"


CRnServoAxiMapping::CRnServoAxiMapping()
{
	m_axi_num = 0;
	m_dsp_num = 0;
	m_pDriver = NULL;
	for (int i = 0; i < RN_MAX_SERVO_AXI_NUM;i++)
	{
		m_axi_inf[i].m_station_id = RN_INVAVLID_STATION_ID;//
	}
}


CRnServoAxiMapping::~CRnServoAxiMapping()
{
}

short CRnServoAxiMapping::InitialMapping(CRingNetDriver* driver)
{
	if (driver == NULL)
		return RTN_NULL_POINT;
	m_pDriver = driver;
	m_axi_num = 0;
	m_dsp_num = 0;
	for (Uint8 i = 0; i < driver->m_device_num;i++)
	{
		switch (driver->m_pRnDeviceOnline[i]->m_staion_type)
		{
		case TB_GTSD13 :
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;
			m_dsp_num++;
			break;
		case TB_GTSD21 :
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			break;
		case TB_GTDS41 :
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			//////////////////////////////////////////////////////////////////////////
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_PCI_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_PCI_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			break;
		case TB_GTSD61 :
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_DSP_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			//////////////////////////////////////////////////////////////////////////
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_PCI_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_PCI_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			//////////////////////////////////////////////////////////////////////////
			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_EXT_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 0;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_axi_inf[m_axi_num].m_station_id = driver->m_pRnDeviceOnline[i]->m_station_id;
			m_axi_inf[m_axi_num].m_station_ch = RN_EXT_CH_ID;
			m_axi_inf[m_axi_num].m_axi_id_in_dsp = 1;
			m_axi_inf[m_axi_num].m_dsp_id = m_dsp_num;
			m_axi_num++;

			m_dsp_num++;
			//////////////////////////////////////////////////////////////////////////
			break;
		default:
			break;
		}
	}
	return RTN_SUCCESS;
}
Uint16 CRnServoAxiMapping::ConvertAxiToStationId(int16 axi_id)
{
	if (axi_id < m_axi_num)
	{
		return (m_axi_inf[axi_id].m_station_id << 8) | m_axi_inf[axi_id].m_station_ch;
	}
	return 0xFFFF;
}

Uint16 CRnServoAxiMapping::ConvertAxiToSubAxiId(int16 axi_id)
{
	if (axi_id < m_axi_num)
	{
		return m_axi_inf[axi_id].m_axi_id_in_dsp;
	}
	return 0xFFFF;
}

Uint16 CRnServoAxiMapping::ConvertAxiToDspId(int16 axi_id)
{
	if (axi_id < m_axi_num)
	{
		return m_axi_inf[axi_id].m_dsp_id;
	}
	return 0xFFFF;
}

Uint16  CRnServoAxiMapping::ConvertDspToStationId(int16 dsp_id)
{
	int16 axi_id = dsp_id << 1;
	if (axi_id < m_axi_num)
	{
		return (m_axi_inf[axi_id].m_station_id << 8) | m_axi_inf[axi_id].m_station_ch;
	}
	return 0xFFFF;
}



Uint16 CRnServoAxiMapping::ConvertFpgaByteAddrByDspId(Uint16 dsp_id, Uint16 fpga_byte_address)
{
	int16 axi_id = dsp_id << 1;
	Uint16 base_address = 0;
	if (axi_id < m_axi_num)
	{
		Uint8 des_ch = m_axi_inf[axi_id].m_station_ch;
		switch (des_ch)
		{
		case RN_DSP_CH_ID:
			base_address = 0x0000;
			break;
		case RN_PCI_CH_ID:
			base_address = 0x8000;
			break;
		case RN_EXT_CH_ID:
			base_address = 0xC000;
			break;
		default:
			base_address = 0x0000;
			break;
		}
	}

	return base_address + fpga_byte_address;
}