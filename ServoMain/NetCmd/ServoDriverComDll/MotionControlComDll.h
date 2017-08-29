//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Communicaiton cmd layer Define		 						//
//	file				:	ServoDriverComDll.h											//
//	Description			:	use for cmd define											//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2016/1/20	|	googoltech		|		2016 - 2019			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef			__GTSD_SERVO_MOTION_COM_DLL__
#define			__GTSD_SERVO_MOTION_COM_DLL__	



// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SERVODRIVERCOMDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SERVODRIVERCOMDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
#include "Basetype_def.h"
#include "BaseReturn_def.h"
#include "StRingNetRegDef.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
SERVODRIVERCOMDLL_API int16 GT_RN_Open(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv);
SERVODRIVERCOMDLL_API int16 GT_RN_Close();

SERVODRIVERCOMDLL_API short GT_RN_PostPci(void* gPci, Uint8 station_id = 0xf0);
SERVODRIVERCOMDLL_API short GT_RN_SendPci(void* gPci, Uint8 station_id = 0xf0);
SERVODRIVERCOMDLL_API short RN_ComHandler(Uint8 mode, Uint8 cmd, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id, Uint8 des_c, Uint8 needReq = TRUE, Uint8 addr_mod = 1, Uint8 wait_level = 0, Uint8 dsitance = 0xf0);
SERVODRIVERCOMDLL_API short RN_GetCns(COMMON_NET_STATUS* pCns, Uint8 dsitance = 0xf0);
SERVODRIVERCOMDLL_API short RN_FpgaUpate(char* filePath, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16 stationId = 0xf0);

#endif