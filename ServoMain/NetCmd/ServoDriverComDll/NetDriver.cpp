#include "stdafx.h"
#include <process.h>
//#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Iphlpapi.h>  
using namespace std;

#include "NetDriver.h"
//#include "pcap/pcap.h"
#include "pcap.h"
#include "Win32-Extensions.h"
//#include <synchapi.h >

#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库  

unsigned __stdcall NetReceiveThread(void *para);

char		errbuf[PCAP_ERRBUF_SIZE];
CNetDriver::CNetDriver()
{
	smac[0] = 0x55;
	smac[1] = 0x55;
	smac[2] = 0x55;
	smac[3] = 0x55;
	smac[4] = 0x55;
	smac[5] = 0x55;
	
	memset(filter, 0, 128);
	sprintf_s(filter, sizeof(filter), "ether src %02lx:%02lx:%02lx:%02lx:%02lx:%02lx", smac[0], smac[1], smac[2], smac[3], smac[4], smac[5]);

	receiveThread = NULL;
//	m_com_tx_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_adapter_inf = NULL;
	m_rx_thread_status = 0;
	m_adapter_handle = NULL;
	iSuccessNum = 0;
	m_com_tx_cs = NULL;
	m_com_rx_cs = NULL;
	m_com_tx_cs = (void*) new CRITICAL_SECTION;
	m_com_rx_cs = (void*) new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);//
	InitializeCriticalSection((CRITICAL_SECTION*)m_com_rx_cs);//
	ScanAdapterNun(m_adapter_num);
}


CNetDriver::~CNetDriver()
{
	CloseAdapter();
	if (m_com_tx_cs)
	{
		DeleteCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		delete m_com_tx_cs;
		m_com_tx_cs = NULL;
	}
	if (m_com_rx_cs)
	{
		DeleteCriticalSection((CRITICAL_SECTION*)m_com_rx_cs);
		delete m_com_rx_cs;
		m_com_rx_cs = NULL;
	}
}

void* CNetDriver::GetNetDriverHandle()
{
	return (void*)this;
}

