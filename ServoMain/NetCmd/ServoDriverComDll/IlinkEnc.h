#pragma once
#include "RingNetPacket.h"
#pragma pack(1)
typedef struct  
{
	Uint8 device_cnt;
	Uint8 append_cnt;
	Uint8 packet_num;
	Uint8 res;
}StIlinkHead;


typedef struct 
{
	Uint8 pre[8];
	StRnHeadFormat head;
	Uint8 dataSection[RN_MAX_PACKET_LEN];	// user data section
}StIlinkPacket;
#pragma pack()

class CIlinkEnc
{
public:
	CIlinkEnc();
	~CIlinkEnc();
};

