#pragma once
#include "StRingNetComUser.h"

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif
class SERVODRIVERCOMDLL_API CUserResp
{
public:
	CUserResp();
	virtual ~CUserResp();
public:
	virtual short UserHandleRespFunction(StUserPacket* packet){ return 0; };
};