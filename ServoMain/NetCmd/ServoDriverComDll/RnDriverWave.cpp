#include "stdafx.h"
#include <winsock2.h>
#include "RnDriverWave.h"


CRnDriverWave::CRnDriverWave(void)
{
	m_critical_section = NULL;
	m_critical_section = (void*) new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)m_critical_section);///

	m_wave_en = 0;
	m_wave_num = 0;
	m_wave_byte_size_list = NULL;
	m_dsp_id = 0xFFFF;

	m_pFrameBuffer = NULL;
	m_pDataTmpBuffer = NULL;
	m_pDataUserRead = NULL;

	m_keyword_distane_cnt = 0;
	m_frame_valid_num = 0;
	m_frame_index = 0;
	m_frame_write_cnt = 0;
	m_frame_read_cnt = 0;

	m_pDataTmp_valid_num = 0;

	m_data_lose_cnt = 0;
	m_read_lose_cnt = 0;

	m_data_ok_cnt = 0;
	m_read_ok_cnt = 0;

	m_find_keyword = FALSE;

}

CRnDriverWave::~CRnDriverWave(void)
{
	if (m_wave_byte_size_list)
	{
		delete[]m_wave_byte_size_list;
	}
	if (m_critical_section)
	{
		DeleteCriticalSection((CRITICAL_SECTION*)m_critical_section);
		delete m_critical_section;
		m_critical_section = NULL;
	}
	if (m_pDataTmpBuffer)
	{
		delete[]m_pDataTmpBuffer;
		m_pDataTmpBuffer = NULL;
	}
	if (m_pDataUserRead)
	{
		delete[]m_pDataUserRead;
		m_pDataUserRead = NULL;
	}
	if (m_pFrameBuffer)
	{
		delete[]m_pFrameBuffer;
		m_pFrameBuffer = NULL;
	}
	
}

