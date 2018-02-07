#include "stdafx.h"
#include "GTCmdCtrl.h"


CGTCmdCtrl::CGTCmdCtrl()
{
	m_pDriver = NULL;
}


CGTCmdCtrl::~CGTCmdCtrl()
{
}

short CGTCmdCtrl::Initial(CMotionCtrlCom* pDriver)
{
	if (pDriver == NULL)
	{
		return RTN_NULL_POINT;
	}

	m_pDriver = pDriver;
	return RTN_SUCCESS;
}

void CGTCmdCtrl::InitCmd(unsigned short cmd)
{
	short i;

	gCommand.data[0] = cmd;
	gCommand.dataLen = 1;

	for (i = 1; i < COMMAND_DATA_LEN; ++i)
	{
		gCommand.data[i] = 0;
		gCommand.result[i] = 0;
	}

	gCommand.resultIndex = 1;
}

void CGTCmdCtrl::Add16(short data16)
{
	if (gCommand.dataLen < COMMAND_DATA_LEN)
	{
		gCommand.data[gCommand.dataLen++] = data16;
	}
}

void CGTCmdCtrl::Add32(long data32)
{
	if (gCommand.dataLen + 1 < COMMAND_DATA_LEN)
	{
		*(long *)&gCommand.data[gCommand.dataLen] = data32;
		gCommand.dataLen += 2;
	}
}

void CGTCmdCtrl::Add32F(double data)
{
	if (gCommand.dataLen + 1 < COMMAND_DATA_LEN)
	{
		*(long *)&gCommand.data[gCommand.dataLen] = (long)(data * 65536);
		gCommand.dataLen += 2;
	}
}

void CGTCmdCtrl::Add48F(double data)
{
	double temp;
	unsigned long tempLong;
	unsigned short tempShort;

	tempShort = (unsigned short)(data * 65536);
	temp = floor(data);
	tempLong = (unsigned long)temp;

	if ((gCommand.dataLen + 2) < COMMAND_DATA_LEN)
	{
		gCommand.data[gCommand.dataLen++] = tempShort;
		*(unsigned long *)&gCommand.data[gCommand.dataLen] = tempLong;
		gCommand.dataLen += 2;
	}
}

void CGTCmdCtrl::AddFloat(float data)
{
	if (gCommand.dataLen + 1 < COMMAND_DATA_LEN)
	{
		*(float *)&gCommand.data[gCommand.dataLen] = data;
		gCommand.dataLen += 2;
	}
}

void CGTCmdCtrl::AddFloat64(double data)
{
	if (gCommand.dataLen + 1 < COMMAND_DATA_LEN)
	{
		*(double *)&gCommand.data[gCommand.dataLen] = data;
		gCommand.dataLen += 4;
	}
}

void CGTCmdCtrl::Get16(short *pData16)
{
	if (gCommand.resultIndex < COMMAND_DATA_LEN)
	{
		*pData16 = gCommand.result[gCommand.resultIndex++];
	}
}

void CGTCmdCtrl::Get32(long *pData32)
{
	if (gCommand.resultIndex + 1 < COMMAND_DATA_LEN)
	{
		*pData32 = *(long *)&gCommand.result[gCommand.resultIndex];
		gCommand.resultIndex += 2;
	}
}

void CGTCmdCtrl::Get32F(double *pData)
{
	if (gCommand.resultIndex + 1 < COMMAND_DATA_LEN)
	{
		*pData = (*(long *)&gCommand.result[gCommand.resultIndex]) / 65536.0;
		gCommand.resultIndex += 2;
	}
}

void CGTCmdCtrl::Get48F(double *pData)
{
	unsigned short fraction;
	long integer;
	double value;

	if (gCommand.resultIndex + 2 < COMMAND_DATA_LEN)
	{
		fraction = gCommand.result[gCommand.resultIndex++];
		integer = (*(long *)&gCommand.result[gCommand.resultIndex]);
		value = fraction;
		value /= 65536.0;
		value += integer;
		*pData = value;
		gCommand.resultIndex += 2;
	}
}

void CGTCmdCtrl::GetFloat(double *pData)
{
	if (gCommand.resultIndex + 1 < COMMAND_DATA_LEN)
	{
		*pData = (*(float *)&gCommand.result[gCommand.resultIndex]);
		gCommand.resultIndex += 2;
	}
}

void CGTCmdCtrl::GetFloat64(double *pData)
{
	if (gCommand.resultIndex + 1 < COMMAND_DATA_LEN)
	{
		*pData = (*(double *)&gCommand.result[gCommand.resultIndex]);
		gCommand.resultIndex += 4;
	}
}

short CGTCmdCtrl::SendCommand(void)
{
	short i, rtn;

	// 	if (CHANNEL_HOST == gChannel[gDevIndex])
	// 	{
	// 		gPci.len = gCommand.dataLen;
	// 
	// 		for (i = 0; i < gCommand.dataLen; ++i)
	// 		{
	// 			gPci.data[i] = gCommand.data[i];
	// 		}
	// 
	// 		rtn = SendPci();
	// 		if (CMD_SUCCESS != rtn)
	// 		{
	// 			return rtn;
	// 		}
	// 
	// 		gCommand.resultLen = gPci.len;
	// 
	// 		for (i = 0; i < gCommand.resultLen; ++i)
	// 		{
	// 			gCommand.result[i] = gPci.data[i];
	// 		}
	// 	}
	// 	///////////////////edited by huang.lz 2016.1.27 begin/////////
	// 	else if (CHANNEL_RINGNET == gChannel[gDevIndex])
	{
		gPci.len = gCommand.dataLen;

		for (i = 0; i < gCommand.dataLen; ++i)
		{
			gPci.data[i] = gCommand.data[i];
		}

		rtn = m_pDriver->SendPci(&gPci, m_dsp_tag_id);
//		rtn = m_pDriver->SendPcie(&gPci, 2, m_dsp_tag_id);
		if (CMD_SUCCESS != rtn)
		{
			return rtn;
		}

		gCommand.resultLen = gPci.len;

		for (i = 0; i < gCommand.resultLen; ++i)
		{
			gCommand.result[i] = gPci.data[i];
		}

	}
	// 	///////////////////edited by huang.lz 2016.1.27 end/////////
	// 	else
	// 	{
	// 		gUart.len = gCommand.dataLen;
	// 
	// 		for (i = 0; i < gCommand.dataLen; ++i)
	// 		{
	// 			gUart.data[i] = gCommand.data[i];
	// 		}
	// 
	// 		rtn = SendUart();
	// 		if (CMD_SUCCESS != rtn)
	// 		{
	// 			return rtn;
	// 		}
	// 
	// 		gCommand.resultLen = gUart.len;
	// 
	// 		for (i = 0; i < gCommand.resultLen; ++i)
	// 		{
	// 			gCommand.result[i] = gUart.data[i];
	// 		}
	// 	}

	return rtn;
}