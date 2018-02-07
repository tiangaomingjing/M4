#include "stdafx.h"
#include "MotionCtrlCom.h"
#include "RingNetDeviceDef.h"



CMotionCtrlCom::CMotionCtrlCom()
{
}


CMotionCtrlCom::~CMotionCtrlCom()
{
}

short CMotionCtrlCom::Initial(CRingNetInterface* pDriver)
{
	if (pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}

	m_pDriver = pDriver;
	return RTN_SUCCESS;
}

short CMotionCtrlCom::PostPci(TPci* gPci, Uint8 station_id)
{
	const int MAX_RETYR = 1;
	short rtn, i;
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	if (gPci == NULL)
	{
		return RTN_NULL_POINT;
	}

	// 计算校验和
	gPci->checksum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		gPci->checksum += gPci->data[i];
	}
	// 设置数据写完标志
	gPci->flag = PCI_PC_FINISH;

	Uint16 byte_num = sizeof(TPci);
	Uint16 dword_num = (byte_num + 3) >> 2;
	int16 pData[250];
	memcpy(pData, gPci, byte_num);

	switch (m_pDriver->m_pRnDevice[station_id]->m_staion_type)
	{
	case TB_GTSD13:
		rtn = m_pDriver->RnNetComHandler(RN_PACKET_PDU_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 1, RN_ADDR_SAME);
		break;
	default:
		rtn = m_pDriver->RnNetComHandler(RN_PACKET_MAIL_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 1, RN_ADDR_SAME);
		break;
	}
	return rtn;
}
short CMotionCtrlCom::SendPci(TPci* gPci, Uint8 station_id)
{
	const int MAX_RETYR = 1;
	short rtn, i;

	// 计算校验和
	gPci->checksum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		gPci->checksum += gPci->data[i];
	}

	// 设置数据写完标志
	gPci->flag = PCI_PC_FINISH;

	Uint16 byte_num = (gPci->len + 3) << 1;
	Uint16 dword_num = (byte_num + 3) >> 2;

	int16 pData[250];
	memcpy(pData, gPci, byte_num);
	switch (m_pDriver->m_pRnDevice[station_id]->m_staion_type)
	{
	case TB_GTSD13: 
		rtn = m_pDriver->RnNetComHandler(RN_PACKET_PDU_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 1, RN_ADDR_SAME);
		break;
	default:
		rtn = m_pDriver->RnNetComHandler(RN_PACKET_MAIL_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 1, RN_ADDR_SAME);
		break;
	}
		/////////////////////////////////////////////////
	memcpy(gPci, pData, 4);
	if (PCI_DSP_FINISH != gPci->flag)
	{
//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("PCI_DSP_FINISH != gPci.flag !\n")));
		return CMD_ERROR_READ_BLOCK;
	}
	if ((gPci->len < 0) || (gPci->len > 32))
	{
//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("( gPci.len < 0 )||( gPci.len > 32 ) !\n")));
		return CMD_ERROR_READ_LEN;
	}
	//////////////////////////////////////
	byte_num = (gPci->len + 3) << 1;
	memcpy(gPci,pData, byte_num);
	////////////////
	short sum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		sum += gPci->data[i];
	}

	// 检查校验和
	if (sum == gPci->checksum)
	{
		//return 0;//
//		pRingNet->m_device_list[pRingNet->m_dsp_tag_id].m_dsp_cmd_index = 0x7F & (pRingNet->m_device_list[pRingNet->m_dsp_tag_id].m_dsp_cmd_index + 1);
		return gPci->data[0];
	}
	else
	{
//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("checksum err !\n")));
		return CMD_ERROR_READ_CHECKSUM;
	}
	return RTN_SUCCESS;
}

short CMotionCtrlCom::PostPcie(TPci* gPci, Uint8 core_index, Uint8 station_id)
{
	const int MAX_RETYR = 1;
	short rtn, i;
	if (m_pDriver == NULL)
	{
		return RTN_OBJECT_UNCREATED;
	}
	if (gPci == NULL)
	{
		return RTN_NULL_POINT;
	}

	// 计算校验和
	gPci->checksum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		gPci->checksum += gPci->data[i];
	}
	// 设置数据写完标志
	switch (core_index)
	{
	case 1: 
		gPci->flag = 0x5a;//pci_pc_finish_core0_ex
		break;
	case 2:
		gPci->flag = 0xa5;//pci_pc_finish_core1_ex
		break;
	default:
		gPci->flag = 0x2D;//pci_pc_finish_ex
		break;
	}
	gPci->checksum += gPci->flag;
