//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	eeprom operate interface		 							//
//	file				:	eepromOpt.h													//
//	Description			:	use for operate eeprom 										//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2017/04/01	|	googoltech		|		2017 - 2020			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GTSD_EEPROM_OPT_
#define	_GTSD_EEPROM_OPT_

#include "Basetype_def.h"

class eepromOpt
{
public:
	eepromOpt();
	~eepromOpt();

	bool read(int16 axis, Uint32 addr, int8 *buf, int32 length, int16 com_type, int16 stationId);
	bool write(int16 axis, Uint32 addr, int8 *buf, int32 length, int16 com_type, int16 stationId);
	bool erase(int16 axis, int16 com_type, int16 stationId);
};
extern eepromOpt* g_eeprom;
#endif