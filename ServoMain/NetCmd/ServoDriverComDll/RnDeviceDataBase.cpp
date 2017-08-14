#include "stdafx.h"
#include "RnDeviceDataBase.h"


CRnDeviceDataBase::CRnDeviceDataBase()
{
	m_lose_cnt = 0;
	m_rx_cnt = 0;
	m_rx_index = 0;
	m_pData = NULL;
}


CRnDeviceDataBase::~CRnDeviceDataBase()
{
}

void CRnDeviceDataBase::CheckRxIndex(Uint8 index)
{
	m_rx_cnt++;
	if (((m_rx_index + 1) & 0x3F) != (index & 0x3F))
	{
		m_lose_cnt++;
	}
	m_rx_index = index;
	return;
}