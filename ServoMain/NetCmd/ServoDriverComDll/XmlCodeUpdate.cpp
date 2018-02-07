#include "stdafx.h"
#include "BaseReturn_def.h"
#include "XmlCodeUpdate.h"


CXmlCodeUpdate::CXmlCodeUpdate()
{
	m_EncodeNumMax = 0;
}


CXmlCodeUpdate::~CXmlCodeUpdate()
{
}

short CXmlCodeUpdate::EraseXmlFlash( void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 size = XML_HEAD_SIZE ;
	short rtn = RTN_SUCCESS;

	if (m_EncodeNum == 0)
		return RTN_SUCCESS;

	size += sizeof(m_EncodeNum);
	for (int i = 0; i < m_EncodeNum; i++)
	{
		size += sizeof(m_pEncodeByteNumList[i]);
		size += sizeof(m_pEncodeTypeList[i]);
		size += m_pEncodeByteNumList[i];
		size += m_pEncodeByteNumList[i] & 0x1;//keep  the size is even num;
	}
	uint32 erase_cnt = 0;
	uint32 ereas_address = SECTOR_SIZE * XML_START_SECTOR_ID;

	progress = 30;
	if (tpfUpdataProgressPt) tpfUpdataProgressPt(ptrv, &progress);

	while (erase_cnt < size)
	{
		rtn = EraseSectorData(ereas_address, tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}

		progress = 30 + (int16)(60 * (erase_cnt / size));
		if (tpfUpdataProgressPt) tpfUpdataProgressPt(ptrv, &progress);

		erase_cnt += SECTOR_SIZE;
		ereas_address += SECTOR_SIZE;
	}
	return rtn;
}
short CXmlCodeUpdate::CheckXmlFlashValid(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	const int BUFFER_SIZE = 100;
	char buffer[BUFFER_SIZE];
	short rtn = RTN_SUCCESS;

	progress = 30;
	if (tpfUpdataProgressPt) tpfUpdataProgressPt(ptrv, &progress);

	rtn = ReadFlashData(CFPGAUpdate::SECTOR_SIZE*XML_START_SECTOR_ID, buffer, BUFFER_SIZE, tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}

	if (CXmlCode::CompareChars(buffer, XML_START_FLAG, XML_START_FLAG_SIZE) == false)
	{
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			if (buffer[i] != (char)0xFFFF)
				return RTN_FILE_ERR_FORMAT;
		}
		return RTN_SUCCESS;
	}

	if (CXmlCode::CompareChars(buffer + XML_START_FLAG_SIZE, XML_VERSION, 16) == false)
	{
		return RTN_FILE_ERR_MISSMATCH;
	}
	return RTN_SUCCESS;

}
short CXmlCodeUpdate::WriteFlashData(Uint32 flash_addr, void *Sendbuf, uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 byte_cnt = 0;
	short rtn = RTN_SUCCESS;
	int16* pData = (int16*)Sendbuf;

	if (byte_num & 0x1)
		return RTN_PARAM_ERR;
	if (tpfUpdataProgressPt)
	{
		progress = 10;
		tpfUpdataProgressPt(ptrv, &progress);
	}
	while (byte_cnt < byte_num)
	{
		uint16 write_num = byte_num - byte_cnt >(MAX_OP_WORD_NUM << 1) ? (MAX_OP_WORD_NUM << 1) : (uint16)(byte_num - byte_cnt);

		rtn = SendFpgaFlashData(flash_addr, &pData[byte_cnt>>1], write_num >> 1);
		if (rtn)
		{
			rtn = SendFpgaFlashData(flash_addr, &pData[byte_cnt >> 1], write_num >> 1);
			return rtn;
		}
// 		char pDataRead[500];
// 		rtn = GetFpgaFlashData(flash_addr, (int16*)pDataRead, write_num >> 1);
// 		if (rtn)
// 		{
// 			return rtn;
// 		}
// 		if (CompareChars(pDataRead, (char*)(&pData[byte_cnt >> 1]), write_num) == false)
// 		{
// 			return RTN_CHECK_RW_ERR;
// 		}

		flash_addr += write_num;
		byte_cnt += write_num;

		if (tpfUpdataProgressPt)
		{
			progress = 10 + (int16)(70*byte_cnt/byte_num);
			tpfUpdataProgressPt(ptrv, &progress);
		}
	}
	return rtn;
}

