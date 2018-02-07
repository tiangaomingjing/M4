#include "stdafx.h"
#include "FPGAUpdate.h"
#include <fstream>
using namespace std;

CFPGAUpdate::CFPGAUpdate()
{
	m_pCom = NULL;
	m_des_id = 0;
	m_byte_write = 0;
}

CFPGAUpdate::~CFPGAUpdate()
{
	m_pCom = NULL;
}

//设置命令更新启动位
int16 CFPGAUpdate::SetRemoteUpdataStartbit()
{
	int16 data = 1; //bit0置1
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;

	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_CTL;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_CTL;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}

	int16 Data = data;
	int16 comNum = 1;
	int16 rtn = pCom->ComWrFpgaHandle(comAddr, &Data, comNum, m_des_id, NULL);
	return rtn;

}
int16 CFPGAUpdate::CheckRemoteUpdataState(int32 delaytimes)
{
	//检查命令是否完成
	int16 iRet;
	int16 data;
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_CTL;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_CTL;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	int16 comNum = 1;
	bool bSuccess = false;

	while (delaytimes--)
	{
		iRet = pCom->ComRdFpgaHandle(comAddr, &data, comNum, m_des_id, NULL);////查询完成标志
		if (iRet == 0)
		{
			if ((data & 0x0004)) //bit2 finish
			{
				bSuccess = true;
				break;
			}
		}
	}

	if (!bSuccess)
	{
		return RTN_UPDATE_WAIT_OVERTIME;
	}

	if (0 == iRet)
	{
		if (data & 0x0002) // bit1 error
		{
			return RTN_UPDATE_FPGA_OP_ERR;
		}
	}
	return iRet;
}
int16 CFPGAUpdate::SetRemoteUpdataReadRequest(Uint32 flash_addr, Uint16 iLength)
{
	//首先写入读命令
	int16 iRet;
	Uint8 data[30] = { 0 };

	//命令
	data[0] = CMD_READ;

	int16 addrLo = LOWORD(flash_addr);
	Uint8 addrLoLo = LOBYTE(addrLo);
	Uint8 addrLoHi = HIBYTE(addrLo);
	int16 addrHi = HIWORD(flash_addr);
	Uint8 addrHiLo = LOBYTE(addrHi);

	//取24bit地址
	data[1] = addrLoLo;
	data[2] = addrLoHi;
	data[3] = addrHiLo;

	Uint8 lengthLo = LOBYTE(iLength * 2);
	Uint8 lengthHi = HIBYTE(iLength * 2);

	//长度
	data[4] = lengthLo;
	data[5] = lengthHi;



	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	int16 comNum = 3;

	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(data), comNum, m_des_id, NULL); //写入读取命令
	if (iRet != 0)
	{
		return iRet;
	}

	//设置命令更新启动位
	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}
	//检查命令是否完成
	iRet = CheckRemoteUpdataState();
	if (iRet != 0)
	{
		return iRet;
	}
	return iRet;
}
int16 CFPGAUpdate::ProtectOff()
{
	int16 iRet;
	Uint8 data[20] = { 0 };
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}

	int16 comNum = 3;
	data[0] = CMD_PRET_OFF;					//命令
	data[4] = 1;							//lenth写1

	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(data), comNum, m_des_id, NULL);//写入protect off 命令
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = CheckRemoteUpdataState(10000);
	if (iRet != 0)
	{
		return iRet;
	}
	return iRet;
}
int16 CFPGAUpdate::ProtectOn()
{
	int16 iRet;
	Uint8 data[20] = { 0 };
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}

	int16 comNum = 3;
	data[0] = CMD_PRET_ON;					//命令
	data[4] = 1;							//lenth写1

	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(data), comNum, m_des_id, NULL);//写入protect on 命令
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = CheckRemoteUpdataState();
	if (iRet != 0)
	{
		return iRet;
	}
	return iRet;
}
int16 CFPGAUpdate::EraseData(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{

	int16 iRet;
	Uint8 data[20] = { 0 };
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}

	int16 comNum = 3;
	data[0] = CMD_ERASE;					//命令
	data[4] = 1;							//lenth写1

	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(data), comNum, m_des_id, NULL); //写入erase 命令
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}

	int32 num = 1000000;
	//!progress高16位置1，用来给界面提示当前正处于擦除状态
	int16 highSet;
	highSet = (int16)(1 << 15);
	for (int32 i = 0; i < num; i++)
	{
		iRet = CheckRemoteUpdataState(100);
		if (iRet == 0)
			break;
		if (i % 10 == 0)
		{
			progress++;
			progress |= highSet;
			if ((progress&(~highSet))>100)
				progress = highSet;
			//      std::cout << "erase num=" << i << "  progress=" << progress << "   progress&(~highSet)=" << (progress&(~highSet))<<std::endl;
			if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptrv, &progress);
		}
	}

	//iRet = CheckRemoteUpdataState(com_type, stationId,100000000);
	if (iRet != 0)
	{
		return iRet;
	}
	return iRet;
}
int16 CFPGAUpdate::GetFPGAByteNum(char* pFileName, uint32& byte_num)
{
	fstream file;
	file.open(pFileName, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		//		ProtectOn(com_type, stationId);
		return RTN_FILE_CREATE_FAIL; //文件打开错误
	}
	unsigned char pBuffer[SECTOR_SIZE];
	file.seekg(0, file.end);
	uint32 file_size = (uint32)file.tellg();
	int file_sector_num = (int)((file_size + SECTOR_SIZE - 1) / SECTOR_SIZE);
	uint32 unuseful_byte_num = 0;

	int read_num = file_size % SECTOR_SIZE;
	if (read_num == 0)
	{
		read_num = SECTOR_SIZE;
	}
	bool find_end = false;
	for (int i = file_sector_num-1; i >= 0; i--)
	{
		file.seekg(i*SECTOR_SIZE, file.beg);
		file.read((char*)pBuffer, read_num);
		for (int j = read_num - 1; j >= 0; j--)
		{
			if (pBuffer[j] == 0xFF)
			{
				unuseful_byte_num++;
				continue;
			}
			else
			{
				byte_num = file_size - unuseful_byte_num;
				file.close();
				return RTN_SUCCESS;
			}
		}
		read_num = SECTOR_SIZE;
	}
	file.close();
	byte_num = 0;//
	return RTN_IMPOSSIBLE_ERR;
}

