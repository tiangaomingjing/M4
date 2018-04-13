
//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	rn Communicaiton top level		 							//
//	file				:	Rninterface.CPP												//
//	Description			:	use for pc and fpga dsp communicaiton						//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2017/1/3	|	googoltech		|		2016 - 2019			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winsock2.h>
#include "RingNetInterface.h"
#include "BaseReturn_def.h"
//#include "PlotWave.h"


//////////////////////////////////////////////////////////////////////////
static const int32			FPGA_MODE_RD = 0x0;							//FPGA读操作
static const int32			FPGA_MODE_WR = 0x1;							//FPGA写操作	

static const int32			DSP_MODE_RD = 0x0;							//DSP读操作
static const int32			DSP_MODE_WR = 0x1;							//DSP写操作	


static const int32			VIRTUAL_DSPA_COMADDR = 0x0400;				 //地址为short地址
static const int32			VIRTUAL_DSPB_COMADDR = 0x8400;


CRingNetInterface::CRingNetInterface()
{
	m_protocol_type = COM_PROTOCO_RINGNET;
	m_com_dsp_check_mode = COM_DSP_CHEKC_NORMAL;
}


CRingNetInterface::~CRingNetInterface()
{

}
/*******************************************************************************************
功能：		打开设备
输入：		adapter: 设备的名称（GUID）
port:		保留参数
返回：		0成功，其他参看错误列表。
*******************************************************************************************/
int16 CRingNetInterface::NC_Open(const int8* adapter, int32 port)
{
	int16 process = 0;
	return OpenAdapter(NULL, NULL, process);
}
/*******************************************************************************************
功能：关闭设备
输入：   无
返回：   无
*******************************************************************************************/
int16 CRingNetInterface::NC_Close()
{
	return CloseAdapter();
}
/*******************************************************************************************
功能：		从扫描到的设备中找到有响应的设备并打开该设备，找到一个有响应的设备后就退出
输入：		无
返回：		0成功，其他参看错误列表。
*******************************************************************************************/
int16 CRingNetInterface::RnNetCom_Open(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	return OpenAdapter(tpfUpdataProgressPt, ptrv, progress);
}
/*******************************************************************************************
功能：关闭扫描到的有响应的设备
输入：   无
返回：   无
*******************************************************************************************/
int16 CRingNetInterface::RnNetCom_Close()
{
	return NC_Close();
}

/*******************************************************************************************
功能：FPGA数据通信交互函数
输入：
mode:			1:写  0：读
byte_addr:		fpga地址
pData:			输入数据
word_num:		输入16位数据长度
输出：pData:    输出数据
num:			输出数据长度
返回：0成功，其他参看错误列表。
*******************************************************************************************/
int16 CRingNetInterface::RnNetCom_FPGA_ComHandler(int16 mode, int16 byte_addr, int16* pData, int16 word_num, int16 des_id, int16 needReq/* = TRUE*/)
{
	StRnPacket packet;
	short rtn;

	Uint8 cmd;
	if (FPGA_MODE_RD == mode)
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}
	else if (FPGA_MODE_WR == mode)
	{
		cmd = RN_AWR;
		//			needReq			= RN_NEED_REQ;//RN_NOTNEED_REQ;
	}
	else
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}

	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	int16 length = (word_num<<1) + 4;
	if (length > RN_USER_TX_LEN_MAX)
		return RTN_PARAM_OVERFLOW;
	if (pData == NULL)
		return RTN_NULL_POINT;

	if (length < RN_USER_TX_LEN_MIN)
		length = RN_USER_TX_LEN_MIN;

	StRnUserPayloadHead* pUser_Tx_payload_head;
	Uint8*				 pUser_Tx_data;

	pUser_Tx_payload_head = (StRnUserPayloadHead*)packet.dataSection;
	pUser_Tx_data = packet.dataSection + sizeof(StRnUserPayloadHead);

	rtn = FormatRingNetUserPakcet(&packet, (Uint8)des_id, RN_FPGA_CH_ID,
		length, cmd, RN_MODE_MAIL, byte_addr, word_num << 1,
		(Uint8)needReq, RN_ISNOT_RESP, 0, RN_ADDR_INC, 0xF0);

	if (FPGA_MODE_WR == mode)
	{
		memcpy(pUser_Tx_data, pData, pUser_Tx_payload_head->num_low + (pUser_Tx_payload_head->num_bit8 << 8));
	}
	if (needReq == RN_NEED_REQ) 
		CloseThreadRx();//close the rx thread, and open it after the work finish. 
	//////////////////////////////////////////////////////////////////////////
	//dule with the adapter buffer data first//
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < 1000; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS || packet_num <= 0)
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		if (needReq == RN_NEED_REQ)
			CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < COM_FPGA_TRY_TIME; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS)
			{
				Sleep(2);
				i = i + 100;
				continue;
			}
			if (packet_num <= 0)
			{
				continue;
			}
			StRnPacket* pRx_packet;
			StRnUserPayloadHead* pUser_payload_head;
			Uint8*				 pUser_data;
			pRx_packet = (StRnPacket*)m_rx_buffer;
			pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
			pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);

			if (pUser_payload_head->resp = RN_IS_RESP &&
				pUser_payload_head->cmd == pUser_Tx_payload_head->cmd && 
				pUser_payload_head->src_ch == pUser_Tx_payload_head->des_ch &&
				pUser_payload_head->start_addr_bit7_0 == pUser_Tx_payload_head->start_addr_bit7_0 && 
				pUser_payload_head->start_addr_bit15_8 == pUser_Tx_payload_head->start_addr_bit15_8) //return CNS
			{
				if (pUser_payload_head->cmd == RN_ARD)
				{
					memcpy(pData, pUser_data, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8));

					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
				else
				{
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
			}
		}
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_WAIT_NET_RESP_OVERTIME;
	}

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}

