#pragma once
#include "StRingNetComUser.h"
class CUserResp
{
public:
	CUserResp();
	virtual ~CUserResp();
public:
	virtual short UserHandleRespFunction(StUserPacket* packet){ return 0; };
};