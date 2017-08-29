//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	eeprom operate interface		 							//
//	file				:	eepromOpt.cpp												//
//	Description			:	use for operate eeprom 										//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2017/04/01	|	googoltech		|		2017 - 2020			//
//--------------------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "eepromOpt.h"
#include "ST_GTSD_Cmd.h"
#include "BaseReturn_def.h"
#include "ServoDriverComDll.h"
extern CAbsCom* g_AbsCom;
eepromOpt* g_eeprom = NULL;

eepromOpt::eepromOpt()
{

}

eepromOpt::~eepromOpt()
{

}

bool eepromOpt::read(int16 axis, Uint32 addr, int8 *buf, int32 length, int16 com_type, int16 stationId)
{
	if (axis >= COM_AXIS_MAX)
	{
		return Net_Rt_param_Err;
	}
	int16 Axis = axis;													//轴号
	int16 com_addr  = FPGA_EEPROM_STATUS;								// EEPROM STATE
	int16 com_addr1 = FPGA_EEPROM_READ_ADDR;							// EEPROM READ ADDR 
	int16 com_addr2 = FPGA_EEPROM_READ_DAT;								// EEPROM READ DAT
	int16 com_addr3 = FPGA_EEPROM_CTL;									// EEPROM CTL 

	int16 base_addr;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		base_addr = (int16)FPGA_EEPROM_PCDEBUG_BASEADDR;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}
	else
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}

	//计算实际的地址
	int16 comAddr;
	int16 comAddr1;
	int16 comAddr2;
	int16 comAddr3;
	int16 comNum;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		//short地址
		//计算实际的地址
		comAddr  = base_addr + (com_addr >> 1);
		comAddr1 = base_addr + (com_addr1 >> 1);
		comAddr2 = base_addr + (com_addr2 >> 1);
		comAddr3 = base_addr + (com_addr3 >> 1);
		comNum = 1;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		//byte地址
		//计算实际的地址
		comAddr = base_addr + (com_addr);
		comAddr1 = base_addr + (com_addr1);
		comAddr2 = base_addr + (com_addr2);
		comAddr3 = base_addr + (com_addr3);
		comNum = 1;
	}


	int16 rtn;
	int16 readAddr = 0;
	int16 cnt = 0;
	int16 status = 0;
	int16 dat = 0;
	for (int16 i = 0; i < length;++i)
	{
		//----------------------------------------------------------------------------
		//写入读地址
		readAddr = (int16)(addr+i);
		rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr1, &readAddr, comNum, stationId);
		if (rtn != GTSD_COM_SUCCESS)
		{
			return false;
		}
		//----------------------------------------------------------------------------
		//使能读取，写控制寄存器
		int16 ctl = 0x0011;
		rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr3, &ctl, comNum, stationId);
		if (rtn != GTSD_COM_SUCCESS)
		{
			return false;
		}
		//----------------------------------------------------------------------------
		//读取状态寄存器
		cnt = 0;
		status = 0;
		do 
		{
			status = 0;
			rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_READ, comAddr, &status, comNum, stationId);
			if (rtn != GTSD_COM_SUCCESS)
			{
				return false;
			}
			cnt++;
		} while (((status&0x0002)== 0)&&(cnt<20000));
		if (cnt >=20000)
		{
			return false;
		}
		Sleep(15);
		//读取返回的数据,暂时读取两次以上可以读到。后续修改后再更改为读取一次。读取状态也是一样的。
		for (int16 j = 0; j < 3;++j)
		{
			rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_READ, comAddr2, &dat, comNum, stationId);
			if (rtn != GTSD_COM_SUCCESS)
			{
				return false;
			}
		}

		buf[i] = (int8)dat;
		Sleep(5);
	}
	
	return true;
}

