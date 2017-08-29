// NetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServoDriverComDll.h"
#include <iostream>
using namespace std;
void updateProgress(void *arg, int16 *value);
#define TEST_UBOOT 1

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0x00ff;
	int aa = 100;
	int comType = 1;
	ret = GTSD_CMD_Open(updateProgress, (void *)&aa, comType);
	cout << "ret=" << ret;
	//GTSD_CMD_Close(comType);
#if TEST_UBOOT
	std::wstring ldrPath = L"D:/Smart/ServoMaster/git-project/servo-4/release/Resource/Uboot/ServoUboot.ldr";
	std::string key = "a5e4b8a4d71d04d2f89d8318fec19283";
	for (int i = 0; i < 3;i++)
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
}

