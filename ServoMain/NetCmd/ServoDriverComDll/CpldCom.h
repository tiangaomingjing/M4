#pragma once
#include "ComBase.h"
#include "GTCmdCtrl.h"
#include "GTDriverCmd.h"
class CCpldCom :
	public CComBase
{

public:
	CCpldCom();
	~CCpldCom();


public:
	//µÈ»·ÍøÆ«ÒÆµØÖ·
	static const Uint16		RN_REMOTE_FPGA_CTL = (0x7F * 2);
	static const Uint16		RN_REMOTE_FPGA_DATA_START = (0x00);
	static const Uint16		RN_REMOTE_FPGA_DATA_END = (0x7C * 2);

	static const Uint16		FPGA_RN_RMT_START_OFST = 0x600;
	static const Uint16		FPGA_RN_RMT_END_OFST = 0x6FF;

	//cpld addresss
	static const short		CPLD_UPDATE_SET_ADDR = 0xD0;
	static const short		CPLD_UPDATE_DATA_DIN = 0xD2;
	static const short		CPLD_UPDATE_CTRL = 0xD4;

public:



protected:
	CGTDriverCmd* m_pDriver;
	short SendCommand(void);
public:
	short Initial(CGTDriverCmd* pDriver);
	virtual short ComWrFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam);
	virtual short ComRdFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam);

protected:
	short RemoteUpdateWr(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id);
	short RemoteUpdateRd(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id);

};

