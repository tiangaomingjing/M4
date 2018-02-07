#pragma once

#include "Basetype_def.h"
#include "BaseReturn_def.h"
const Uint16 NET_PACKET_SIZE_MIN = 60;// 64 - 4crc;
//
/*
//////////////////////////////////////////////////////////////////////////
该类为网络底层类，它的作用
1：扫描所有可用网卡，然后出现接收线程。
2：内部构建了网络发送函数和网络解包函数。
3：此处的网络发送函数，不关系报文格式，仅仅是将指定长度的报文往外发送。内部实现了最小包长的补零操作。
4：报文的处理函数RxPacketDecoder为虚构函数，可以重构。
*/

//#define MY_CNetDriver_DEBUG_ 

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif
class SERVODRIVERCOMDLL_API CNetDriver
{
public:
	CNetDriver();
	virtual ~CNetDriver();
public:
	static short ScanAdapterNun(Uint8& adapter_num);//扫描网卡信息，获取网卡个数。
	virtual short OpenAdapter(Uint8 adapter_id);//扫描网卡信息，打开指定网卡。
	virtual short CloseAdapter();//关闭当前网卡。

	short TxPacket(Uint8* pData, Uint16 tx_byte_num);//调用winpcap发送数据至网卡。
	virtual short RxPacketDecoder(const void* src , const Uint16 src_len, void* des, Uint16& des_len);//收到的数据在这个函数中进行解析。该函数可以虚构。
	virtual void* GetNetDriverHandle();//获取本对象的this指针。
	virtual short CloseThreadRx();//暂停接收线程的接收。测试用于实时监测网络中是否有报文
	virtual short OpenThreadRx();//启动接收线程处理数据
	virtual bool TryThreadRx();//主要用于接收线程判断是否需要主动接收数据。

private:
	short GetAdapterInf(char* devs_name);

public:
	short CheckAdapterPacket(int& packet_num);//判断网络中有没有收到数据。
public:
	Uint8 smac[6];
	int8 filter[128];
private:
//	CRITICAL_SECTION m_com_tx_cs;
	void* m_com_tx_cs;                 //CRITICAL_SECTION for tx receive 
	void* m_com_rx_cs;                 //CRITICAL_SECTION for rx receive

	int iSuccessNum;
public:
	Uint16 m_rx_thread_status;
public:
	static const Uint16 MAX_PACKET_SZIE = 16384;// 1024;
	static const int32 	MIN_PACKET_LEN = 34;							// 返回包最小长度限制
	Uint16 m_tx_packet_length;
	Uint8 m_tx_buffer[MAX_PACKET_SZIE];

	Uint16 m_rx_packet_length;
	Uint8 m_rx_buffer[MAX_PACKET_SZIE];
	
//	void* m_pcap_pkthr;
//	pcap_pkthdr *header;
// public:
// 	static char		errbuf[256];// PCAP_ERRBUF_SIZE];
protected:
public:
	Uint8 m_adapter_num;						//网卡个数
	//////////////////////////////////////////////////////////////////////////
	Uint8 m_adapter_id;							//当前打开网卡的ID
	void* m_adapter_handle;						//当前打开网卡句柄
	
	void*  m_adapter_inf;					//当前打开网卡详细信息
	Uint32	 m_adapter_speed;						//当前打开网卡的速度
//	pcap_t*	m_pcap_adhandle;							//wpcap对象指针
//	int8 adapter[1024];
//	int32 port;

protected:

	int32 threadLevel;
	int32 processLevel;
	void* receiveThread;
	char *	m_adapterName;						//网络适配器名称
public:
	inline void* GetAdapterHandle()
	{
		return m_adapter_handle;
	}

	inline Uint8 GetAllAdapterNun()
	{
		return m_adapter_num;
	}

public:
	Uint32 m_test;
};

