#pragma once
#include "StFileOp.h"

//#define CFileServer_OFFLINE

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

class SERVODRIVERCOMDLL_API CFileServer
{
public:
	CFileServer();
	~CFileServer();
private:
	void* m_com_driver;
	StFileOp m_server_rx_file;//tmp file
public:
	short m_Thread_sleep_time;
public:
	short Initial(void* pDriver);
	short RingNetFuctionDriver(LPVOID lp, StFunction* param, unsigned char station_id, BOOL resp_req = TRUE);

	short RingNetWrFloder(LPCTSTR src_file, LPCTSTR des_file, unsigned char station_id, 
		void(*tpfUpdataProgressPt)(void*, short*) = NULL, void* ptrv = NULL);
	short RingNetWrFile(LPCTSTR src_file, DWORD src_dwCreationDisposition,
		LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id, 
		void(*tpfUpdataProgressPt)(void*, short*) = NULL, void* ptrv = NULL);
	short RingNetReadFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id);
	inline short RingNetCtrlCfg(LPVOID lp, short* thread_sleep_time, unsigned char station_id)
	{
		return RN_FileOpCtrlCfg(lp, thread_sleep_time, station_id);
	}
public:
	//////////////////////////////////////////////////////////////////////////
	static short FileOpCreate(StFileOp* pFileOp);
	static short FileOpDelete(StFileOp* pFileOp);
	static short FileOpFileOpen(StFileOp* pFileOp, LPCTSTR m_pathName, DWORD dwCreationDisposition = CREATE_ALWAYS);
	static short FileOpFileClose(StFileOp* pFileOp);
	static short FileOpFileWrite(StFileOp* pFileOp, short *len, void* pData);
	static short FileOpFileRead(StFileOp* pFileOp, short *len, void* pData);
	static short FileOpFileCheckExsits(StFileOp* pFileOp, LPCTSTR file_name);
	static short FileOpFileDelete(StFileOp* pFileOp, LPCTSTR file_name);

	static short FileOpDirctoryCheck(LPCTSTR m_pathName);
	static short FileOpDirctoryCreate(StFileOp* pFileOp, LPCTSTR m_pathName);
	static short FileOpDirctoryDelete(StFileOp* pFileOp, LPCTSTR m_pathName);

	static short CRC16_Calc(unsigned char* pchMsg, short wDataLen, unsigned char& chCRCHi, unsigned char &chCRCLo);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	short StFnProcess(LPVOID lp, unsigned short data_size_in, void* pData, unsigned short* data_size_out);
protected:
	short Fn_Real_FileOpFileOpen(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpFileClose(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpFileWrite(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpFileRead(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpFileCheckExsits(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpFileDelete(LPVOID lp, StFunction* param, char* pData);

	short Fn_Real_FileOpDirctoryCreate(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpDirctoryDelete(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpGetCrcResult(LPVOID lp, StFunction* param, char* pData);
	short Fn_Real_FileOpCtrlCfg(LPVOID lp, StFunction* param, char* pData);
	//////////////////////////////////////////////////////////////////////////
	short RN_FileOpFileOpen(LPVOID lp, LPCTSTR m_pathName, DWORD dwCreationDisposition, unsigned char station_id, BOOL resp_req = 1);
	short RN_FileOpFileClose(LPVOID lp, unsigned char station_id, BOOL resp_req = 1);
	short RN_FileOpFileWrite(LPVOID lp, short *len, void* pData, unsigned char station_id, BOOL resp_req = 1);
	short RN_FileOpFileRead(LPVOID lp, short *len, void* pData, unsigned char station_id);
	short RN_FileOpFileCheckExsits(LPVOID lp, LPCTSTR file_name, unsigned char station_id);
	short RN_FileOpFileDelete(LPVOID lp, LPCTSTR file_name, unsigned char station_id, BOOL resp_req = 1);

	short RN_FileOpDirctoryCreate(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req = 1);
	short RN_FileOpDirctoryDelete(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req = 1);
	short RN_FileOpGetCrcResult(LPVOID lp, short* crc_result, unsigned char station_id);
	short RN_FileOpCtrlCfg(LPVOID lp, short* thread_sleep_time, unsigned char station_id);
	//////////////////////////////////////////////////////////////////////////

	short RN_WriteFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id);
	short RN_WriteDirctory(LPVOID lp, LPCTSTR src_file, LPCTSTR des_file, unsigned char station_id);
	short RN_ReadFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id);

};

