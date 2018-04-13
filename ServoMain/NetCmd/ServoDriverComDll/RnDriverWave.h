#pragma once
//#include "gdef.h"
#include "BaseReturn_def.h"
#include "StRingNetComUser.h"

#define MAX_NUM_PRE_PACKET 512
static const int32		READ_LENTH_ONCE = 10000;		//pc一次读取的double数据的个数，每一条线的数据个数,根据FPGAbuffer的大小而定义

class CRnDriverWave
{
public:
	CRnDriverWave();
	~CRnDriverWave();
	static const int32		RAW_BUFFER_LENTH = 200000;		//PC读取FPGA缓存的buffer，没有分离曲线
	static const int32		WAVE_LINE_BUFFER_LENTH = 200000;		//曲线buffuer
	static const int32		RAW_CACHE_BUFFER_LENTH = 10000;		//raw data buffer lenth

	static const int32		FRAME_KEYWORD_DISTANCE_NUM = 256;//Dsp负责每256帧数据增加一个同步帧
	static const int32		FRAME_KEYWORD_LOW = 0xaaaa;		//同步帧的定义
	static const int32		FRAME_KEYWORD_HIGH = 0x5555;
	static const Uint32		FRAME_KEYWORD = 0x5555aaaa;//
	static const Uint32		MAX_FRAME_NUM = 33*1000;//
//	static const int16		pw_MaxAxis = MAX_DSP_WAVE * 2;			//最大轴数定义

	Uint16		m_dsp_id;//which combine with des_id and des_ch; m_dsp_id = (des_id <<8) | (des_ch)
protected:

	void* m_critical_section;                 //CRITICAL_SECTION for data receive 

//	WAVE_BUF_PRM m_wave_param;

	Uint16		m_size_of_frame;
	Uint16		m_wave_en;
	Uint16		m_wave_num;
	Uint16		*m_wave_byte_size_list;
  bool		m_find_keyword;

	Uint16		m_keyword_distane_cnt;
	//////////////////////////////////////////////////////////////////////////
	Uint8		*m_pDataTmpBuffer;	//the data from the dsp will fill to here 
//	Uint8		m_pDataTmpBuffer[2 * MAX_NUM_PRE_PACKET];
	//	Uint16		m_pDataTmp_size;
	Uint16		m_pDataTmp_valid_num;//
	//////////////////////////////////////////////////////////////////////////
	Uint8		*m_pFrameBuffer;	//m_pFrameBuffer[m_frame_max_num*m_frame_byte_size];
//	Uint8		m_pFrameBuffer[6*MAX_FRAME_NUM];
//	Uint16		m_frame_max_num;	//this var is used to malloc the memeroy;
	Uint32		m_frame_valid_num;		//this var is used to calc how many frames valid;
	Uint32		m_frame_index;

	//////////////////////////////////////////////////////////////////////////
	double		*m_pDataUserRead; //用于存放上层读取的数据
//	double		m_pDataUserRead[2 * READ_LENTH_ONCE]; //用于存放上层读取的数据
	//////////////////////////////////////////////////////////////////////////
	Uint32		m_frame_write_cnt;	//total write frame num from start plot.
	Uint32		m_frame_read_cnt;	//total read frame num from start plot.



	Uint32		m_data_lose_cnt;// this will not clear
	Uint32		m_read_lose_cnt;// this will clear when the cfg update;
	Uint32		m_data_ok_cnt;
	Uint32		m_read_ok_cnt;// this will clear when the cfg update;

protected:
	short SearchFrameKeyWord(Uint16& key_index, Uint16 byte_num, Uint8* pData);
	short FetchWaveDataToFrameBuffer(Uint16 byte_num, Uint8* pData, Uint16& left_byte_num);
//	short ClearDspWaveVar();
public:
//	short  ParseDspWaveData(Uint16 dsp_id, Uint16 byte_num, Uint8* pData);
//	double	plotDataBuffer_dsp[MAX_DSP_WAVE][MAX_WAVE_PLOT_NUM][READ_LENTH_ONCE];//用于存放上层读取的数据

// 	short InitDspWaveVar(WAVE_BUF_PRM& wave);
// 	short CloseDspWave(WAVE_BUF_PRM& wave);
	
	short InitDspWaveVar(Uint16 wave_num, Uint16 *wave_byte_size_list);
	short CloseDspWave();

	short PW_PcGetDspWaveData(double** data, Uint32& number);
	short ParseDspWaveData(Uint16 dsp_id, Uint16 byte_num, Uint8* pData);

#ifdef  TIME_TEST

	int16 readnumber_testA[10000];
	int16 readnumber_test_indexA;
	int16 readnumber_testB[1000];
	int16 readnumber_test_indexB;

	int32 readpointerA[1000];
	int32 writepointerA[1000];
	int16 pointerindexA;
	int16 readpointerB[1000];
	int16 writepointerB[1000];
	int16 pointerindexB;

	int32 value_exceed;
	int32 overflow_flag;
	int16 allnumber_test[10000];
	int32 allnumber_test_index;
#endif
};

