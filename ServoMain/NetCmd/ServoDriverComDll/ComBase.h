#pragma once
#include "RingNetDriver.h"

/************************************************************************/
/* ����ͨ������                                                        */
/************************************************************************/
typedef enum
{
	COM_PROTOCO_NET,			//�������
	COM_PROTOCO_TCPIP,		//TCP/IPЭ������
	COM_PROTOCO_USB2UART,		//usbת����
	COM_PROTOCO_VIRTUAL,		//�����豸
	COM_PROTOCO_RINGNET,		//�Ȼ���
	COM_PROTOCO_MAX			//���ֵ
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

