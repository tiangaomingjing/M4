#include "stdafx.h"
#include "Eeprom.h"


CEeprom::CEeprom()
{
	m_pCom = NULL;
	m_des_id = 0;
	m_eeprom_id = FPGA_NORMAL_EEPROM;
}


CEeprom::~CEeprom()
{
	m_pCom = NULL;
}


int16 CEeprom::Initial(CComBase* pComBase)
{
	if (pComBase == NULL)
	{
		return RTN_NULL_POINT;
	}

	m_pCom = pComBase;
	return RTN_SUCCESS;
}

int16 CEeprom::EepromBaseOptWr(Uint16 eeprom_addr, Uint8 byte_data)
{
	int16 iRet;
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;
	Uint8 data_tmp[2];
	data_tmp[0] = byte_data;
	data_tmp[1] = 0;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = m_pCom;

	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = eeprom_addr;
        //base_addr = FPGA_RN_EPR_START_OFST;
        base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_RN_EPR_START_OFST : FPGA_RN_EPR_EXT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = eeprom_addr;
        //base_addr = FPGA_EEPROM_BASEADDR;
        base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_EEPROM_BASEADDR : FPGA_EEPROM_EXT_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	int16 comNum = 1;

	iRet = pCom->ComWrFpgaHandle((comAddr), (int16*)data_tmp, comNum, m_des_id, NULL); //

	return iRet;
}

int16 CEeprom::EepromBaseOptRd(Uint16 eeprom_addr, Uint8* byte_data)
{
	int16 iRet;
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;
	int8 read_data[2] = {0, 0};

	if (NULL == byte_data) return RTN_NULL_POINT;
	if (NULL == m_pCom) return RTN_NULL_POINT;
	CComBase* pCom = m_pCom;

	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = eeprom_addr;
        //base_addr = FPGA_RN_EPR_START_OFST;
        base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_RN_EPR_START_OFST : FPGA_RN_EPR_EXT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = eeprom_addr;
        //base_addr = FPGA_EEPROM_BASEADDR;
        base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_EEPROM_BASEADDR : FPGA_EEPROM_EXT_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	int16 comNum = 1;

	iRet = pCom->ComRdFpgaHandle((comAddr), (int16*)read_data, comNum, m_des_id, NULL);//
	*byte_data = read_data[0];
	return iRet;
}