Uint16 CRingNetInterface::RnNetCom_DSP_FroceCheckMode(Uint16 mode)
{ 
	Uint16 pre_mode = m_com_dsp_check_mode;
	m_com_dsp_check_mode = mode; 
	return pre_mode;
}
/*******************************************************************************************
功能：dsp数据通信交互函数
输入：
mode:			1:写  0：读
byte_addr:		dsp地址 just used to choice which dsp to select
pData:			输入数据
word_num:		输入数据长度
输出：pData:    输出数据
num:			输出数据长度
返回：0成功，其他参看错误列表。
*******************************************************************************************/
int16 CRingNetInterface::RnNetCom_DSP_ComHandler(int16 mode, int16 byte_addr, int16* pData, int16 word_num, int16 des_id)
{
	//////////////////////////////////////////////////////////////////////////
	StRnPacket packet;
	short rtn;

	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	int16 length = (word_num << 1) + 4;
	if (length > RN_USER_TX_LEN_MAX)
		return RTN_PARAM_OVERFLOW;
	if (pData == NULL)
		return RTN_NULL_POINT;

	if (length < RN_USER_TX_LEN_MIN)
		length = RN_USER_TX_LEN_MIN;

	StRnUserPayloadHead* pUser_Tx_payload_head;
	Uint8*				 pUser_Tx_data;

	pUser_Tx_payload_head = (StRnUserPayloadHead*)packet.dataSection;
	pUser_Tx_data = packet.dataSection + sizeof(StRnUserPayloadHead);

	//根据地址判断，兼容之前的PCdebug的地址，虽然这个地址现在没有用处
	Uint8 des_ch;
	if ((Uint16)byte_addr == (Uint16)VIRTUAL_DSPA_COMADDR)
	{
		des_ch = RN_DSP_CH_ID;
	}
	else if ((Uint16)byte_addr == (((Uint16)VIRTUAL_DSPB_COMADDR) & 0xffff))
	{
		des_ch = RN_PCI_CH_ID;
	}

	//根据模式设置cmd和是否需要响应
	Uint8 cmd;
	Uint8 needReq;
	Uint8 com_mode = RN_MODE_MAIL;
	Uint8 IsResp = RN_ISNOT_RESP;
	if (DSP_MODE_RD == mode)
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}
	else if (DSP_MODE_WR == mode)
	{
		cmd = RN_AWR;
		needReq = RN_NEED_REQ;
	}
	else
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}

	rtn = FormatRingNetUserPakcet(&packet, (Uint8)des_id, des_ch,
		length, cmd, com_mode, RN_USER_PROTOCOL_DRIVER, word_num << 1,
		needReq, IsResp, 0, RN_ADDR_SAME, 0xF0);

	int16 order = *pData;
	
	const Uint32 WAIT_LONG_TIME = 12000;
	const Uint32 WAIT_SHORT_TIME = 0;// 200;
	int32 delay_time = WAIT_SHORT_TIME;
	//////////////////////////////////////////////////////////////////////////
	//根据命令不同，延迟等待时间不同
	switch (order & 0x0fff)
	{
		//如有长时间的指令就在此增加
	case 38:
	case 39:
		delay_time = WAIT_LONG_TIME;
		break;
	default:
		break;
	}

	memcpy(pUser_Tx_data, pData, pUser_Tx_payload_head->num_low + (pUser_Tx_payload_head->num_bit8 << 8));

	if (needReq == RN_NEED_REQ)
		CloseThreadRx();//close the rx thread, and open it after the work finish. 
	//////////////////////////////////////////////////////////////////////////
	//dule with the adapter buffer data first//
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < 1000; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS || packet_num <= 0)
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		if (needReq == RN_NEED_REQ)
			CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < COM_DSP_TRY_TIME + delay_time; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS)
			{
				Sleep(2);
				i = i + 100;
				continue;
			}
			if (packet_num <= 0)
			{
				if (delay_time == WAIT_LONG_TIME)
				{
					Sleep(2);
				}
				continue;
			}
			StRnPacket* pRx_packet;
			StRnUserPayloadHead* pUser_payload_head;
			Uint8*				 pUser_data;
			pRx_packet = (StRnPacket*)m_rx_buffer;
			pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
			pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);

			if (pUser_payload_head->resp = RN_IS_RESP &&
				pUser_payload_head->cmd == pUser_Tx_payload_head->cmd && 
				pUser_payload_head->src_ch == pUser_Tx_payload_head->des_ch &&
				pUser_payload_head->start_addr_bit7_0 == pUser_Tx_payload_head->start_addr_bit7_0 &&
				pUser_payload_head->start_addr_bit15_8 == pUser_Tx_payload_head->start_addr_bit15_8) //return CNS
			{
        if (((Uint32*)pData)[0] != ((Uint32*)pUser_data)[0])//the return data cmd is matching
				{
					continue;
				}
				//查询返回信息是否正确
				switch (pUser_data[4])
				{
				case NET_COM_EXECUTE_FAIL:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Execute_Fail;

				case NET_COM_EXECUTE_SUCCESS:
					break;

				case NET_COM_PARAMETER_INVALID:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Parameter_invalid;

				case NET_COM_INSTRUCTION_INVALID:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Instruction_invalid;

				default:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Other_Error;
				}
				if (pUser_payload_head->cmd == RN_ARD)
				{
//the function need return user data only, the cmd head take 6bytes.
					memcpy(pData, pUser_data+6, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8) - 6);
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
				else
				{
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
			}
		}
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_WAIT_NET_RESP_OVERTIME;
	}

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}

