#pragma once
#pragma once
#include <string>

#include "StString.h"


#define GOOGOL_PRINF_EN_OFF

#ifdef GOOGOL_PRINF_EN_OFF
#define GOOGOL_PRINF_EN 0
#else
#define GOOGOL_PRINF_EN 1
#endif

#define MAX_FIFE_BUFFER_SIZE 2000000

#define FN_PARAM_TYPE 0
#define FN_FILEOP_TYPE 1

#define FN_FileOpFileOpen			100
#define FN_FileOpFileClose			101
#define FN_FileOpFileWrite			102
#define FN_FileOpFileRead			103
#define FN_FileOpFileCheckExsits	104
#define FN_FileOpFileDelete			105

#define FN_FileOpDirctoryCreate		106
#define FN_FileOpDirctoryDelete		107
#define FN_FileOpGetCrcResult		108

#define FN_FileOpCtrlCfg			200


typedef struct
{
	unsigned short m_id;
	unsigned short m_rtn;
	unsigned short m_param_num;
	unsigned short m_len;
	unsigned char* m_pData;
}StFunction;

// typedef struct  
// {
// 	Uint16 m_num;
// 	Uint8* pData; 
// }StFnAllParam;
// 
typedef struct
{
	unsigned short m_size;
	char* m_pData;
}StFnSubParam;

/////////////////////////////////////////////////////////////////////

// typedef struct
// {
// 	StString m_pathName;
// 	StString m_fileName;
// 	//////////////////////////////////////////////////////////////////////////
// 	HANDLE m_file;
// 	//	CFile m_file;
// 	//	FILE* m_pFile;
// 	BOOL  m_file_status;
// 	DWORD m_file_size;
// 	unsigned char  m_crc_high;//crc16_h;
// 	unsigned char  m_crc_low;//crc16_l;
// 	char* m_pBuffer;
// 	unsigned int m_buffer_cnt;
// }StFileOp;

class CLPBYTEList
{
public:
	StFnSubParam* m_list;
	char*	m_pData;
	unsigned short m_use_len;
	unsigned short m_param_num;
public:
	CLPBYTEList()
	{
		m_list = NULL;
		m_pData = NULL;
		m_param_num = 0;
		m_use_len = 0;
	};
	short CGetList(StFunction* param, char* pData)
	{
		m_use_len = 0;
		if (m_list) delete[] m_list;
		if (param == NULL)
		{
			m_list = NULL;
			return 0;
		}
		if (param->m_param_num == 0)
		{
			m_list = NULL;
			return 0;
		}
		if (pData == NULL)
		{
			m_list = NULL;
			return 0;
		}
		//		printf(("m_list = new StFnSubParam[param->m_param_num] !\n"));
		m_list = new StFnSubParam[param->m_param_num];

		m_list[0].m_size = *((unsigned short*)pData);
		m_list[0].m_pData = pData + sizeof(unsigned short);
		m_use_len = m_use_len + sizeof(unsigned short)+m_list[0].m_size;

		m_param_num = param->m_param_num;
		m_pData = pData;

		for (int i = 1; i < param->m_param_num; i++)
		{
			m_list[i].m_size = *((unsigned short*)(m_list[i - 1].m_pData + m_list[i - 1].m_size));
			m_list[i].m_pData = (m_list[i - 1].m_pData + m_list[i - 1].m_size + sizeof(unsigned short));
			m_use_len = m_use_len + sizeof(unsigned short)+m_list[i].m_size;
		}
		return 0;
	};
	short CClearPData(char* pData)
	{
		m_pData = pData;
		m_use_len = 0;
		m_param_num = 0;
		return 0;
	}
	short CAddParam(unsigned short len, char* pData)
	{
		m_param_num++;
		m_use_len += sizeof(unsigned short);
		*((unsigned short*)m_pData) = len;
		m_pData = m_pData + 2;

		m_use_len += len;
		memcpy(m_pData, pData, len);
		m_pData = m_pData + len;
		return 0;
	}
	short CSetStFunction(StFunction* param)
	{
		param->m_len = m_use_len;
		param->m_param_num = m_param_num;
		return 0;
	};
	virtual ~CLPBYTEList(){ if (m_list) delete[]m_list; };
};

