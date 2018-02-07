#include "stdafx.h"
#include "GTDriverCmd.h"


CGTDriverCmd::CGTDriverCmd()
{
}


CGTDriverCmd::~CGTDriverCmd()
{
}

short CGTDriverCmd::GTD_ST_SetStationType(short axis, short Data)
{
	unsigned long adr;
	short dat;
	adr = 226; //test param 4 addr
	dat = Data;

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((dat <0))
	{
		return CMD_ERROR_PARAMETER;
	}

	return GTD_ST_SetFlashParamIndex(axis, adr, &dat);
	//	return CMD_SUCCESS;
}

//////////////////////////////////////////////////////////
// ???????   ??Data = 1 2 3....; ??Data = 0;
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_GetStationType(short axis, short* Data)
{
	unsigned long adr;
	adr = 226; //test param 4 addr

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	return GTD_ST_GetFlashParamIndex(axis, adr, Data);
	//	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ADC?? ????,??2s????????? ???ADC???flash,??????????????????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorAdcAdjust(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	pNum = 2;
	id = 1;
	Data[0] = 1; //???
	Data[1] = 1; //ADC??

	return GTD_ST_SetDrvCmd(axis, pNum, id, Data);

	//	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ?????? ,??15s????????? ???ADC???flash,??????????????????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorInitPosAdjust(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	pNum = 4;
	id = 1;
	Data[0] = 1;		//???
	Data[1] = 2;		//????
	Data[3] = 1500;		//????????

	return GTD_ST_SetDrvCmd(axis, pNum, id, Data);

	//	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??? ,??????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_ServoOff(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };


	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	pNum = 2;
	id = 1;
	Data[0] = 0;		//???
	Data[1] = 0;		//idle

	return GTD_ST_SetDrvCmd(axis, pNum, id, Data);

	//	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??????????? mode = 0 ????,???????????????,
// mode = 7 ????,??????????????,????????????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_ServoModeSwitch(short axis, short mode)
{
	short adr;
	short mod;
	adr = 1326; //????????mask?
	mod = mode;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((mod != 0) && (mod != 7))
	{
		return CMD_ERROR_PARAMETER;
	}


	return GTD_ST_SetRamIndex16(axis, adr, &mod);

	//	return CMD_SUCCESS;

}

//////////////////////////////////////////////////////////
// ??? spd ????,spdbase ?????,??????16384----3000rpm,?????????3000
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorSpdloop(short axis, short spd, short spdbase)
{
	short pNum;
	short id;
	short Data[20] = { 0 };


	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((spd >(short)(0.9*spdbase * 2)) || (spd <(short)(-0.9*spdbase * 2)))
	{
		return CMD_ERROR_PARAMETER;
	}

	pNum = 7;
	id = 1;
	Data[0] = 1;		//???
	Data[1] = 6;		//???
	Data[6] = (short)((((double)spd) / ((double)spdbase)*16384.0));
	return GTD_ST_SetDrvCmd(axis, pNum, id, Data);

	//	return CMD_SUCCESS;
}

//////////////////////////////////////////////////////////
// ????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorClrAlarm(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };


	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	pNum = 1;
	id = 8;
	Data[0] = 1;		//????
	return GTD_ST_SetDrvCmd(axis, pNum, id, Data);

	//	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??ADC???????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorSaveAdcOffset(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };
	short ia_ofst;
	short ib_ofst;
	short ic_ofst;
	short adr;
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	id = 9;
	pNum = 4;

	//????????????,

	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;


	//??flash??
	ia_ofst = Data[0];
	ib_ofst = Data[1];
	ic_ofst = Data[2];

	adr = 52;
	rtn = GTD_ST_SetFlashParamIndex(axis, adr, &ia_ofst);
	if (rtn != CMD_SUCCESS) return rtn;

	adr = 53;
	rtn = GTD_ST_SetFlashParamIndex(axis, adr, &ib_ofst);
	if (rtn != CMD_SUCCESS) return rtn;

	adr = 54;
	rtn = GTD_ST_SetFlashParamIndex(axis, adr, &ic_ofst);
	if (rtn != CMD_SUCCESS) return rtn;

	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??????????????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_MotorSavePosOffset(short axis)
{
	short pNum;
	short id;
	short Data[20] = { 0 };
	short pos_ofst;
	short seq_dir;
	short adr;
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	//??????????
	id = 2;
	pNum = 11;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	//??flash??
	seq_dir = Data[10];
	adr = 69;
	rtn = GTD_ST_SetFlashParamIndex(axis, adr, &seq_dir);
	if (rtn != CMD_SUCCESS) return rtn;

	//????????????
	id = 7;
	pNum = 2;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	//??flash??
	pos_ofst = Data[1];
	adr = 138;
	rtn = GTD_ST_SetFlashParamIndex(axis, adr, &pos_ofst);
	if (rtn != CMD_SUCCESS) return rtn;

	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ???????,????,??,?????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_GetMotorMessage(short axis, drivermessage* drvmsg)
{
	short pNum;
	short id;
	short Data[20] = { 0 };
	short Imax;
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	//????IMAX,??????
	id = 2;
	pNum = 11;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	Imax = Data[9];


	//???????????
	id = 6;
	pNum = 16;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	drvmsg->motor_temper = ((float)(Data[14] - KTY84_TEMPER)) / ((float)KTY84_RMP);

	//??????????????
	drvmsg->motor_current_rms = (float)((Data[8] / (15000 / (Imax*0.1))) / 1.414);

	//??????????,???1S?
	id = 13;
	pNum = 4;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	drvmsg->motor_brake_time = (float)(((int32)((Data[0] << 16) | (Data[1]))) / 8000.0);
	drvmsg->motor_brake_number = (float)((int32)((Data[2] << 16) | (Data[3])));

	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_GetFirmwareVersion(short axis, firmwareversion* fm_ver)
{
	short pNum;
	short id;
	short Data[20] = { 0 };
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}
	//???????????
	id = 1;
	pNum = 6;
	rtn = GTD_ST_GetDrvInf(axis, pNum, id, Data);
	if (rtn != CMD_SUCCESS) return rtn;

	fm_ver->dsp_ver_year = Data[0];
	fm_ver->dsp_ver_md = Data[1];
	fm_ver->fpga_ver_year = Data[2];
	fm_ver->fpga_ver_md = Data[3];
	fm_ver->cpld_ver_year = Data[4];
	fm_ver->cpld_ver_md = Data[5];

	return CMD_SUCCESS;
}
//////////////////////////////////////////////////////////
// ??????
//////////////////////////////////////////////////////////
short CGTDriverCmd::GTD_ST_WriteDriverParamFileToFlash(short axis, char*  pFileName)
{
	short rtn;
	FILE *fp = NULL;
	unsigned long address;
	short count;
	short data[40];
	rtn = 0;
	char modename[16] = "rb"; //??????
	char* fname;			//???????
	fname = pFileName;

	//short axis = 1;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	//???bin????flash
	rtn = fopen_s(&fp, fname, &modename[0]);
	if (NULL == fp)
	{
		return 2; //??????
	}

  const char *company = "GoogolTech_drivers";
	char code[18];
	short num = fread(code, 18, 1, fp);
	if (num != 18) return 4;
	for (int i = 0; i < 18; i++)
	{
		if (company[i] != code[i])
		{
			return 3;
		}
	}

	while (1)
	{
		num = fread(&address, sizeof(address), 1, fp);
		if (num != sizeof(address))
		{
			rtn = 4;
			break;
		}

		num = fread(&count, sizeof(count), 1, fp);
		if (num != sizeof(count) && count != 1)
		{
			rtn = 4;
			break;
		}

		num = fread(&data[0], sizeof(data[0]), count, fp);
		if (num != sizeof(data[0]))
		{
			rtn = 4;
			break;
		}
		rtn = GTD_ST_SetFlashParamIndex(axis, address, &data[0]);
		if (rtn != RTN_SUCCESS)
		{
			break;
		}
	}

	fclose(fp);

	return rtn;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

short CGTDriverCmd::GTD_ST_GetNetFollowError(short axis, short part, short *pNum, short* pdata)
{
	short i, rtn;
	short num;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_NET_SYNC_TEST_FOLLOWERROR);
	Add16(axis);
	Add16(part);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pNum);

	num = *pNum;
	if (num > 20)
	{
		num = 20;
	}

	for (i = 0; i<num; ++i)
	{
		Get16(&pdata[i]);
	}

	return CMD_SUCCESS;
}


short CGTDriverCmd::GTD_ST_SetLedMessage(short axis, short mode)
{
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(APP_KESAI_SET_LED_MESSAGE);
	Add16(axis);
	Add16(mode);

	return SendCommand();
}
short CGTDriverCmd::GTD_ST_GetLedMessage(short axis, short* mode)
{
	short rtn;
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(APP_KESAI_GET_LED_MESSAGE);
	Add16(axis);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}
	Get16(mode);

	return CMD_SUCCESS;

}
short CGTDriverCmd::GTD_ST_GetNetSyncTime(short axis, short part, short *pNum, short* pdata)
{
	short i, rtn;
	short num;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_NET_SYNC_TEST_TIME);
	Add16(axis);
	Add16(part);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pNum);

	num = *pNum;
	if (num > 20)
	{
		num = 20;
	}

	for (i = 0; i<num; ++i)
	{
		Get16(&pdata[i]);
	}

	return CMD_SUCCESS;
}
short CGTDriverCmd::GTD_ST_GetNetSyncPrfPos(short axis, short part, short *pNum, short* pdata)
{
	short i, rtn;
	short num;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_NET_SYNC_TEST_PRFPOS);
	Add16(axis);
	Add16(part);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pNum);

	num = *pNum;
	if (num > 20)
	{
		num = 20;
	}

	for (i = 0; i<num; ++i)
	{
		Get16(&pdata[i]);
	}

	return CMD_SUCCESS;
}
short CGTDriverCmd::GTD_ST_GetNetSyncFdPos(short axis, short part, short *pNum, short* pdata)
{
	short i, rtn;
	short num;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_NET_SYNC_TEST_FDPOS);
	Add16(axis);
	Add16(part);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pNum);

	num = *pNum;
	if (num > 20)
	{
		num = 20;
	}

	for (i = 0; i<num; ++i)
	{
		Get16(&pdata[i]);
	}

	return CMD_SUCCESS;
}


