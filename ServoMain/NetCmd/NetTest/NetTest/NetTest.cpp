// NetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServoDriverComDll.h"
#include <iostream>
using namespace std;
void updateProgress(void *arg, int16 *value);

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0x00ff;
	//int aa = 100;
	int comType = 1;
	//ret = GTSD_CMD_Open(updateProgress, (void *)&aa, comType);
	//cout << "ret=" << ret;
	//GTSD_CMD_Close(comType);

	short netCarMsg = GTSD_CMD_GetNetCardMsg();
	Uint16 version;
	ret=GTSD_CMD_ReadProcessorVersion(0, version, comType, 0);
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