class SERVODRIVERCOMDLL_API StFileOp
{
public:
	StFileOp()
	{
		FileOpCreate(this);
	}
	~StFileOp()
	{
		FileOpDelete(this);
	}
	StString m_pathName;
	StString m_fileName;
	//////////////////////////////////////////////////////////////////////////
	HANDLE m_file;
	//	CFile m_file;
	//	FILE* m_pFile;
	BOOL  m_file_status;
	DWORD m_file_size;
	unsigned char  m_crc_high;//crc16_h;
	unsigned char  m_crc_low;//crc16_l;
	char* m_pBuffer;
	unsigned int m_buffer_cnt;
// 	//////////////////////////////////////////////////////////////////////////
// 	//static int m_com_driver;
	//////////////////////////////////////////////////////////////////////////
	short FileOpCreate(StFileOp* pFileOp);
	short FileOpDelete(StFileOp* pFileOp);
// 	static short FileOpFileOpen(StFileOp* pFileOp, LPCTSTR m_pathName, DWORD dwCreationDisposition = CREATE_ALWAYS);
 	short FileOpFileClose(StFileOp* pFileOp);
// 	static short FileOpFileWrite(StFileOp* pFileOp, short *len, void* pData);
// 	static short FileOpFileRead(StFileOp* pFileOp, short *len, void* pData);
// 	static short FileOpFileCheckExsits(StFileOp* pFileOp, LPCTSTR file_name);
// 	static short FileOpFileDelete(StFileOp* pFileOp, LPCTSTR file_name);
// 
// 	static short FileOpDirctoryCheck(LPCTSTR m_pathName);
// 	static short FileOpDirctoryCreate(StFileOp* pFileOp, LPCTSTR m_pathName);
// 	static short FileOpDirctoryDelete(StFileOp* pFileOp, LPCTSTR m_pathName);
// 
// 	static short CRC16_Calc(unsigned char* pchMsg, short wDataLen, unsigned char& chCRCHi, unsigned char &chCRCLo);
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	//////////////////////////////////////////////////////////////////////////
// 	static short StFnProcess(LPVOID lp, unsigned short data_size_in, void* pData, unsigned short* data_size_out);
// 
// 	static short Fn_Real_FileOpFileOpen(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpFileClose(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpFileWrite(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpFileRead(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpFileCheckExsits(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpFileDelete(LPVOID lp, StFunction* param, char* pData);
// 
// 	static short Fn_Real_FileOpDirctoryCreate(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpDirctoryDelete(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpGetCrcResult(LPVOID lp, StFunction* param, char* pData);
// 	static short Fn_Real_FileOpCtrlCfg(LPVOID lp, StFunction* param, char* pData);
// 	//////////////////////////////////////////////////////////////////////////
// 	static short RingNetFuctionDriver(LPVOID lp, StFunction* param, unsigned char station_id, BOOL resp_req = 1);
// 	//////////////////////////////////////////////////////////////////////////
// 	static short RN_FileOpFileOpen(LPVOID lp, LPCTSTR m_pathName, DWORD dwCreationDisposition, unsigned char station_id, BOOL resp_req = 1);
// 	static short RN_FileOpFileClose(LPVOID lp, unsigned char station_id, BOOL resp_req = 1);
// 	static short RN_FileOpFileWrite(LPVOID lp, short *len, void* pData, unsigned char station_id, BOOL resp_req = 1);
// 	static short RN_FileOpFileRead(LPVOID lp, short *len, void* pData, unsigned char station_id);
// 	static short RN_FileOpFileCheckExsits(LPVOID lp, LPCTSTR file_name, unsigned char station_id);
// 	static short RN_FileOpFileDelete(LPVOID lp, LPCTSTR file_name, unsigned char station_id, BOOL resp_req = 1);
// 
// 	static short RN_FileOpDirctoryCreate(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req = 1);
// 	static short RN_FileOpDirctoryDelete(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req = 1);
// 	static short RN_FileOpGetCrcResult(LPVOID lp, short* crc_result, unsigned char station_id);
// 	static short RN_FileOpCtrlCfg(LPVOID lp, short* thread_sleep_time, unsigned char station_id);
// 	static short RN_WriteFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id);
// 	static short RN_WriteDirctory(LPVOID lp, LPCTSTR src_file, LPCTSTR des_file, unsigned char station_id);
// 	static short RN_ReadFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id);

};

