#pragma once
#include "NetDriver.h"
#include "RingNetPacket.h"
#include "RnDeviceDataBase.h"
#include "StRingNetComUser.h"
#include "UserResp.h"

const Uint16 RN_PACKET_LEN_MAX = 510;
const Uint16 RN_USER_TX_LEN_MIN = ((NET_PACKET_SIZE_MIN - 8 - 2 - 1)+1) & 0xFFFE;//(NET_PACKET_SIZE_MIN - sizeof(StRnHeadFormat) - sizeof_len - 0xff)
const Uint16 RN_USER_TX_LEN_MAX = (RN_PACKET_LEN_MAX - 8 - 14 - 8 - 2 - 1 - 4) & 0xFFFE;//RN_PACKET_LEN_MAX - 8pre_code-14 ethernet head, 8 ringnet head, 2 length, 1 end flag, 4 crc

class CRingNetDriver :
	public CNetDriver
{
public:
	CRingNetDriver();
	virtual ~CRingNetDriver();
	virtual short OpenAdapter(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CloseAdapter();//关闭当前网卡。
	short TxPacket(StRnPacket* packet);
	bool m_none_gigabit_device;
	bool m_none_operate_device;
public:
	CRnDeviceDataBase * m_pRnDevice[MAX_STATION_NUM];
	CRnDeviceDataBase * m_pRnDeviceOnline[MAX_STATION_NUM];
	Uint8				m_device_num;
	Uint8				m_topology_update;

	Uint8				m_index[MAX_STATION_NUM];

// 	short(*UserHandleRespFunctionNomal)(StUserPacket* packet);
// 	short(*UserHandleRespFunctionPC)(StUserPacket* packet);
// 	short(*UserHandleRespFunctionMotion)(StUserPacket* packet);
// 	short(*UserHandleRespFunctionDriver)(StUserPacket* packet);
	CUserResp *m_pUserHandleRespFunctionNomal;
	CUserResp *m_pUserHandleRespFunctionPC;
	CUserResp *m_pUserHandleRespFunctionMotion;
	CUserResp *m_pUserHandleRespFunctionDriver;

protected:
	//	CRITICAL_SECTION m_com_tx_cs;
	void* m_com_tx_cs;                 //CRITICAL_SECTION for tx receive 
	void* m_com_rx_cs;                 //CRITICAL_SECTION for rx receive

protected:
	short CheckRingNetProtocol(); //check whether the adatpter connet with the ringnet device 
	virtual short RxPacketDecoder(const void* src, const Uint16 src_len, void* des, Uint16& des_len);//收到的数据在这个函数中进行解析。该函数可以虚构。
	virtual short DecoderUserPacket(StRnPacket* pPacket);
	virtual short RespUserPacket(StRnPacket* pPacket);

public:
	static short RingNetBufferToCnsReg(Uint16* pData, COMMON_NET_STATUS* pCNS);

public:
	static short FormatRingNetUserPakcet(
		StRnPacket* pPacket,
		Uint8 des_id, //
		Uint8 des_ch, //
		Uint16 datalenth,// 
		Uint8 cmd, //
		Uint8 mode, //
		Uint16 addr,//
		Uint16 num,//
		Uint8 NeedReq, // 
		Uint8 IsReq, //
		Uint8 RespOk = 1,
		Uint8 delta = 1,//
		Uint8 max_path = 255
		);
	static short CalcRingNetHeadCheckSum(StRnHeadFormat* pData);
	static bool CheckRingNetHeadCheckSum(StRnHeadFormat* pData);

};

