#include "stdafx.h"
#include "PcCtrlCom.h"


CPcCtrlCom::CPcCtrlCom()
{
	m_Thread_sleep_time = 3;
}


CPcCtrlCom::~CPcCtrlCom()
{
}

short CPcCtrlCom::Initial(CRingNetInterface* pDriver)
{
	if (pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}

	m_pDriver = pDriver;
	return RTN_SUCCESS;
}

short CPcCtrlCom::FileFuctionDriver(StFunction* param, unsigned char station_id, BOOL resp_req)
{
	if (m_pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}
	//m_pDriver->RnNetCom(1,RN_LMWR, 0, 
	unsigned char pData[512];
// 	RN_PACKET packet;
// 	RN_PACKET_HEAD head;
// 
// 	packet.pHead = &head;
	if (param == NULL)
	{
		if (GOOGOL_PRINF_EN) printf("RingNetFuctionDriver : input param == NULL  ERR ! \n");
		//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("RingNetFuctionDriver : input param == NULL  ERR ! \n")));
		return RTN_NULL_POINT;
	}

	unsigned short byte_num = sizeof(unsigned short)* 4 + param->m_len;
	if (byte_num > 480)
	{
		if (GOOGOL_PRINF_EN) printf("RingNetFuctionDriver : byte_num > 480  ERR ! \n");
		//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("RingNetFuctionDriver : byte_num > 480  ERR ! \n")));
		return RTN_PARAM_OVERFLOW;
	}
	//////////////////////////////////////////////////////////////////////////
	((unsigned short*)pData)[0] = param->m_id;
	((unsigned short*)pData)[1] = param->m_rtn;
	((unsigned short*)pData)[2] = param->m_param_num;
	((unsigned short*)pData)[3] = param->m_len;


	memcpy((void*)(pData + sizeof(unsigned short)* 4), (void*)(param->m_pData), param->m_len);
	//////////////////////////////////
	unsigned short dword_num = (byte_num + 3) >> 2;
	short rtn = m_pDriver->RnNetCom(1, RN_LMWR, 0, (int16*)pData, dword_num << 1, station_id, RN_PCI_CH_ID, resp_req);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}

	if (param->m_id != ((unsigned short*)pData)[0] && resp_req)
	{
		return RTN_FIFE_FUNCTION_ID_RETURN_ERR;
	}
	param->m_id = ((unsigned short*)pData)[0];
	param->m_rtn = ((unsigned short*)pData)[1];
	param->m_param_num = ((unsigned short*)pData)[2];
	param->m_len = ((unsigned short*)pData)[3];


	memcpy((void*)(param->m_pData), (void*)(pData + sizeof(unsigned short)* 4), param->m_len);
	return RTN_SUCCESS;
// 
// 	packet.length = byte_num + 4;
// 
// 	packet.packet_type = RN_PACKET_MAIL_WR_ASK;
// 	head.bit.cmd = RN_LMWR;
// 	head.bit.delta = 1;
// 	head.bit.des_ch = RN_PCI_CH_ID;
// 	head.bit.id.des_id = station_id;
// 	head.bit.len_low = packet.length;
// 	head.bit.len_bit8 = packet.length >> 8;
// 
// 	head.bit.num_bit8 = byte_num >> 8;
// 	head.bit.num_low = byte_num;
// 	head.bit.resp_req = resp_req;
// 	head.bit.resp = 0;
// 	head.bit.start_addr = 0;

//	short rtn = RN_MailOp(pRingNet, &packet);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		return rtn;
// 	}
// 
// 	if (param->m_id != ((unsigned short*)packet.pData)[0] && resp_req)
// 	{
// 		return RTN_FIFE_FUNCTION_ID_RETURN_ERR;
// 	}
// 	param->m_id = ((unsigned short*)packet.pData)[0];
// 	param->m_rtn = ((unsigned short*)packet.pData)[1];
// 	param->m_param_num = ((unsigned short*)packet.pData)[2];
// 	param->m_len = ((unsigned short*)packet.pData)[3];
// 
// 
// 	memcpy((void*)(param->m_pData), (void*)(packet.pData + sizeof(unsigned short)* 4), param->m_len);
}