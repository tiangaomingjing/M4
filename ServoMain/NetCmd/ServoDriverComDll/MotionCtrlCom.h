#pragma once
#include "Basetype_def.h"
#include "RingNetInterface.h"

#ifndef RING_NET_MOTION_RESOURCE

#define RING_NET_MOTION_RESOURCE
typedef struct
{
	short flag;
	short len;
	short checksum;
	short data[32];
} TPci;

typedef struct
{
	short dataLen;
	short data[32];

	short resultLen;
	short result[32];
	short resultIndex;
}TCommand;

#endif

class CMotionCtrlCom
{
public:
	CMotionCtrlCom();
	~CMotionCtrlCom();
protected:
	CRingNetInterface * m_pDriver;
	enum ENUM_PCI_STS
	{
		PCI_IDLE = 0,
		PCI_PC_BUSY	= 1,
		PCI_PC_FINISH = 2,
		PCI_DSP_BUSY = 3,
		PCI_DSP_FINISH = 4
	};
public:
	short Initial(CRingNetInterface* pDriver);
	short PostPci(TPci* gPci, Uint8 station_id = 0xf0);
	short SendPci(TPci* gPci, Uint8 station_id = 0xf0);

	short PostPcie(TPci* gPci, Uint8 core_index, Uint8 station_id = 0xf0);
	short SendPcie(TPci* gPci, Uint8 core_index, Uint8 station_id = 0xf0);
	virtual short GetComProtocolType(){ return m_pDriver->GetComProtocolType(); };

};