short CXmlCodeUpdate::ReadFlashData(Uint32 flash_addr, void *Sendbuf, uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 byte_cnt = 0;
	short rtn = RTN_SUCCESS;
	int16* pData = (int16*)Sendbuf;

	if (byte_num & 0x1)
		return RTN_PARAM_ERR;

	if (tpfUpdataProgressPt)
	{
		progress = 10;
		tpfUpdataProgressPt(ptrv, &progress);
	}

	while (byte_cnt < byte_num)
	{
		uint16 write_num = byte_num - byte_cnt >(MAX_OP_WORD_NUM << 1) ? (MAX_OP_WORD_NUM << 1) : (uint16)(byte_num - byte_cnt);

		rtn = GetFpgaFlashData(flash_addr, &pData[byte_cnt >> 1], write_num >> 1);
		if (rtn)
		{
			rtn = GetFpgaFlashData(flash_addr, &pData[byte_cnt >> 1], write_num >> 1);
			return rtn;
		}
		flash_addr += write_num;
		byte_cnt += write_num;

		if (tpfUpdataProgressPt)
		{
			progress = 10 + (int16)(70 * byte_cnt / byte_num);
			tpfUpdataProgressPt(ptrv, &progress);
		}
	}
	return rtn;
}

short CXmlCodeUpdate::ProgramXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 size = XML_HEAD_SIZE;
	short rtn = RTN_SUCCESS;

	if (m_EncodeNum == 0)
		return RTN_SUCCESS;

	uint32 flash_address = SECTOR_SIZE * XML_START_SECTOR_ID;
	rtn = WriteFlashData(flash_address, XML_START_FLAG, XML_START_FLAG_SIZE, tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	flash_address += XML_START_FLAG_SIZE;
	rtn = WriteFlashData(flash_address, XML_VERSION, XML_VERSION_SIZE, tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	flash_address += XML_VERSION_SIZE;

	rtn = WriteFlashData(flash_address, &m_EncodeNum, sizeof(m_EncodeNum), tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	flash_address += sizeof(m_EncodeNum);
	for (int i = 0; i < m_EncodeNum; i++)
	{

		//////////////////////////////////////////////////////////////////////////
		rtn = WriteFlashData(flash_address, &m_pEncodeByteNumList[i], sizeof(m_pEncodeByteNumList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		flash_address += sizeof(m_pEncodeByteNumList[i]);
		//////////////////////////////////////////////////////////////////////////
		rtn = WriteFlashData(flash_address, &m_pEncodeTypeList[i], sizeof(m_pEncodeTypeList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		flash_address += sizeof(m_pEncodeTypeList[i]);
		//////////////////////////////////////////////////////////////////////////
		if (m_pEncodeByteNumList[i] & 0x1) //odd num
		{
			rtn = WriteFlashData(flash_address, m_pEncodeBufferList[i], m_pEncodeByteNumList[i] & 0xFFFFFFFE, tpfUpdataProgressPt, ptrv, progress);
			if (rtn)
			{
				return rtn;
			}
			flash_address += (m_pEncodeByteNumList[i] & 0xFFFFFFFE);
			short data = 0xFF00 | m_pEncodeBufferList[i][m_pEncodeByteNumList[i]-1];

			rtn = WriteFlashData(flash_address, &data, 2, tpfUpdataProgressPt, ptrv, progress);
			if (rtn)
			{
				return rtn;
			}
			flash_address += 2;
		}
		else
		{
			rtn = WriteFlashData(flash_address, m_pEncodeBufferList[i], m_pEncodeByteNumList[i], tpfUpdataProgressPt, ptrv, progress);
			if (rtn)
			{
				return rtn;
			}
			flash_address += m_pEncodeByteNumList[i];
		}
	}
	//////////////////////////////////////////////////////////////////////////
	return RTN_SUCCESS;
}
short CXmlCodeUpdate::ReadXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 size = XML_HEAD_SIZE;
	short rtn = RTN_SUCCESS;

	uint32 flash_address = SECTOR_SIZE * XML_START_SECTOR_ID + XML_START_FLAG_SIZE + XML_VERSION_SIZE;
	ReleaseEncodeBuffer();
	rtn = ReadFlashData(flash_address, &m_EncodeNum, sizeof(m_EncodeNum), tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	flash_address += sizeof(m_EncodeNum);
	if (m_EncodeNum > m_EncodeNumMax)
	{
		m_EncodeNum = m_EncodeNumMax;
	}
	
	if (m_EncodeNum == 0)
		return RTN_FILE_ERR_MISSMATCH;
	m_pEncodeByteNumList = new int[m_EncodeNum];
	m_pEncodeBufferList = new char*[m_EncodeNum];
	m_pEncodeTypeList = new int[m_EncodeNum];
	if (m_pEncodeByteNumList == NULL || m_pEncodeBufferList == NULL || m_pEncodeTypeList == NULL)
		return RTN_MALLOC_FAIL;

	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_EncodeNum; i++)
	{

		//////////////////////////////////////////////////////////////////////////
		rtn = ReadFlashData(flash_address, &m_pEncodeByteNumList[i], sizeof(m_pEncodeByteNumList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		flash_address += sizeof(m_pEncodeByteNumList[i]);
		//////////////////////////////////////////////////////////////////////////
		rtn = ReadFlashData(flash_address, &m_pEncodeTypeList[i], sizeof(m_pEncodeTypeList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		flash_address += sizeof(m_pEncodeTypeList[i]);
		//////////////////////////////////////////////////////////////////////////
		int buffer_size = ((m_pEncodeByteNumList[i] + 1) >> 1) << 1; //keep the buffer_size to be even num
		m_pEncodeBufferList[i] = NULL;
		m_pEncodeBufferList[i] = new char[buffer_size];
		if (m_pEncodeBufferList[i] == NULL)
		{
			return RTN_MALLOC_FAIL;
		}

		rtn = ReadFlashData(flash_address, m_pEncodeBufferList[i], buffer_size, tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		flash_address += buffer_size;
	}
	//////////////////////////////////////////////////////////////////////////
	return RTN_SUCCESS;
}
short CXmlCodeUpdate::CheckXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress)
{
	uint32 size = XML_HEAD_SIZE;
	short rtn = RTN_SUCCESS;
	char head_flag[XML_HEAD_SIZE];

	uint32 flash_address = SECTOR_SIZE * XML_START_SECTOR_ID;
	rtn = ReadFlashData(flash_address, &head_flag, XML_HEAD_SIZE, tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	rtn = memcmp(head_flag, XML_START_FLAG, XML_START_FLAG_SIZE);
	if (rtn)
	{
		return RTN_CHECK_RW_ERR;
	}

	rtn = memcmp(head_flag + XML_START_FLAG_SIZE, XML_VERSION, XML_VERSION_SIZE);
	if (rtn)
	{
		return RTN_CHECK_RW_ERR;
	}
	flash_address += XML_HEAD_SIZE;
	//////////////////////////////////////////////////////////////////////////

	/////////////////////////////////check num/////////////////////////////////////////
	
	int EncodeNumTmp;
	rtn = ReadFlashData(flash_address, &EncodeNumTmp, sizeof(m_EncodeNum), tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
	{
		return rtn;
	}
	if (EncodeNumTmp != m_EncodeNum)
		return RTN_CHECK_RW_ERR;
	flash_address += sizeof(m_EncodeNum);
	////////////////////////////check num///////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_EncodeNum; i++)
	{
		int value;
		//////////////////////////////////////////////////////////////////////////
		rtn = ReadFlashData(flash_address, &value, sizeof(m_pEncodeByteNumList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		if (value != m_pEncodeByteNumList[i])
		{
			return RTN_CHECK_RW_ERR;
		}
		flash_address += sizeof(m_pEncodeByteNumList[i]);
		//////////////////////////////////////////////////////////////////////////

		rtn = ReadFlashData(flash_address, &value, sizeof(m_pEncodeTypeList[i]), tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			return rtn;
		}
		if (value != m_pEncodeTypeList[i])
		{
			return RTN_CHECK_RW_ERR;
		}
		flash_address += sizeof(m_pEncodeTypeList[i]);
		//////////////////////////////////////////////////////////////////////////
		int buffer_size = ((m_pEncodeByteNumList[i] + 1) >> 1) << 1; //keep the buffer_size to be even num
		char* buffer_tmp = new char[buffer_size];
		if (buffer_tmp == NULL)
		{
			delete buffer_tmp;
			return RTN_MALLOC_FAIL;
		}

		rtn = ReadFlashData(flash_address, buffer_tmp, buffer_size, tpfUpdataProgressPt, ptrv, progress);
		if (rtn)
		{
			delete buffer_tmp;
			return rtn;
		}
//		rtn = CompareChars(buffer_tmp, m_pEncodeBufferList[i], buffer_size);
		if (CompareChars(buffer_tmp, m_pEncodeBufferList[i], m_pEncodeByteNumList[i]) == false)//rtn)
		{
			delete buffer_tmp;
			return RTN_CHECK_RW_ERR;
		}
		flash_address += buffer_size;
		delete buffer_tmp;
	}
	//////////////////////////////////////////////////////////////////////////
	return RTN_SUCCESS;
}


short CXmlCodeUpdate::WriteFile(char* pFileNameList[], int pFileTypeList[], int file_num,
	void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn = RTN_SUCCESS;

	rtn = CXmlCode::WriteFile(pFileNameList, pFileTypeList, file_num, tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;

	rtn = CheckXmlFlashValid(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;

	rtn = EraseXmlFlash(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;


	rtn = ProgramXmlFlash(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;


	rtn = CheckXmlFlash(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;
	
	return rtn;
}

short CXmlCodeUpdate::ReadFile(char* pFileNameList[], int pFileTypeList[], int& file_num,
	void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn = RTN_SUCCESS;
	m_EncodeNumMax = file_num;

	rtn = CheckXmlFlashValid(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;

	rtn = ReadXmlFlash(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;

	rtn = CheckXmlFlash(tpfUpdataProgressPt, ptrv, progress);
	if (rtn)
		return rtn;

	rtn = CXmlCode::ReadFile(pFileNameList, pFileTypeList, file_num, tpfUpdataProgressPt, ptrv, progress);
	return rtn;
}