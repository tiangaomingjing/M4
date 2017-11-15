#pragma once
#include "Basetype_def.h"
class CDeviceDataBase
{
public:
	CDeviceDataBase();
	virtual ~CDeviceDataBase();
	Uint8 m_station_valid;
	Uint8 m_distance;
	Uint8 m_station_id;
	Uint16 m_staion_type;
// 	Uint16 m_version;
// 	Uint16 m_year;
// 	Uint16 m_month;
// 	Uint16 m_data;
// 	Uint16 m_appendix_a;
// 	Uint16 m_appendix_b;
	
};