int16 CRingNetInterface::RnNetCom_DSP_ComHandler(int16 mode, int16 byte_addr, int16* pData, int16 word_num, Uint8 des_id, Uint8 des_ch, Uint8 check_en)
{
	//////////////////////////////////////////////////////////////////////////
	StRnPacket packet;
	short rtn;
	if (m_com_dsp_check_mode == COM_DSP_CHEKC_FORCE_OFF)
	{
		check_en = 0;
	}
	else if (m_com_dsp_check_mode == COM_DSP_CHEKC_FORCE_ON)
	{
		check_en = 1;
	}

	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	//  [10/9/2017 googol]
	if (check_en)
	{
		word_num = word_num + 1;
	}

	int16 length = (word_num << 1) + 4;
	if (length > RN_USER_TX_LEN_MAX)
		return RTN_PARAM_OVERFLOW;
	if (pData == NULL)
		return RTN_NULL_POINT;

	if (length < RN_USER_TX_LEN_MIN)
		length = RN_USER_TX_LEN_MIN;

	StRnUserPayloadHead* pUser_Tx_payload_head;
	Uint8*				 pUser_Tx_data;

	pUser_Tx_payload_head = (StRnUserPayloadHead*)packet.dataSection;
	pUser_Tx_data = packet.dataSection + sizeof(StRnUserPayloadHead);

	//根据模式设置cmd和是否需要响应
	Uint8 cmd;
	Uint8 needReq;
	Uint8 com_mode = RN_MODE_MAIL;
	Uint8 IsResp = RN_ISNOT_RESP;
	if (DSP_MODE_RD == mode)
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}
	else if (DSP_MODE_WR == mode)
	{
		cmd = RN_AWR;
		needReq = RN_NEED_REQ;
	}
	else
	{
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
	}


	//////////////////////////////////////////////////////////////////////////
	rtn = FormatRingNetUserPakcet(&packet, (Uint8)des_id, des_ch,
		length, cmd, com_mode, RN_USER_PROTOCOL_DRIVER, word_num << 1,
		needReq, IsResp, 0, RN_ADDR_SAME, 0xF0);

	int16 order = *pData;

	const Uint32 WAIT_LONG_TIME = 12000;
	const Uint32 WAIT_SHORT_TIME = 0;// 200;
	int32 delay_time = WAIT_SHORT_TIME;
	//////////////////////////////////////////////////////////////////////////
	//根据命令不同，延迟等待时间不同
	switch (order & 0x0fff)
	{
		//如有长时间的指令就在此增加
	case 38:
	case 39:
		delay_time = WAIT_LONG_TIME;
		break;
	default:
		break;
	}

	/////////////////////////////////////////////////////
	//  [10/9/2017 googol]
	if (check_en)
	{
		Uint16 check_sum = 0xFFFF;
		pData[1] = pData[1] | 0x8;//enable checksum
		for (int i = 0; i < word_num - 1; i++)
		{
			check_sum = check_sum - pData[i];
		}
	
		memcpy(pUser_Tx_data, pData, (word_num-1)<<1);
		((Uint16*)pUser_Tx_data)[word_num - 1] = check_sum;
	}
	//////////////////////////////////////////////////////////////////////////
	else
	{
		memcpy(pUser_Tx_data, pData, pUser_Tx_payload_head->num_low + (pUser_Tx_payload_head->num_bit8 << 8));
	}
	

	if (needReq == RN_NEED_REQ)
		CloseThreadRx();//close the rx thread, and open it after the work finish. 
	//////////////////////////////////////////////////////////////////////////
	//dule with the adapter buffer data first//
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < 1000; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS || packet_num <= 0)
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		if (needReq == RN_NEED_REQ)
			CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	if (needReq == RN_NEED_REQ)
	{
		for (int i = 0; i < COM_DSP_TRY_TIME + delay_time; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS)
			{
				Sleep(2);
				i = i + 100;
				continue;
			}
			if (packet_num <= 0)
			{
				if (delay_time == WAIT_LONG_TIME)
				{
					Sleep(2);
				}
				continue;
			}
			StRnPacket* pRx_packet;
			StRnUserPayloadHead* pUser_payload_head;
			Uint8*				 pUser_data;
			pRx_packet = (StRnPacket*)m_rx_buffer;
			pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
			pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);

			if (pUser_payload_head->resp = RN_IS_RESP &&
				pUser_payload_head->cmd == pUser_Tx_payload_head->cmd && 
				pUser_payload_head->src_ch == pUser_Tx_payload_head->des_ch &&
				pUser_payload_head->start_addr_bit7_0 == pUser_Tx_payload_head->start_addr_bit7_0 &&
				pUser_payload_head->start_addr_bit15_8 == pUser_Tx_payload_head->start_addr_bit15_8) //return CNS
			{
				if (((Uint32*)pData)[0] != ((Uint32*)pUser_data)[0])//the return data cmd is matching
				{
					continue;
				}
				//////////////////////////////////////////////////////////////////////////
				//  [10/9/2017 googol]
				if (check_en)
				{
					Uint16 dword_num = ((pUser_payload_head->num_bit8 << 8) + pUser_payload_head->num_low)>>1;
					Uint16 check_sum = 0;
					for (int i = 0; i < dword_num;i++)
					{
						check_sum += ((Uint16*)pUser_data)[i];
					}
					if (check_sum != 0xFFFF)
					{
						CNetDriver::OpenThreadRx();
						LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
						return Net_Rt_Other_Error;
					}
				}
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////

				//查询返回信息是否正确
				switch (pUser_data[4])
				{
				case NET_COM_EXECUTE_FAIL:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Execute_Fail;

				case NET_COM_EXECUTE_SUCCESS:
					break;

				case NET_COM_PARAMETER_INVALID:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Parameter_invalid;

				case NET_COM_INSTRUCTION_INVALID:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Instruction_invalid;

				default:
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return Net_Rt_Other_Error;
				}
				if (pUser_payload_head->cmd == RN_ARD)
				{
//the function need return user data only, the cmd head take 6bytes.
					if (check_en)
					{
						memcpy(pData, pUser_data + 6, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8) - 6 - 2);
					}
					else
					{
						memcpy(pData, pUser_data + 6, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8) - 6);
					}
					
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
				else
				{
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
			}
		}
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_WAIT_NET_RESP_OVERTIME;
	}

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}

