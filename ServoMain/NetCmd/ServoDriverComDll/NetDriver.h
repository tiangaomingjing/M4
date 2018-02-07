#pragma once

#include "Basetype_def.h"
#include "BaseReturn_def.h"
const Uint16 NET_PACKET_SIZE_MIN = 60;// 64 - 4crc;
//
/*
//////////////////////////////////////////////////////////////////////////
����Ϊ����ײ��࣬��������
1��ɨ�����п���������Ȼ����ֽ����̡߳�
2���ڲ����������緢�ͺ�����������������
3���˴������緢�ͺ���������ϵ���ĸ�ʽ�������ǽ�ָ�����ȵı������ⷢ�͡��ڲ�ʵ������С�����Ĳ��������
4�����ĵĴ�����RxPacketDecoderΪ�鹹�����������ع���
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
	static short ScanAdapterNun(Uint8& adapter_num);//ɨ��������Ϣ����ȡ����������
	virtual short OpenAdapter(Uint8 adapter_id);//ɨ��������Ϣ����ָ��������
	virtual short CloseAdapter();//�رյ�ǰ������

	short TxPacket(Uint8* pData, Uint16 tx_byte_num);//����winpcap����������������
	virtual short RxPacketDecoder(const void* src , const Uint16 src_len, void* des, Uint16& des_len);//�յ�����������������н��н������ú��������鹹��
	virtual void* GetNetDriverHandle();//��ȡ�������thisָ�롣
	virtual short CloseThreadRx();//��ͣ�����̵߳Ľ��ա���������ʵʱ����������Ƿ��б���
	virtual short OpenThreadRx();//���������̴߳�������
	virtual bool TryThreadRx();//��Ҫ���ڽ����߳��ж��Ƿ���Ҫ�����������ݡ�

private:
	short GetAdapterInf(char* devs_name);

public:
	short CheckAdapterPacket(int& packet_num);//�ж���������û���յ����ݡ�
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
	static const int32 	MIN_PACKET_LEN = 34;							// ���ذ���С��������
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
	Uint8 m_adapter_num;						//��������
	//////////////////////////////////////////////////////////////////////////
	Uint8 m_adapter_id;							//��ǰ��������ID
	void* m_adapter_handle;						//��ǰ���������
	
	void*  m_adapter_inf;					//��ǰ��������ϸ��Ϣ
	Uint32	 m_adapter_speed;						//��ǰ���������ٶ�
//	pcap_t*	m_pcap_adhandle;							//wpcap����ָ��
//	int8 adapter[1024];
//	int32 port;

protected:

	int32 threadLevel;
	int32 processLevel;
	void* receiveThread;
	char *	m_adapterName;						//��������������
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