int16 CFPGAUpdate::EraseFPGAData(uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	void* ptr = ptrv;
	progress = 10;
	if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);
	int sector_num = (byte_num + SECTOR_SIZE - 1) / SECTOR_SIZE;
	for (int i = 0; i < sector_num;i++)
	{
		short rtn = EraseSectorData(SECTOR_SIZE*i, tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			rtn = EraseSectorData(SECTOR_SIZE*i, tpfUpdataProgressPt, ptrv, progress);
			if (rtn)
			{
				return rtn;
			}
		}
	}
	return RTN_SUCCESS;
}

int16 CFPGAUpdate::EraseSectorData(uint32 byte_address, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{

	int16 iRet;
	Uint8 data[20] = { 0 };
	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}

	int16 comNum = 3;
	data[0] = CMD_SECTOR_ERASE;					//命令
	data[1] = byte_address & 0xFF;
	data[2] = (byte_address>>8) & 0xFF;
	data[3] = (byte_address>>16) & 0xFF;
	data[4] = 1;							//lenth写1

	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(data), comNum, m_des_id, NULL); //写入erase 命令
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}

	int32 num = 1000000;
	//!progress高16位置1，用来给界面提示当前正处于擦除状态
	int16 highSet;
	highSet = (int16)(1 << 15);
	for (int32 i = 0; i < num; i++)
	{
		iRet = CheckRemoteUpdataState(100);
		if (iRet == 0)
			break;
		if (i % 10 == 0)
		{
			progress++;
			progress |= highSet;
			if ((progress&(~highSet))>100)
				progress = highSet;
			//      std::cout << "erase num=" << i << "  progress=" << progress << "   progress&(~highSet)=" << (progress&(~highSet))<<std::endl;
			if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptrv, &progress);
		}
	}

	//iRet = CheckRemoteUpdataState(com_type, stationId,100000000);
	if (iRet != 0)
	{
		return iRet;
	}
	return iRet;
}