short CGTDriverCmd::GTD_ST_GetIoBit(short axis, short* pdata)
{
	short rtn;
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(IO_GET_MESSAGE);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}
	Get16(pdata);
	return CMD_SUCCESS;
}

short CGTDriverCmd::GTD_ST_SetIoBit(short axis, unsigned short bitmask, short data)
{
	short rtn;
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}
	InitCmd(IO_SET_MESSAGE);
	Add16(axis);
	Add16(bitmask);
	Add16(data);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}
	return CMD_SUCCESS;
}
short CGTDriverCmd::GTD_ST_GetPunchZeroPos(short axis, long* pdata)
{
	short rtn;
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}
	InitCmd(APP_PUNCH_GET_ZEROPOS);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}
	Get32(pdata);
	return CMD_SUCCESS;
}
//20151123 wang.bin  ctl bit14 1:offset+1,0:offset+0
short CGTDriverCmd::GTD_ST_InfBoardFpga(short axis, unsigned short num, short* pdata, unsigned short addr, unsigned short ctl)
{
	short rtn;
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_INFBOARD_FPGA);
	Add16(axis);
	//data[2]???
	if (num>25)
	{
		num = 25;
	}
	Add16(num);
	Add16(addr);
	Add16(ctl);

	//write  bit15---1 write
	if (((unsigned short)(ctl)) & 0x8000)
	{
		for (int i = 0; i<num; ++i)
		{
			Add16(pdata[i]);
		}
		return SendCommand();
	}
	//read
	else
	{
		rtn = SendCommand();

		if (0 != rtn)
		{
			return rtn;
		}
		for (int i = 0; i<num; ++i)
		{
			Get16(&pdata[i]);
		}

		return CMD_SUCCESS;
	}
}


///////////////////////////////////////////////////////////////////////////////////
//20130407 by wangbin

short CGTDriverCmd::GTD_ST_SetModuleParam(short axis, short fc, short size, short *pdata)
{
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_MODULEPARAM);
	Add16(axis);
	//data[2]???
	Add16(fc);
	Add16(size);
	for (int i = 0; i<size; ++i)
	{
		Add16(pdata[i]);
	}

	return SendCommand();
}


short CGTDriverCmd::GTD_ST_GetModuleParam(short axis, short fc, short *pData)
{
	short i, rtn, size;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_MODULEPARAM);

	Add16(axis);

	Add16(fc);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(&size);

	for (i = 0; i<size - 1; ++i)
	{
		Get16(&pData[i]);
	}

	return CMD_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////////
//20130506 by wangbin

short CGTDriverCmd::GTD_ST_GetFlashParamIndexBase(short axis, unsigned long adr, short *pData)
{
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_FLASHPARAMINDEX);

	Add16(axis);

	Add32(adr);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pData);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GTD_ST_SetFlashParamIndexBase(short axis, unsigned long adr, short *pData)
{
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_FLASHPARAMINDEX);
	Add16(axis);
	//data[2]???
	Add32(adr);
	Add16(*pData);

	return SendCommand();
}

short CGTDriverCmd::GTD_ST_GetFlashParamIndex(short axis, unsigned long adr, short *pData)
{

	short rtn;
	short rd_data[2];
	rtn = GTD_ST_GetFlashParamIndexBase(axis, adr, &rd_data[0]);
	if (rtn)
		return rtn;

	rtn = GTD_ST_GetFlashParamIndexBase(axis, adr, &rd_data[1]);
	if (rtn)
		return rtn;

	if (rd_data[0] != rd_data[1])
	{
		return -9;
	}

	*pData = rd_data[0];
	return RTN_SUCCESS;

}

short CGTDriverCmd::GTD_ST_SetFlashParamIndex(short axis, unsigned long adr, short *pData)
{
	short rtn;
	short rd_data;
	rtn = GTD_ST_SetFlashParamIndexBase(axis, adr, pData);
	if (rtn)
		return rtn;

	rtn = GTD_ST_GetFlashParamIndexBase(axis, adr, &rd_data);
	if (rtn)
		return rtn;

	if (rd_data != *pData)
	{
		return -9;
	}

	return RTN_SUCCESS;
}

//wang bin 20130624

short CGTDriverCmd::GTD_ST_SetRamIndex16(short axis, short adr, short *pData)
{
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_RAMINDEX16);
	Add16(axis);
	//data[2]???
	Add16(adr);
	Add16(*pData);

	return SendCommand();
}
short CGTDriverCmd::GTD_ST_SetRamIndex32(short axis, short adr, long *pData)
{
	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_RAMINDEX32);
	Add16(axis);
	//data[2]???
	Add16(adr);
	Add32(*pData);

	return SendCommand();
}

short CGTDriverCmd::GTD_ST_GetRamIndex16(short axis, short adr, short *pData)
{
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_RAMINDEX16);

	Add16(axis);

	Add16(adr);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pData);

	return CMD_SUCCESS;
}
short CGTDriverCmd::GTD_ST_GetRamIndex32(short axis, short adr, long *pData)
{
	short rtn;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_RAMINDEX32);

	Add16(axis);

	Add16(adr);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get32(pData);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GTD_ST_GetBufData(short axis, short identify, short *pNum, short *pStatus, short *pData)
{
	short i, rtn;
	short num;

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_BUF_DATA);
	Add16(axis);
	Add16(identify);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pNum);
	Get16(pStatus);

	num = *pNum;
	if (num > 28)
	{
		num = 28;
	}

	for (i = 0; i<num; ++i)
	{
		Get16(&pData[i]);
	}

	return CMD_SUCCESS;
}
/*
short GTD_SetBufVarible(short axis,short pNum,short *pData0,short *pData1)
{
if( ( axis < 1 ) || ( axis > 8 ) )
{
return CMD_ERROR_PARAMETER;
}

InitCmd(DRV_SETBUF_VARIABLE);

Add16(axis);

//?????,?????id,?????

Add16(pNum);

for(int i=0;i<pNum;i++)
{
Add16(pData0[i]);
Add16(pData1[i]);
}

return SendCommand();
}
*/

short CGTDriverCmd::GTD_ST_SetDrvCmd(short axis, short pNum, short id, short *pData0)
{
	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SetDrvCmd);

	Add16(axis);

	//?????,?????id,?????

	Add16(pNum);

	Add16(id);

	for (int i = 0; i<pNum; i++)
	{
		Add16(pData0[i]);
	}

	return SendCommand();
}

short CGTDriverCmd::GTD_ST_GetDrvInf(short axis, short pNum, short id, short *pData0)
{
	short rtn;

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GetDrvInf);

	Add16(axis);

	//?????,?????id,?????

	Add16(pNum);

	Add16(id);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	for (int i = 0; i< pNum; i++)
	{
		Get16(&pData0[i]);
	}

	return CMD_SUCCESS;
}

//wangbin 20130905   ???cpac???flash

short CGTDriverCmd::GTD_ST_AppSaveFlashParam(short axis, short id, unsigned long adr, short *pdata)
{
	const unsigned long MIN_ADDR = 0;
	const unsigned long MAX_ADDR = 65536;
	if (MIN_ADDR <= adr && adr < MAX_ADDR)
	{
		return GTD_ST_SetFlashParamIndex(axis, adr, pdata);
	}
	return CMD_ERROR_PARAMETER;

	//if( ( axis < 1 ) || ( axis > 8 ) )
	//{
	//	return CMD_ERROR_PARAMETER;
	//}

	//InitCmd(DRV_SET_FLASHPARAMINDEX);
	//Add16(axis);
	////data[2]???
	//Add32(adr);
	//Add16(*pdata);

	//return SendCommand();
}

//wangbin 20130905   ???cpac?????

short CGTDriverCmd::GTD_ST_AppReadVariable(short axis, short id, short adr, short *pData)
{
	short rtn;

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_RAMINDEX16);

	Add16(axis);

	Add16(adr);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pData);

	return CMD_SUCCESS;
}


//wangbin 20131017  ???cpac??flash

short CGTDriverCmd::GTD_ST_AppReadFlashParam(short axis, short id, unsigned long adr, short *pdata)
{
	const unsigned long MIN_ADDR = 0;
	const unsigned long MAX_ADDR = 65536;
	if (MIN_ADDR <= adr && adr < MAX_ADDR)
	{
		return GTD_ST_GetFlashParamIndex(axis, adr, pdata);
	}
	return CMD_ERROR_PARAMETER;


	//short rtn;

	//if( ( axis < 1 ) || ( axis > 8 ) )
	//{
	//	return CMD_ERROR_PARAMETER;
	//}

	//InitCmd(DRV_GET_FLASHPARAMINDEX);

	//Add16(axis);

	//Add32(adr);

	//rtn =  SendCommand();

	//if( 0 != rtn )
	//{
	//	return rtn;
	//}

	//Get16(pdata);

	//return CMD_SUCCESS;
}

//wangbin 20131021  ?????
/*
short CGTDriverCmd::GTD_ST_AppGetVersionDriver(short axis,unsigned long adryear,unsigned long adrmd,short *pdata)
{
short rtn;

if( ( axis < 1 ) || ( axis > 8 ) )
{
return CMD_ERROR_PARAMETER;
}

InitCmd(DRV_GetVersionDriver);

Add16(axis);

Add32(adryear);
Add32(adrmd);

rtn =  SendCommand();

if( 0 != rtn )
{
return rtn;
}

for (int i = 0;i<6;i++)
{
Get16(&pdata[i]);
}

return CMD_SUCCESS;
}
*/
short CGTDriverCmd::GTD_ST_SetFpgaAddr(short axis, short adr, short *pData)
{
	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_FPGAADDR);
	Add16(axis);
	//data[2]???
	Add16(adr);
	Add16(*pData);

	return SendCommand();
}

