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
	Uint8 m_axi_id_in_dsp;//�����ڸ�DSP��������һ���ᡣ
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
	StDspAxiStationInf m_axi_inf[RN_MAX_SERVO_AXI_NUM]; // ÿһ���洢�ռ��ڴ洢���Ƕ�Ӧ���axi��վ�š�
//	StDspAxiStationInf m_dsp_inf[RN_MAX_SERVO_DSP_NUM]; // ÿһ���洢�ռ��ڴ洢���Ƕ�Ӧ���axi��վ�š�
protected:
	//��dsp��صĵ�ַƫ��
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

	//��dsp�޹صĵ�ַƫ��

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
	Uint16 ConvertAxiToStationId(int16 axi_id);//�����ת��Ϊ���Ӧ��վ�ź�ͨ����
	Uint16 ConvertDspToStationId(int16 dsp_id);//��DSPվ�ź�ת��Ϊ���Ӧ��վ�ź�ͨ����
	Uint16 ConvertAxiToDspId(int16 axi_id);
	Uint16 ConvertAxiToSubAxiId(int16 axi_id);//�����ת��ΪDSP�еĶ�Ӧ�����
public:
	Uint16 ConvertFpgaByteAddrByDspId(Uint16 axi_id, Uint16 fpga_byte_address);
	//add by luo.mj 20180328
	int16 m_map_type;//mapģʽ��0������ӳ�䣻1����վ��ӳ�䣻Ĭ��Ϊ����ӳ��
	Uint16 m_station_id;//��վ��ӳ��ʱ���洢վ����Ϣ
	/////////////////////////////////////////////
};

