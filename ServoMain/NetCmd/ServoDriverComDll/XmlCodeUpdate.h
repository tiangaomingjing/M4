#pragma once
#include "XmlCode.h"
#include "FPGAUpdate.h"

class CXmlCodeUpdate :
	public CXmlCode, public CFPGAUpdate
{
public:
	CXmlCodeUpdate();
	~CXmlCodeUpdate();
public:
	virtual short WriteFile(char* pFileNameList[], int pFileTypeList[], int file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

	virtual short ReadFile(char* pFileNameList[], int pFileTypeList[], int& file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

protected:
	virtual short CXmlCodeUpdate::EraseXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CXmlCodeUpdate::CheckXmlFlashValid(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CXmlCodeUpdate::ProgramXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CXmlCodeUpdate::ReadXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CXmlCodeUpdate::WriteFlashData(Uint32 flash_addr, void *Sendbuf, uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	virtual short CXmlCodeUpdate::ReadFlashData(Uint32 flash_addr, void *Sendbuf, uint32 byte_num, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	
	virtual short CXmlCodeUpdate::CheckXmlFlash(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);

protected:
	int m_EncodeNumMax;
#define XML_START_SECTOR_ID  (64)
#define XML_HEAD_SIZE (32)
#define	XML_START_FLAG	"XML_PROGRAM_FLAG"
#define XML_START_FLAG_SIZE 16
#define XML_VERSION		"V00000000000000"
#define XML_VERSION_SIZE 16



};

