#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <Iphlpapi.h>  

#include "RingNetDriver.h"


CRingNetDriver::CRingNetDriver()
{
	m_none_gigabit_device = true;
	m_none_operate_device = true;
	int i;
// 	srand(time(0));/*设置种子,并生成伪随机序列*/
	for (i = 0; i < MAX_STATION_NUM; i++)
	{
		m_pRnDevice[i] = NULL;
		m_pRnDeviceOnline[i] = NULL;
		m_index[i] = 0;//rand()
	}
	m_device_num = 0;
	m_topology_update = 0;

	m_com_tx_cs = NULL;
	m_com_rx_cs = NULL;
	m_com_tx_cs = (void*) new CRITICAL_SECTION;
	m_com_rx_cs = (void*) new CRITICAL_SECTION;

	InitializeCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);//
	InitializeCriticalSection((CRITICAL_SECTION*)m_com_rx_cs);//
	m_pUserHandleRespFunctionNomal = NULL;
	m_pUserHandleRespFunctionPC = NULL;
	m_pUserHandleRespFunctionMotion = NULL;
	m_pUserHandleRespFunctionDriver = NULL;
}


CRingNetDriver::~CRingNetDriver()
{
	int i;
	for (i = 0; i < MAX_STATION_NUM; i++)
	{
		if (m_pRnDeviceOnline[i])
		{
			delete m_pRnDeviceOnline[i];
			m_pRnDeviceOnline[i] = NULL;
		}	
	}

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

short CRingNetDriver::OpenAdapter(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	short rtn;
	m_none_gigabit_device = TRUE;
	//百分比进度
	progress = 15;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptrv, &progress);
	for (int i = 0; i < m_adapter_num;i++)
	{
		//百分比进度
		progress = 15 + (i+i)*80/m_adapter_num;
		if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptrv, &progress);
		rtn = CNetDriver::OpenAdapter(i);
		if (rtn != RTN_SUCCESS)
			continue;
		if(m_adapter_inf == NULL)
			continue;
		MIB_IFROW* adapter_inf = (MIB_IFROW*)m_adapter_inf;
		if (adapter_inf->dwSpeed != 1000000000)// only support 1GHz
			continue;
		m_none_gigabit_device = FALSE;
		if (adapter_inf->dwOperStatus != IF_OPER_STATUS_OPERATIONAL)
			continue;
		m_none_operate_device = FALSE;
		rtn = CheckRingNetProtocol();
		if (m_device_num == 0)
		{
			continue;
		}
		Uint8 topology_update_tmp = m_topology_update;
		for (int j = 0; j < 10;j++)
		{
			rtn = CheckRingNetProtocol();
			if (rtn != RTN_SUCCESS)
			{
				continue;
			}
			if (topology_update_tmp == m_topology_update)
			{
				break;
			}
			topology_update_tmp = m_topology_update;
		}
		if (rtn == RTN_SUCCESS)
		{
			progress = 100;
			if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptrv, &progress);
			return RTN_SUCCESS;
		}
	}
	progress = 100;
	if (tpfUpdataProgressPt) (*tpfUpdataProgressPt)(ptrv, &progress);
	return RTN_INITIAL_ERR;
}

