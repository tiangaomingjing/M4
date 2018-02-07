#pragma once
#include "Basetype_def.h"
#include "ComBase.h"

/*
Head support epcs4/epcs16/epcs64/ only
*/
class CFPGAUpdate
{
public:
	CFPGAUpdate();
	~CFPGAUpdate();

public:
	static const int32		BUF_LEN = 200;
	static const int32		FF_LEN = 200;
	static const int16		DELAY_TIMES = 100;

	static const int32		CMD_READ = 0;
	static const int32		CMD_WRITE = 1;
	static const int32		CMD_PRET_ON = 2;
	static const int32		CMD_PRET_OFF = 3;
	static const int32		CMD_ERASE = 4;
	static const int32		CMD_SECTOR_ERASE = 5;

	static const int32		SECTOR_SIZE = 1 << 16;// 2 ^ 16;// 64Kbyte
	static const int16		MAX_OP_WORD_NUM = 120;

	//pcdebug偏移地址，基地址是0
	static const Uint16		REMOTE_FPGA_CTL = 0x37F;
	static const Uint16		REMOTE_FPGA_DATA_START = 0x300;
	static const Uint16		REMOTE_FPGA_DATA_END = 0x37C;

	//等环网偏移地址
	static const Uint16		RN_REMOTE_FPGA_CTL = (0x7F * 2);
	static const Uint16		RN_REMOTE_FPGA_DATA_START = (0x00);
	static const Uint16		RN_REMOTE_FPGA_DATA_END = (0x7C * 2);

	uint32 m_byte_write;
public:
	// pcdebug 地址为dsp与fpga之间通信的fpga地址，不同的dsp对应不同的fpga地址。
	static const Uint16						DSPA_COMADDR = 0x0400;				 //地址为short地址
	static const Uint16						DSPB_COMADDR = 0x8400;

	static const Uint16						FPGA_DSPA_BASEADDR = 0;
	static const Uint16						FPGA_DSPB_BASEADDR = 0x8000;				//short地址

	static const Uint16						FPGA_RN_RMT_START_OFST = 0x600;
	static const Uint16						FPGA_RN_RMT_END_OFST = 0x6FF;


	CComBase**		m_pCom;
	Uint16			m_des_id;
protected:
	int16 SetRemoteUpdataStartbit();
	int16 CheckRemoteUpdataState(int32 delaytimes = DELAY_TIMES);
	int16 SetRemoteUpdataReadRequest(Uint32 flash_addr, Uint16 iLength);
	int16 ProtectOff();
	int16 ProtectOn();
	int16 EraseData(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	int16 EraseFPGAData(uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	int16 GetFPGAByteNum(char* pFileName, uint32& byte_num);
	int16 EraseSectorData(uint32 byte_address, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	int16 GetFpgaFlashData(Uint32 flash_addr, int16 *Getbuf, Uint16 iLength);
	int16 SendFpgaFlashData(Uint32 flash_addr, int16 *Sendbuf, Uint16 iLength);
	int32 CheckFFNumber(short* buffer, int lenth);
public:
	int16 WriteFPGAFileToFlash(char* pFileName, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	int16 ReadFPGADataToFile(char* FileName, Uint32 Bytelenth);

};