int16 CRingNetInterface::RnNetComHandler(Uint8 mode, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id, Uint8 des_ch, 
	Uint8 needReq/* = TRUE*/, Uint8 addr_mod/* = RN_ADDR_INC*/, Uint8 wait_level/* = RN_OP_WAIT_DEFAULT*/, Uint8 dsitance /*= 0xf0*/)
{
	//////////////////////////////////////////////////////////////////////////
	StRnPacket packet;
	short rtn;

	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	int16 length = (word_num << 1) + 4;
	if (length > RN_USER_TX_LEN_MAX)//472
		return RTN_PARAM_OVERFLOW;
	if (pData == NULL)
		return RTN_NULL_POINT;

	if (length < RN_USER_TX_LEN_MIN)//50
		length = RN_USER_TX_LEN_MIN;

	StRnUserPayloadHead* pUser_Tx_payload_head;
	Uint8*				 pUser_Tx_data;

	pUser_Tx_payload_head = (StRnUserPayloadHead*)packet.dataSection;
	pUser_Tx_data = packet.dataSection + sizeof(StRnUserPayloadHead);

	//根据模式设置cmd和是否需要响应
	Uint8 cmd;
	Uint8 com_mode;
	Uint8 IsResp ;
	switch (mode)
	{
	case RN_PACKET_MAIL_RD_ASK:
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;

	case RN_PACKET_MAIL_WR_ASK:
		cmd = RN_AWR;
		needReq = needReq;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;

	case RN_PACKET_MAIL_RD_RESP:
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
		IsResp = RN_IS_RESP;
		com_mode = RN_MODE_MAIL;
		break;
	case RN_PACKET_MAIL_WR_RESP:
		cmd = RN_AWR;
		needReq = RN_NEED_REQ;
		IsResp = RN_IS_RESP;
		com_mode = RN_MODE_MAIL;
		break;
	//////////////////////////////////////////////////////////////////////////
	case RN_PACKET_PDU_RD_ASK:
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_PDU;
		break;

	case RN_PACKET_PDU_WR_ASK:
		cmd = RN_AWR;
		needReq = needReq;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_PDU;
		break;

	case RN_PACKET_PDU_RD_RESP:
		cmd = RN_ARD;
		needReq = RN_NEED_REQ;
		IsResp = RN_IS_RESP;
		com_mode = RN_MODE_PDU;
		break;
	case RN_PACKET_PDU_WR_RESP:
		cmd = RN_AWR;
		needReq = RN_NEED_REQ;
		IsResp = RN_IS_RESP;
		com_mode = RN_MODE_PDU;
		break;
/////////////////////////////////////
	case RN_PACKET_DMA_MAP_RD_ASK:
		cmd = RN_LMRD;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;
	case RN_PACKET_DMA_MAP_WR_ASK:
		cmd = RN_LMWR;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;
//////////////////////////////////////////////////////////////////////////
	case RN_PACKET_DMA_CFG_RD_ASK:
		cmd = RN_TCRD;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;
	case RN_PACKET_DMA_CFG_WR_ASK:
		cmd = RN_TCWR;
		needReq = RN_NEED_REQ;
		IsResp = RN_ISNOT_RESP;
		com_mode = RN_MODE_MAIL;
		break;
	default:
		return RTN_PACKET_ERR;
		break;
	}

	rtn = FormatRingNetUserPakcet(&packet, (Uint8)des_id, des_ch,
		length, cmd, com_mode, byte_addr, word_num << 1,
		needReq, IsResp, 0, addr_mod, dsitance);


	int32 try_time;
	switch (wait_level)
	{
	case RN_OP_WAIT_DEFAULT:
		if (des_ch == RN_FPGA_CH_ID)
		{
			try_time = COM_FPGA_TRY_TIME;
			wait_level = RN_OP_WAIT_NORMAL;
		}
		else if (des_ch == RN_DSP_CH_ID)
		{
			try_time = COM_DSP_TRY_TIME;
			wait_level = RN_OP_WAIT_MEDIUM;
		}
		else
		{
			try_time = COM_DSP_TRY_TIME * 10;
			wait_level = RN_OP_WAIT_LONG;
		}
		break;
	case RN_OP_WAIT_NORMAL:
		try_time = COM_FPGA_TRY_TIME;
		break;
	case RN_OP_WAIT_MEDIUM:
		try_time = COM_DSP_TRY_TIME;
		break;
	case RN_OP_WAIT_LONG:
		try_time = COM_DSP_TRY_TIME * 10;
		break;
	case RN_OP_WAIT_INFINITE:
		try_time = COM_DSP_TRY_TIME * 100;
		break;
	default:
		try_time = COM_DSP_TRY_TIME * 10;
		wait_level = RN_OP_WAIT_LONG;
		break;
	}
	//////////////////////////////////////////////////////////////////////////
	memcpy(pUser_Tx_data, pData, pUser_Tx_payload_head->num_low + (pUser_Tx_payload_head->num_bit8 << 8));

	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
		CloseThreadRx();//close the rx thread, and open it after the work finish. 
	//////////////////////////////////////////////////////////////////////////
	//dule with the adapter buffer data first//
	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
	{
		for (int i = 0; i < 1000; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS || packet_num <= 0)
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
			CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
	{
		for (int i = 0; i < try_time; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS)
			{
				Sleep(2);
				i = i + 100;
				continue;
			}
			if (packet_num <= 0)
			{
				switch (wait_level)
				{
				case RN_OP_WAIT_NORMAL:
					break;
				default:
					Sleep(2);
					break;
				}
				continue;
			}
			StRnPacket* pRx_packet;
			StRnUserPayloadHead* pUser_payload_head;
			Uint8*				 pUser_data;
			pRx_packet = (StRnPacket*)m_rx_buffer;
			pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
			pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);

			if (pUser_payload_head->resp = RN_IS_RESP && 
				pUser_payload_head->cmd == pUser_Tx_payload_head->cmd && 
				pUser_payload_head->src_ch == pUser_Tx_payload_head->des_ch &&
				pUser_payload_head->start_addr_bit7_0 == pUser_Tx_payload_head->start_addr_bit7_0 &&
				pUser_payload_head->start_addr_bit15_8 == pUser_Tx_payload_head->start_addr_bit15_8) //return CNS
			{
//				if (pUser_payload_head->cmd == RN_ARD)
				{
					memcpy(pData, pUser_data, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8));
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
// 				else
// 				{
// 					CNetDriver::OpenThreadRx();
// 					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
// 					return RTN_SUCCESS;;
// 				}
			}
		}
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_WAIT_NET_RESP_OVERTIME;
	}

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}

