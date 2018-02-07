#pragma once
#include "RingNetDriver.h"

/************************************************************************/
/* 定义通信类型                                                        */
/************************************************************************/
typedef enum
{
	COM_PROTOCO_NET,			//裸机网口
	COM_PROTOCO_TCPIP,		//TCP/IP协议网口
	COM_PROTOCO_USB2UART,		//usb转串口
	COM_PROTOCO_VIRTUAL,		//虚拟设备
	COM_PROTOCO_RINGNET,		//等环网
	COM_PROTOCO_MAX			//最大值
}COM_PROTOCOL_TYPE;

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

class SERVODRIVERCOMDLL_API CComBase
{
public:
	CComBase();
	virtual ~CComBase();
protected:
	short m_protocol_type;
public:

	virtual short GetComProtocolType(){ return m_protocol_type; };
	virtual short ComWrFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam){ return NULL; };
	virtual short ComRdFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam){ return NULL; };
};

