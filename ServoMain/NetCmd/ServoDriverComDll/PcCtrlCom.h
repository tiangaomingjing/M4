#pragma once

#include "Basetype_def.h"
#include "RingNetInterface.h"
#include "StFileOp.h"

#ifndef RING_NET_MOTION_RESOURCE

#define RING_NET_MOTION_RESOURCE
// typedef struct
// {
// 	short flag;
// 	short len;
// 	short checksum;
// 	short data[32];
// } TPci;
// 
// typedef struct
// {
// 	short dataLen;
// 	short data[32];
// 
// 	short resultLen;
// 	short result[32];
// 	short resultIndex;
// }TCommand;
// 
// 
// #define MAX_DEBUG_CMD_SIZE (256)
// #define MAX_DEBUG_CMD_DATA_SIZE (252)
// 
// typedef struct
// {
// 	uint16 cmd;
// 	uint16 sLen;
// 	uint16 param;
// 	uint16 checksum;
// 	uint16 pData[MAX_DEBUG_CMD_DATA_SIZE];
// }StUSER_PROTOCOL_DEBUG_CMD;

#endif

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif


class SERVODRIVERCOMDLL_API CPcCtrlCom
{
public:
	CPcCtrlCom();
	~CPcCtrlCom();
protected:
	CRingNetInterface * m_pDriver;
public:
	short Initial(CRingNetInterface* pDriver);
	short FileFuctionDriver(StFunction* param, unsigned char station_id, BOOL resp_req);
public:
	StFileOp m_file;
	short m_Thread_sleep_time;

};