//	gPci->flag = PCI_PC_FINISH;

	Uint16 byte_num = sizeof(TPci);
	Uint16 dword_num = (byte_num + 3) >> 2;
	int16 pData[250];
	memcpy(pData, gPci, byte_num);

	rtn = m_pDriver->RnNetComHandler(RN_PACKET_MAIL_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 0, RN_ADDR_SAME);
	return rtn;
}
short CMotionCtrlCom::SendPcie(TPci* gPci, Uint8 core_index, Uint8 station_id)
{
	const int MAX_RETYR = 1;
	short rtn, i;

	// 计算校验和
	gPci->checksum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		gPci->checksum += gPci->data[i];
	}

	switch (core_index)
	{
	case 1:
		gPci->flag = 0x5a;//pci_pc_finish_core0_ex
		break;
	case 2:
		gPci->flag = 0xa5;//pci_pc_finish_core1_ex
		break;
	default:
		gPci->flag = 0x2D;//pci_pc_finish_ex
		break;
	}

	gPci->checksum += gPci->flag;
// 	// 设置数据写完标志
// 	gPci->flag = PCI_PC_FINISH;

	Uint16 byte_num = (gPci->len + 3) << 1;
	Uint16 dword_num = (byte_num + 3) >> 2;

	int16 pData[250];
	memcpy(pData, gPci, byte_num);
	rtn = m_pDriver->RnNetComHandler(RN_PACKET_MAIL_WR_ASK, RN_USER_PROTOCOL_MOTION, (int16*)pData, dword_num << 1, station_id, RN_DSP_CH_ID, 1, RN_ADDR_SAME);
	/////////////////////////////////////////////////
	memcpy(gPci, pData, 4);
	if (PCI_DSP_FINISH != gPci->flag)
	{
		//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("PCI_DSP_FINISH != gPci.flag !\n")));
		return CMD_ERROR_READ_BLOCK;
	}
	if ((gPci->len < 0) || (gPci->len > 32))
	{
		//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("( gPci.len < 0 )||( gPci.len > 32 ) !\n")));
		return CMD_ERROR_READ_LEN;
	}
	//////////////////////////////////////
	byte_num = (gPci->len + 3) << 1;
	memcpy(gPci, pData, byte_num);
	////////////////
	short sum = gPci->len;
	for (i = 0; i < gPci->len; ++i)
	{
		sum += gPci->data[i];
	}

	// 检查校验和
	if (sum == gPci->checksum)
	{
		//return 0;//
		//		pRingNet->m_device_list[pRingNet->m_dsp_tag_id].m_dsp_cmd_index = 0x7F & (pRingNet->m_device_list[pRingNet->m_dsp_tag_id].m_dsp_cmd_index + 1);
		return gPci->data[0];
	}
	else
	{
		//		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("checksum err !\n")));
		return CMD_ERROR_READ_CHECKSUM;
	}
	return RTN_SUCCESS;
}

short CMotionCtrlCom::CheckUserProtocol(StUSER_PROTOCOL_DEBUG_CMD* cmd)
{
	uint16 checksum = 0;
	uint16 *pData = (uint16*)cmd;
	if (cmd->sLen > MAX_DEBUG_CMD_DATA_SIZE)
	{
		return RTN_PACKET_ERR;
	}
	for (uint16 i = 0; i < cmd->sLen + (MAX_DEBUG_CMD_SIZE - MAX_DEBUG_CMD_DATA_SIZE);i++)
	{
		checksum += pData[i];
	}
	if (checksum == 0xFFFF)
	{
		return RTN_SUCCESS;
	}
	else
	{
		return RTN_PACKET_ERR;
	}

}
short CMotionCtrlCom::CalcUserProtocol(StUSER_PROTOCOL_DEBUG_CMD* cmd)
{
	uint16 checksum = 0xFFFF;
	uint16* pData = (uint16*)cmd;
	cmd->checksum = 0;
	if (cmd->sLen > MAX_DEBUG_CMD_DATA_SIZE)
	{
		return RTN_PACKET_ERR;
	}
	for (uint16 i = 0; i < cmd->sLen + (MAX_DEBUG_CMD_SIZE - MAX_DEBUG_CMD_DATA_SIZE);i++)
	{
		checksum -= pData[i];
	}
	cmd->checksum = checksum;
	return RTN_SUCCESS;
}

short CMotionCtrlCom::SendUserDebugCmd(StUSER_PROTOCOL_DEBUG_CMD* cmd, Uint8 station_id)
{
	short rtn = CalcUserProtocol(cmd);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	rtn = m_pDriver->RnNetComHandler(RN_PACKET_MAIL_WR_ASK, RN_USER_PROTOCOL_DEBUG, (int16*)cmd, (cmd->sLen+MAX_DEBUG_CMD_SIZE-MAX_DEBUG_CMD_DATA_SIZE) << 1, station_id, RN_DSP_CH_ID, 0, RN_ADDR_SAME);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	rtn = CheckUserProtocol(cmd);
	if (rtn != RTN_SUCCESS)
	{
		return rtn;
	}
	return RTN_SUCCESS;
}