short CGTDriverCmd::GTD_ST_GetFpgaAddr(short axis, short adr, short *pData)
{
	short rtn;

	if ((axis < 1) || (axis > 8))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_FPGAADDR);
	Add16(axis);
	Add16(adr);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}
	Get16(pData);
	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_SetMemory(unsigned long address, short count, short *pData)
{
	short i, cc, cc2;

	// ???????

	if (address % 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// ????SDRAM

	cc = (address >= 4) && (address <= (unsigned long)(0x02000000));

	// NVRAM
	cc2 = (address >= (unsigned long)(0x20300100)) && (address < (unsigned long)(0x20300400));

	if ((0 == cc) && (0 == cc2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((count < 0) || (count > 20))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_MEMORY);
	Add32(address);
	Add16(count);

	for (i = 0; i<count; ++i)
	{
		Add16(pData[i]);
	}

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FlashToSdram(long *pRetry)
{
	short rtn;

	InitCmd(FLASH_TO_SDRAM);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	if (NULL != pRetry)
	{
		Get32(pRetry);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SdramToFlash2(long *pRetry)
{
	short rtn;

	InitCmd(SDRAM_TO_FLASH_2);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	if (NULL != pRetry)
	{
		Get32(pRetry);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_CheckFlashPassword(void)
{
	InitCmd(CHECK_FLASH_PASSWORD);
	return SendCommand();
}

//liang.jj 20131104

short CGTDriverCmd::GT_ST_SetInjectPara(short active, TInjectPara *pInjectPara)
{
	double temp;

	if ((pInjectPara->adjustType < 0) || (pInjectPara->adjustType > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_INJECT_PARA);

	Add16(active);
	Add48F(pInjectPara->endPos);
	Add32(pInjectPara->valveShutTime);
	Add32(pInjectPara->deltaDecPos);
	Add32(pInjectPara->valveDo);
	Add32(pInjectPara->valveDoMask);
	Add16(pInjectPara->adjustType);
	Add16(pInjectPara->maxP);
	Add16(pInjectPara->maxQ);
	Add16(pInjectPara->minQ);
	Add16(pInjectPara->maxQAcc);
	Add32(pInjectPara->posOffsetInMinQ);
	temp = pInjectPara->adjustCoeff*65536.0;
	Add32((long)temp);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetInjectPara(TInjectPara *pInjectPara)
{
	short rtn;

	InitCmd(GET_INJECT_PARA);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get48F(&pInjectPara->endPos);
	Get32(&pInjectPara->valveShutTime);
	Get32(&pInjectPara->deltaDecPos);
	Get32(&pInjectPara->valveDo);
	Get32(&pInjectPara->valveDoMask);
	Get16(&pInjectPara->adjustType);
	Get16(&pInjectPara->maxP);
	Get16(&pInjectPara->maxQ);
	Get16(&pInjectPara->minQ);
	Get16(&pInjectPara->maxQAcc);
	Get32(&pInjectPara->posOffsetInMinQ);
	Get32F(&pInjectPara->adjustCoeff);
	Get32(&pInjectPara->deltaPosInMinQ);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFbPara(TFeedbackPara *pFeedbackPara)
{
	if ((pFeedbackPara->fbType != MC_ERULER) && (pFeedbackPara->fbType != MC_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FEEDBACK_PARA);

	Add16(pFeedbackPara->fbType);
	Add16(pFeedbackPara->fbIndex);
	Add16(pFeedbackPara->fbFilterPara1);
	Add16(pFeedbackPara->fbFilterPara2);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_StartInject()
{
	InitCmd(START_INJECT);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetValveDoValue(long mask)
{
	InitCmd(SET_VALVE_DO_VALUE);

	Add32(mask);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetValveDoValue(long *mask)
{
	short rtn;

	InitCmd(GET_VALVE_DO_VALUE);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get32(mask);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetInjectEncPos(double *fbPos)
{
	short rtn;

	InitCmd(GET_INJECT_ENC_POS);

	rtn = SendCommand();

	if (0 != rtn)
	{
		return rtn;
	}

	Get48F(fbPos);

	return CMD_SUCCESS;
}



// Add  by wu.jr 2014.01.02

short CGTDriverCmd::GT_ST_Update(long mask)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(UPDATE);
	Add32(mask);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPos(short profile, long pos)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((pos > (long)(0x3fffffff)) || (pos < (long)(0xc0000000)))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_POS);
	Add16(profile);
	Add32(pos);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPos(short profile, long *pPos)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_POS);
	Add16(profile);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(pPos);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetVel(short profile, double vel)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_VEL);
	Add16(profile);
	Add32F(vel);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetVel(short profile, double *pVel)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_VEL);
	Add16(profile);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(pVel);

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_PrfTrap(short profile)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PRF_TRAP);
	Add16(profile);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetTrapPrm(short profile, TTrapPrm *pPrm)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPrm)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pPrm->acc <= 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pPrm->velStart < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pPrm->smoothTime < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_TRAP_PRM);
	Add16(profile);
	Add32F(pPrm->acc);
	Add32F(pPrm->dec);
	Add32F(pPrm->velStart);
	Add16(pPrm->smoothTime);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetTrapPrm(short profile, TTrapPrm *pPrm)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPrm)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_TRAP_PRM);
	Add16(profile);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&pPrm->acc);
	Get32F(&pPrm->dec);
	Get32F(&pPrm->velStart);
	Get16(&pPrm->smoothTime);

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_SetPid(short control, short index, TPid *pPid)
{
	if ((control < 1) || (control > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((index < 1) || (index > 4))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPid)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PID);
	Add16(control);
	Add16(index);
	Add32F(pPid->kp);
	Add32F(pPid->ki);
	Add32F(pPid->kd);
	Add32F(pPid->kvff);
	Add32F(pPid->kaff);
	Add32(pPid->integralLimit);
	Add32(pPid->derivativeLimit);
	Add16(pPid->limit);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPid(short control, short index, TPid *pPid)
{
	short rtn;

	if ((control < 1) || (control > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((index < 1) || (index > 4))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPid)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PID);
	Add16(control);
	Add16(index);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&pPid->kp);
	Get32F(&pPid->ki);
	Get32F(&pPid->kd);
	Get32F(&pPid->kvff);
	Get32F(&pPid->kaff);
	Get32(&pPid->integralLimit);
	Get32(&pPid->derivativeLimit);
	Get16(&pPid->limit);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_CtrlMode(short axis, short mode)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(CTRL_MODE);
	Add16(axis);
	Add16(mode);

	return SendCommand();
}


short CGTDriverCmd::GT_ST_AxisOn(short axis)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(AXIS_ENABLE);
	Add16(axis);
	Add16(1);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_AxisOff(short axis)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(AXIS_ENABLE);
	Add16(axis);
	Add16(0);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_Stop(long mask, long option)
{
	InitCmd(STOP);
	Add32(mask);
	Add32(option);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPrfPos(short profile, double *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (profile + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PROFILE_INFO);
	Add16(profile);
	Add16(count);
	Add16(PROFILE_INFO_POS);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get48F(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPrfVel(short profile, double *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (profile + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PROFILE_INFO);
	Add16(profile);
	Add16(count);
	Add16(PROFILE_INFO_VEL);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get32F(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_GetEncPos(short encoder, double *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((encoder < 1) || (encoder > MAX_PROFILE))//?????encoder > 2
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (encoder + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_COUNT_INFO);
	Add16(encoder);
	Add16(count);
	Add16(COUNT_INFO_ENCODER_POS);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get48F(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_GetEncVel(short encoder, double *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((encoder < 1) || (encoder > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (encoder + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_COUNT_INFO);
	Add16(encoder);
	Add16(count);
	Add16(COUNT_INFO_ENCODER_VEL);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get32F(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}


//------------------------------------------------------------------------------------------------
// axis??????????
// axis???profile?encoer?pulse?control??
//------------------------------------------------------------------------------------------------
short CGTDriverCmd::GT_ST_ZeroPos(short axis, short count)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (axis + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	InitCmd(ZERO_POS);
	Add16(axis);
	Add16(count);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SynchPrfPosToEnc(short profile, short encoder)
{
	InitCmd(SYNCH_PRF_POS_TO_ENC);
	Add16(profile);
	Add16(encoder);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SynchAxisPos(short axis)
{
	InitCmd(SYNCH_AXIS_POS);
	Add16(axis);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_AlarmOff(short axis)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(ALARM_ENABLE);
	Add16(axis);
	Add16(0);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_AlarmOn(short axis)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(ALARM_ENABLE);
	Add16(axis);
	Add16(1);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_LmtsOn(short axis, short limitType)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(LMT_ENABLE);
	Add16(axis);
	Add16(limitType);
	Add16(1);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_LmtsOff(short axis, short limitType)
{
	if ((axis < 1) || (axis > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(LMT_ENABLE);
	Add16(axis);
	Add16(limitType);
	Add16(0);
	return SendCommand();
}


short CGTDriverCmd::GT_ST_GetSts(short axis, long *pSts, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (axis + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	if (NULL == pSts)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_STS);
	Add16(axis);
	Add16(count);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get32(&pSts[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_ClrSts(short axis, short count)
{
	if ((axis < 1) || (axis > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > MAX_PROFILE)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (axis + count > MAX_PROFILE + 1)
	{
		count = 1;
	}

	InitCmd(CLR_STS);
	Add16(axis);
	Add16(count);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_DrvSetVelPid(short control, short index, TPid *pPid)
{
	if ((control < 1) || (control > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((index < 1) || (index > 4))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPid)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_SET_VEL_PID);
	Add16(control);
	Add16(index);
	Add32F(pPid->kp);
	Add32F(pPid->ki);
	Add32F(pPid->kd);
	Add32F(pPid->kvff);
	Add32F(pPid->kaff);
	Add32(pPid->integralLimit);
	Add32(pPid->derivativeLimit);
	Add16(pPid->limit);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_DrvGetVelPid(short control, short index, TPid *pPid)
{
	short rtn;

	if ((control < 1) || (control > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((index < 1) || (index > 4))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPid)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(DRV_GET_VEL_PID);
	Add16(control);
	Add16(index);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&pPid->kp);
	Get32F(&pPid->ki);
	Get32F(&pPid->kd);
	Get32F(&pPid->kvff);
	Get32F(&pPid->kaff);
	Get32(&pPid->integralLimit);
	Get32(&pPid->derivativeLimit);
	Get16(&pPid->limit);

	return CMD_SUCCESS;
}


//----------------------------------------------------------
// PT??????
//----------------------------------------------------------
short CGTDriverCmd::GT_ST_PrfPt(short profile, short mode)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PRF_PT);
	Add16(profile);
	Add16(mode);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPtLoop(short profile, long loop)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PT_LOOP);
	Add16(profile);
	Add32(loop);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPtLoop(short profile, long *pLoop)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PT_LOOP);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get32(pLoop);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PtSpace(short profile, short *pSpace, short fifo)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pSpace)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_SPACE);
	Add16(profile);
	Add16(fifo);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pSpace);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PtData(short profile, double pos, long time, short type, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (type)
	{
	case PT_SEGMENT_NORMAL:
	case PT_SEGMENT_EVEN:
	case PT_SEGMENT_STOP:	break;
	default: return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_DATA);
	Add16(profile);
	Add16(fifo);
	Add48F(pos);
	Add32(time);
	Add16(type);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PtDataWN(short profile, double pos, long time, short type, long segNum, short fifo)
{
	if ((profile < 1) || (profile > 2))
	{
		return  CMD_ERROR_PARAMETER;
	}

	switch (type)
	{
	case PT_SEGMENT_NORMAL:
	case PT_SEGMENT_EVEN:
	case PT_SEGMENT_STOP:   break;
	default: return  CMD_ERROR_PARAMETER;
	}

	if (segNum < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_DATA_WN);
	Add16(profile);
	Add16(fifo);
	Add48F(pos);
	Add32(time);
	Add16(type);
	Add32(segNum);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PtGetSegNum(short profile, long *pSegNum)
{
	short rtn;

	if ((profile < 1) || (profile > 2))
	{
		return  CMD_ERROR_PARAMETER;
	}

	if (NULL == pSegNum)
	{
		return  CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_GET_SEG_NUM);
	Add16(profile);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get32(pSegNum);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PtClear(short profile, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_CLEAR);
	Add16(profile);
	Add16(fifo);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PtStart(long mask, long option)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PT_START);
	Add32(mask);
	Add32(option);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPtMemory(short profile, short memory)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((memory != 0) && (memory != 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PT_MEMORY);
	Add16(profile);
	Add16(memory);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPtMemory(short profile, short *pMemory)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PT_MEMORY);
	Add16(profile);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pMemory);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetDi(short diType, long *pValue)
{
	short rtn;

	switch (diType)
	{
	case MC_LIMIT_POSITIVE:
	case MC_LIMIT_NEGATIVE:
	case MC_ALARM:
	case MC_HOME:
	case MC_GPI:
	case MC_ARRIVE:
	case MC_EGPI0:
	case MC_EGPI1: 		break;
	default: return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_DI);
	Add16(diType);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(pValue);

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_SetDo(short doType, long pValue)
{
	switch (doType)
	{
	case MC_ENABLE:
	case MC_CLEAR:
	case MC_GPO:break;
	default: return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_DO);
	Add16(doType);
	Add32(pValue);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetEncPos(short encoder, long pos)
{
	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_COUNT_POS);
	Add16(1);
	Add16(encoder);
	Add32(pos);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPrfPos(short profile, long pos)
{
	if ((profile < 1) || (profile > PROFILE_MAX))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRF_POS);
	Add16(profile);
	Add32(pos);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetControlEncoder(short control, short encoder)
{
	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CONTROL_ENCODER);
	Add16(control);
	Add16(encoder);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetControlEncoder(short control, short *pEncoder)
{
	short rtn;

	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CONTROL_ENCODER);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pEncoder);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetControlValue(short control, short value)
{
	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CONTROL_VALUE);
	Add16(control);
	Add16(value);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetControlValue(short control, short *pValue)
{
	short rtn;

	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CONTROL_VALUE);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pValue);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetLoopMode(short axis, TLoopMode *pMode)
{
	InitCmd(SET_LOOP_MODE);
	Add16(axis);
	Add16(pMode->loopMode);
	Add16(pMode->pressProfileMode);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetLoopMode(short axis, TLoopMode *pMode)
{
	short rtn;

	InitCmd(GET_LOOP_MODE);
	Add16(axis);
	rtn = SendCommand();

	if (rtn)
	{
		return rtn;
	}

	Get16(&(pMode->loopMode));
	Get16(&(pMode->pressProfileMode));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetAdcValue(short adc, short *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_ADC_VALUE);
	Add16(adc);
	Add16(count);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get16(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetAdcFilterEx(short adc, TAdcFilter *pFilter)
{
	InitCmd(SET_ADC_FILTER_EX);
	Add16(adc);
	Add32F(pFilter->k);
	Add16(pFilter->ignoreBit);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetAdcFilterEx(short adc, TAdcFilter *pFilter)
{
	short rtn;
	InitCmd(GET_ADC_FILTER_EX);
	Add16(adc);

	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&(pFilter->k));
	Get16(&(pFilter->ignoreBit));
	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetStopOffset(short axis, TStopOffset *pStopOffset)
{
	InitCmd(SET_STOP_OFFSET);
	Add16(axis);
	Add32(pStopOffset->distance);
	Add32F(pStopOffset->vel);
	Add32F(pStopOffset->acc);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetStopOffset(short axis, TStopOffset *pStopOffset)
{
	short rtn;

	InitCmd(GET_STOP_OFFSET);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(&(pStopOffset->distance));
	Get32F(&(pStopOffset->vel));
	Get32F(&(pStopOffset->acc));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PressStopOn(short axis, TLoopMode *pLoopMode)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(ENABLE_PRESS_STOP);
	Add16(axis);
	Add16(1);
	Add16(pLoopMode->loopMode);
	Add16(pLoopMode->pressProfileMode);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_PressStopOff(short axis)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(ENABLE_PRESS_STOP);
	Add16(axis);
	Add16(0);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPressStop(short axis, TPressStop *pPressStop)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_STOP);
	Add16(axis);
	Add16(pPressStop->limit1);
	Add16(pPressStop->limit2);
	Add16(pPressStop->time);
	Add16(pPressStop->triggerCondition);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressStop(short axis, TPressStop *pPressStop)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_STOP);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(&(pPressStop->limit1));
	Get16(&(pPressStop->limit2));
	Get16(&(pPressStop->time));
	Get16(&(pPressStop->triggerCondition));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_TorqueStopOn(short axis)
{
	InitCmd(ENABLE_TORQUE_STOP);
	Add16(axis);
	Add16(1);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_TorqueStopOff(short axis)
{
	InitCmd(ENABLE_TORQUE_STOP);
	Add16(axis);
	Add16(0);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetTorqueStop(short axis, TPressStop *pPressStop)
{

	InitCmd(SET_TORQUE_STOP);
	Add16(axis);
	Add16(pPressStop->limit1);
	Add16(pPressStop->limit2);
	Add16(pPressStop->time);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetTorqueStop(short axis, TPressStop *pPressStop)
{
	short rtn;

	InitCmd(GET_TORQUE_STOP);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(&(pPressStop->limit1));
	Get16(&(pPressStop->limit2));
	Get16(&(pPressStop->time));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetLoopSwitch(short axis, TLoopSwitch *pLoopSwitch)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_LOOP_SWITCH);
	Add16(axis);
	Add32F(pLoopSwitch->dec);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetLoopSwitch(short axis, TLoopSwitch *pLoopSwitch)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_LOOP_SWITCH);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&(pLoopSwitch->dec));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressRange(short axis, short centerSynch, long range)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_RANGE);
	Add16(axis);
	Add16(centerSynch);
	Add32(range);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressRange(short axis, long *pCenterPos, long *pRange)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_RANGE);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}

	Get32(pCenterPos);
	Get32(pRange);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressCross(short axis, short dir, long pos)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_CROSS);
	Add16(axis);
	Add16(dir);
	Add32(pos);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressCross(short axis, short *pDir, long *pPos)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_CROSS);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}

	Get16(pDir);
	Get32(pPos);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetTorqueLimit(short axis, short torqueLimit)
{
	InitCmd(SET_TORQUE_LIMIT);
	Add16(axis);
	Add16(torqueLimit);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetTorqueLimit(short axis, short *pTorqueLimit)
{
	short rtn;

	InitCmd(GET_TORQUE_LIMIT);
	Add16(axis);

	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pTorqueLimit);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressPid(short axis, TPressPid *pPid)
{
	InitCmd(SET_PRESS_PID);
	Add16(axis);
	Add32F(pPid->kp);
	Add32F(pPid->ki);
	Add32F(pPid->kd);
	Add32F(pPid->kvff);
	Add32F(pPid->kaff);
	Add32F(pPid->piConvertPara);
	Add32(pPid->integralLimit);
	Add32(pPid->derivativeLimit);
	Add16(pPid->limitMax);
	Add16(pPid->limitMin);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressPid(short axis, TPressPid *pPid)
{
	short rtn;

	InitCmd(GET_PRESS_PID);
	Add16(axis);

	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&pPid->kp);
	Get32F(&pPid->ki);
	Get32F(&pPid->kd);
	Get32F(&pPid->kvff);
	Get32F(&pPid->kaff);
	Get32F(&pPid->piConvertPara);
	Get32(&pPid->integralLimit);
	Get32(&pPid->derivativeLimit);
	Get16(&pPid->limitMax);
	Get16(&pPid->limitMin);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressFilter(short axis, TPressFilter *pPressFilter)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_FILTER);
	Add16(axis);
	Add32(pPressFilter->t);
	Add32F(pPressFilter->k);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressFilter(short axis, TPressFilter *pPressFilter)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_FILTER);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}

	Get32(&(pPressFilter->t));
	Get32F(&(pPressFilter->k));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPressStatus(short axis, long *pStatus)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_STATUS);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(pStatus);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPrfPress(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRF_PRESS);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(pValue);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetAtlPress(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_ATL_PRESS);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	short value;
	Get16(&value);

	*pValue = value;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPrfSpeed(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRF_SPEED);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	short value;
	Get16(&value);

	*pValue = value;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetAtlSpeed(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_ATL_SPEED);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	short value;
	Get16(&value);

	*pValue = value;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPrfTorque(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRF_TORQUE);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	short value;
	Get16(&value);

	*pValue = value;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetAtlTorque(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_ATL_TORQUE);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	short value;
	Get16(&value);

	*pValue = value;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressPrm(short axis, TPressPrm *pPressPrm)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_PRM);
	Add16(axis);
	Add32F(pPressPrm->acc);
	Add32F(pPressPrm->dec);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressPrm(short axis, TPressPrm *pPressPrm)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_PRM);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&(pPressPrm->acc));
	Get32F(&(pPressPrm->dec));

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPress(short axis, double value)
{
	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS);
	Add16(axis);
	Add32F(value);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPress(short axis, double *pValue)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(pValue);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPressArray(short axis, TPressArray *pPressArray)
{
	short i;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pPressArray->count > 4)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PRESS_ARRAY);
	Add16(axis);
	Add16(pPressArray->count);

	for (i = 0; i<pPressArray->count; ++i)
	{
		Add32F(pPressArray->buffer[i].pressTarget);
		Add32(pPressArray->buffer[i].pressTime);
		Add32F(pPressArray->buffer[i].pressAcc);
	}

	Add16(pPressArray->exit);

	return SendCommand();
}


short CGTDriverCmd::GT_ST_GetPressArray(short axis, TPressArray *pPressArray)
{
	short rtn;
	short i;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PRESS_ARRAY);
	Add16(axis);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}

	Get16(&(pPressArray->count));

	for (i = 0; i<pPressArray->count; ++i)
	{
		Get32F(&(pPressArray->buffer[i].pressTarget));
		Get32(&(pPressArray->buffer[i].pressTime));
		Get32F(&(pPressArray->buffer[i].pressAcc));
	}

	Get16(&(pPressArray->exit));

	return CMD_SUCCESS;
}

/**/

short CGTDriverCmd::GT_ST_PressTableClear(short table)
{
	InitCmd(PRESS_TABLE_CLEAR);
	Add16(table);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_PressTableData(short table, float t, float k[])
{
	InitCmd(PRESS_TABLE_DATA);
	Add16(table);
	Add32(*(long *)&t);
	Add32(*(long *)&k[0]);
	Add32(*(long *)&k[1]);
	Add32(*(long *)&k[2]);
	Add32(*(long *)&k[3]);
	return SendCommand();
}

void CGTDriverCmd::fsin(double A, double w, double x, double &y, double &v)
{
	y = A*(1 - cos(w*x)) / 2.0;
	v = A*w*sin(w*x) / 2.0;
}

void CGTDriverCmd::Poly3Coef(double dt, double y1, double y2, double v1, double v2, float k[])
{
	double dy, dv, m;
	double dt2, dt3;

	dy = y2 - y1;
	dv = v2 - v1;
	m = dy - v1*dt;

	dt2 = dt*dt;
	dt3 = dt2*dt;

	k[0] = (float)(-2 * m / dt3 + dv / dt2);
	k[1] = (float)(3 * m / dt2 - dv / dt);
	k[2] = (float)v1;
	k[3] = (float)y1;
}

short CGTDriverCmd::GT_ST_PressTableSin(short table, double A, double T)
{
	short rtn;

	rtn = GT_ST_PressTableClear(table);
	if (rtn) return rtn;

	double w, dt;
	double y1, y2;
	double v1, v2;
	double t;
	float k[4];

	w = 2 * 3.1415926535897932384626433832795 / T;
	dt = T / 4;

	for (t = 0; t<T; t += dt)
	{
		fsin(A, w, t, y1, v1);
		fsin(A, w, t + dt, y2, v2);
		Poly3Coef(dt, y1, y2, v1, v2, k);

		rtn = GT_ST_PressTableData(table, (float)t, k);
		if (rtn) return rtn;
	}

	k[0] = 0;
	k[1] = 0;
	k[2] = 0;
	k[3] = 0;
	return GT_ST_PressTableData(table, (float)T, k);
}

short CGTDriverCmd::GT_ST_PressTableSelect(short axis, short table)
{
	InitCmd(PRESS_TABLE_SELECT);
	Add16(axis);
	Add16(table);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPressTableLoop(short axis, short loop)
{
	InitCmd(SET_PRESS_TABLE_LOOP);
	Add16(axis);
	Add32(loop);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPressTableLoop(short axis, long *pLoopCount, long *pLoop)
{
	short rtn;

	InitCmd(GET_PRESS_TABLE_LOOP);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(pLoopCount);
	Get32(pLoop);
	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetPressTableStatus(short axis, short *pTableId, float *pTime)
{
	short rtn;

	InitCmd(GET_PRESS_TABLE_STATUS);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pTableId);
	Get32((long *)pTime);
	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PressTableStart(short axis, short table)
{
	InitCmd(PRESS_TABLE_START);
	Add16(axis);
	Add16(table);
	return SendCommand();
}


/**/

short CGTDriverCmd::GT_ST_SetStopDec(short profile, double decSmoothStop, double decAbruptStop)
{
	if ((profile < 1) || (profile > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_STOP_DEC);
	Add16(profile);
	Add32F(decSmoothStop);
	Add32F(decAbruptStop);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetStopDec(short profile, double *pDecSmoothStop, double *pDecAbruptStop)
{
	short rtn;

	if ((profile < 1) || (profile > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_STOP_DEC);
	Add16(profile);
	rtn = SendCommand();
	if (0 != rtn)
	{
		return rtn;
	}

	Get32F(pDecSmoothStop);
	Get32F(pDecAbruptStop);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetPosErr(short control, long error)
{
	InitCmd(SET_POS_ERR);
	Add16(control);
	Add32(error);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPosErr(short control, long *pError)
{
	short rtn;

	InitCmd(GET_POS_ERR);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(pError);
	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetAxisError(short axis, double *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > 1)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pValue)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_AXIS_INFO);
	Add16(axis);
	Add16(count);
	Add16(AXIS_INFO_ERROR);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get48F(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetControlInfo(short control, TControlInfo *pControlInfo)
{
	short rtn;
	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pControlInfo)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CONTROL_INFO);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get48F(&pControlInfo->refPos);
	Get48F(&pControlInfo->refPosFilter);
	Get48F(&pControlInfo->refPosFilter2);
	Get48F(&pControlInfo->cntPos);
	Get48F(&pControlInfo->cntPosFilter);
	Get48F(&pControlInfo->error);
	Get32F(&pControlInfo->refVel);
	Get32F(&pControlInfo->refAcc);
	Get16(&pControlInfo->value);
	Get16(&pControlInfo->valueFilter);
	Get16(&pControlInfo->offset);

	return CMD_SUCCESS;
}
//zhao.xc20141228
short CGTDriverCmd::GT_ST_GetDebugInfo(short control, TDebugInfo *pDebugInfo)
{
	short rtn;
	if ((control < 1) || (control > 21))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pDebugInfo)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_DEBUG_INFO);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(&pDebugInfo->cntPos_Debug);
	Get32(&pDebugInfo->prfPos_Debug);
	Get32(&pDebugInfo->error_Debug);
	Get16(&pDebugInfo->encoder_Debug);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_ClearTime(void)
{
	InitCmd(CLEAR_TIME);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetTime(long item, unsigned long *pTime, unsigned long *pTimeMax)
{
	short rtn;

	InitCmd(GET_TIME);
	Add32(item);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32((long *)pTime);
	Get32((long *)pTimeMax);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetDriverAlarm(short axis, short *pAlarmFlag, short *pAlarmCode)
{
	short rtn;

	if ((axis < 1) || (axis > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_DRIVER_ALARM);
	Add16(axis);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pAlarmFlag);
	Get16(pAlarmCode);

	return CMD_SUCCESS;
}


short CGTDriverCmd::GT_ST_SetMoveDistancePress(short axis, TMoveDistancePress *pPress)
{
	InitCmd(SET_MOVE_DISTANCE);
	Add16(axis);
	Add32(pPress->distance);

	if (pPress->enable)
	{
		Add16(MOVE_DISTANCE_PRESS);
		Add16((short)(pPress->value));
	}
	else
	{
		Add16(MOVE_DISTANCE_NONE);
	}


	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetMoveDistancePress(short axis, TMoveDistancePress *pPress)
{
	short rtn;

	InitCmd(GET_MOVE_DISTANCE);
	Add16(axis);

	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32(&(pPress->distance));

	short mode;
	short value;
	Get16(&mode);

	if (MOVE_DISTANCE_PRESS == mode)
	{
		pPress->enable = 1;
		Get16(&value);
	}
	else
	{
		pPress->enable = 0;
		value = 0;
	}

	pPress->value = value;

	return CMD_SUCCESS;
}

//----------------------------------------------------------
// Follow??????
//----------------------------------------------------------
short CGTDriverCmd::GT_ST_PrfFollowEx(short profile, short dir)
{

	InitCmd(PRF_FOLLOW_EX);
	Add16(profile);
	Add16(dir);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetFollowMasterEx(short profile, short masterIndex, short masterType, short masterItem)
{


	InitCmd(SET_FOLLOW_MASTER_EX);
	Add16(profile);
	Add16(masterIndex);
	Add16(masterType);
	Add16(masterItem);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowMasterEx(short profile, short *pMasterIndex, short *pMasterType, short *pMasterItem)
{
	short rtn;
	short masterType, masterItem;



	InitCmd(GET_FOLLOW_MASTER_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pMasterIndex);
	Get16(&masterType);
	Get16(&masterItem);

	if (NULL != pMasterType)
	{
		*pMasterType = masterType;
	}

	if (NULL != pMasterItem)
	{
		*pMasterItem = masterItem;
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowLoopEx(short profile, long loop)
{


	InitCmd(SET_FOLLOW_LOOP_EX);
	Add16(profile);
	Add32(loop);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowLoopEx(short profile, long *pLoop)
{
	short rtn;



	if (NULL == pLoop)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_LOOP_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get32(pLoop);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowEventEx(short profile, short event, short masterDir, long pos)
{


	InitCmd(SET_FOLLOW_EVENT_EX);
	Add16(profile);
	Add16(event);
	Add16(masterDir);
	Add32(pos);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowEventEx(short profile, short *pEvent, short *pMasterDir, long *pPos)
{
	short rtn;



	if ((NULL == pEvent) || (NULL == pMasterDir))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_EVENT_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pEvent);
	Get16(pMasterDir);

	if (NULL != pPos)
	{
		Get32(pPos);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_FollowSpaceEx(short profile, short *pSpace, short fifo)
{
	short rtn;



	if (NULL == pSpace)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_SPACE_EX);
	Add16(profile);
	Add16(fifo);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pSpace);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_FollowDataPercentEx(short profile, double masterSegment, double slaveSegment, short type, short percent, short fifo)
{


	switch (type)
	{
	case FOLLOW_SEGMENT_NORMAL:
	case FOLLOW_SEGMENT_EVEN:
	case FOLLOW_SEGMENT_STOP:
	case FOLLOW_SEGMENT_CONTINUE:	break;
	default: return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_DATA_PERCENT_EX);
	Add16(profile);
	Add16(fifo);
	AddFloat64(masterSegment);
	AddFloat64(slaveSegment);
	Add16(type);
	Add16(percent);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowDataPercent2Ex(short profile, double masterSegment, double slaveSegment, double velBeginRatio, double velEndRatio, short percent, short *pPercent1, short fifo)
{

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_DATA_PERCENT2_EX);
	Add16(profile);
	Add16(fifo);
	AddFloat64(masterSegment);
	AddFloat64(slaveSegment);
	AddFloat64(velBeginRatio);
	AddFloat64(velEndRatio);
	Add16(percent);

	short rtn;
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	if (NULL != pPercent1)
	{
		Get16(pPercent1);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetFollowDataPercent2Ex(double masterPos, double v1, double v2, double p, double p1, double *pSlavePos)
{
	short rtn;

	InitCmd(GET_FOLLOW_DATA_PERCENT2_EX);
	AddFloat64(masterPos);
	AddFloat64(v1);
	AddFloat64(v2);
	AddFloat64(p);
	AddFloat64(p1);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	GetFloat64(pSlavePos);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_FollowClearEx(short profile, short fifo)
{


	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_CLEAR_EX);
	Add16(profile);
	Add16(fifo);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowStartEx(long mask, long option)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_START_EX);
	Add32(mask);
	Add32(option);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowSwitchEx(long mask)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_SWITCH_EX);
	Add32(mask);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetFollowMemoryEx(short profile, short memory)
{
	if ((0 != memory) && (1 != memory))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_MEMORY_EX);
	Add16(profile);
	Add16(memory);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowMemoryEx(short profile, short *pMemory)
{
	short rtn;



	if (NULL == pMemory)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_MEMORY_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pMemory);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetFollowStatusEx(short profile, short *pFifoNum, short *pSwitchStatus)
{
	short rtn;



	if (NULL == pFifoNum)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pSwitchStatus)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_STATUS_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pFifoNum);
	Get16(pSwitchStatus);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowPhasingEx(short profile, short profilePhasing)
{
	InitCmd(SET_FOLLOW_PHASING_EX);
	Add16(profile);
	Add16(profilePhasing);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowPhasingEx(short profile, short *pProfilePhasing)
{
	short rtn;

	if (pProfilePhasing == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_PHASING_EX);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pProfilePhasing);
	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_EncSns(unsigned short sense)
{
	InitCmd(ENC_SNS);
	Add16((short)sense);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PrfJog(short profile)
{
	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PRF_JOG);
	Add16(profile);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetJogPrm(short profile, TJogPrm *pPrm)
{
	if ((profile < 1) || (profile >2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPrm)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pPrm->acc <= 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((pPrm->smooth < 0) || (pPrm->smooth >= 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_JOG_PRM);
	Add16(profile);
	Add32F(pPrm->acc);
	Add32F(pPrm->dec);
	Add16((short)(pPrm->smooth * 65536));

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetJogPrm(short profile, TJogPrm *pPrm)
{
	short rtn;
	unsigned short smooth;

	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pPrm)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_JOG_PRM);
	Add16(profile);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32F(&pPrm->acc);
	Get32F(&pPrm->dec);
	Get16((short *)&smooth);
	pPrm->smooth = smooth / 65536.0;

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetControlMode(short control, short controlMode)
{
	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (controlMode)
	{
	case MC_FULL_CLOSE_MODE:
	case MC_SEMI_CLOSE_MODE:
	case MC_HYBRID_CLOSE_MODE:break;
	default: return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CONTROL_MODE);
	Add16(control);
	Add16(controlMode);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetControlMode(short control, short *pControlMode)
{
	short rtn;

	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CONTROL_MODE);
	Add16(control);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pControlMode);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetEncoderEquivalant(short control, double equivalantRatio)
{
	if ((control < 1) || (control > 1))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_ENCODER_EQUIVALANT);
	Add16(control);
	Add32F(equivalantRatio);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetCaptureMode(short encoder, short mode)
{
	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (mode)
	{
	case CAPTURE_HOME:
	case CAPTURE_INDEX:
	case CAPTURE_PROBE:
	case CAPTURE_HSIO0:
	case CAPTURE_HSIO1:
	case CAPTURE_SOFT_PROBE0:
	case CAPTURE_SOFT_PROBE1:    break;
	default:	return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CAPTURE_MODE);
	Add16(encoder);
	Add16(mode);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetCaptureMode(short encoder, short *pMode, short count)
{
	short rtn, i;

	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > RES_ENCODER)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (encoder + count > RES_ENCODER + 1)
	{
		count = RES_ENCODER + 1 - encoder;
	}

	if (NULL == pMode)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CAPTURE_MODE);
	Add16(encoder);
	Add16(count);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get16(&pMode[i]);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetCaptureStatus(short encoder, short *pStatus, long *pValue, short count, unsigned long *pClock)
{
	short rtn, i;

	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > RES_ENCODER)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (encoder + count > RES_ENCODER + 1)
	{
		count = RES_ENCODER + 1 - encoder;
	}

	if ((NULL == pStatus) || (NULL == pValue))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CAPTURE_STATUS);
	Add16(encoder);
	Add16(count);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	// ??????
	for (i = 0; i<count; ++i)
	{
		Get16(&pStatus[i]);
	}

	// ?????
	for (i = 0; i<count; ++i)
	{
		Get32(&pValue[i]);
	}

	if (NULL != pClock)
	{
		Get32((long *)pClock);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetCaptureSense(short encoder, short mode, short sense)
{
	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (mode)
	{
	case CAPTURE_HOME:
	case CAPTURE_INDEX:
	case CAPTURE_PROBE:
	case CAPTURE_SOFT_PROBE0:
	case CAPTURE_SOFT_PROBE1:    break;
	default:	return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CAPTURE_SENSE);
	Add16(encoder);
	Add16(mode);
	Add16(sense);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_TriggerSoftProbe(short mode, short state)
{
	switch (mode)
	{
	case CAPTURE_SOFT_PROBE0:
	case CAPTURE_SOFT_PROBE1:    break;
	default:	return CMD_ERROR_PARAMETER;
	}
	InitCmd(TRIGGER_SOFT_PROBE);
	Add16(mode);
	Add16(state);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetCaptureType(short axis, short type)
{
	short encoder;
	encoder = axis;

	if ((encoder < 1) || (encoder > RES_ENCODER))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (type)
	{
	case PULSE_COUNT:
	case ENCODER_COUNT: break;
	default:	return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_CAPTURE_TYPE);
	Add16(encoder);
	Add16(type);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetClockHighPrecision(unsigned long *pClock)
{
	short rtn;

	if (NULL == pClock)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_CLOCK_HIGH_PRECISION);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32((long *)pClock);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetMemory(unsigned long address, short count, short *pData)
{
	short rtn, i, cc1, cc2, cc3, cc4;

	if (address % 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// SDRAM
	cc1 = (address >= 4) && (address <= (unsigned long)(0x02000000));

	// L1 全局变量
	cc2 = (address >= (unsigned long)(0xff900000)) && (address <= (unsigned long)(0xff907fff));

	// Flash
	cc3 = (address >= (unsigned long)(0x20000000)) && (address < (unsigned long)(0x20080000));

	// NVRAM
	cc4 = (address >= (unsigned long)(0x20300100)) && (address < (unsigned long)(0x20300400));

	if ((0 == cc1) && (0 == cc2) && (0 == cc3) && (0 == cc4))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((count < 0) || (count > 20))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_MEMORY);
	Add32(address);
	Add16(count);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get16(&pData[i]);
	}

	return CMD_SUCCESS;
}

//----------------------------------------------------------
// PVT??????
//----------------------------------------------------------
short CGTDriverCmd::GT_ST_PrfPvt(short profile)
{
	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PRF_PVT);
	Add16(profile);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetPvtLoop(short profile, long loop)
{
	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_PVT_LOOP);
	Add16(profile);
	Add32(loop);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetPvtLoop(short profile, long *pLoopCount, long *pLoop)
{
	short rtn;

	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_PVT_LOOP);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get32(pLoopCount);
	Get32(pLoop);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PvtStatus(short profile, short *pTableId, double *pTime, short count)
{
	short rtn, i;

	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (count > 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (profile + count > 2 + 1)
	{
		count = 2 + 1 - profile;
	}

	InitCmd(PVT_STATUS);
	Add16(profile);
	Add16(count);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	for (i = 0; i<count; ++i)
	{
		Get16(&pTableId[i]);
		Get48F(&pTime[i]);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PvtStart(long mask)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PVT_START);
	Add32(mask);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PvtTableSelect(short profile, short tableId)
{
	if ((profile < 1) || (profile > 2))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PVT_TABLE_SELECT);
	Add16(profile);
	Add16(tableId);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_PvtTable(short tableId, long n, double *pTime, double *pPos, double *pVel)
{
	short rtn;
	long i;
	double a, b, c;

	a = 0;
	b = 0;
	c = 0;

	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// ???????
	for (i = 0; i<n - 1; ++i)
	{
		if (pTime[i + 1] <= pTime[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// ?????
	InitCmd(PVT_TABLE_CLEAR);
	Add16(tableId);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	// ???????
	for (i = 0; i<n - 1; ++i)
	{
		Hermite(2, &pTime[i], &pPos[i], &pVel[i], &a, &b, &c);

		InitCmd(PVT_TABLE_DATA);
		Add16(tableId);
		AddFloat((float)pTime[i]);
		AddFloat((float)pPos[i]);
		AddFloat((float)a);
		AddFloat((float)b);
		AddFloat((float)c);

		rtn = SendCommand();
		if (CMD_SUCCESS != rtn)
		{
			return rtn;
		}
	}

	InitCmd(PVT_TABLE_DATA);
	Add16(tableId);
	AddFloat((float)pTime[n - 1]);
	AddFloat((float)pPos[n - 1]);
	AddFloat(0);
	AddFloat(0);
	AddFloat(0);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PvtTableEx(short tableId, long n, double *pTime, double *pPos, double *pVelBegin, double *pVelEnd)
{
	short rtn;
	long i;
	double vel[2], a, b, c;

	vel[0] = 0;
	vel[1] = 0;
	a = 0;
	b = 0;
	c = 0;

	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// ???????
	for (i = 0; i<n - 1; ++i)
	{
		if (pTime[i + 1] <= pTime[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// ?????
	InitCmd(PVT_TABLE_CLEAR);
	Add16(tableId);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	// ???????
	for (i = 0; i<n - 1; ++i)
	{
		vel[0] = pVelBegin[i];
		vel[1] = pVelEnd[i];

		Hermite(2, &pTime[i], &pPos[i], vel, &a, &b, &c);

		InitCmd(PVT_TABLE_DATA);
		Add16(tableId);
		AddFloat((float)pTime[i]);
		AddFloat((float)pPos[i]);
		AddFloat((float)a);
		AddFloat((float)b);
		AddFloat((float)c);

		rtn = SendCommand();
		if (CMD_SUCCESS != rtn)
		{
			return rtn;
		}
	}

	InitCmd(PVT_TABLE_DATA);
	Add16(tableId);
	AddFloat((float)pTime[n - 1]);
	AddFloat((float)pPos[n - 1]);
	AddFloat(0);
	AddFloat(0);
	AddFloat(0);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	return CMD_SUCCESS;
}
short CGTDriverCmd::GT_ST_PvtTableComplete(short tableId, long n, double *pTime, double *pPos, double *pA, double *pB, double *pC, double velBegin, double velEnd)
{
	short rtn;
	long i;

	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// ???????
	for (i = 0; i<n - 1; ++i)
	{
		if (pTime[i + 1] <= pTime[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// ????a, b, c
	rtn = SplineComplete(n, pTime, pPos, pA, pB, pC, velBegin, velEnd);
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	// ?????
	InitCmd(PVT_TABLE_CLEAR);
	Add16(tableId);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	// ????
	for (i = 0; i<n - 1; ++i)
	{
		InitCmd(PVT_TABLE_DATA);
		Add16(tableId);
		AddFloat((float)pTime[i]);
		AddFloat((float)pPos[i]);
		AddFloat((float)pA[i]);
		AddFloat((float)pB[i]);
		AddFloat((float)pC[i]);

		rtn = SendCommand();
		if (CMD_SUCCESS != rtn)
		{
			return rtn;
		}
	}

	InitCmd(PVT_TABLE_DATA);
	Add16(tableId);
	AddFloat((float)pTime[n - 1]);
	AddFloat((float)pPos[n - 1]);
	AddFloat(0);
	AddFloat(0);
	AddFloat(0);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PvtTablePercent(short tableId, long n, double *pTime, double *pPos, double *pPercent, double velBegin)
{
	short rtn;
	long i, j, count;
	double time[4], pos[4], vel[4];
	double v[2], dx, dy, a, b, c;

	rtn = 0;
	i = 0;
	j = 0;
	count = 0;
	for (i = 0; i<4; ++i)
	{
		time[i] = 0;
		pos[i] = 0;
		vel[i] = 0;
	}
	v[0] = 0;
	v[1] = 0;
	dx = 0;
	dy = 0;
	a = 0;
	b = 0;
	c = 0;

	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// pTime?????
	for (i = 0; i<n - 1; ++i)
	{
		if (pTime[i + 1] <= pTime[i])
		{
			return CMD_ERROR_PARAMETER;
		}

		if ((pPercent[i] < 0) || (pPercent[i] > 100))
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// ?????
	InitCmd(PVT_TABLE_CLEAR);
	Add16(tableId);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	v[0] = velBegin;

	for (i = 0; i<n - 1; ++i)
	{
		dx = pTime[i + 1] - pTime[i];
		dy = pPos[i + 1] - pPos[i];

		v[1] = 2 * dy / dx - v[0];

		PercentSplit(2, &pTime[i], &pPos[i], v, &pPercent[i], &count, time, pos, vel);

		// ?????abc
		for (j = 0; j<count - 1; ++j)
		{
			// ??abc
			Hermite(2, &time[j], &pos[j], &vel[j], &a, &b, &c);

			// ????
			InitCmd(PVT_TABLE_DATA);
			Add16(tableId);
			AddFloat((float)time[j]);
			AddFloat((float)pos[j]);
			AddFloat((float)a);
			AddFloat((float)b);
			AddFloat((float)c);

			rtn = SendCommand();
			if (CMD_SUCCESS != rtn)
			{
				return rtn;
			}
		}

		v[0] = v[1];
	}

	InitCmd(PVT_TABLE_DATA);
	Add16(tableId);
	AddFloat((float)pTime[n - 1]);
	AddFloat((float)pPos[n - 1]);
	AddFloat(0);
	AddFloat(0);
	AddFloat(0);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_PvtPercentCalculate(long n, double *pTime, double *pPos, double *pPercent, double velBegin, double *pVel)
{
	long i;
	double v[2], dx, dy;

	i = 0;
	v[0] = 0;
	v[1] = 0;
	dx = 0;
	dy = 0;

	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// pTime?????
	for (i = 0; i<n - 1; ++i)
	{
		if (pTime[i + 1] <= pTime[i])
		{
			return CMD_ERROR_PARAMETER;
		}

		if ((pPercent[i] < 0) || (pPercent[i] > 100))
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	v[0] = velBegin;

	for (i = 0; i<n - 1; ++i)
	{
		pVel[i] = v[0];

		dx = pTime[i + 1] - pTime[i];
		dy = pPos[i + 1] - pPos[i];

		v[1] = 2 * dy / dx - v[0];

		v[0] = v[1];
	}

	pVel[n - 1] = v[0];

	return CMD_SUCCESS;
}

// ????????
short PvtTableContinuousCheck(long n, double *pPos, double *pVel, double *pPercent, double *pVelMax, double *pAcc, double *pDec)
{
	long i;
	double velMax, v1, v2;
	double s;

	i = 0;
	velMax = 0;
	v1 = 0;
	v2 = 0;
	s = 0;

	// 检查段数
	if ((n < 2) || (n > 1024))
	{
		return CMD_ERROR_PARAMETER;
	}

	// 检查加速度、减速度、百分比
	for (i = 0; i<n; ++i)
	{
		// 最大速度
		if (pVelMax[i] <= 0)
		{
			return CMD_ERROR_PARAMETER;
		}

		// 加速度
		if (pAcc[i] <= 0)
		{
			return CMD_ERROR_PARAMETER;
		}

		// 减速度
		if (pDec[i] <= 0)
		{
			return CMD_ERROR_PARAMETER;
		}

		// 百分比
		if ((pPercent[i] < 0) || (pPercent[i] > 100))
		{
			pPercent[i] = 0;
		}
	}

	// 确保各点速度不大于前后段的最大速度
	// 这样可以确保速度分段时形态简单
	if (pVel[0] > pVelMax[0])
	{
		pVel[0] = pVelMax[0];
	}
	else if (pVel[0] < -pVelMax[0])
	{
		pVel[0] = -pVelMax[0];
	}

	for (i = 1; i<n; ++i)
	{
		// 取当前点前后段最小的velMax
		velMax = pVelMax[i];

		if (pVelMax[i - 1] < velMax)
		{
			velMax = pVelMax[i - 1];
		}

		// 当前点速度必须小于前后段的最大速度
		if (pVel[i] > velMax)
		{
			pVel[i] = velMax;
		}
		else if (pVel[i] < -velMax)
		{
			pVel[i] = -velMax;
		}
	}

	// ??????????
	for (i = 0; i<n - 1; ++i)
	{
		s = pPos[i + 1] - pPos[i];
		v1 = pVel[i];
		v2 = pVel[i + 1];

		if ((0 == v1) && (0 == v2))
		{
			if (0 == s)
			{
				return CMD_ERROR_PARAMETER;
			}

			continue;
		}

		if ((v1 >= 0) && (v2 >= 0))
		{
			if (s <= 0)
			{
				return CMD_ERROR_PARAMETER;
			}
		}

		if ((v1 <= 0) && (v2 <= 0))
		{
			if (s >= 0)
			{
				return CMD_ERROR_PARAMETER;
			}
		}
	}

	return CMD_SUCCESS;
}

//-----------------------------------------------------------------------------
// tableId		???
// n			????
// pPos			?????
// pVel			?????
// pPercent		???????????S?????
// pVelMax		???????????????
// pAcc			??????????????
// pDec			??????????????
// timeBegin	?????????
//-----------------------------------------------------------------------------
short CGTDriverCmd::GT_ST_PvtTableContinuous(short tableId, long n, double *pPos, double *pVel, double *pPercent, double *pVelMax, double *pAcc, double *pDec, double timeBegin)
{
	short rtn;
	long i, j, k, count, scount;
	double time[5], pos[5], vel[5];
	double spos[4], svel[4], stime[4];
	double t, a, b, c;

	rtn = 0;
	i = 0;
	j = 0;
	k = 0;
	count = 0;
	scount = 0;
	for (i = 0; i<5; ++i)
	{
		time[i] = 0;
		pos[i] = 0;
		vel[i] = 0;
	}
	for (i = 0; i<4; ++i)
	{
		spos[i] = 0;
		svel[i] = 0;
		stime[i] = 0;
	}
	t = 0;
	a = 0;
	b = 0;
	c = 0;

	rtn = PvtTableContinuousCheck(n, pPos, pVel, pPercent, pVelMax, pAcc, pDec);
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	if (timeBegin < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	// 确保各段终点速度合理
	PvLookahead(n, pPos, pVel, pAcc, pDec);

	// 清空数据表
	InitCmd(PVT_TABLE_CLEAR);
	Add16(tableId);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	t = timeBegin;

	// 速度分段
	for (i = 0; i<n - 1; ++i)
	{
		// 拆分成单调段，最多能够拆出5个节点
		PvSplit(2, t, &pPos[i], &pVel[i], &pVelMax[i], &pAcc[i], &pDec[i], &count, time, pos, vel);

		// 更新节点时间
		t = time[count - 1];

		// 拆分成S曲线
		for (j = 0; j<count - 1; ++j)
		{
			// 根据百分比拆分成S曲线
			PercentSplit(2, &time[j], &pos[j], &vel[j], &pPercent[i], &scount, stime, spos, svel);

			// 计算各段的abc
			for (k = 0; k<scount - 1; ++k)
			{
				// 计算abc
				Hermite(2, &stime[k], &spos[k], &svel[k], &a, &b, &c);

				// 发送数据
				InitCmd(PVT_TABLE_DATA);
				Add16(tableId);
				AddFloat((float)stime[k]);
				AddFloat((float)spos[k]);
				AddFloat((float)a);
				AddFloat((float)b);
				AddFloat((float)c);

				rtn = SendCommand();
				if (CMD_SUCCESS != rtn)
				{
					return rtn;
				}
			}
		}
	}

	// 终点
	InitCmd(PVT_TABLE_DATA);
	Add16(tableId);
	AddFloat((float)time[count - 1]);
	AddFloat((float)pos[count - 1]);
	AddFloat(0);
	AddFloat(0);
	AddFloat(0);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	return CMD_SUCCESS;
}

//-----------------------------------------------------------------------------
// n			????
// pPos			?????
// pVel			?????
// pPercent		???????????S?????
// pVelMax		???????????????
// pAcc			??????????????
// pDec			??????????????
// pTime		????????
//-----------------------------------------------------------------------------
short CGTDriverCmd::GT_ST_PvtContinuousCalculate(long n, double *pPos, double *pVel, double *pPercent, double *pVelMax, double *pAcc, double *pDec, double *pTime)
{
	short rtn;
	long i, count;
	double time[5], pos[5], vel[5];
	double t;

	rtn = 0;
	i = 0;
	count = 0;
	for (i = 0; i<5; ++i)
	{
		time[i] = 0;
		pos[i] = 0;
		vel[i] = 0;
	}
	t = 0;

	rtn = PvtTableContinuousCheck(n, pPos, pVel, pPercent, pVelMax, pAcc, pDec);
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	// 确保各段终点速度合理
	PvLookahead(n, pPos, pVel, pAcc, pDec);

	t = 0;

	// 速度分段
	for (i = 0; i<n - 1; ++i)
	{
		pTime[i] = t;

		// 拆分成单调段，最多能够拆出5个节点
		PvSplit(2, t, &pPos[i], &pVel[i], &pVelMax[i], &pAcc[i], &pDec[i], &count, time, pos, vel);

		// 更新节点时间
		t = time[count - 1];
	}

	pTime[n - 1] = time[count - 1];

	return CMD_SUCCESS;
}
//----------------------------------------------------------
// Follow模式相关函数
//----------------------------------------------------------
short CGTDriverCmd::GT_ST_PrfFollow(short profile, short dir)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(PRF_FOLLOW);
	Add16(profile);
	Add16(dir);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetFollowMaster(short profile, short masterIndex, short masterType, short masterItem)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_MASTER);
	Add16(profile);
	Add16(masterIndex);
	Add16(masterType);
	Add16(masterItem);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowMaster(short profile, short *pMasterIndex, short *pMasterType, short *pMasterItem)
{
	short rtn;
	short masterType, masterItem;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_MASTER);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pMasterIndex);
	Get16(&masterType);
	Get16(&masterItem);

	if (NULL != pMasterType)
	{
		*pMasterType = masterType;
	}

	if (NULL != pMasterItem)
	{
		*pMasterItem = masterItem;
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowLoop(short profile, long loop)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_LOOP);
	Add16(profile);
	Add32(loop);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowLoop(short profile, long *pLoop)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pLoop)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_LOOP);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get32(pLoop);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowEvent(short profile, short event, short masterDir, long pos)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_EVENT);
	Add16(profile);
	Add16(event);
	Add16(masterDir);
	Add32(pos);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowEvent(short profile, short *pEvent, short *pMasterDir, long *pPos)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((NULL == pEvent) || (NULL == pMasterDir))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_EVENT);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pEvent);
	Get16(pMasterDir);

	if (NULL != pPos)
	{
		Get32(pPos);
	}

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_FollowSpace(short profile, short *pSpace, short fifo)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pSpace)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_SPACE);
	Add16(profile);
	Add16(fifo);

	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pSpace);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_FollowData(short profile, long masterSegment, double slaveSegment, short type, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	switch (type)
	{
	case FOLLOW_SEGMENT_NORMAL:
	case FOLLOW_SEGMENT_EVEN:
	case FOLLOW_SEGMENT_STOP:
	case FOLLOW_SEGMENT_CONTINUE:	break;
	default: return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_DATA);
	Add16(profile);
	Add16(fifo);
	Add32(masterSegment);
	Add48F(slaveSegment);
	Add16(type);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowClear(short profile, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_CLEAR);
	Add16(profile);
	Add16(fifo);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowStart(long mask, long option)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_START);
	Add32(mask);
	Add32(option);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_FollowSwitch(long mask)
{
	if (0 == mask)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(FOLLOW_SWITCH);
	Add32(mask);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_SetFollowMemory(short profile, short memory)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != memory) && (1 != memory))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_MEMORY);
	Add16(profile);
	Add16(memory);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowMemory(short profile, short *pMemory)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pMemory)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_MEMORY);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pMemory);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetFollowStatus(short profile, short *pFifoNum, short *pSwitchStatus)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pFifoNum)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (NULL == pSwitchStatus)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_STATUS);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pFifoNum);
	Get16(pSwitchStatus);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_SetFollowPhasing(short profile, short profilePhasing)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((profilePhasing < 0) || (profilePhasing > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_PHASING);
	Add16(profile);
	Add16(profilePhasing);
	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowPhasing(short profile, short *pProfilePhasing)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pProfilePhasing == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_PHASING);
	Add16(profile);
	rtn = SendCommand();
	if (CMD_SUCCESS != rtn)
	{
		return rtn;
	}

	Get16(pProfilePhasing);
	return CMD_SUCCESS;
}
short CGTDriverCmd::GT_ST_SetFollowVirtualSeg(short profile, short segment, short axis, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (segment < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((axis < 1) || (axis > MAX_AXIS))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_VIRTUAL_SEG);
	Add16(profile);
	Add16(fifo);
	Add16(segment);
	Add16(axis);

	return SendCommand();
}

short CGTDriverCmd::GT_ST_GetFollowVirtualSeg(short profile, short *pSegment, short *pAxis, short fifo)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pSegment == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pAxis == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_VIRTUAL_SEG);
	Add16(profile);
	Add16(fifo);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pSegment);
	Get16(pAxis);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetFollowVirtualErr(short profile, double *pVirtualErr)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pVirtualErr == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_VIRTUAL_ERR);
	Add16(profile);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get48F(pVirtualErr);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_ClearFollowVirtualErr(short profile)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(CLEAR_FOLLOW_VIRTUAL_ERR);
	Add16(profile);
	return SendCommand();
}
short CGTDriverCmd::GT_ST_GetFollowRegist(short profile, short *pSegment, short fifo)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pSegment == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_REGIST);
	Add16(profile);
	Add16(fifo);
	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get16(pSegment);

	return CMD_SUCCESS;
}

short CGTDriverCmd::GT_ST_GetFollowRegistCount(short profile, unsigned long *pCount)
{
	short rtn;

	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (pCount == NULL)
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(GET_FOLLOW_REGIST_COUNT);
	Add16(profile);

	rtn = SendCommand();
	if (rtn)
	{
		return rtn;
	}

	Get32((long *)pCount);

	return CMD_SUCCESS;
}
short CGTDriverCmd::GT_ST_SetFollowRegist(short profile, short segment, short fifo)
{
	if ((profile < 1) || (profile > MAX_PROFILE))
	{
		return CMD_ERROR_PARAMETER;
	}

	if (segment < 0)
	{
		return CMD_ERROR_PARAMETER;
	}

	if ((0 != fifo) && (1 != fifo))
	{
		return CMD_ERROR_PARAMETER;
	}

	InitCmd(SET_FOLLOW_REGIST);
	Add16(profile);
	Add16(fifo);
	Add16(segment);

	return SendCommand();
}