int16 CFPGAUpdate::GetFpgaFlashData(Uint32 flash_addr, int16 *Getbuf, Uint16 iLength)
{
	int16 iRet;
	short rtn = RTN_SUCCESS;
	if (iLength > MAX_OP_WORD_NUM || (flash_addr & 0x0) == 0x1)
	{
		return RTN_PARAM_OVERFLOW;
	}

// 	int beg_sector = (int)(flash_addr / SECTOR_SIZE);
// 	int end_sector = (int)((flash_addr + iLength * 2 - 1) / SECTOR_SIZE);
// 	if (beg_sector != end_sector)
// 	{
// 		Uint16 sub_byte_size = Uint16(end_sector*SECTOR_SIZE - flash_addr);
// 		rtn = GetFpgaFlashData(flash_addr, Getbuf, sub_byte_size >> 1);
// 		if (rtn)
// 		{
// 			return rtn;
// 		}
// 		flash_addr += sub_byte_size;
// 		iLength -= (sub_byte_size >> 1);
// 		Getbuf += (sub_byte_size >> 1);
// 	}

	//设置读请求
	iRet = SetRemoteUpdataReadRequest(flash_addr, iLength);
	if (iRet != 0)
	{
		return iRet;
	}

	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr)+3; //地址不同？;
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr)+6;
	}
	int16 comNum = iLength;

	iRet = pCom->ComRdFpgaHandle(comAddr, Getbuf, comNum, m_des_id, NULL);
	if (iRet)
	{
		return iRet;
	}
	// 	for (int16 i = 0; i < iLength; ++i)
	// 	{
	// 		//读数据
	// 		iRet = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_READ, comAddr, (int16*)(&Getbuf[i]), comNum, stationId);
	// 		if (0 != iRet)
	// 		{
	// 			return -1;
	// 		}
	// 		comAddr+=2;
	// 	}
	return 0;
}
int16 CFPGAUpdate::SendFpgaFlashData(Uint32 flash_addr, int16 *Sendbuf, Uint16 iLength)
{
	int16 iRet;
	Uint8 data[300] = { 0 };
	short rtn = RTN_SUCCESS;
	if (iLength > MAX_OP_WORD_NUM || (flash_addr&0x0) == 0x1)
	{
		return RTN_PARAM_OVERFLOW;
	}

// 	int beg_sector = (int)(flash_addr / SECTOR_SIZE);
// 	int end_sector = (int)((flash_addr + iLength * 2 - 1) / SECTOR_SIZE);
// 	if (beg_sector != end_sector)
// 	{
// 		Uint16 sub_byte_size = Uint16(end_sector*SECTOR_SIZE - flash_addr);
// 		rtn = SendFpgaFlashData(flash_addr, Sendbuf, sub_byte_size >> 1);
// 		if (rtn)
// 		{
// 			return rtn;
// 		}
// 		flash_addr += sub_byte_size;
// 		iLength -= (sub_byte_size >> 1);
// 		Sendbuf += (sub_byte_size >> 1);
// 	}

	//命令
	data[0] = CMD_WRITE;

	int16 addrLo = LOWORD(flash_addr);
	Uint8 addrLoLo = LOBYTE(addrLo);
	Uint8 addrLoHi = HIBYTE(addrLo);
	int16 addrHi = HIWORD(flash_addr);
	Uint8 addrHiLo = LOBYTE(addrHi);

	//取24bit地址
	data[1] = addrLoLo;
	data[2] = addrLoHi;
	data[3] = addrHiLo;

	Uint8 lengthLo = LOBYTE(iLength * 2);
	Uint8 lengthHi = HIBYTE(iLength * 2);

	//长度
	data[4] = lengthLo;
	data[5] = lengthHi;

	//将数据放到buffer中从6开始
	memcpy_s(&data[6], iLength*sizeof(Uint16), Sendbuf, iLength*sizeof(Uint16));

	int16 com_addr;
	int16 base_addr;
	int16 comAddr;

	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	if (pCom->GetComProtocolType() == COM_PROTOCO_NET)
	{
		com_addr = REMOTE_FPGA_DATA_START;
		base_addr = FPGA_DSPA_BASEADDR;
		comAddr = base_addr + (com_addr);
	}
	else if (pCom->GetComProtocolType() == COM_PROTOCO_RINGNET)
	{
		com_addr = RN_REMOTE_FPGA_DATA_START;
		base_addr = FPGA_RN_RMT_START_OFST;
		comAddr = base_addr + (com_addr);
	}
	int16 comNum = 1;


	//for (int16 i = 0; i < iLength + 3;++i)
	//{
	//	//向里面压数据
	//	iRet = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr, (int16*)(&data[i*2]), comNum, stationId);
	//	if (0 != iRet)
	//	{
	//		return -1;
	//	}
	//	if (com_type == GTSD_COM_TYPE_NET)
	//	{
	//		//short地址
	//		comAddr++;
	//	}
	//	else if (com_type == GTSD_COM_TYPE_RNNET)
	//	{
	//		//byte地址
	//		comAddr += 2;
	//	}

	//}

	//提高效率，一次写200byte+6byte包头
	//向里面压数据
	iRet = pCom->ComWrFpgaHandle(comAddr, (int16*)(&data[0]), (iLength + 3), m_des_id, NULL);
	if (0 != iRet)
	{
		return iRet;
	}

	iRet = SetRemoteUpdataStartbit();
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = CheckRemoteUpdataState(1000);
	if (iRet != 0)
	{
		return iRet;
	}

	return 0;
}
int32 CFPGAUpdate::CheckFFNumber(short* buffer, int lenth)
{
	//查找连续的0xff
	int32 ffnum = 0;
	for (int32 i = 0; i < lenth; i++)
	{
		if ((Uint16)(buffer[i]) != 0xffff)
			break;

		ffnum++;
	}
	return ffnum;
}
int16 CFPGAUpdate::WriteFPGAFileToFlash(char* pFileName, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	void* ptr = ptrv;
	int iRet;
	iRet = ProtectOff();//关闭写保护
	if (iRet != 0)
	{
		return iRet;
	}
	//////////////////////////////////////////////////////////////////////////
// 	{
// 		int i;
// 		iRet = EraseData(tpfUpdataProgressPt, ptr, progress); //清除fpga flash
// 		const int32 MAX_NUM_BYTE = 1 << 23;
// 		int16* pData = new int16[MAX_NUM_BYTE / 2];
// 		int16* pReadData = new int16[MAX_NUM_BYTE / 2];
// 		for (i = 0; i < (1 << 23);i=i+2)
// 		{
// 			pData[i / 2] = i;
// 		}
// 		for (i = 0; i < (1 << 23); i += BUF_LEN)
// 		{
// 			iRet = SendFpgaFlashData(i, &pData[i / 2], BUF_LEN / 2);//the param len must less than 127.
// 			//写不成功再尝试写多一次
// 		}
// 		for (i = 0; i < (1 << 23); i += BUF_LEN)
// 		{
// 			iRet = GetFpgaFlashData(i, &pData[i / 2], BUF_LEN / 2);//the param len must less than 127.
// 			//写不成功再尝试写多一次
// 		}
// 		int err_cnt = 0;
// 		for (i = 0; i < (1 << 23); i = i + 2)
// 		{
// 			if (pData[i / 2] == pReadData[i / 2])
// 			{
// 				err_cnt++;
// 			}
// 		}
// 		delete pData;
// 		delete pReadData;
// 		return RTN_SUCCESS;
// 	}















	//////////////////////////////////////////////////////////////////////////
//	int32 byte_num = 0;
	iRet = GetFPGAByteNum(pFileName, m_byte_write);
	if (iRet)
	{
		return iRet;
	}
	iRet = EraseFPGAData(m_byte_write, tpfUpdataProgressPt, ptr, progress);
	if (iRet)
	{
		return iRet;
	}

// 	iRet = EraseData(tpfUpdataProgressPt, ptr, progress); //清除fpga flash
// 	if (iRet != 0)
// 	{
// 		//		ProtectOn(com_type, stationId);
// 		return iRet;
// 	}
	//  [8/2/2017 googol]
	//百分比进度
// 	progress = 10;
// 	if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);

// 	//打开文件
// 	fstream file;
// 	file.open(pFileName, ios::in | ios::out | ios::binary);
// 	if (!file)
// 	{
// 		//		ProtectOn(com_type, stationId);
// 		return RTN_FILE_CREATE_FAIL; //文件打开错误
// 	}

// 	//首先将数据读出来
// 	int16 buffer[BUF_LEN] = { 0 };
// 	int16 real_read_lenth = 0;
// 	int16 finish_flag = 0;//是否读取完成标志
// 	Uint32 flash_addr = 0;
// 	Uint32 sum_byte_lenth = 0;
// 	Uint32 index = 0;
// 	Uint32 times = 0;//需要读取的次数
// 	Uint32 times_bk = 0;
// 	while (!finish_flag)
// 	{
// 		//读取BUF_LEN个数据，返回真正读取的数据，该条件的前提是后面的ffff足够多
// 		file.read((int8*)&buffer, sizeof(Uint16)*BUF_LEN);
// 
// 		sum_byte_lenth += 2 * BUF_LEN;
// 
// 		//判断其中的数据是否有连续的FF_LEN个0xffff
// 		int32 number = CheckFFNumber(buffer, BUF_LEN);
// 
// 		//如果全是0xff那么就说明已经读取到最后的无用区域了
// 		if (number == BUF_LEN)
// 		{
// 			finish_flag = 1;
// 			m_byte_write = sum_byte_lenth;
// 		}
// 		else
// 		{
// 			finish_flag = 0;
// 		}
// 		index++;
// 		if (index > 1400)
// 		{
// 			//百分比
// 			if (index % 20 == 0)
// 			{
// 				progress = 13;
// 				if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);
// 			}
// 		}
// 	}
// 	index = 0;
// 	//get the times
// 	times = m_byte_write / (2 * BUF_LEN);
// 	times_bk = times;
// 	file.close();

	//百分比
	progress = 15;
	if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);

	int16 buffer[BUF_LEN] = { 0 };
	Uint32 flash_addr = 0;
	Uint32 index = 0;
	Uint32 times = m_byte_write / (2 * BUF_LEN) + 1;//需要读取的次数
	Uint32 times_bk = times;
	//打开文件
	fstream file;
	file.open(pFileName, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		//		ProtectOn(com_type, stationId);
		return 4; //文件打开错误
	}
	int retSend = 0;
	int retValue = 0;
	while (times != 0)
	{
		//读取BUF_LEN个数据，返回真正读取的数据，该条件的前提是后面的ffff足够多
		file.read((char*)&buffer, sizeof(Uint16)*BUF_LEN);

		//放在外面为了读取到全是ffff的时候还是写入一次
		for (int i = 0; i < 2; i++)
		{
			//将数据写入,一次写100个short
			retSend = SendFpgaFlashData(flash_addr, &buffer[i*(BUF_LEN >> 1)], BUF_LEN / 2);//the param len must less than 127.
			//写不成功再尝试写多一次
			if (retSend != 0)
				retSend = SendFpgaFlashData(flash_addr, &buffer[i*(BUF_LEN >> 1)], BUF_LEN / 2);//the param len must less than 127.
			if (retSend != 0)
			{
				retValue = retSend;
				times = 1;
				break;
			}
			//地址增加
			flash_addr += (2 * (BUF_LEN >> 1));
		}
		index++;

		if (index % 10 == 0)
		{
			progress = 15 + (int16)((((double)index) / times_bk) * 35);
			if (progress >= 50)
			{
				progress = 50;
			}
			if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);
		}

		times--;
	}
	file.close();
	if (retValue)
	{
		progress = 100;
		if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);
		return retValue;
	}
	//////////////////////////////////////////////////////////////////////////
	////读数数据进行校验
	//打开文件
	file.open(pFileName, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		//		ProtectOn(com_type, stationId);
		return RTN_FILE_CREATE_FAIL; //文件打开错误
	}

	times = times_bk;
	flash_addr = 0;
	index = 0;
	while (times != 0)
	{
		int16 rx_buffer[BUF_LEN / 2];
		//读取BUF_LEN个数据，返回真正读取的数据，该条件的前提是后面的ffff足够多
		file.read((char*)buffer, sizeof(Uint16)*BUF_LEN);

		//放在外面为了读取到全是ffff的时候还是写入一次
		for (int i = 0; i < 2; i++)
		{
			//将数据写入,一次写100个short
			retValue = GetFpgaFlashData(flash_addr, rx_buffer, BUF_LEN / 2);//the param len must less than 127.
			//写不成功再尝试写多一次
			if (retValue != 0)
				retValue = GetFpgaFlashData(flash_addr, rx_buffer, BUF_LEN / 2);//the param len must less than 127.
			if (retValue != 0)
			{
				times = 1;
				break;
			}
			int check_cnt = 0;
			for (int j = 0; j < BUF_LEN / 2; j++)
			{
				if (rx_buffer[j] != buffer[i*(BUF_LEN / 2) + j])
				{
					if (check_cnt == 0) //try read once time
					{
						check_cnt++;
						retValue = GetFpgaFlashData(flash_addr, rx_buffer, BUF_LEN / 2);//the param len must less than 127.
						if (retValue != 0)
						{
							break;
						}
						else
						{
							j--;
							continue;
						}
					}
					else
					{
						retValue = RTN_UPDATE_CAMPARE_ERR;
						break;
					}
				}
			}
			if (retValue)
			{
				break;
			}
			//地址增加
			flash_addr += (2 * (BUF_LEN >> 1));
		}
		if (retValue)
		{
			break;
		}
		index++;

		if (index % 10 == 0)
		{
			progress = 50 + (int16)((((double)index) / times_bk) * 50);
			if (progress >= 100)
			{
				progress = 100;
			}
			if (tpfUpdataProgressPt)(*tpfUpdataProgressPt)(ptr, &progress);
		}

		times--;
	}
	file.close();
	//屏蔽该部分，仿真器无法烧写。
	//iRet = ProtectOn(com_type, stationId);//open写保护
	//if (iRet != 0)
	//{
	//	return 6;
	//}
	return retValue;
}


