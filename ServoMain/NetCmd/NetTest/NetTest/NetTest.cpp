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
	for (int i = 0; i < 3;i=i+2)
	{
		ret=GTSD_CMD_ProcessorUartBootHandler(i, ldrPath, 115200, 1, key, updateProgress, NULL, 1, 1);
		cout << "ret=" << ret;
	}
#endif

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

