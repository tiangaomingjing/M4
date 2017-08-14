#pragma once
#include "DeviceDataBase.h"
#include "StRingNetRegDef.h"

class CRnDeviceDataBase :
	public CDeviceDataBase
{
public:
	CRnDeviceDataBase();
	virtual ~CRnDeviceDataBase();
public:
	COMMON_NET_STATUS		m_CNS;
	Uint8					m_index;

	Uint8					m_rx_index;
	Uint32					m_lose_cnt;
	Uint32					m_rx_cnt;

	void* m_pData;
public:
	void CheckRxIndex(Uint8 index);
};

