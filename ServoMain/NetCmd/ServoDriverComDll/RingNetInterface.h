#pragma once
#include "RingNetDriver.h"
#include "ComBase.h"
typedef enum opt_type
{
	GTSD_COM_MODE_READ,			//������
	GTSD_COM_MODE_WRITE			//д����
}OPT_TYPE;

typedef enum
{
	RN_PACKET_MAIL_RD_ASK = 0,
	RN_PACKET_MAIL_WR_ASK = 1,

	RN_PACKET_MAIL_RD_RESP = 2,
	RN_PACKET_MAIL_WR_RESP = 3,

	RN_PACKET_PDU_RD_ASK = 4,
	RN_PACKET_PDU_WR_ASK = 5,

	RN_PACKET_PDU_RD_RESP = 6,
	RN_PACKET_PDU_WR_RESP = 7,

	RN_PACKET_DMA_MAP_RD_ASK = 8,
	RN_PACKET_DMA_MAP_WR_ASK = 9,

	RN_PACKET_DMA_CFG_RD_ASK = 10,
	RN_PACKET_DMA_CFG_WR_ASK = 11
}ENUM_RnOpType;

typedef enum
{
	RN_OP_WAIT_DEFAULT = 0,
	RN_OP_WAIT_NORMAL = 1,
	RN_OP_WAIT_MEDIUM = 2,
	RN_OP_WAIT_LONG = 3,
	RN_OP_WAIT_INFINITE = 4
}ENUM_RnOpWaitLevel;

#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

class SERVODRIVERCOMDLL_API CRingNetInterface :
	public CRingNetDriver, public CComBase
{
public:
	CRingNetInterface();
	~CRingNetInterface();

protected:
	Uint16 m_com_dsp_check_mode;

public:
	const int COM_DSP_TRY_TIME = 1000;
	const int COM_FPGA_TRY_TIME = 200;
	/*******************************************************************************************
	���ܣ�		��ɨ�赽���豸���ҵ�����Ӧ���豸���򿪸��豸���ҵ�һ������Ӧ���豸����˳�
	���룺		��
	���أ�		0�ɹ��������ο������б�
	*******************************************************************************************/
	int16 RnNetCom_Open(void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
	/*******************************************************************************************
	���ܣ��ر�ɨ�赽������Ӧ���豸
	���룺   ��
	���أ�   ��
	*******************************************************************************************/
	int16 RnNetCom_Close();

	/*******************************************************************************************
	���ܣ�FPGA����ͨ�Ž�������
	���룺
	mode:			1:д  0����
	dma_addr:		dma��ַ
	pData:			��������
	dma_num:		�������ݳ���
	�����pData:    �������
	dma_num:		������ݳ���
	���أ�0�ɹ��������ο������б�
	*******************************************************************************************/
	int16 RnNetCom_FPGA_ComHandler(int16 mode, int16 addr, int16* pData, int16 word_num, int16 des_id, int16 needReq = RN_NEED_REQ);

	/*******************************************************************************************
	���ܣ�dsp����ͨ�Ž�������
	���룺
	mode:			1:д  0����
	dma_addr:		dma��ַ
	pData:          ��������
	word_num:		�������ݳ���
	�����pData:    �������
	word_num:		������ݳ���
	���أ�0�ɹ��������ο������б�
	*******************************************************************************************/
	static const int32			NET_COM_EXECUTE_FAIL = 0;							// ����ִ��ʧ��
	static const int32			NET_COM_EXECUTE_SUCCESS = 1;							// ����ִ�гɹ�
	static const int32			NET_COM_PARAMETER_INVALID = 2;							// ��Ч����
	static const int32			NET_COM_INSTRUCTION_INVALID = 3;							// �Ƿ�ָ��
	static const Uint16			COM_DSP_CHEKC_NORMAL = 0;//check_en ctrl by the input param
	static const Uint16			COM_DSP_CHEKC_FORCE_ON = 1;//check_en don't ctrl by the input param, and force to on
	static const Uint16			COM_DSP_CHEKC_FORCE_OFF = 2;//check_en don't ctrl by the input param, and force to on
	int16 RnNetCom_DSP_ComHandler(int16 mode, int16 addr, int16* pData, int16 word_num, int16 des_id);
	int16 RnNetCom_DSP_ComHandler(int16 mode, int16 byte_addr, int16* pData, int16 word_num, Uint8 des_id, Uint8 des_ch, Uint8 check_en = true);

	Uint16 RnNetCom_DSP_FroceCheckMode(Uint16 mode);
	int16 RnNetComHandler(Uint8 mode, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id, Uint8 des_ch, Uint8 needReq = true, Uint8 addr_mod = RN_ADDR_INC, Uint8 wait_level = RN_OP_WAIT_DEFAULT, Uint8 dsitance = 0xf0);
	int16 RnNetCom(Uint8 com_mode, Uint8 cmd, Uint16 byte_addr, int16* pData, Uint16 word_num, Uint8 des_id, Uint8 des_ch, Uint8 needReq = true, Uint8 addr_mod = RN_ADDR_INC, Uint8 wait_level = RN_OP_WAIT_DEFAULT, Uint8 dsitance = 0xf0);
	int16 RnNetGetCns(COMMON_NET_STATUS* pCns, Uint8 dsitance);
public:
	virtual short ComWrFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam);
	virtual short ComRdFpgaHandle(Uint16 byte_addr, int16* pData, Uint16 word_num, Uint16 des_id, void* pParam);
private:
	int16 NC_Open(const int8* adapter, int32 port);
	int16 NC_Close(void);
};

//short UserRespDriver(StUserPacket* packet);