#pragma once
//#include "gdef.h"
#include "BaseReturn_def.h"
#include "StRingNetComUser.h"
#include "RnDriverWave.h"
#include "UserResp.h"

class CRnDriverPlot : 
	public CUserResp
{
public:
	CRnDriverPlot();
	~CRnDriverPlot();
protected:
	CRnDriverWave* m_pWaveList;
	Uint16 m_wave_num;

public:
	int16 PW_CreateDspWave(Uint16 wave_num, Uint16* dsp_id_list);
	int16 PW_PcGetDspWaveData(Uint16 dsp_station_id, double** data, Uint32& number);	// 	//从DSPA或者是DSPB获取数据
	
	short PW_StartDspPlot(Uint16 dsp_station_id, Uint16 wave_num, Uint16 *wave_byte_size_list);
	short PW_StopDspPlot(Uint16 dsp_station_id);

// 	int16 PW_StartDspPlot(Uint16 dsp_station_id, WAVE_BUF_PRM& wave);//启动停止DSP的画图
// 	int16 PW_StopDspPlot(Uint16 dsp_station_id, WAVE_BUF_PRM& wave);//启动停止DSP的画图

	short ParseDspWaveData(StUserPacket* packet);
	virtual short UserHandleRespFunction(StUserPacket* packet){ return ParseDspWaveData(packet); };

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