int16 CFPGAUpdate::ReadFPGADataToFile(char* FileName, Uint32 Bytelenth)
{
	if (Bytelenth == 0)
	{
		return RTN_PACKET_ERR;
	}
	Uint32 flash_addr = 0;
	int16 rx_buffer[100];
	int16 rx_buffer_tmp[100];
	int rtn = 0;
	Uint16 iLength;
	const Uint16 MAX_WORD_NUM = 100;
	int err_cnt = 0;

	fstream file;
	file.open(FileName, ios::in | ios::out | ios::trunc | ios::binary);

	while (flash_addr < Bytelenth)
	{
		if (Bytelenth - flash_addr >(MAX_WORD_NUM * 2))
		{
			iLength = MAX_WORD_NUM;
		}
		else
		{
			iLength = Uint16(((Bytelenth - flash_addr) + 1) >> 1);
		}
		rtn = GetFpgaFlashData(flash_addr, rx_buffer, iLength);//the param len must less than 127.
		if (rtn)
		{
			rtn = GetFpgaFlashData(flash_addr, rx_buffer, iLength);//the param len must less than 127.
			if (rtn) break;
		}

		rtn = GetFpgaFlashData(flash_addr, rx_buffer_tmp, iLength);//the param len must less than 127.
		if (rtn)
		{
			rtn = GetFpgaFlashData(flash_addr, rx_buffer_tmp, iLength);//the param len must less than 127.
			if (rtn) break;
		}
		for (int i = 0; i < iLength; i++)
		{
			if (rx_buffer_tmp[i] != rx_buffer[i]) //check_err
			{
				err_cnt++;
				break;
			}
		}
		if (err_cnt > 1) //try read two time, and err.
		{
			rtn = RTN_UPDATE_CAMPARE_ERR;
			break;
		}
		else //check ok
		{
			err_cnt = 0;
			file.write((int8*)rx_buffer, iLength * 2);
			flash_addr = flash_addr + iLength * 2;
		}
	}

	file.close();
	return rtn;
	// 	if (Bytelenth == 0)
	// 	{
	// 		return -1;
	// 	}
	// 	Uint32 flash_addr = 0;
	// 	int16* buffer = new int16[Bytelenth >> 1];
	// 	int16* buffer_old = new int16[Bytelenth]; //因为写下去的每个16bit数据占了32bit
	// 	
	// 	//每次读取100个short
	// 	for (Uint32 i = 0; i < (Bytelenth / (BUF_LEN));++i)
	// 	{
	// 		GetFpgaFlashData(com_type, flash_addr, &buffer_old[i*(BUF_LEN >> 1)], (BUF_LEN >> 1), stationId);//the param len must less than 127.
	// 		//地址增加
	// 		flash_addr += (2 * (BUF_LEN >> 1));
	// 	}
	// 
	// 	for (Uint32 i = 0; i < (Bytelenth >> 1);++i)
	// 	{
	// 		buffer[i] = buffer_old[i * 2];
	// 	}
	// 	//打开文件
	// 	fstream file;
	// 	file.open(FileName.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
	// 	file.write((int8*)buffer, Bytelenth);
	// 	file.close();
	// 
	// 	delete buffer;
	// 	delete buffer_old;
	// 	return 0;
}