short CRingNetDriver::CloseAdapter()
{
	int i;
	for (i = 0; i < MAX_STATION_NUM; i++)
	{
		if (m_pRnDeviceOnline[i])
		{
			delete m_pRnDeviceOnline[i];
			m_pRnDeviceOnline[i] = NULL;
		}
		m_pRnDevice[i] = NULL;
	}
	m_none_gigabit_device = true;
	m_none_operate_device = true;
	m_device_num = 0;
	m_topology_update = 0;

	return CNetDriver::CloseAdapter();

}
short CRingNetDriver::RingNetBufferToCnsReg(Uint16* pData, COMMON_NET_STATUS* pCNS)
{
	pCNS->m_port_status.all = pData[0];
	pCNS->m_net_run_status.all = pData[1];
	pCNS->m_sync_cycle.all = pData[2];
	pCNS->m_online_msg.all = pData[3];
	pCNS->m_crc_ok_cnt_a_l.all = pData[4];
	pCNS->m_crc_ok_cnt_a_h.all = pData[5];
	pCNS->m_crc_err_cnt_a.all = pData[6];
	pCNS->m_station_msg.all = pData[7];

	pCNS->m_crc_ok_cnt_b_l.all = pData[8];
	pCNS->m_crc_ok_cnt_b_h.all = pData[9];
	pCNS->m_crc_err_cnt_b.all = pData[10];
	pCNS->m_station_id.all = pData[11];
	return RTN_SUCCESS;
}
short CRingNetDriver::CheckRingNetProtocol() //check whether the adatpter connet with the ringnet device 
{
	StRnPacket packet;
	short rtn;
	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);

	rtn = FormatRingNetUserPakcet(&packet, 0xFF, RN_FPGA_CH_ID,
		RN_USER_TX_LEN_MIN, RN_ARD, RN_MODE_MAIL, 0, (RN_USER_TX_LEN_MIN - 4) & 0x1FE, 
		RN_NEED_REQ, RN_ISNOT_REQ, 0, RN_ADDR_INC, 0xF0);

	CNetDriver::CloseThreadRx();

	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	for (int i = 0; i < 700; )
	{
		int packet_num = 0;
		rtn = CheckAdapterPacket(packet_num);
		if (rtn != RTN_SUCCESS)
		{
			Sleep(2);
			i++;
			continue;
		}
		if (packet_num <= 0)
		{
			Sleep(1);
			i++;
			continue;
		}
		StRnPacket* pRx_packet;
		StRnUserPayloadHead* pUser_payload_head;
		Uint8*				 pUser_data;
		pRx_packet = (StRnPacket*)m_rx_buffer;
		pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
		pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);
		if (pUser_payload_head->cmd == RN_ARD && pUser_payload_head->src_ch == RN_FPGA_CH_ID && 
			pUser_payload_head->start_addr_bit7_0 == 0 && pUser_payload_head->start_addr_bit15_8 == 0) //return CNS
		{

			RingNetBufferToCnsReg((Uint16*)pUser_data, &m_pRnDevice[pRx_packet->ringnet_head.src_id]->m_CNS);
			m_pRnDevice[pRx_packet->ringnet_head.src_id]->m_staion_type = m_pRnDevice[pRx_packet->ringnet_head.src_id]->m_CNS.m_station_msg.bit.station_msg;
		}
	}
	CNetDriver::OpenThreadRx();

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}

short CRingNetDriver::RespUserPacket(StRnPacket* pPacket)
{
#ifdef DEBUG
	return UserHandleRespFunctionDriver(NULL);
#endif
	short rtn;
	if (pPacket == NULL)
	{
		return RTN_SUCCESS;
	}
	StRnUserPayloadHead* pUser_payload_head;
	Uint8*				 pUser_data;
	pUser_payload_head = (StRnUserPayloadHead*)pPacket->dataSection;
	pUser_data = pPacket->dataSection + sizeof(StRnUserPayloadHead);

	StUserPacket user_packet;

	if (pPacket->ringnet_head.src_id == RN_FPGA_CH_ID)
	{
		return RTN_PACKET_ERR;
	}
	user_packet.src_id = pPacket->ringnet_head.src_id;
	user_packet.src_ch = pUser_payload_head->src_ch;
	user_packet.cmd = pUser_payload_head->cmd;
	user_packet.resp_req = pUser_payload_head->resp_req;
	user_packet.resp = 0;
	user_packet.resp_ok = 0;
	user_packet.length = (pUser_payload_head->len_bit8 << 8) + pUser_payload_head->len_low - 4;
	user_packet.pData = pUser_data;
	if (pUser_payload_head->start_addr_bit7_0 == RN_USER_PROTOCOL_DRIVER)
	{
		if (m_pUserHandleRespFunctionDriver != NULL)
		{
			rtn = m_pUserHandleRespFunctionDriver->UserHandleRespFunction(&user_packet);
			if (rtn != RTN_SUCCESS)
			{
				return rtn;
			}
			if (user_packet.resp == 0)
			{
				return RTN_SUCCESS;
			}
		}
		else
		{
			user_packet.resp = 1;
		}
	}
	else if (pUser_payload_head->start_addr_bit7_0 == RN_USER_PROTOCOL_MOTION)
	{
		if (m_pUserHandleRespFunctionMotion != NULL)
		{
			rtn = m_pUserHandleRespFunctionMotion->UserHandleRespFunction(&user_packet);
			if (rtn != RTN_SUCCESS)
			{
				return rtn;
			}
			if (user_packet.resp == 0)
			{
				return RTN_SUCCESS;
			}
		}
		else
		{
			user_packet.resp = 1;
		}
	}
	else if (pUser_payload_head->start_addr_bit7_0 == RN_USER_PROTOCOL_PC)
	{
		if (m_pUserHandleRespFunctionPC != NULL)
		{
			rtn = m_pUserHandleRespFunctionPC->UserHandleRespFunction(&user_packet);
			if (rtn != RTN_SUCCESS)
			{
				return rtn;
			}
			if (user_packet.resp == 0)
			{
				return RTN_SUCCESS;
			}
		}
		else
		{
			user_packet.resp = 1;
		}
	}
	else
	{
		if (m_pUserHandleRespFunctionNomal != NULL)
		{
			rtn = m_pUserHandleRespFunctionNomal->UserHandleRespFunction(&user_packet);
			if (rtn != RTN_SUCCESS)
			{
				return rtn;
			}
			if (user_packet.resp == 0)
			{
				return RTN_SUCCESS;
			}
		}
		else
		{
			user_packet.resp = 1;
		}
	}
	if (user_packet.resp_req == 0)
	{
		return RTN_SUCCESS;
	}

	StRnPacket resp_packet;

	rtn = FormatRingNetUserPakcet(&resp_packet, user_packet.src_id, user_packet.src_ch,
		user_packet.length + 4, user_packet.cmd, pUser_payload_head->mode, 
		pUser_payload_head->start_addr_bit7_0 + (pUser_payload_head->start_addr_bit15_8<<8),0,
		RN_IS_REQ, RN_NEED_REQ, pUser_payload_head->delta, 0xF0);

	rtn = TxPacket(&resp_packet);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	return RTN_SUCCESS;
}
short CRingNetDriver::DecoderUserPacket(StRnPacket* pPacket)
{
#ifdef DEBUG
	return RespUserPacket(pPacket);
#endif

	if (pPacket == NULL)
		return RTN_NULL_POINT;

	StRnUserPayloadHead* pUser_payload_head;
	Uint8*				 pUser_data;

	pUser_payload_head = (StRnUserPayloadHead*)pPacket->dataSection;
	pUser_data = pPacket->dataSection + sizeof(StRnUserPayloadHead);

	if (pUser_payload_head->resp_req && pUser_payload_head->resp) //属于应答报文
	{
		return RTN_SUCCESS;
	}
	else
	{
		return RespUserPacket(pPacket);
	}
}