bool eepromOpt::write(int16 axis, Uint32 addr, int8 *buf, int32 length, int16 com_type, int16 stationId)
{
	if (axis >= COM_AXIS_MAX)
	{
		return Net_Rt_param_Err;
	}
	int16 Axis = axis;													//轴号
	int16 com_addr = FPGA_EEPROM_STATUS;								// EEPROM STATE
	int16 com_addr1 = FPGA_EEPROM_WRITE_ADDR;							// EEPROM WRITE ADDR 
	int16 com_addr2 = FPGA_EEPROM_WRITE_DAT;							// EEPROM WRITE DAT
	int16 com_addr3 = FPGA_EEPROM_CTL;									// EEPROM CTL 

	int16 base_addr;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		base_addr = (int16)FPGA_EEPROM_PCDEBUG_BASEADDR;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}
	else
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}

	//计算实际的地址
	int16 comAddr;
	int16 comAddr1;
	int16 comAddr2;
	int16 comAddr3;
	int16 comNum;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		//short地址
		//计算实际的地址
		comAddr = base_addr + (com_addr >> 1);
		comAddr1 = base_addr + (com_addr1 >> 1);
		comAddr2 = base_addr + (com_addr2 >> 1);
		comAddr3 = base_addr + (com_addr3 >> 1);
		comNum = 1;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		//byte地址
		//计算实际的地址
		comAddr = base_addr + (com_addr);
		comAddr1 = base_addr + (com_addr1);
		comAddr2 = base_addr + (com_addr2);
		comAddr3 = base_addr + (com_addr3);
		comNum = 1;
	}


	int16 rtn;
	int16 cnt = 0;
	int16 status = 0;
	int16 dat = 0;
	int16 writeAddr;
	for (int16 i = 0; i < length; ++i)
	{
		//----------------------------------------------------------------------------
		//写入写地址
		writeAddr = (int16)(addr + i);
		rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr1, &writeAddr, comNum, stationId);
		if (rtn != GTSD_COM_SUCCESS)
		{
			return false;
		}
		//----------------------------------------------------------------------------
		//写入数据
		dat = buf[i];
		rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr2, &dat, comNum, stationId);
		if (rtn != GTSD_COM_SUCCESS)
		{
			return false;
		}
		//----------------------------------------------------------------------------
		//使能写入，写控制寄存器
		int16 ctl = 0x0010;
		rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr3, &ctl, comNum, stationId);
		if (rtn != GTSD_COM_SUCCESS)
		{
			return false;
		}
		//----------------------------------------------------------------------------
		//读取状态寄存器
		cnt = 0;
		status = 0;
		do
		{
			status = 0;
			rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_READ, comAddr, &status, comNum, stationId);
			if (rtn != GTSD_COM_SUCCESS)
			{
				return false;
			}
			cnt++;
		} while (((status & 0x0002) == 0) && (cnt < 20000));
		if (cnt >= 20000)
		{
			return false;
		}
		Sleep(5);
	}

	return true;
}

bool eepromOpt::erase(int16 axis, int16 com_type, int16 stationId)
{
	int16 com_addr = FPGA_EEPROM_CTL;									// EEPROM CTL 

	int16 base_addr;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		base_addr = (int16)FPGA_EEPROM_PCDEBUG_BASEADDR;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}
	else
	{
		base_addr = (int16)FPGA_EEPROM_RNNET_BASEADDR;
	}

	//计算实际的地址
	int16 comAddr;
	int16 comNum;

	if (com_type == GTSD_COM_TYPE_NET)
	{
		//short地址
		//计算实际的地址
		comAddr = base_addr + (com_addr >> 1);
		comNum = 1;
	}
	else if (com_type == GTSD_COM_TYPE_RNNET)
	{
		//byte地址
		//计算实际的地址
		comAddr = base_addr + (com_addr);
		comNum = 1;
	}
	int16 rtn;

	//----------------------------------------------------------------------------
	//写入控制地址
	int16 ctl = 0x0030;
	
	rtn = g_AbsCom->GTSD_Com_Firmware_handler(com_type, GTSD_COM_MODE_WRITE, comAddr, &ctl, comNum, stationId);
	if (rtn != GTSD_COM_SUCCESS)
	{
		return false;
	}

	return  true;
}