int16 CEeprom::EepromWrite8bit(Uint16 byte_addr, Uint8 byte_data)
{
	int16 iRet;
	StEepromCtl stEepromCtl;
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;
	int16 comNum = 0;
	Uint8 data_tmp[6];
	Uint16 iFinish;
	Uint8 status;

	memset(data_tmp, 0, 6 * sizeof(Uint8));

	if (m_pCom == NULL) return RTN_NULL_POINT;

	if (m_pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = ADDR_CRL;
		base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_RN_EPR_START_OFST : FPGA_RN_EPR_EXT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	else if (m_pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = ADDR_CRL;
		base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_EEPROM_BASEADDR : FPGA_EEPROM_EXT_BASEADDR;
		comAddr = base_addr + (com_addr);
	}

	
	//先写控制寄存器
	stEepromCtl.all = 0;
	stEepromCtl.bit.ctl_read_write = 0;
	stEepromCtl.bit.enable_RW = 1;
	stEepromCtl.bit.addr_chip = (byte_addr >> 8);
	data_tmp[0] = stEepromCtl.all;
	data_tmp[2] = (Uint8)byte_addr;
	data_tmp[4] = byte_data;

	comNum = 3;

	iRet = m_pCom->ComWrFpgaHandle((comAddr), (int16*)data_tmp, comNum, m_des_id, NULL);//
	if (iRet)
	{
		return iRet;
	}

	for (iFinish = 0; iFinish < 4; iFinish++)
	{
		Sleep(5);
		//检测写数据是否完成
		iRet = EepromBaseOptRd(ADDR_STS, &status);
		if ((1 == (status & 0x0001)))//判断读写是否出错
		{
			//如果读写无应答
			break;
		}
		else if (0 == ((status & 0x0002) >> 1))//判断读写是否完成
		{
			//如果没有完成
			continue;
		}

		if ((0 == (status & 0x0001)) && (1 == ((status & 0x0002) >> 1)))//判断读写是否出错
		{
			//如果读写无错误并且完成
			return RTN_SUCCESS;
		}

	}
	return RTN_PCI_FPGA_ERR;
}

int16 CEeprom::EepromRead8bit(Uint16 byte_addr, Uint8* byte_data)
{
	int16 iRet;
	StEepromCtl stEepromCtl;
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;
	int16 comNum = 0;
	Uint8 data_tmp[10];
	Uint16 iFinish;
	Uint8 status;

	memset(data_tmp, 0, 10 * sizeof(Uint8));
	*byte_data = data_tmp[8];

	if (m_pCom == NULL) return RTN_NULL_POINT;

	if (m_pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = ADDR_CRL;
		base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_RN_EPR_START_OFST : FPGA_RN_EPR_EXT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	else if (m_pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = ADDR_CRL;
		base_addr = m_eeprom_id == FPGA_NORMAL_EEPROM ? FPGA_EEPROM_BASEADDR : FPGA_EEPROM_EXT_BASEADDR; 
		comAddr = base_addr + (com_addr);
	}

	//先写控制寄存器
	stEepromCtl.all = 0;
	stEepromCtl.bit.ctl_read_write = 1;
	stEepromCtl.bit.enable_RW = 1;
	stEepromCtl.bit.addr_chip = (byte_addr >> 8);
	data_tmp[0] = stEepromCtl.all;
	data_tmp[6] = (Uint8)byte_addr;

	comNum = 4;
	iRet = m_pCom->ComWrFpgaHandle((comAddr), (int16*)data_tmp, comNum, m_des_id, NULL);//
	if (iRet)
	{
		return iRet;
	}

	for (iFinish = 0; iFinish < 4; iFinish++)
	{
		Sleep(5);
		//检测写数据是否完成
		iRet = EepromBaseOptRd(ADDR_STS, &status);
		if ((1 == (status & 0x0001)))//判断读写是否出错
		{
			//如果读写无应答
			break;
		}
		else if (0 == ((status & 0x0002) >> 1))//判断读写是否完成
		{
			//如果没有完成
			continue;
		}

		if ((0 == (status & 0x0001)) && (1 == ((status & 0x0002) >> 1)))//判断读写是否出错
		{
			//如果读写无错误并且完成
			break;;
		}
	}

	if (iFinish >= 4)
	{
		return RTN_PCI_FPGA_ERR;
	}

	comNum = 1;
	iRet = m_pCom->ComRdFpgaHandle((comAddr+ ADDR_READ_DATA), (int16*)&data_tmp[8], comNum, m_des_id, NULL);//
	*byte_data = data_tmp[8];

	return iRet;
}

int16 CEeprom::EepromWrite(Uint16 byte_addr, Uint8* byte_data, Uint16 byte_num)
{
	int16 iRet;
	Uint16 i, j;//, iFinish;
//	Uint8 status;
	Uint8 read_data;
	bool write_ok=false, read_ok=false;

	if (m_pCom == NULL) return RTN_NULL_POINT;


// 	if ((byte_addr > 255) || (byte_num > 256))
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	if ((byte_addr + byte_num)>256)
// 	{
// 		return RTN_PARAM_ERR;
// 	}

	for (i = 0; i < byte_num; i++)
	{
		for (j = 0; j < 100; j++)
		{
			//先写数据
			iRet = EepromWrite8bit(byte_addr + i, byte_data[i]);
			if (0 == iRet)
			{
				break;
			}
		}

		if (j >= 100)
		{
			return iRet;
		}

		for (j = 0; j < 10; j++)
		{
			//读取写入的数据进行校验
			iRet = EepromRead8bit(byte_addr + i, &read_data);
			if (0 == iRet)
			{
				break;
			}
		}

		if ( j< 10)
		{
			if (read_data == byte_data[i])
			{
				continue;// return RTN_SUCCESS;
			}
			else
			{
				return CMD_ERROR_READ_BLOCK;
			}
		}
		else
		{
			return iRet;
		}
	}

	return RTN_SUCCESS;
}

int16 CEeprom::EepromRead(Uint16 byte_addr, Uint8* byte_data, Uint16 byte_num)
{
	int16 iRet;
	Uint16 i, j;// , iFinish;
//	Uint8 status;
	bool  read_ok = false;

	if (m_pCom == NULL) return RTN_NULL_POINT;

// 	if ((byte_addr > 255) || (byte_num > 256))
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	if ((byte_addr + byte_num) > 256)
// 	{
// 		return RTN_PARAM_ERR;
// 	}

	for (i = 0; i < byte_num; i++)
	{
		for (j = 0; j < 100; j++)
		{
			//读取写入的数据进行校验
			iRet = EepromRead8bit(byte_addr + i, &byte_data[i]);
			if (0 == iRet)
			{
				break;
			}
		}		

		if (j >= 100)
		{
			return RTN_PCI_FPGA_ERR;
		}
	}

	return RTN_SUCCESS;
}
