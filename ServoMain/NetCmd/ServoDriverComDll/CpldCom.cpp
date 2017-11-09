#include "stdafx.h"
#include "CpldCom.h"


CCpldCom::CCpldCom()
{
	m_pDriver = NULL;
}


CCpldCom::~CCpldCom()
{
}

short CCpldCom::Initial(CGTDriverCmd* pDriver)
{
	if (pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}

	m_pDriver = pDriver;
	m_protocol_type = m_pDriver->GetComProtocolType();

	return RTN_SUCCESS;
}

short CCpldCom::ComWrFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam)
{
	switch (byte_addr & 0xFF00)
	{
	case FPGA_RN_RMT_START_OFST:
		return RemoteUpdateWr(byte_addr & 0xFF, pData, word_num, des_id);
		break;
	default:
		break;
	}
	return RTN_SUCCESS;
}
short CCpldCom::ComRdFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam)
{
	switch (byte_addr & 0xFF00)
	{
	case FPGA_RN_RMT_START_OFST:
		return RemoteUpdateRd(byte_addr & 0xFF, pData, word_num, des_id);
		break;
	default:
		break;
	}
	return RTN_SUCCESS;
}

short CCpldCom::RemoteUpdateWr(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id)
{
	m_pDriver->SetTagId((Uint8)des_id);
	switch (byte_addr)
	{
	case RN_REMOTE_FPGA_CTL:
		if (word_num != 1)
		{
			return RTN_PACKET_ERR;
		}
		return  m_pDriver->GTD_ST_InfBoardFpga(1, 1, pData, CPLD_UPDATE_CTRL, INBOARDFPGA_WR_SAME);
	default:
		short start_address = byte_addr >> 1;
		Uint16 count = 0;
		short rtn = m_pDriver->GTD_ST_InfBoardFpga(1, 1, &start_address, CPLD_UPDATE_SET_ADDR, INBOARDFPGA_WR_SAME);
		if (rtn)
		{
			return rtn;
		}
		while ((word_num - count) >= INBOARDFPGA_MAX_WORD)
		{
			rtn = m_pDriver->GTD_ST_InfBoardFpga(1, INBOARDFPGA_MAX_WORD, &(pData[count]), CPLD_UPDATE_DATA_DIN, INBOARDFPGA_WR_SAME);
			if (rtn)
			{
				return rtn;
			}
			count += INBOARDFPGA_MAX_WORD;
		}
		if (word_num - count > 0)
		{
			rtn = m_pDriver->GTD_ST_InfBoardFpga(1, word_num - count, &(pData[count]), CPLD_UPDATE_DATA_DIN, INBOARDFPGA_WR_SAME);
			return rtn;
		}
		return rtn;
		break;
	}
	return RTN_SUCCESS;
}
short CCpldCom::RemoteUpdateRd(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id)
{
	m_pDriver->SetTagId((Uint8)des_id);
	switch (byte_addr)
	{
	case RN_REMOTE_FPGA_CTL:
		if (word_num != 1)
		{
			return RTN_PACKET_ERR;
		}
		return  m_pDriver->GTD_ST_InfBoardFpga(1, 1, pData, CPLD_UPDATE_CTRL, INBOARDFPGA_RD_SAME);
	default:
		short start_address = byte_addr >> 1;
		Uint16 count = 0;
		short rtn = m_pDriver->GTD_ST_InfBoardFpga(1, 1, &start_address, CPLD_UPDATE_SET_ADDR, INBOARDFPGA_WR_SAME);
		if (rtn)
		{
			return rtn;
		}
		while ((word_num - count) >= INBOARDFPGA_MAX_WORD)
		{
			rtn = m_pDriver->GTD_ST_InfBoardFpga(1, INBOARDFPGA_MAX_WORD, &(pData[count]), CPLD_UPDATE_DATA_DIN, INBOARDFPGA_RD_SAME);
			if (rtn)
			{
				return rtn;
			}
			count += INBOARDFPGA_MAX_WORD;
		}
		if (word_num - count > 0)
		{
			rtn = m_pDriver->GTD_ST_InfBoardFpga(1, word_num - count, &(pData[count]), CPLD_UPDATE_DATA_DIN, INBOARDFPGA_RD_SAME);
			return rtn;
		}
		return rtn;
		break;
	}
	return RTN_SUCCESS;
}