int16 CRingNetInterface::RnNetCom(Uint8 com_mode, Uint8 cmd, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id, Uint8 des_ch,
	Uint8 needReq/* = TRUE*/, Uint8 addr_mod/* = RN_ADDR_INC*/, Uint8 wait_level/* = RN_OP_WAIT_DEFAULT*/, Uint8 dsitance /*= 0xf0*/)
{
	//////////////////////////////////////////////////////////////////////////
	StRnPacket packet;
	short rtn;

	EnterCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	int16 length = (word_num << 1) + 4;
	if (length > RN_USER_TX_LEN_MAX)//472
		return RTN_PARAM_OVERFLOW;
	if (pData == NULL)
		return RTN_NULL_POINT;

	if (length < RN_USER_TX_LEN_MIN)//50
		length = RN_USER_TX_LEN_MIN;

	StRnUserPayloadHead* pUser_Tx_payload_head;
	Uint8*				 pUser_Tx_data;

	pUser_Tx_payload_head = (StRnUserPayloadHead*)packet.dataSection;
	pUser_Tx_data = packet.dataSection + sizeof(StRnUserPayloadHead);

	//根据模式设置cmd和是否需要响应
// 	Uint8 cmd;
// 	Uint8 com_mode;
	Uint8 IsResp = RN_ISNOT_RESP;
// 	switch (mode)
// 	{
// 	case RN_PACKET_MAIL_RD_ASK:
// 		cmd = RN_ARD;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_ISNOT_RESP;
// 		com_mode = RN_MODE_MAIL;
// 		break;
// 
// 	case RN_PACKET_MAIL_WR_ASK:
// 		cmd = RN_AWR;
// 		needReq = needReq;
// 		IsResp = RN_ISNOT_RESP;
// 		com_mode = RN_MODE_MAIL;
// 		break;
// 
// 	case RN_PACKET_MAIL_RD_RESP:
// 		cmd = RN_ARD;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_IS_RESP;
// 		com_mode = RN_MODE_MAIL;
// 		break;
// 	case RN_PACKET_MAIL_WR_RESP:
// 		cmd = RN_AWR;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_IS_RESP;
// 		com_mode = RN_MODE_MAIL;
// 		break;
// 		//////////////////////////////////////////////////////////////////////////
// 	case RN_PACKET_PDU_RD_ASK:
// 		cmd = RN_ARD;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_ISNOT_RESP;
// 		com_mode = RN_MODE_PDU;
// 		break;
// 
// 	case RN_PACKET_PDU_WR_ASK:
// 		cmd = RN_AWR;
// 		needReq = needReq;
// 		IsResp = RN_ISNOT_RESP;
// 		com_mode = RN_MODE_PDU;
// 		break;
// 
// 	case RN_PACKET_PDU_RD_RESP:
// 		cmd = RN_ARD;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_IS_RESP;
// 		com_mode = RN_MODE_PDU;
// 		break;
// 	case RN_PACKET_PDU_WR_RESP:
// 		cmd = RN_AWR;
// 		needReq = RN_NEED_REQ;
// 		IsResp = RN_IS_RESP;
// 		com_mode = RN_MODE_PDU;
// 		break;
// 	default:
// 		break;
// 	}

	rtn = FormatRingNetUserPakcet(&packet, (Uint8)des_id, des_ch,
		length, cmd, com_mode, byte_addr, word_num << 1,
		needReq, IsResp, 0, addr_mod, dsitance);


	int32 try_time;
	switch (wait_level)
	{
	case RN_OP_WAIT_DEFAULT:
		if (des_ch == RN_FPGA_CH_ID)
		{
			try_time = COM_FPGA_TRY_TIME;
			wait_level = RN_OP_WAIT_NORMAL;
		}
		else if (des_ch == RN_DSP_CH_ID)
		{
			try_time = COM_DSP_TRY_TIME;
			wait_level = RN_OP_WAIT_MEDIUM;
		}
		else
		{
			try_time = COM_DSP_TRY_TIME * 10;
			wait_level = RN_OP_WAIT_LONG;
		}
		break;
	case RN_OP_WAIT_NORMAL:
		try_time = COM_FPGA_TRY_TIME;
		break;
	case RN_OP_WAIT_MEDIUM:
		try_time = COM_DSP_TRY_TIME;
		break;
	case RN_OP_WAIT_LONG:
		try_time = COM_DSP_TRY_TIME * 10;
		break;
	case RN_OP_WAIT_INFINITE:
		try_time = COM_DSP_TRY_TIME * 100;
		break;
	default:
		try_time = COM_DSP_TRY_TIME * 10;
		wait_level = RN_OP_WAIT_LONG;
		break;
	}
	//////////////////////////////////////////////////////////////////////////
	memcpy(pUser_Tx_data, pData, pUser_Tx_payload_head->num_low + (pUser_Tx_payload_head->num_bit8 << 8));

	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
		CloseThreadRx();//close the rx thread, and open it after the work finish. 
	//////////////////////////////////////////////////////////////////////////
	//dule with the adapter buffer data first//
	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
	{
		for (int i = 0; i < 1000; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS || packet_num <= 0)
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	rtn = TxPacket(&packet);
	if (rtn != RTN_SUCCESS)
	{
		if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
			CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return rtn;
	}
	if (needReq == RN_NEED_REQ && IsResp == RN_ISNOT_RESP)
	{
		for (int i = 0; i < try_time; i++)
		{
			int packet_num = 0;
			rtn = CheckAdapterPacket(packet_num);
			if (rtn != RTN_SUCCESS)
			{
				Sleep(2);
				i = i + 100;
				continue;
			}
			if (packet_num <= 0)
			{
				switch (wait_level)
				{
				case RN_OP_WAIT_NORMAL:
					break;
				default:
					Sleep(2);
					break;
				}
				continue;
			}
			StRnPacket* pRx_packet;
			StRnUserPayloadHead* pUser_payload_head;
			Uint8*				 pUser_data;
			pRx_packet = (StRnPacket*)m_rx_buffer;
			pUser_payload_head = (StRnUserPayloadHead*)pRx_packet->dataSection;
			pUser_data = pRx_packet->dataSection + sizeof(StRnUserPayloadHead);

			if (pUser_payload_head->resp = RN_IS_RESP &&
				pUser_payload_head->cmd == pUser_Tx_payload_head->cmd &&
				pUser_payload_head->src_ch == pUser_Tx_payload_head->des_ch &&
				pUser_payload_head->start_addr_bit7_0 == pUser_Tx_payload_head->start_addr_bit7_0 &&
				pUser_payload_head->start_addr_bit15_8 == pUser_Tx_payload_head->start_addr_bit15_8) //return CNS
			{
				//				if (pUser_payload_head->cmd == RN_ARD)
				{
					memcpy(pData, pUser_data, pUser_payload_head->num_low + (pUser_payload_head->num_bit8 << 8));
					CNetDriver::OpenThreadRx();
					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
					return RTN_SUCCESS;;
				}
				// 				else
				// 				{
				// 					CNetDriver::OpenThreadRx();
				// 					LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
				// 					return RTN_SUCCESS;;
				// 				}
			}
		}
		CNetDriver::OpenThreadRx();
		LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
		return RTN_WAIT_NET_RESP_OVERTIME;
	}

	LeaveCriticalSection((CRITICAL_SECTION*)m_com_tx_cs);
	return RTN_SUCCESS;
}


int16 CRingNetInterface::RnNetGetCns(COMMON_NET_STATUS* pCns, Uint8 dsitance)
{
	if (dsitance < m_device_num)
	{
		*pCns = m_pRnDeviceOnline[dsitance]->m_CNS;
		return 0;
	}
	else
	{
		return RTN_PARAM_ERR;
	}
}
// short UserRespDriver(StUserPacket* packet)
// {
// 	Uint16 lenth;
// 	Uint8 dspId;
// 	//曲线部分
// 	lenth = packet->length;// ((pRx->header.bit.num_low & 0x00ff) | ((pRx->header.bit.num_bit8 << 8) & 0x0100));
// 	waveDataLenth = (lenth >> 1);
// 	memcpy_s(parsePacket, (lenth)* sizeof(int8), packet->pData, (lenth)* sizeof(int8));
// 	//用于区分哪个dsp
// 	//////////////////////////////////////////////////////////////////////////
// 	dspId = packet->src_ch;
// 	switch (dspId)
// 	{
// 		//DSPA
// 	case RN_DSP_CH_ID:
// 		g_plotWave->m_rn_noTimer->GetPlotWaveDataFromRn(GTSD_DSP_A + packet->src_id - 1);
// 		break;
// 		//DSPB
// 	case RN_PCI_CH_ID:
// 		g_plotWave->m_rn_noTimer->GetPlotWaveDataFromRn(GTSD_DSP_B + packet->src_id - 1);
// 		break;
// 	case RN_EXT_CH_ID:
// 		g_plotWave->m_rn_noTimer->GetPlotWaveDataFromRn(GTSD_DSP_C + packet->src_id - 1);
// 	default:
// 		break;
// 	}
// 	return RTN_SUCCESS;
// }


short CRingNetInterface::ComWrFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam)
{
	if (pParam == NULL)
	{
		return RnNetCom(RN_MODE_MAIL, RN_AWR, byte_addr, pData, word_num, (Uint8)des_id, RN_FPGA_CH_ID);
	}
	return RTN_PARAM_ERR;
}
short CRingNetInterface::ComRdFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam)
{
	if (pParam == NULL)
	{
		return RnNetCom(RN_MODE_MAIL, RN_ARD, byte_addr, pData, word_num, (Uint8)des_id, RN_FPGA_CH_ID);
	}
	return RTN_PARAM_ERR;
}