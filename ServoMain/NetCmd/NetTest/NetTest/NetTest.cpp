// NetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServoDriverComDll.h"
#include <iostream>
#include <windows.h>
using namespace std;
void updateProgress(void *arg, int16 *value);
#define TEST_UBOOT 1
#define  TEST_PLOT 0
#define TEST_FPGA 1
#define FPGA_RPD_FILE (L"C:/Users/googol/Desktop/gtsd42_va_20170920_1.rpd")
int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0x00ff;
	int aa = 100;
	int comType = 1;
	ret = GTSD_CMD_Open(updateProgress, (void *)&aa, comType);
	cout << "ret=" << ret;
	//GTSD_CMD_Close(comType);
#if TEST_FPGA
	Uint16 axis = 0;
	std::wstring fpgaFileName = FPGA_RPD_FILE;
	ret = GTSD_CMD_FirmwareFlashHandler(axis, fpgaFileName, updateProgress, NULL, comType, 0xf0);
#endif

#if TEST_PLOT

	WAVE_BUF_PRM buf_prm;
	buf_prm.cmd.bit.ENP = 1;
	buf_prm.cmd.bit.NUM = 1;
	buf_prm.cmd.bit.TIM = 1;
	buf_prm.inf[0].base = 0;
	buf_prm.inf[0].bytes = 2;
	buf_prm.inf[0].ofst = 406;
	int16 axisNum = 0;
	double *ppValue = NULL;
	int32 retPointCount = 0;

	GTSD_CMD_StartPlot(axisNum, buf_prm, comType, 0xf0);

	for (int i = 0; i < 1000;i++)
	{
		GTSD_CMD_PcGetWaveData(axisNum, &ppValue, retPointCount, comType, 0xf0);
		Sleep(80);
	}
	
	GTSD_CMD_StopPlot(axisNum, buf_prm,comType, 0xf0);

	WAVE_BUF_PRM buf_prm2;
	buf_prm2.cmd.bit.ENP = 1;
	buf_prm2.cmd.bit.NUM = 1;
	buf_prm2.cmd.bit.TIM = 1;
	buf_prm2.inf[0].base = 0;
	buf_prm2.inf[0].bytes = 4;
	buf_prm2.inf[0].ofst = 668;
	GTSD_CMD_StartPlot(axisNum, buf_prm2, comType, 0xf0);

	for (int i = 0; i < 1000;i++)
	{
		GTSD_CMD_PcGetWaveData(axisNum, &ppValue, retPointCount, comType, 0xf0);
		Sleep(80);
	}

#endif
#if TEST_UBOOT
	std::wstring ldrPath = L"D:/Smart/ServoMaster/git-project/servo-4/release/Resource/Uboot/ServoUboot.ldr";
	std::string key = "a5e4b8a4d71d04d2f89d8318fec19283";
	for (int i = 0; i < 2;i++)
	{
		ret = GTSD_CMD_ProcessorUartBootHandler(2*i, ldrPath, 115200, 1, key, updateProgress, NULL, comType, 1);
		cout << "ret=" << ret;
	}
#endif
	for (int i = 0; i < 4;i++)
	{
		GENERALFUNCTION func;
		COM_ERROR result;
		int id;
		int getIndex;
		double kgain;
		unsigned short cmd;
		unsigned short length;
		short buf[6] = { 0 };
		id = 27;
		getIndex = 1;
		kgain = 1;
		cmd = 41;
		length = 6;
		func.data = buf;
		//      qDebug()<<cmdName<<"id"<<id<<"getindex"<<getIndex<<"length"<<length<<"cmd"<<cmd<<"type"<<type;
		if (id != -1)
		{
			func.data[3] = id;
		}
		func.cmd = cmd;
		func.mode = 1;
		func.dataLenth = length;
		result = (COM_ERROR)GTSD_CMD_ProcessorGeneralFunc(i, &func, comType, 0xf0);
		std::cout << result;
	}
//	result = (COM_ERROR)GTSD_CMD_ProcessorGeneralFunc(4, &func, comType, 0xf0);
//	result = (COM_ERROR)GTSD_CMD_ProcessorGeneralFunc(5, &func, comType, 0xf0);

	while (true)
	{

	}
	return 0;
}
void updateProgress(void *arg, int16 *value)
{
	int16 v = *value;
	cout << "value=" << v << endl;
	cout << "aaaaaaaaaaaaaaaaaaaa";
}