short CRingNetDriver::RxPacketDecoder(const void* src, const Uint16 src_len, void* des, Uint16& des_len)
{
#ifdef DEBUG
	return DecoderUserPacket(NULL);
#endif // DEBUG

	short rtn = CNetDriver::RxPacketDecoder(src, src_len, des, des_len);
	if (RTN_SUCCESS != rtn)
	{
		return rtn;
	}

	StRnPacket* pPacket = (StRnPacket*)des;
	bool check_rtn = CheckRingNetHeadCheckSum(&(pPacket->ringnet_head));//判断校验和
	if (check_rtn == FALSE)
	{
		return RTN_PACKET_ERR;
	}
	if (pPacket->ringnet_head.src_id >= MAX_STATION_NUM || pPacket->ringnet_head.ttl >= MAX_STATION_NUM)//校验参数
	{
		return RTN_PACKET_ERR;
	}

	if (m_pRnDeviceOnline[pPacket->ringnet_head.ttl] == NULL) //如果发现新的对象，则创建该对象。
	{
		m_pRnDeviceOnline[pPacket->ringnet_head.ttl] = new CRnDeviceDataBase;
		m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->m_distance = pPacket->ringnet_head.ttl;
		m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->m_station_id = pPacket->ringnet_head.src_id;//record  new object id and distance;
//		if (m_pRnDevice[pPacket->ringnet_head.src_id] != NULL)
		{
			m_topology_update++;
		}
		m_pRnDevice[pPacket->ringnet_head.src_id] = m_pRnDeviceOnline[pPacket->ringnet_head.ttl];//set the device point to new object
		m_device_num++;
	}
	else 
	{
		if (m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->m_station_id != pPacket->ringnet_head.src_id) //the object id change 
		{
			m_pRnDevice[m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->m_station_id] = NULL;
			m_pRnDevice[pPacket->ringnet_head.src_id] = m_pRnDeviceOnline[pPacket->ringnet_head.ttl];
			m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->m_station_id = pPacket->ringnet_head.src_id;
			m_topology_update++;
		}
	}
////////////////////////////////check packet lost//////////////////////////////////////////
	m_pRnDeviceOnline[pPacket->ringnet_head.ttl]->CheckRxIndex(pPacket->ringnet_head.protocolType0);
	//////////////////////////////////////////////////////////////////////////

	if (pPacket->ringnet_head.basecontrol.packet_type == RN_PACKET_USER) //用户数据报文
	{
		return rtn = DecoderUserPacket(pPacket);
	}
	else 
	{
		return RTN_PACKET_ERR;
	}
}