short CRnDriverWave::SearchFrameKeyWord(Uint16& key_index, Uint16 byte_num, Uint8* pData)
{
	for (Uint16 i = 0; i <= byte_num - sizeof(FRAME_KEYWORD); i++)
	{
		if (pData[i] == (FRAME_KEYWORD & 0xFF))
		{
			if(FRAME_KEYWORD == *(Uint32*)(pData + i)) // mactch the FRAME_KEYWORD
			{
				key_index = i;
				return RTN_SUCCESS;
			}
		}
	}
	return RTN_SUCCESS;
}
short CRnDriverWave::FetchWaveDataToFrameBuffer(Uint16 byte_num, Uint8* pData, Uint16& left_byte_num)
{
	Uint16 i;
	for (i = 0; i <= byte_num - m_size_of_frame; i = i + m_size_of_frame)
	{
		if (m_find_keyword == FALSE)
		{
			continue;
		}
		memcpy(m_pFrameBuffer + m_frame_index*m_size_of_frame, pData + i, m_size_of_frame);
// 		if ( *((Uint16*)(pData + i)) != 5000)
// 			i = i;
// 		if ( *((Uint32*)(pData + i + 2)) != 0)
// 			i = i;
		m_frame_write_cnt++;
		m_frame_index++;
		m_keyword_distane_cnt++;
		m_frame_index = m_frame_index % MAX_FRAME_NUM;
	}
	left_byte_num = byte_num - i;
	return RTN_SUCCESS;
}
//------------------------------------------------------
//该数的作用是，将传进来的数据先和历史遗留的数据进行挣了到临时buffer中，然后在这个临时buffer找寻keyword。
//如果找不到keywork则将buffer中所有的数据存储在环形frame_buffer中。如果buffer中余留的数据不够一个frame，则留作下次使用。
//如果找到keywork则，然后将keywork之前buffer中所有的数据存储在环形frame_buffer，如果buffer余留的数据不够一个frame，则直接丢掉。然后去除keywork。
short CRnDriverWave::ParseDspWaveData(Uint16 dsp_id, Uint16 byte_num, Uint8* pData)
{

	if (dsp_id != m_dsp_id || !m_wave_en)
	{
		return RTN_SUCCESS;
	}
	if (m_pDataTmpBuffer == NULL)
	{
		m_pDataTmp_valid_num = 0;
		m_pDataTmpBuffer = new Uint8[2 * MAX_NUM_PRE_PACKET];
		if (m_pDataTmpBuffer == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
	}
	if (m_pFrameBuffer == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	EnterCriticalSection((CRITICAL_SECTION*)m_critical_section);
	////////////////////////////////cpy the data into the temp buffer/////////////////////////////////////////
	if (m_pDataTmp_valid_num + byte_num > 2*MAX_NUM_PRE_PACKET) //some thing is wrong, clean th tmp buffer.
	{
		m_data_lose_cnt++;
		m_pDataTmp_valid_num = 0;
	}
	memcpy(m_pDataTmpBuffer+m_pDataTmp_valid_num, pData, byte_num);
	m_pDataTmp_valid_num = m_pDataTmp_valid_num + byte_num; 
	//////////////////////////////find the key word////////////////////////////////////////////
	Uint16 key_index= 0xFFFF;
	Uint16 byte_valid_num = 0;
//	bool find_frame_key = false;
	SearchFrameKeyWord(key_index, m_pDataTmp_valid_num, m_pDataTmpBuffer);
	if (key_index == 0xFFFF) // no find frame_key, all the data is valid
	{
		byte_valid_num = m_pDataTmp_valid_num - sizeof(FRAME_KEYWORD) + 1;//-3 it mean the last valid data is m_pDataTmpBuffer[byte_valid_num-1]
		Uint16 left_byte_num = 0;
		FetchWaveDataToFrameBuffer(byte_valid_num, m_pDataTmpBuffer, left_byte_num);
		
		Uint16 really_left_byte_num = m_pDataTmp_valid_num - (byte_valid_num - left_byte_num);
		memcpy(m_pDataTmpBuffer, m_pDataTmpBuffer + byte_valid_num - left_byte_num, really_left_byte_num);//cpy the m_pDataTmpBuffer[m_pDataTmp_valid_num-1 : byte_valid_num-left_byte_num] to m_pDataTmpBuffer[x:0]
		m_pDataTmp_valid_num = really_left_byte_num;
	}
	else // find frame_key
	{
		byte_valid_num = key_index;
//		find_frame_key = true;
		Uint16 left_byte_num = 0;
		FetchWaveDataToFrameBuffer(byte_valid_num, m_pDataTmpBuffer, left_byte_num);
		if (left_byte_num != 0 || m_keyword_distane_cnt != FRAME_KEYWORD_DISTANCE_NUM)
		{
			m_data_lose_cnt++;
		}
		else
		{

			m_data_ok_cnt++;
		}
		m_keyword_distane_cnt = 0;
		Uint16 really_left_byte_num = m_pDataTmp_valid_num - (key_index + sizeof(FRAME_KEYWORD));
		memcpy(m_pDataTmpBuffer, m_pDataTmpBuffer + key_index + sizeof(FRAME_KEYWORD), really_left_byte_num);//cpy the m_pDataTmpBuffer[m_pDataTmp_valid_num-1 : byte_valid_num+sizeof(FRAME_KEYWORD)] to m_pDataTmpBuffer[x:0]
		m_pDataTmp_valid_num = really_left_byte_num;
		m_find_keyword = TRUE;
	}
	//////////////////////////////////////////////////////////////////////////
	LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
	return RTN_SUCCESS;
}
//初始化dspAwave
// short CRnDriverWave::InitDspWaveVar(WAVE_BUF_PRM& wave)
// {
// 	EnterCriticalSection((CRITICAL_SECTION*)m_critical_section);
// 	
// 	m_size_of_frame = 0;
// 	bool param_update = false;
// 	if (m_wave_param.cmd.bit.NUM != wave.cmd.bit.NUM)
// 	{
// 		param_update = true;
// 	}
// 	for (int i = 0; i < wave.cmd.bit.NUM;i++)
// 	{
// 		m_size_of_frame += m_wave_param.inf[i].bytes;
// 		if (wave.inf[i].bytes != m_wave_param.inf[i].bytes)
// 		{
// 			param_update = true; 
// 		}
// 	}
// 	if (param_update == false)
// 	{
// 		LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
// 		return RTN_SUCCESS;
// 	}
// 
// //	ClearDspWaveVar();
// 
// 	if (m_pFrameBuffer)
// 	{
// 		delete []m_pFrameBuffer;
// 		m_pFrameBuffer = NULL;
// 	}
// 
// 	if (m_pDataUserRead)
// 	{
// 		delete[]m_pDataUserRead;
// 		m_pDataUserRead = NULL;
// 	}
// 
// 	wave.cmd.bit.ENP = 1;
// 	m_wave_param = wave;
// 	//////////////////////////////////////////////////////////////////////////
// 	m_pFrameBuffer = new Uint8[m_size_of_frame*MAX_FRAME_NUM];
// 	m_pDataUserRead = new double[m_wave_param.cmd.bit.NUM*READ_LENTH_ONCE];
// 	if (m_pFrameBuffer == NULL || m_pDataUserRead == NULL)
// 	{
// 		LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
// 		return RTN_MALLOC_FAIL;
// 	}
// 
// 	m_keyword_distane_cnt = 0;
// 	m_frame_valid_num = 0;
// 	m_frame_index = 0;
// 	m_frame_write_cnt = 0;
// 	m_frame_read_cnt = 0;
// 
// 	m_pDataTmp_valid_num = 0;
// 
// 	m_read_lose_cnt = 0;// this will clear when the cfg update;
// 
// 
// 	LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
// 	return RTN_SUCCESS;
// }
// 
// //关闭dspAwave
// short CRnDriverWave::CloseDspWave(WAVE_BUF_PRM& wave)
// {
// 	wave.cmd.bit.ENP = 0;
// 	m_wave_param.cmd.bit.ENP = 0;
// 	return RTN_SUCCESS;
// }

short CRnDriverWave::InitDspWaveVar(Uint16 wave_num, Uint16 *wave_byte_size_list)
{
	EnterCriticalSection((CRITICAL_SECTION*)m_critical_section);
	m_wave_en = 0;
	m_size_of_frame = 0;
	bool param_update = false;
	if (m_wave_num != wave_num)
	{
		param_update = true;
		if (m_wave_byte_size_list)
			delete[]m_wave_byte_size_list;
		m_wave_byte_size_list = NULL;

		m_wave_num = wave_num;
		m_wave_byte_size_list = new Uint16[wave_num];
		if (m_wave_byte_size_list == NULL)
		{
			LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
			return RTN_MALLOC_FAIL;
		}
		for (int i = 0; i < wave_num; i++)
		{
			m_wave_byte_size_list[i] = wave_byte_size_list[i];
			m_size_of_frame += m_wave_byte_size_list[i];
		}
	}
	else
	{
		for (int i = 0; i < wave_num; i++)
		{
			m_size_of_frame += wave_byte_size_list[i];
			if (m_wave_byte_size_list[i] != wave_byte_size_list[i])
			{
				param_update = true;
			}
		}
	}
	if (param_update == false)
	{
		m_wave_en = 1;
		LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
		return RTN_SUCCESS;
	}
	m_find_keyword = FALSE;
	//	ClearDspWaveVar();

	if (m_pFrameBuffer)
	{
		delete[]m_pFrameBuffer;
		m_pFrameBuffer = NULL;
	}

	if (m_pDataUserRead)
	{
		delete[]m_pDataUserRead;
		m_pDataUserRead = NULL;
	}

	if (m_wave_num == 0)
	{
		LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
		return RTN_SUCCESS;
	}
	//////////////////////////////////////////////////////////////////////////
 	m_pFrameBuffer = new Uint8[m_size_of_frame*MAX_FRAME_NUM];
 	m_pDataUserRead = new double[m_wave_num*READ_LENTH_ONCE];
	if (m_pFrameBuffer == NULL || m_pDataUserRead == NULL)
	{
		LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
		return RTN_MALLOC_FAIL;
	}

	m_keyword_distane_cnt = 0;
	m_frame_valid_num = 0;
	m_frame_index = 0;
	m_frame_write_cnt = 0;
	m_frame_read_cnt = 0;

	m_pDataTmp_valid_num = 0;

	m_read_lose_cnt = 0;// this will clear when the cfg update;


	m_wave_en = 1;
	LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
	return RTN_SUCCESS;
}
short CRnDriverWave::CloseDspWave()
{
	m_wave_en = 0;

	m_find_keyword = FALSE;
	m_keyword_distane_cnt = 0;
	m_frame_valid_num = 0;
	m_frame_index = 0;
	m_frame_write_cnt = 0;
	m_frame_read_cnt = 0;

	m_pDataTmp_valid_num = 0;

	m_read_lose_cnt = 0;// this will clear when the cfg update;
	return RTN_SUCCESS;
}

//number实际取到的数据，数据的指针
short CRnDriverWave::PW_PcGetDspWaveData(double** data, Uint32& number)// number means point
{
	number = 0;
	*data = m_pDataUserRead;

	if (data == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (m_pDataUserRead == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	EnterCriticalSection((CRITICAL_SECTION*)m_critical_section);
	//////////////////////////////////////////////////////////////////////////
	Uint32 valid_frame_num = m_frame_write_cnt - m_frame_read_cnt;
	if (valid_frame_num >= MAX_FRAME_NUM)
	{
		m_frame_read_cnt = m_frame_write_cnt - MAX_FRAME_NUM + 1;
		m_read_lose_cnt++;
	}
	else
	{
		m_read_ok_cnt++;
	}

	valid_frame_num = m_frame_write_cnt - m_frame_read_cnt;
	
	if (valid_frame_num > READ_LENTH_ONCE) 
	{
		number = READ_LENTH_ONCE;
	}
	else
	{
		number = valid_frame_num;
	}
	//////////////////////////////////////////////////////////////////////////
	Uint32 read_beg_index = (m_frame_index + MAX_FRAME_NUM - valid_frame_num) % MAX_FRAME_NUM;
	Uint32 read_frame_index_byte_offset;
	Uint16 byte_cnt;

	for (Uint32 i = 0; i < number; i++)
	{
		read_frame_index_byte_offset = ((read_beg_index + i) % MAX_FRAME_NUM) * m_size_of_frame;
		byte_cnt = 0;
		for (int j = 0; j < m_wave_num;j++)
		{
			switch (m_wave_byte_size_list[j])
			{
			case 2: 
				m_pDataUserRead[READ_LENTH_ONCE*j + i] = (double)(*(int16*)(m_pFrameBuffer + read_frame_index_byte_offset + byte_cnt));
				break;
			case 4:
				m_pDataUserRead[READ_LENTH_ONCE*j + i] = (double)(*(int32*)(m_pFrameBuffer + read_frame_index_byte_offset + byte_cnt));
				break;
			case 8:
				m_pDataUserRead[READ_LENTH_ONCE*j + i] = (double)(*(int64*)(m_pFrameBuffer + read_frame_index_byte_offset + byte_cnt));
				break;
			default:
				LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
				return RTN_PARAM_ERR;
			}
			byte_cnt += m_wave_byte_size_list[j];
		}
	}

	m_frame_read_cnt += number;
	//返回读取的个数
	LeaveCriticalSection((CRITICAL_SECTION*)m_critical_section);
#ifdef TIME_TEST

	readpointerA[pointerindexA] = waveLine_RdIndex_dspA[0];
	writepointerA[pointerindexA] = waveLine_WrIndex_dspA[0];
	if (readpointerA[pointerindexA] > writepointerA[pointerindexA])
	{
		pointerindexA = pointerindexA;
	}
	pointerindexA++;
	if (pointerindexA >= 1000)
	{
		pointerindexA = 0;
	}

#endif	
	return RTN_SUCCESS;
}
