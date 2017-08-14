#pragma once
#include "RingNetDriver.h"
#define RN_MAX_SERVO_AXI_NUM 256
#define RN_MAX_SERVO_DSP_NUM 256
const Uint16 RN_INVAVLID_STATION_ID = 0xFE;
typedef struct
{
	Uint16 m_dsp_id;//dsp_id
	Uint8 m_station_id;
	Uint8 m_station_ch;
	Uint8 m_axi_id_in_dsp;//该轴在该DSP中属于哪一个轴。
}StDspAxiStationInf;

class CRnServoAxiMapping
{
public:
	CRnServoAxiMapping();
	~CRnServoAxiMapping();
protected:
	CRingNetDriver* m_pDriver;
	Uint16 m_axi_num;
	Uint16 m_dsp_num;
	StDspAxiStationInf m_axi_inf[RN_MAX_SERVO_AXI_NUM]; // 每一个存储空间内存储的是对应这个axi的站号。
//	StDspAxiStationInf m_dsp_inf[RN_MAX_SERVO_DSP_NUM]; // 每一个存储空间内存储的是对应这个axi的站号。
protected:
	//和dsp相关的地址偏移
	const Uint16						FPGA_RN_ENC_START_OFST = 0x100;
	const Uint16						FPGA_RN_ENC_END_OFST = 0x1FF;

	const Uint16						FPGA_RN_AIN_START_OFST = 0x300;
	const Uint16						FPGA_RN_AIN_END_OFST = 0x3FF;

	const Uint16						FPGA_RN_IO_START_OFST = 0x400;
	const Uint16						FPGA_RN_IO_END_OFST = 0x4FF;

	const Uint16						FPGA_RN_REF_START_OFST = 0x500;
	const Uint16						FPGA_RN_REF_END_OFST = 0x5FF;

	const int32						FPGA_RN_UART_START_OFST = 0x800;
	const int32						FPGA_RN_UART_END_OFST = 0x8FF;

	//和dsp无关的地址偏移

	const int32						FPGA_RN_CTL_START_OFST = 0x000;
	const int32						FPGA_RN_CTL_END_OFST = 0x0FF;

	const int32						FPGA_RN_TRIG_START_OFST = 0x200;
	const int32						FPGA_RN_TRIG_END_OFST = 0x2FF;

	const int32						FPGA_RN_RMT_START_OFST = 0x600;
	const int32						FPGA_RN_RMT_END_OFST = 0x6FF;

	const int32						FPGA_RN_SYS_START_OFST = 0x700;
	const int32						FPGA_RN_SYS_END_OFST = 0x7FF;

	const int32						FPGA_RN_RAM_START_OFST = 0x1000;
	const int32						FPGA_RN_RAM_END_OFST = 0x1FFF;

	const int32						FPGA_RN_ILINK_START_OFST = 0x2000;
	const int32						FPGA_RN_ILINK_END_OFST = 0x23FF;

	const int32						FPGA_RN_USER_START_OFST = 0xC000;
	const int32						FPGA_RN_USER_END_OFST = 0xFEFF;

	const int32						FPGA_RN_APP_START_OFST = 0xFF00;
	const int32						FPGA_RN_APP_END_OFST = 0xFFFF;
public:
	short InitialMapping(CRingNetDriver* driver);
	Uint16 ConvertAxiToStationId(int16 axi_id);
	Uint16 ConvertDspToStationId(int16 dsp_id);
	Uint16 ConvertAxiToDspId(int16 axi_id);
	Uint16 ConvertAxiToSubAxiId(int16 axi_id);
public:
	Uint16 ConvertFpgaByteAddrByDspId(Uint16 axi_id, Uint16 fpga_byte_address);
};