short CRingNetDriver::TxPacket(StRnPacket* pPacket)
{
	short rtn = RTN_SUCCESS;
	if (pPacket == NULL)
		return RTN_NULL_POINT;
	if (pPacket->ringnet_head.des_id >= MAX_STATION_NUM)
	{
		return RTN_PARAM_ERR;
	}
	if (pPacket->ringnet_head.basecontrol.packet_type == RN_PACKET_USER)
	{
		StRnUserPayloadHead* pUser_payload_head;
		Uint8*				 pUser_data;
		Uint16				tx_byte_num;
		Uint16				user_data_len;
		Uint8*				pData;

		pUser_payload_head = (StRnUserPayloadHead*)pPacket->dataSection;
		pUser_data = pPacket->dataSection + sizeof(StRnUserPayloadHead);

		pPacket->ringnet_head.protocolType0 = (m_index[pPacket->ringnet_head.des_id] & 0x7F) + 0x40;
		m_index[pPacket->ringnet_head.des_id]++;
		user_data_len = pUser_payload_head->len_low + (pUser_payload_head->len_bit8 << 8);
		pUser_data[user_data_len-4] = 0xFF;

		tx_byte_num = user_data_len + 8 + 3;
		if (tx_byte_num < NET_PACKET_SIZE_MIN)
		{
			return RTN_PARAM_ERR;
		}
		pData = (Uint8*)(&(pPacket->ringnet_head));
		rtn = CNetDriver::TxPacket(pData, tx_byte_num);
		if (rtn != RTN_SUCCESS)
		{
			return rtn;
		}
		return RTN_SUCCESS;
	}
	return RTN_PARAM_ERR;
}

short CRingNetDriver::FormatRingNetUserPakcet(
	StRnPacket* pPacket,
	Uint8 des_id, //
	Uint8 des_ch, //
	Uint16 datalenth,// 
	Uint8 cmd, //
	Uint8 mode, //
	Uint16 addr,//
	Uint16 num,//
	Uint8 NeedReq, // 
	Uint8 IsResp, //
	Uint8 RespOk,
	Uint8 delta,//
	Uint8 max_path
	)
{
	StRnUserPayloadHead* pUser_payload_head;
	Uint8*				 pUser_data;

	if (pPacket == NULL)
	{
		return RTN_NULL_POINT;
	}
	pUser_payload_head	= (StRnUserPayloadHead*)pPacket->dataSection;
	pUser_data = pPacket->dataSection + sizeof(StRnUserPayloadHead);
	

	pPacket->ringnet_head.ttl = 0;
	pPacket->ringnet_head.basecontrol.packet_type = RN_PACKET_USER;
	pPacket->ringnet_head.basecontrol.port_id = 0;
	pPacket->ringnet_head.basecontrol.rsv = 0;
	pPacket->ringnet_head.des_id = des_id;
	pPacket->ringnet_head.src_id = RN_DEVICE_WATCH_ID;
	pPacket->ringnet_head.ttlbase = max_path;
	CalcRingNetHeadCheckSum(&pPacket->ringnet_head);
	pPacket->ringnet_head.protocolType1 = 0xFF;

	pUser_payload_head->len_bit8 = datalenth >> 8;
	pUser_payload_head->len_low = datalenth & 0xFF;
	pUser_payload_head->mode = mode;
	pUser_payload_head->src_ch = RN_PCI_CH_ID;
	pUser_payload_head->des_ch = des_ch;
	pUser_payload_head->cmd = cmd;
	pUser_payload_head->delta = delta;
	
	pUser_payload_head->resp_req = NeedReq;
	pUser_payload_head->resp = IsResp;
	pUser_payload_head->resp_ok = IsResp ? RespOk : 0;
	pUser_payload_head->num_bit8 = num >> 8;
	pUser_payload_head->num_low = num & 0xFF;
	
	pUser_payload_head->start_addr_bit7_0 = addr & 0xFF;
	pUser_payload_head->start_addr_bit15_8 = addr >> 8;


	return RTN_SUCCESS;
}

short  CRingNetDriver::CalcRingNetHeadCheckSum(StRnHeadFormat* pData)
{
	if (pData == NULL)
	{
		return RTN_NULL_POINT;
	}
	Uint8* data = (Uint8*)pData;
	data[5] = data[0] + data[1] + data[2] + data[3] + data[4];
	return RTN_SUCCESS;
}
bool  CRingNetDriver::CheckRingNetHeadCheckSum(StRnHeadFormat* pData)
{
	if (pData == NULL)
	{
		return false;
	}
	Uint8* data = (Uint8*)pData;
	return  (data[5] == ((data[0] + data[1] + data[2] + data[3] + data[4]) & 0xFF));
}