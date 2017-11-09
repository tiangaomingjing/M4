#pragma once
#include "MotionCtrlCom.h"
#define COMMAND_DATA_LEN               32

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

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

class SERVODRIVERCOMDLL_API CGTCmdCtrl
{
public:
	CGTCmdCtrl();
	~CGTCmdCtrl();
public:
	TPci	 gPci;
	TCommand gCommand;
protected:
	CMotionCtrlCom* m_pDriver;
protected:
	Uint8 m_dsp_tag_id;

public:
	short Initial(CMotionCtrlCom* pDriver);
	virtual short GetComProtocolType(){ return m_pDriver->GetComProtocolType(); };
	short SetTagId(Uint8 id)
	{
		m_dsp_tag_id = id;
		return  RTN_SUCCESS;
	}
	short GetTagId(Uint8* id)
	{
		*id = m_dsp_tag_id;
		return RTN_SUCCESS;
	}
public:
	void InitCmd(unsigned short cmd);
	void Add16(short data16);
	void Add32(long data32);
	void Add32F(double data);
	void Add48F(double data);
	void AddFloat(float data);
	void AddFloat64(double data);
	void Get16(short *pData16);
	void Get32(long *pData32);
	void Get32F(double *pData);
	void Get48F(double *pData);
	void GetFloat(double *pData);
	void GetFloat64(double *pData);

	short SendCommand(void);
};