short CNetDriver::ScanAdapterNun(Uint8& adapter_num)
{
	pcap_if_t*	alldevs;
	pcap_if_t*	devs;
//	char		errbuf[PCAP_ERRBUF_SIZE];
	adapter_num = 0;
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
		return Net_Rt_Not_Get_Net_DevList;

	if (NULL == alldevs)
		return Net_Rt_Not_Find_Net_Device;


	devs = alldevs;
	adapter_num++;
	while (devs->next != NULL)
	{
		adapter_num++;
		devs = devs->next;
	}
	pcap_freealldevs(alldevs);
	return RTN_SUCCESS;
}
short CNetDriver::GetAdapterInf(char* devs_name)
{
	MIB_IFTABLE   *pIfTable = NULL;
	ULONG          dwSize = 0;
	DWORD          dwRet;

	if (devs_name == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (m_adapter_inf) //clear the memory
	{
		delete m_adapter_inf;
		m_adapter_inf = NULL;
	}
	dwRet = GetIfTable(pIfTable, &dwSize, TRUE);//just get the dwSize
	if (dwRet != ERROR_INSUFFICIENT_BUFFER)
	{
		return RTN_IMPOSSIBLE_ERR;
	}
	pIfTable = (MIB_IFTABLE *) new char[dwSize];
	if (pIfTable == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	dwRet = GetIfTable(pIfTable, &dwSize, TRUE);
	if (dwRet == NO_ERROR)
	{
//		printf("dwNumEntries = %u\n", pIfTable->dwNumEntries);
		int16 beg_index_a = 0;
		int16 beg_index_b = 0;
		for (beg_index_a = 0; beg_index_a < 256; beg_index_a++)
		{
			if (devs_name[beg_index_a] == 0)
			{
				delete pIfTable;
				return RTN_SUCCESS;
			}
			if (devs_name[beg_index_a] == '{')
			{
				break;
			}
		}

		for (Uint32 i = 0; i < pIfTable->dwNumEntries; i++)
		{

//			if ((pIfTable->table[i]).dwType == MIB_IF_TYPE_ETHERNET && (pIfTable->table[i]).dwAdminStatus == 1 && ((pIfTable->table[i]).dwPhysAddrLen == 6))// && ((pIfTable->table[i].dwOperStatus) == MIB_IF_OPER_STATUS_OPERATIONAL))//MIB_IF_TYPE_ETHERNET ->以太网
			if ((pIfTable->table[i]).dwAdminStatus == 1 && ((pIfTable->table[i]).dwPhysAddrLen == 6))// && ((pIfTable->table[i].dwOperStatus) == MIB_IF_OPER_STATUS_OPERATIONAL))//MIB_IF_TYPE_ETHERNET ->以太网
			{
				for (beg_index_b = 0; beg_index_b < 256; beg_index_b++)
				{
					if (pIfTable->table[i].wszName[beg_index_b] == 0)
					{
						delete pIfTable;
						return RTN_SUCCESS;
					}
					if (pIfTable->table[i].wszName[beg_index_b] == L'{')
					{
						break;
					}
				}

		
				for (int j = 0; j + beg_index_b < 256; j++)
				{
					if (devs_name[j + beg_index_a] != pIfTable->table[i].wszName[j + beg_index_b])
					{
						break;
					}
					else if (devs_name[j + beg_index_a] == '}')
					{
						MIB_IFROW * adapter_inf = (new MIB_IFROW);
						*adapter_inf = pIfTable->table[i];
						m_adapter_inf = adapter_inf;
						delete pIfTable;
						return RTN_SUCCESS;
					}
				}
// 				printf("table[%1d].dwIndex = %u\n", i, (pIfTable->table[i]).dwIndex);
// 				printf("        dwType  = %u\n", (pIfTable->table[i]).dwType);
// 				printf("         dwSpeed = %u\n", (pIfTable->table[i]).dwSpeed);
// 				wcout << (pIfTable->table[i]).wszName << endl;
			}
		}
	}
	delete pIfTable;
	return RTN_SUCCESS;
}

short CNetDriver::OpenAdapter(Uint8 adapter_id)
{
	pcap_if_t*	alldevs;
	pcap_if_t*	devs;
//	char		errbuf[PCAP_ERRBUF_SIZE];
	if (m_adapter_handle)
	{
		CloseAdapter();
	}
	m_adapter_id = adapter_id;
	//获取设备列表
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
		return Net_Rt_Not_Get_Net_DevList;

	if (NULL == alldevs)
		return Net_Rt_Not_Find_Net_Device;

	devs = alldevs;
//	char* strAdapterName;
	for (int i = 0; i < adapter_id; i++)
	{
		devs = devs->next;
		if (devs == NULL)
		{
			pcap_freealldevs(alldevs);
			return RTN_PARAM_OVERFLOW;
		}
	}

	if ((m_adapter_handle = /*pcap_open(devs->name,*/pcap_open_live(devs->name,		// name of the device
		65536,			// portion of the packet to capture. // 65536 grants that the whole packet will be captured on all the MACs.					
		1,				//PCAP_OPENFLAG_PROMISCUOUS  promiscuous mode (nonzero means promiscuous)
		-1,				// read timeout
		errbuf			// error buffer
		)) == NULL)
	{
		//释放设备
		pcap_freealldevs(alldevs);
		return Net_Rt_Open_Device_Err;
	}

	GetAdapterInf(devs->name);

	pcap_freealldevs(alldevs);


// 	/*设置用户层缓冲*/
// 	if (pcap_setuserbuffer((pcap_t*)m_adapter_handle, 1 * 1024 * 1024/*500000000*/) == -1)
// 	{
// 		printf("Can't set up the user buffer!");
// 		return -1;
// 	}
// 
// 	/*设置从内核缓冲区到用户缓冲区的最小传递量*/
// 	if (pcap_setmintocopy((pcap_t*)m_adapter_handle, 25600/*3840000*/) == -1)
// 	{
// 		printf("Can,t set the transmition between the kernel buffer and user buffer!");
// 		return -1;
// 	}
// 
// 	/*设置内核缓冲*/
// 	if (pcap_setbuff((pcap_t*)m_adapter_handle, 20 * 1024 * 1024/*100000000*/) == -1)
// 	{
// 		printf("Can't set up the kernel buffer!");
// 		return -1;
// 	}

// 	if (pcap_setbuff((pcap_t*)m_adapter_handle, 1 * 1024 * 1024) == -1)
// 	{
// 		return RTN_MALLOC_FAIL;
// //		TRACE("-------ERROR: 设置内核缓冲区大小失败---------------\n");
// 	}
// 
// 	if (pcap_setuserbuffer((pcap_t*)m_adapter_handle, 1 * 1024 * 1024) == -1)
// 	{
// 		return RTN_MALLOC_FAIL;
// 		//		TRACE("-------ERROR: 设置内核缓冲区大小失败---------------\n");
// 	}

// 	sprintf_s(filter, sizeof(filter), "ether dst %02lx:%02lx:%02lx:%02lx:%02lx:%02lx", smac[0], smac[1], smac[2], smac[3], smac[4], smac[5]);

	//compile the filter
	bpf_u_int32			NetMask;
	struct bpf_program	fcode;
	NetMask = 0xffffff;
	if (pcap_compile((pcap_t*)m_adapter_handle, &fcode, filter, 1, NetMask) < 0)
	{
		pcap_close((pcap_t*)m_adapter_handle);
		m_adapter_handle = NULL;
		return RN_Net_Rt_Complie_Err;
	}
	if (pcap_setfilter((pcap_t*)m_adapter_handle, &fcode) < 0)
	{
		pcap_close((pcap_t*)m_adapter_handle);
		m_adapter_handle = NULL;
		return RN_Net_Rt_SetFilter_Err;
	}

	//开始接收,启动一个线程
	if (receiveThread != NULL)
	{
		return RTN_SUCCESS;
	}

	m_rx_thread_status = 1;
	receiveThread = (HANDLE)_beginthreadex(NULL, 0, &NetReceiveThread, GetNetDriverHandle(), 0, NULL);
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS/*HIGH_PRIORITY_CLASS*/);
	processLevel = GetPriorityClass(GetCurrentProcess());
	SetThreadPriority(receiveThread, THREAD_PRIORITY_TIME_CRITICAL);
	threadLevel = GetThreadPriority(receiveThread);
	

	return RTN_SUCCESS;
}

short CNetDriver::CloseAdapter()
{
	if (m_rx_thread_status == 1)
	{
		m_rx_thread_status = 0;
		for (int i = 0; i < 100; i++)
		{
			Sleep(2);
			if (m_rx_thread_status == 2)
			{
				break;
			}
		}
		receiveThread = NULL;
	}
	if (m_adapter_handle)
	{
		pcap_close((pcap_t*)m_adapter_handle);
		m_adapter_handle = NULL;
	}
	if (m_adapter_inf)
	{
		delete m_adapter_inf;
		m_adapter_inf = NULL;
	}

	m_rx_thread_status = 0;

	return RTN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
short CNetDriver::TxPacket(Uint8* pData, Uint16 tx_byte_num)
{
	Uint8 buffer[NET_PACKET_SIZE_MIN];
	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	if (pData == NULL)
	{
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_NULL_POINT;
	}
	if (m_adapter_handle == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	if (tx_byte_num < NET_PACKET_SIZE_MIN - 4)
	{
		memcpy_s( (void*)buffer, sizeof(Uint8)*tx_byte_num, (void*)pData, sizeof(Uint8)*tx_byte_num );
		if (pcap_sendpacket((pcap_t*)m_adapter_handle, buffer, NET_PACKET_SIZE_MIN) != 0)
		{
			LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
			return Net_Rt_Send_Err;
		}
	}
	else
	{
		if (pcap_sendpacket((pcap_t*)m_adapter_handle, pData, tx_byte_num) != 0)
		{
			LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
			return Net_Rt_Send_Err;
		}
	}
	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return Rt_Success;
}
////////////////////////////////////////////////////////////////////////////
short CNetDriver::CloseThreadRx()
{
	EnterCriticalSection((CRITICAL_SECTION*)(m_com_rx_cs));
	return RTN_SUCCESS;
}
short CNetDriver::OpenThreadRx()
{
	LeaveCriticalSection((CRITICAL_SECTION*)(m_com_rx_cs));
	return RTN_SUCCESS;
}
bool CNetDriver::TryThreadRx()
{
	return (TryEnterCriticalSection((CRITICAL_SECTION*)(m_com_rx_cs)) == TRUE);
}

short CNetDriver::RxPacketDecoder(const void* src, const Uint16 src_len, void* des, Uint16& des_len)
{
	if (src == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (des == NULL)
	{
		return RTN_NULL_POINT;
	}
	memcpy_s(des, src_len, src, src_len);
	des_len = src_len;
	return RTN_SUCCESS;
}
/////////////////////判断有没有报文过来///////////
short CNetDriver::CheckAdapterPacket(int& packet_num)
{
#ifdef MY_CNetDriver_DEBUG_
	return RxPacketDecoder(NULL, 0, m_rx_buffer, m_rx_packet_length);
#endif // MY_CNetDriver_DEBUG_
	pcap_pkthdr *header = NULL;
	short rtn;
	const Uint8 *pTempRx = NULL;
	if (m_adapter_handle == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	packet_num = pcap_next_ex((pcap_t*)m_adapter_handle, &header, &pTempRx);
	if (packet_num <= 0)
	{
		return RTN_SUCCESS;
	}
	if (NULL == header || header->caplen <= MIN_PACKET_LEN)
	{
		return RTN_PACKET_ERR;
	}
	//QueryPerformanceCounter(&g_Time3);
	iSuccessNum++;
	rtn = RxPacketDecoder(pTempRx, header->caplen, m_rx_buffer, m_rx_packet_length);
	
	return rtn;
}
/////////////////////接收报文线程，当处于线程接收模式，所有的报文都是由该函数处理///////////
unsigned __stdcall NetReceiveThread(void *para)
{
	/* 开始捕获 */

	CNetDriver* pDriver = (CNetDriver*)para;
	pcap_pkthdr *header = NULL;
	int32 nret = -1;
	const Uint8 *pTempRx = NULL;
	int32 iCount = 0;
	int32 iSuccessNum = 0;
	bool bSuccess = false;
	int packet_num;
	while (1)
	{
		if (pDriver->m_rx_thread_status == 0)
		{
			pDriver->m_rx_thread_status = 2;
			return RTN_SUCCESS;
		}
		if (pDriver->TryThreadRx())
		{
//			int i;
// 			for (i = 0; i < 1000;i++)
// 			{
// 				pDriver->CheckAdapterPacket(packet_num);
// 				if (packet_num == 0)
// 				{
// 					break;
// 				}
// 			}
			pDriver->CheckAdapterPacket(packet_num);
			pDriver->OpenThreadRx();
			if (packet_num <= 0)
			{
				Sleep(5);
			}
		}
	}
	return RTN_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////接收报文线程，当处于线程接收模式，所有的报文都是由该函数处理///////////
// void my_packet_handler(u_char *para, const struct pcap_pkthdr *header, const Uint8 *pkt_data);
// unsigned __stdcall NetReceiveThread(void *para)
// {
// 	/* 开始捕获 */
// 
// 	CNetDriver* pDriver = (CNetDriver*)para;
// 	pcap_pkthdr *header = NULL;
// 	int32 nret = -1;
// 	const Uint8 *pTempRx = NULL;
// 	int32 iCount = 0;
// 	int32 iSuccessNum = 0;
// 	bool bSuccess = false;
// 	int packet_num;
// 	while (1)
// 	{
// 		short rtn = pcap_dispatch((pcap_t*)(pDriver->m_adapter_handle), -1, my_packet_handler, (u_char*)para);
// 		if (-1 == rtn)
// 		{
// 			printf("---- pcap_loop error\n");
// 		}
// 		else if (-2 == rtn)
// 		{
// 			printf("---- pcap_loop break!\n");
// 		}
// 	}
// 	return RTN_SUCCESS;
// }
// 
// /* 每次捕获到数据包时，libpcap都会自动调用这个回调函数 */
// // typedef void(*pcap_handler)(u_char *, const struct pcap_pkthdr *,
// // 	const u_char *);
// void my_packet_handler(u_char *para, const struct pcap_pkthdr *header, const Uint8 *pkt_data)
// {
// 
// 	CNetDriver* pDriver = (CNetDriver*)para;
// //	pcap_pkthdr *header = NULL;
// 	int32 nret = -1;
// //	const Uint8 *pTempRx = NULL;
// 	int32 iCount = 0;
// 	int32 iSuccessNum = 0;
// 	bool bSuccess = false;
// 	int packet_num;
// 
// 	short rtn;
// 	const Uint8 *pTempRx = pkt_data;
// 
// 	if (NULL == header || header->caplen <= CNetDriver::MIN_PACKET_LEN)
// 	{
// 		return ;
// 	}
// 	//QueryPerformanceCounter(&g_Time3);
// 	iSuccessNum++;
// 
// 	rtn = pDriver->RxPacketDecoder(pTempRx, header->caplen, pDriver->m_rx_buffer, pDriver->m_rx_packet_length);
// 
// 	return ;
// }
//////////////////////////////////////////////////////////////////////////
