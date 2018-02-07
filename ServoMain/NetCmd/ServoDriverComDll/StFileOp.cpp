#include "stdafx.h"
#include "StFileOp.h"

#include "BaseReturn_def.h"
#include "StFileOp.h"
#include "PcCtrlCom.h"

// #include "rn_type.h"
// #include "rn_st.h"
// #include "StRingNet.h"
// #include "StShowMessage.h"

short StFileOp::FileOpCreate(StFileOp* pFileOp)
{
	pFileOp->m_file_status = NULL;
	pFileOp->m_file = NULL;
	pFileOp->m_crc_high = 0xFF;
	pFileOp->m_crc_low = 0xFF;

	pFileOp->m_pBuffer = NULL;
	pFileOp->m_buffer_cnt = 0;
	return RTN_SUCCESS;
}
short StFileOp::FileOpDelete(StFileOp* pFileOp)
{
	if (pFileOp->m_file_status)
	{
		FileOpFileClose(pFileOp);
	}
	pFileOp->m_file_status = NULL;

	if (pFileOp->m_pBuffer) delete[]pFileOp->m_pBuffer;

	pFileOp->m_pBuffer = NULL;
	pFileOp->m_buffer_cnt = 0;

	return RTN_SUCCESS;
}
// short StFileOp::FileOpFileOpen(StFileOp* pFileOp, LPCTSTR file_name, DWORD dwCreationDisposition)
// {
// 	// 	short rtn;
// 	if (pFileOp->m_file_status)
// 	{
// 		FileOpFileClose(pFileOp);
// 	}
// 	StString str;
// 	if (pFileOp->m_pathName.GetStStringLen()) str = pFileOp->m_pathName + L"\\";
// 	str += file_name;
// 	// 
// 	pFileOp->m_crc_high = 0xFF;
// 	pFileOp->m_crc_low = 0xFF;
// 	pFileOp->m_file = CreateFile(str.GetLPCSTR(),//_T(“//My Documents//MYFILE.TXT”),
// 		GENERIC_READ | GENERIC_WRITE,
// 		FILE_SHARE_READ,
// 		NULL,
// 		dwCreationDisposition,//OPEN_ALWAYS ,
// 		FILE_ATTRIBUTE_NORMAL,
// 		NULL);
// 
// 	if (pFileOp->m_file == INVALID_HANDLE_VALUE)//create fail
// 	{
// //		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("FileOpFileOpen %s Err! \n"), file_name));
// 		return RTN_FILE_CREATE_FAIL;
// 	}
// 	// 
// 	// 	HANDLE CreateFile(str.GetLPCSTR(),
// 	// 		LPCTSTR lpFileName,
// 	// 		DWORD dwDesireAccess,
// 	// 		DWORD dwShareMode,
// 	// 		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
// 	// 		DWORD dwCreationDispostion,
// 	// 		DWORD dwFlagsAndAttributes,
// 	// 		HANDLE hTemplateFile);
// 
// 	// 	string str;
// 	// 	str = pFileOp->m_pathName;
// 	// 	str +="\\";
// 	// 	str +=file_name;
// 	// 	函数原型：FILE * fopen(const char * path,const char * mode);
// 	// 
// 	// 		if((fin = fopen("a.txt","r")) == NULL)
// 	// 			if(GOOGOL_PRINF_EN) printf("Open file error.\n");
// 	//	pFileOp->m_pFile = fopen(str.GetLPCSTR(),"r");
// 	// 	if (pFileOp->m_pFile == NULL)
// 	// 	{
// 	// 		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_,(TEXT("FileOpFileOpen %s Err! \n"), file_name));
// 	// 		return RTN_MALLOC_FAIL;
// 	// 	}
// 
// 	// 	if (!pFileOp->m_file.Open(str.GetLPCSTR(),CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone|CFile::modeNoTruncate))//create fail
// 	// 	{
// 	// 		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_,(TEXT("FileOpFileOpen %s Err! \n"), file_name));
// 	// 		return RTN_MALLOC_FAIL;
// 	// 	}
// 
// 	pFileOp->m_file_size = GetFileSize(pFileOp->m_file, NULL);
// 	//	pFileOp->m_file.SeekToBegin();//将指针移到文件末尾
// 	SetFilePointer(pFileOp->m_file, 0, NULL, FILE_BEGIN);
// 	pFileOp->m_buffer_cnt = 0;
// 
// 	// 	DWORD SetFilePointer(
// 	// 		HANDLE hFile,
// 	// 		LONG lDistanceToMove,
// 	// 		PLONG lpDistanceToMoveHigh,
// 	// 		DWORD dwMoveMethod);
// 	pFileOp->m_file_status = TRUE;
// 	return RTN_SUCCESS;
// }
short StFileOp::FileOpFileClose(StFileOp* pFileOp)
{
	BOOL write_ok = TRUE;
	if (pFileOp->m_file_status)
	{
		if (pFileOp->m_buffer_cnt && pFileOp->m_pBuffer)
		{
			DWORD write_num;
			SetFilePointer(pFileOp->m_file, 0, NULL, FILE_END);
			WriteFile(pFileOp->m_file, pFileOp->m_pBuffer, pFileOp->m_buffer_cnt, &write_num, NULL);
			write_ok = pFileOp->m_buffer_cnt == write_num;
			pFileOp->m_buffer_cnt = 0;

		}

		//		pFileOp->m_file.Close();
		CloseHandle(pFileOp->m_file);
		//BOOL CloseHandle(HANDLE hObject);
	}
	pFileOp->m_file_status = NULL;

	if (write_ok == FALSE)
		return RTN_FILE_MALLOC_FAIL;

	return RTN_SUCCESS;
}
// short StFileOp::FileOpFileWrite(StFileOp* pFileOp, short *len, void* pData)
// {
// 	if (pFileOp->m_file_status == NULL) return RTN_FILE_MALLOC_FAIL;
// 	//	pFileOp->m_file.SeekToEnd();//将指针移到文件末尾
// 	//	pFileOp->m_file.Write(pData,len);
// 	if (pFileOp->m_pBuffer)
// 	{
// 		memcpy(pFileOp->m_pBuffer + pFileOp->m_buffer_cnt, pData, *len);
// 		pFileOp->m_buffer_cnt += (*len);
// 		if (pFileOp->m_buffer_cnt + 480 > MAX_FIFE_BUFFER_SIZE)
// 		{
// 			DWORD write_num;
// 			SetFilePointer(pFileOp->m_file, 0, NULL, FILE_END);
// 			WriteFile(pFileOp->m_file, pFileOp->m_pBuffer, pFileOp->m_buffer_cnt, &write_num, NULL);
// 			if (write_num != pFileOp->m_buffer_cnt)
// 				return RTN_FILE_MALLOC_FAIL;
// 
// 			pFileOp->m_buffer_cnt = 0;
// 		}
// 		//	WriteFile(pFileOp->m_file, pData, *len, &write_num, NULL);
// 	}
// 	CRC16_Calc((unsigned char*)pData, *len, pFileOp->m_crc_high, pFileOp->m_crc_low);
// 
// 
// 	//	*len = (short)write_num;
// 
// 	// 	BOOL WriteFile(
// 	// 		HANDLE hFile,
// 	// 		LPCVOID lpBuffer,
// 	// 		DWORD nNumberOfBytesWritten,
// 	// 		NULL);
// 	return RTN_SUCCESS;
// }
// short StFileOp::FileOpFileRead(StFileOp* pFileOp, short* len, void* pData)
// {
// 	if (pFileOp->m_file_status == NULL) return RTN_FILE_MALLOC_FAIL;
// 	// 	BOOL ReadFile(
// 	// 		HANDLE hFile,
// 	// 		LPVOID lpBuffer,
// 	// 		DWORD nNumberOfBytesToRead,
// 	// 		LPDWORD lpNumberOfBytesRead,
// 	// 		NULL);
// 	DWORD readlen;
// 	ReadFile(pFileOp->m_file, pData, *len, &readlen, NULL);
// 	*len = (short)readlen;
// 	CRC16_Calc((unsigned char*)pData, *len, pFileOp->m_crc_high, pFileOp->m_crc_low);
// 	//	short rtn = pFileOp->m_file.Read(pData,*len);
// 	//	*len = rtn;
// 	return RTN_SUCCESS;
// }
// 
// 
// short StFileOp::FileOpFileCheckExsits(StFileOp* pFileOp, LPCTSTR file_name)
// {
// 
// 	// 	CString str;
// 	// 	str = pFileOp->m_pathName;
// 	// 	str +="\\";
// 	// 	str +=file_name;
// 	// 	CStLpStr str;
// 	// 	if(pFileOp->m_pathName.GetLPCSTR()) str.LpStrAdd(pFileOp->m_pathName.GetLPCSTR(), L"\\");
// 	// 	str.LpStrAdd(str.GetLPCSTR(), file_name);
// 	StString str;
// 	if (pFileOp->m_pathName.GetStStringLen()) str = pFileOp->m_pathName + L"\\";
// 	str += file_name;
// 	if (::GetFileAttributes(str.GetLPCSTR()) != 0xFFFFFFFF)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return RTN_FILE_NOT_EXSITS;
// 	}
// }
// short StFileOp::FileOpFileDelete(StFileOp* pFileOp, LPCTSTR file_name)
// {
// 	short rtn;
// 	// 	CString str;
// 	// 	str = pFileOp->m_pathName;
// 	// 	str +="\\";
// 	// 	str +=file_name;
// 	StString str;
// 	if (pFileOp->m_pathName.GetStStringLen()) str = pFileOp->m_pathName + L"\\";
// 	str += file_name;
// 	if (pFileOp->m_file_status)
// 	{
// 		rtn = FileOpFileClose(pFileOp);
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			return rtn;
// 		}
// 	}
// 	if (!DeleteFile(str.GetLPCSTR()))
// 	{
// 		return RTN_FILE_DELETE_FAIL;
// 	}
// 	return RTN_SUCCESS;
// }
// 
// short StFileOp::FileOpDirctoryCheck(LPCTSTR m_pathName)
// {
// 	WIN32_FIND_DATA fd;
// 	HANDLE hdFind = FindFirstFile(m_pathName, &fd);
// 	if (hdFind != INVALID_HANDLE_VALUE)
// 	{
// 		if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
// 		{
// 			FindClose(hdFind);
// 			return RTN_SUCCESS;
// 		}
// 	}
// 	FindClose(hdFind);
// 	return RTN_FILE_NOT_EXSITS;
// }
// short StFileOp::FileOpDirctoryCreate(StFileOp* pFileOp, LPCTSTR m_pathName)
// {
// 	pFileOp->m_pathName.SetStSting(m_pathName);
// 	if (FileOpDirctoryCheck(pFileOp->m_pathName.GetLPCSTR()) == RTN_SUCCESS)
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	if (CreateDirectory(pFileOp->m_pathName.GetLPCSTR(), NULL))
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return RTN_FILE_CREATE_FAIL;
// 	}
// }
// 
// short StFileOp::FileOpDirctoryDelete(StFileOp* pFileOp, LPCTSTR m_pathName)
// {
// 	if (RemoveDirectory(m_pathName))
// 	{
// 		return RTN_SUCCESS;
// 	}
// 	else
// 	{
// 		return RTN_FILE_DELETE_FAIL;
// 	}
// }
// //////////////////////////////////////////////////////////////////////////
// // ---------------- POPULAR POLYNOMIALS ----------------
// // CCITT:      x^16 + x^12 + x^5 + x^0                 (0x1021)
// // CRC-16:     x^16 + x^15 + x^2 + x^0                 (0x8005)
// //#define         CRC_16_POLYNOMIALS      0x8005
// const unsigned char chCRCHTalbe[] =                                 // CRC 高位字节值表
// {
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
// 	0x00, 0xC1, 0x81, 0x40
// };
// const unsigned char chCRCLTalbe[] =                                 // CRC 低位字节值表
// {
// 	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
// 	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
// 	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
// 	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
// 	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
// 	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
// 	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
// 	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
// 	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
// 	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
// 	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
// 	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
// 	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
// 	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
// 	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
// 	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
// 	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
// 	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
// 	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
// 	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
// 	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
// 	0x41, 0x81, 0x80, 0x40
// };
// 
// short StFileOp::CRC16_Calc(unsigned char* pchMsg, short wDataLen, unsigned char& chCRCHi, unsigned char &chCRCLo)
// {
// 	// 	char chCRCHi = 0xFF; // 高CRC字节初始化
// 	// 	char chCRCLo = 0xFF; // 低CRC字节初始化
// 	short wIndex;            // CRC循环中的索引
// 	while (wDataLen--)
// 	{
// 		// 计算CRC
// 		wIndex = chCRCLo ^ *pchMsg++;
// 		chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex];
// 		chCRCHi = chCRCLTalbe[wIndex];
// 	}
// 	return ((chCRCHi << 8) | chCRCLo);
// }
// //////////////////////////////////////////////////////////////////////////
// short StFileOp::StFnProcess(LPVOID lp, Uint16 data_size_in, void* pData, Uint16* data_size_out)
// {
// 	short rtn;
// 	char* m_pData = (char*)pData;
// 	if (data_size_in < sizeof(unsigned short)* 4)
// 	{
// 		return RTN_FILE_PARAM_ERR;
// 	}
// 	StFunction* pFn = (StFunction*)m_pData;
// 	m_pData = m_pData + sizeof(unsigned short)* 4;//sizeof(StFunction);
// 
// 	switch (pFn->m_id)
// 	{
// 	case FN_FileOpDirctoryCreate:
// 	{
// 									rtn = Fn_Real_FileOpDirctoryCreate(lp, pFn, m_pData);
// 									break;
// 	}
// 	case FN_FileOpDirctoryDelete:
// 	{
// 									rtn = Fn_Real_FileOpDirctoryDelete(lp, pFn, m_pData);
// 									break;
// 	}
// 	case FN_FileOpFileOpen:
// 	{
// 							  rtn = Fn_Real_FileOpFileOpen(lp, pFn, m_pData);
// 							  break;
// 	}
// 	case FN_FileOpFileClose:
// 	{
// 							   rtn = Fn_Real_FileOpFileClose(lp, pFn, m_pData);
// 							   break;
// 	}
// 	case FN_FileOpFileWrite:
// 	{
// 							   rtn = Fn_Real_FileOpFileWrite(lp, pFn, m_pData);
// 							   break;
// 	}
// 	case FN_FileOpFileRead:
// 	{
// 							  rtn = Fn_Real_FileOpFileRead(lp, pFn, m_pData);
// 							  break;
// 	}
// 	case FN_FileOpFileCheckExsits:
// 	{
// 									 rtn = Fn_Real_FileOpFileCheckExsits(lp, pFn, m_pData);
// 									 break;
// 	}
// 	case FN_FileOpFileDelete:
// 	{
// 								rtn = Fn_Real_FileOpFileDelete(lp, pFn, m_pData);
// 								break;
// 	}
// 	case FN_FileOpGetCrcResult:
// 	{
// 								  rtn = Fn_Real_FileOpGetCrcResult(lp, pFn, m_pData);
// 								  break;
// 	}
// 	case FN_FileOpCtrlCfg:
// 	{
// 							 rtn = Fn_Real_FileOpCtrlCfg(lp, pFn, m_pData);
// 							 break;
// 
// 	}
// 	default:
// 	{
// 			   rtn = RTN_PARAM_ERR;
// 			   break;
// 	}
// 	}
// 	*data_size_out = pFn->m_len + sizeof(unsigned short)* 4;
// 	return rtn;
// }
// 
// short StFileOp::Fn_Real_FileOpFileOpen(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 2)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	LPCTSTR m_pathName = (LPCTSTR)(param_list.m_list[0].m_pData);
// 	DWORD dwCreationDisposition = *((DWORD*)param_list.m_list[1].m_pData);
// 	param->m_rtn = FileOpFileOpen(&pRingNet->m_file, m_pathName, dwCreationDisposition);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpFileClose(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 0)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	param->m_rtn = FileOpFileClose(&pRingNet->m_file);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpFileWrite(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 2)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	short len = *(short*)(param_list.m_list[0].m_pData);
// 	void* pWriteData = (void*)(param_list.m_list[1].m_pData);
// 	param->m_rtn = FileOpFileWrite(&pRingNet->m_file, &len, pWriteData);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpFileRead(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	short len = *(short*)(param_list.m_list[0].m_pData);
// 	char read_data[512];
// 
// 	param->m_rtn = FileOpFileRead(&pRingNet->m_file, &len, read_data);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CAddParam(sizeof(short), (param_list.m_list[0].m_pData));
// 	param_list.CAddParam(sizeof(char)*len, read_data);
// 
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpFileCheckExsits(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	LPCTSTR m_pathName = (LPCTSTR)(param_list.m_list[0].m_pData);
// 	param->m_rtn = FileOpFileCheckExsits(&pRingNet->m_file, m_pathName);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpFileDelete(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	LPCTSTR m_pathName = (LPCTSTR)(param_list.m_list[0].m_pData);
// 	param->m_rtn = FileOpFileCheckExsits(&pRingNet->m_file, m_pathName);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// 
// short StFileOp::Fn_Real_FileOpDirctoryCreate(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	LPCTSTR m_pathName = (LPCTSTR)(param_list.m_list[0].m_pData);
// 	param->m_rtn = FileOpDirctoryCreate(&pRingNet->m_file, m_pathName);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// short StFileOp::Fn_Real_FileOpDirctoryDelete(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	LPCTSTR m_pathName = (LPCTSTR)(param_list.m_list[0].m_pData);
// 	param->m_rtn = FileOpDirctoryDelete(&pRingNet->m_file, m_pathName);
// 
// 	param_list.CClearPData(pData);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// 
// short StFileOp::Fn_Real_FileOpGetCrcResult(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 	param->m_rtn = 0;
// 	short crc_check = *(short*)(param_list.m_list[0].m_pData);
// 	short crc = (pRingNet->m_file.m_crc_high << 8) | (pRingNet->m_file.m_crc_low & 0xFF);
// 	if (crc_check != crc)
// 	{
// 		if (GOOGOL_PRINF_EN) printf(("%s,CRC Err !\n"), pRingNet->m_file.m_fileName.GetLPCSTR());
// //		RETAILMSG(_GOOGOLTECH_RING_NET_DEBUG_, (TEXT("%s,CRC Err !\n"), pRingNet->m_file.m_fileName.GetLPCSTR()));
// 		param->m_rtn = RTN_FIFE_CRC_CHECK_ERR;
// 		FileOpFileDelete(&pRingNet->m_file, pRingNet->m_file.m_fileName.GetLPCSTR());
// 	}
// 	param_list.CClearPData(pData);
// 
// 	param_list.CAddParam(sizeof(short), (char*)&crc);
// 	param_list.CSetStFunction(param);
// 
// 	return RTN_SUCCESS;
// }
// 
// 
// //////////////////////////////////////////////////////////////////////////
// //  [9/20/2016 googol]
// short StFileOp::Fn_Real_FileOpCtrlCfg(LPVOID lp, StFunction* param, char* pData)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	if (param->m_param_num != 1)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 
// 	CLPBYTEList param_list;
// 	param_list.CGetList(param, pData);
// 	if (param_list.m_use_len > param->m_len)
// 	{
// 		return RTN_PARAM_ERR;
// 	}
// 	param->m_rtn = 0;
// 	short thread_sleep_time = *(short*)(param_list.m_list[0].m_pData);
// 	short crc = (pRingNet->m_file.m_crc_high << 8) | (pRingNet->m_file.m_crc_low & 0xFF);
// 	param_list.CClearPData(pData);
// 
// 	param_list.CAddParam(sizeof(short), (char*)&(pRingNet->m_Thread_sleep_time));
// 	param_list.CSetStFunction(param);
// 
// 	pRingNet->m_Thread_sleep_time = thread_sleep_time;
// 	if (pRingNet->m_Thread_sleep_time == 0 && pRingNet->m_file.m_pBuffer == NULL)
// 	{
// 		//		printf(("pRingNet->m_file.m_pBuffer = new char[MAX_FIFE_BUFFER_SIZE] !\n"));
// 		pRingNet->m_file.m_pBuffer = new char[MAX_FIFE_BUFFER_SIZE];
// 		pRingNet->m_file.m_buffer_cnt = 0;
// 	}
// 	else if (pRingNet->m_Thread_sleep_time != 0 && pRingNet->m_file.m_pBuffer != NULL)
// 	{
// 		delete[]pRingNet->m_file.m_pBuffer;
// 		pRingNet->m_file.m_pBuffer = NULL;
// 		pRingNet->m_file.m_buffer_cnt = 0;
// 	}
// 
// 	return RTN_SUCCESS;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// //  [8/25/2016 googol]
// //////////////////////////////////////////////////////////////////////////
// // net function packet
// //////////////////////////////////////////////////////////////////////////
// short StFileOp::RingNetFuctionDriver(LPVOID lp, StFunction* param, unsigned char station_id, BOOL resp_req)
// {
// 	CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 	return pRingNet->FileFuctionDriver(param, station_id, resp_req);
// }
// 
// //////////////////////////////////////////////////////////////////////////
// short StFileOp::RN_FileOpFileOpen(LPVOID lp, LPCTSTR m_pathName, DWORD dwCreationDisposition, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileOpen;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	short len;
// 	GetLPCSTRLen(m_pathName, &len);
// 
// 	param_list.CAddParam(2 * len + 2, (char*)m_pathName);
// 	param_list.CAddParam(sizeof(DWORD), (char*)(&dwCreationDisposition));
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// short StFileOp::RN_FileOpFileClose(LPVOID lp, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileClose;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// short StFileOp::RN_FileOpFileWrite(LPVOID lp, short *len, void* pData, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileWrite;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	param_list.CAddParam(sizeof(short), (char*)len);
// 	param_list.CAddParam(*len, (char*)pData);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// short StFileOp::RN_FileOpFileRead(LPVOID lp, short *len, void* pData, unsigned char station_id)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileRead;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	param_list.CAddParam(sizeof(short), (char*)len);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	if (param.m_param_num != 2) return RTN_FILE_PARAM_NUM_ERR;
// 
// 	param_list.CGetList(&param, (char*)param.m_pData);
// 	if (param.m_len < param_list.m_use_len) return RTN_FILE_PARAM_LEN_ERR;
// 
// 	*len = *((short*)param_list.m_list[0].m_pData);
// 	memcpy(pData, param_list.m_list[1].m_pData, *len);
// 	return param.m_rtn;
// }
// short StFileOp::RN_FileOpFileCheckExsits(LPVOID lp, LPCTSTR file_name, unsigned char station_id)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileCheckExsits;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	short len;
// 	GetLPCSTRLen(file_name, &len);
// 
// 	//	param_list.CClearPData(buffer);
// 	param_list.CAddParam(2 * len + 2, (char*)file_name);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// short StFileOp::RN_FileOpFileDelete(LPVOID lp, LPCTSTR file_name, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpFileDelete;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	short len;
// 	GetLPCSTRLen(file_name, &len);
// 
// 	//	param_list.CClearPData(buffer);
// 	param_list.CAddParam(2 * len + 2, (char*)file_name);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// 
// short StFileOp::RN_FileOpDirctoryCreate(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpDirctoryCreate;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	short len;
// 	GetLPCSTRLen(m_pathName, &len);
// 
// 	//	param_list.CClearPData(buffer);
// 	param_list.CAddParam(2 * len + 2, (char*)m_pathName);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// 
// }
// short StFileOp::RN_FileOpDirctoryDelete(LPVOID lp, LPCTSTR m_pathName, unsigned char station_id, BOOL resp_req)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpDirctoryDelete;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 
// 	short len;
// 	GetLPCSTRLen(m_pathName, &len);
// 
// 	//	param_list.CClearPData(buffer);
// 	param_list.CAddParam(2 * len + 2, (char*)m_pathName);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, resp_req);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	else return param.m_rtn;
// }
// 
// short StFileOp::RN_FileOpGetCrcResult(LPVOID lp, short* crc_result, unsigned char station_id)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpGetCrcResult;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 	param_list.CAddParam(sizeof(short), (char*)crc_result);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	if (param.m_param_num != 1) return RTN_FILE_PARAM_NUM_ERR;
// 
// 	param_list.CGetList(&param, (char*)param.m_pData);
// 	if (param.m_len < param_list.m_use_len) return RTN_FILE_PARAM_LEN_ERR;
// 
// 	*crc_result = *((short*)param_list.m_list[0].m_pData);
// 	return param.m_rtn;
// }
// //////////////////////////////////////////////////////////////////////////
// //  [9/21/2016 googol]
// short StFileOp::RN_FileOpCtrlCfg(LPVOID lp, short* thread_sleep_time, unsigned char station_id)
// {
// 	StFunction param;
// 	CLPBYTEList param_list;
// 	char buffer[512];
// 	param.m_id = FN_FileOpCtrlCfg;
// 	param.m_rtn = 0;
// 	param.m_pData = (unsigned char*)buffer;
// 	param_list.CClearPData(buffer);
// 	param_list.CAddParam(sizeof(short), (char*)thread_sleep_time);
// 	param_list.CSetStFunction(&param);
// 
// 	short rtn = RingNetFuctionDriver(lp, &param, station_id, 0xFF != station_id);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	if (param.m_param_num != 1) return RTN_FILE_PARAM_NUM_ERR;
// 
// 	param_list.CGetList(&param, (char*)param.m_pData);
// 	if (param.m_len < param_list.m_use_len) return RTN_FILE_PARAM_LEN_ERR;
// 
// 	*thread_sleep_time = *((short*)param_list.m_list[0].m_pData);
// 	return param.m_rtn;
// }
// //////////////////////////////////////////////////////////////////////////
// 
// short StFileOp::RN_WriteFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id)
// {
// 	const int SLEEP_TIME = 15;
// 	/////////////////////////////////////////////////////////////////////////
// 	{
// 		StString tsrc = src_file;
// 		StString tdes = des_file;
// 		CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 		if (tsrc == tdes && (/*pRingNet->m_CNS.m_online_msg.bit.device_id == station_id ||*/ station_id == 0xFF))
// 		{
// 			return RTN_PARAM_ERR;
// 		}
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 	StFileOp src_file_op;
// 
// 	short rtn = FileOpCreate(&src_file_op);
// 	char buffer[480];
// 
// 	GetFilePathFileName(src_file, src_file_op.m_pathName, src_file_op.m_fileName);
// 	rtn = FileOpFileCheckExsits(&src_file_op, src_file_op.m_fileName.GetLPCSTR());
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	rtn = FileOpFileOpen(&src_file_op, src_file_op.m_fileName.GetLPCSTR(), src_dwCreationDisposition);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 	//////////////////////////////////////////////////////////////////////////
// 	StString des_path, des_name;
// 	GetFilePathFileName(des_file, des_path, des_name);
// 	rtn = RN_FileOpDirctoryCreate(lp, des_path.GetLPCSTR(), station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 	rtn = RN_FileOpFileOpen(lp, des_name.GetLPCSTR(), des_dwCreationDisposition, station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 
// 	short len;
// 	for (int i = 0; i < 100000000; i++)
// 	{
// 		len = 460;
// 		rtn = FileOpFileRead(&src_file_op, &len, buffer);
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			FileOpFileClose(&src_file_op);
// 			return rtn;
// 		}
// 		if (len == 0) break;
// 
// 		rtn = RN_FileOpFileWrite(lp, &len, buffer, station_id, station_id != 0xFF);
// 		if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			FileOpFileClose(&src_file_op);
// 			return rtn;
// 		}
// 	}
// 	rtn = FileOpFileClose(&src_file_op);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	rtn = RN_FileOpFileClose(lp, station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	if (station_id != 0xFF)
// 	{
// 		short crc;
// 		short crc_src;
// 		crc_src = (src_file_op.m_crc_high << 8) | (src_file_op.m_crc_low & 0xFF);
// 		crc = crc_src;
// 		rtn = RN_FileOpGetCrcResult(lp, &crc, station_id);
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			return rtn;
// 		}
// 		if (crc != crc_src)
// 		{
// 			return RTN_FIFE_CRC_CHECK_ERR;
// 		}
// 	}
// 	return RTN_SUCCESS;
// }
// 
// short StFileOp::RN_WriteDirctory(LPVOID lp, LPCTSTR src_file, LPCTSTR des_file, unsigned char station_id)
// {
// 	StFileOp src_file_op;
// 	StFileOp des_file_op;
// 	GetFilePathFileName(src_file, src_file_op.m_pathName, src_file_op.m_fileName);
// 	if (src_file_op.m_pathName.GetStStringLen() == NULL) return RTN_PACKET_ERR;
// 
// 	GetFilePathFileName(des_file, des_file_op.m_pathName, des_file_op.m_fileName);
// 	if (des_file_op.m_pathName.GetStStringLen() == NULL) return RTN_PACKET_ERR;
// 
// 	StString search_str = src_file_op.m_pathName + L"\\*.*";
// 	short rtn;
// 	WIN32_FIND_DATA fd;
// 	HANDLE hdFind;
// 	hdFind = FindFirstFile(search_str.GetLPCSTR(), &fd);
// 	if (hdFind != INVALID_HANDLE_VALUE)
// 	{
// 		do
// 		{
// 			rtn = RN_FileOpDirctoryCreate(lp, des_file_op.m_pathName.GetLPCSTR(), station_id, station_id != 0xFF);
// 			if (rtn != RTN_SUCCESS)
// 			{
// 				FindClose(hdFind);
// 				return rtn;
// 			}
// 
// 			//At winXP system the "." means current directory, the ".."means parent directory.   
// 			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && fd.cFileName[0] != L'.')
// 			{
// 				StString src_next_str = src_file_op.m_pathName + L"\\";
// 				StString des_next_str = des_file_op.m_pathName + L"\\";
// 				src_next_str += fd.cFileName;
// 				des_next_str += fd.cFileName;
// 				rtn = RN_FileOpDirctoryCreate(lp, des_next_str.GetLPCSTR(), station_id, station_id != 0xFF);
// 				if (rtn)
// 				{
// 					FindClose(hdFind);
// 					return rtn;
// 				}
// 
// 				rtn = RN_WriteDirctory(lp, src_next_str.GetLPCSTR(), des_next_str.GetLPCSTR(), station_id);
// 				if (rtn)
// 				{
// 					FindClose(hdFind);
// 					return rtn;
// 				}
// 
// 			}
// 			else if (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
// 			{
// 				//It is file    
// 				StString src_file_str = src_file_op.m_pathName + L"\\";
// 				StString des_file_str = des_file_op.m_pathName + L"\\";
// 				src_file_str += fd.cFileName;
// 				des_file_str += fd.cFileName;
// 				rtn = RN_WriteFile(lp, src_file_str.GetLPCSTR(), OPEN_EXISTING, des_file_str.GetLPCSTR(), CREATE_ALWAYS, station_id);
// 				if (rtn)
// 				{
// 					FindClose(hdFind);
// 					return rtn;
// 				}
// 			}
// 		} while (FindNextFile(hdFind, &fd));
// 	}
// 	else
// 	{
// 		FindClose(hdFind);
// 		return RTN_FILE_MALLOC_FAIL;
// 	}
// 	FindClose(hdFind);
// 	return RTN_SUCCESS;
// }
// 
// 
// short StFileOp::RN_ReadFile(LPVOID lp, LPCTSTR src_file, DWORD src_dwCreationDisposition, LPCTSTR des_file, DWORD des_dwCreationDisposition, unsigned char station_id)
// {
// 	const int SLEEP_TIME = 15;
// 	/////////////////////////////////////////////////////////////////////////
// 	{
// 		StString tsrc = src_file;
// 		StString tdes = des_file;
// 		CPcCtrlCom* pRingNet = (CPcCtrlCom*)lp;
// 		if (tsrc == tdes && (/*pRingNet->m_CNS.m_online_msg.bit.device_id == station_id || */station_id == 0xFF))
// 		{
// 			return RTN_PARAM_ERR;
// 		}
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 	StFileOp src_file_op;
// 
// 	short rtn = FileOpCreate(&src_file_op);
// 	char buffer[480];
// 
// 	GetFilePathFileName(src_file, src_file_op.m_pathName, src_file_op.m_fileName);
// 	rtn = FileOpFileCheckExsits(&src_file_op, src_file_op.m_fileName.GetLPCSTR());
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	rtn = FileOpFileOpen(&src_file_op, src_file_op.m_fileName.GetLPCSTR(), src_dwCreationDisposition);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 	//////////////////////////////////////////////////////////////////////////
// 	StString des_path, des_name;
// 	GetFilePathFileName(des_file, des_path, des_name);
// 	rtn = RN_FileOpDirctoryCreate(lp, des_path.GetLPCSTR(), station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 	rtn = RN_FileOpFileOpen(lp, des_name.GetLPCSTR(), des_dwCreationDisposition, station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS)
// 	{
// 		FileOpFileClose(&src_file_op);
// 		return rtn;
// 	}
// 
// 	short len;
// 	for (int i = 0; i < 100000000; i++)
// 	{
// 		len = 460;
// 		rtn = FileOpFileRead(&src_file_op, &len, buffer);
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			FileOpFileClose(&src_file_op);
// 			return rtn;
// 		}
// 		if (len == 0) break;
// 
// 		rtn = RN_FileOpFileWrite(lp, &len, buffer, station_id, station_id != 0xFF);
// 		if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			FileOpFileClose(&src_file_op);
// 			return rtn;
// 		}
// 	}
// 	rtn = FileOpFileClose(&src_file_op);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 	rtn = RN_FileOpFileClose(lp, station_id, station_id != 0xFF);
// 	if (station_id == 0xFF) Sleep(SLEEP_TIME);
// 	if (rtn != RTN_SUCCESS) return rtn;
// 
// 	if (station_id != 0xFF)
// 	{
// 		short crc;
// 		short crc_src;
// 		crc_src = (src_file_op.m_crc_high << 8) | (src_file_op.m_crc_low & 0xFF);
// 		rtn = RN_FileOpGetCrcResult(lp, &crc, station_id);
// 		if (rtn != RTN_SUCCESS)
// 		{
// 			return rtn;
// 		}
// 		if (crc != crc_src)
// 		{
// 			return RTN_FIFE_CRC_CHECK_ERR;
// 		}
// 	}
// 	return RTN_SUCCESS;
// }
// 
// //////////////////////////////////////////////////////////////////////////
