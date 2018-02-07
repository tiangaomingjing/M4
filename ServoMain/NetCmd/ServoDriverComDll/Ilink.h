#pragma once
#include "RingNetPacket.h"
#include "ComBase.h"

#define					INCREMENT_PCI_VALUE							4
/////////////////////this addr is calc by int////////////////////////////////
#define					ADDR_ILINK_MASTER_VERSION	  				(0x0000/INCREMENT_PCI_VALUE)
#define					ADDR_ILINK_MASTER_STATUS	  				(0x000C/INCREMENT_PCI_VALUE)
#define					ADDR_ILINK_PACKET_HEAD		  				(0x00010/INCREMENT_PCI_VALUE)
#define					ADDR_ILINK_PACETS_DATA					  	(0x00014/INCREMENT_PCI_VALUE)
/////////////////////this addr is calc by byte////////////////////////////////
///////////////////////////this addr is calc by byte ////////////////////
#define					ADDR_RN_ILINK_START						0xc
//返回值
#define ILINK_SUCCESS						0;//操作成功
#define ILINK__FAIL_PCI						1;//初始化PCI失败
#define ILINK__ERROR							2;//参数错误

#define ILINK_PACKET_END 0xFFFFFFFF

#ifndef ILINK_PDU

#define ILINK_PDU	0
#define ILINK_MAIL	1

#define ILINK_PDU	0

#endif

#define ILINK_MAIL_RD	1
#define ILINK_MAIL_WR	2
#define ILINK_MAIL_RW	3

#define ILINK_CTRL_BY_LOCAL		0
#define ILINK_CTRL_BY_REMOTE	1


#pragma pack(1)
////////////////////////////////////////////////////////////
//主站通讯状态和控制  地址0x0C 0x0E
/////////////////ILINK_CTRL_STATUS///////////////////////////////////////////
typedef struct
{
	//0x0C
	Uint16				port_err_cnt : 8;
	Uint16				flag_crc_err : 1;
	Uint16				flag_check_err : 1;
	Uint16				flag_head_err : 1;
	Uint16				flag_empty_err : 1;
	Uint16				phy_rx_err : 1;
	Uint16				phy_rx_overflow : 1;
	Uint16				tx_overflow : 1;
	Uint16				tx_underflow : 1;
	//0x0E
	Uint16				length : 10;
	Uint16				auto_send_en : 1;//
	Uint16				err_clr : 1;//(清除0x10)
	Uint16				link_status : 1;//( 只读)
	Uint16				ctrl_src_mask : 1;//该值仅本地配置，只有该值为1时，ctrl_src才会被修改	length只有对应的控制方，才能修改。
	Uint16				ctrl_src : 1;//ctrl_src:（默认为1）该值仅本地配置。0：表示所有状态由本地址控制，1：表示所有状态由远程控制
	Uint16				rx_ok : 1;//(只读)
}ILINK_CTRL_STATUS_BIT;

typedef union
{
	Uint32 all;
	ILINK_CTRL_STATUS_BIT bit;
}ILINK_CTRL_STATUS;

//////////ILINK_PACKET_HEAD///////////////////
typedef struct
{
	//byte0
	Uint8				device_cnt;//从站个数
	//byte1
	Uint8				append_cnt : 8;//附加累加器
	//byte2  //byte3
	Uint8				packet_num : 8;
	Uint8				rvsd : 8;
}ILINK_PACKET_HEAD_BIT;

typedef union
{
	Uint32 all;
	ILINK_PACKET_HEAD_BIT bit;
}ILINK_PACKET_HEAD;

//////////////ILINK_PACKET_SUB_HEAD/////////////////////
typedef struct
{
	Uint8						length : 7;
	Uint8						type : 1;//byte1

	Uint8						device_id;//
	Uint16						data : 16;
}ILINK_PACKET_SUB_HEAD_BIT;

typedef union
{
	Uint32 all;
	ILINK_PACKET_SUB_HEAD_BIT bit;

}ILINK_PACKET_SUB_HEAD;


////////////ILINK_PACKET_PDU_HEAD////////////////////////
typedef struct
{
	//byte0
	Uint8						length : 7;
	Uint8						type : 1;//byte1

	Uint8						device_id;//
	//byte2  //byte3
	Uint8						device_type;
	Uint8						device_status;
//	REG_ILINK_DEVICE_STATUS		device_status;
}ILINK_PACKET_PDU_HEAD_BIT;

typedef union
{
	Uint32 all;
	ILINK_PACKET_PDU_HEAD_BIT bit;

}ILINK_PACKET_PDU_HEAD;

////////////ILINK_PACKET_MAIL_HEAD/////////////////////////
typedef struct
{
	//byte0
	Uint16						length : 7;
	Uint16						type : 1;//byte1

	Uint16						device_id : 8;//
	//byte2  //byte3
	Uint16						addr_bit8tobit11 : 4;
	Uint16						rvsd_bit4 : 1;
	Uint16						model : 1;// 0: always access addr;  1 addr++;
	Uint16						cmd : 2;//1 :RD; 2: WR; 3: RW
	Uint16						addr_low : 8;
}ILINK_PACKET_MAIL_HEAD_BIT;

typedef union
{
	Uint32 all;
	ILINK_PACKET_MAIL_HEAD_BIT bit;
}ILINK_PACKET_MAIL_HEAD;
//////////////////////////////////////////////////////

typedef struct
{
	Uint8 pre[8];
	StRnHeadFormat head;
	Uint8 dataSection[RN_MAX_PACKET_LEN];	// user data section
}StIlinkPacket;
////////////////////////////

//////////////////////////////////////////////////////////////////////////

typedef struct
{

	/////////////////////////////

}StIlink;



class CIlink
{
public:
	CIlink();
	~CIlink();
public:
	static const Uint16						FPGA_RN_ILINK_START_OFST = 0x2000; //ilink address base

	//等环网偏移地址
	static const Uint16		RN_ILINK_FPGA_CTL = (0x7F * 2);
	static const Uint16		RN_REMOTE_FPGA_DATA_START = (0x00);
	static const Uint16		RN_REMOTE_FPGA_DATA_END = (0x7C * 2);
public:
	ILINK_CTRL_STATUS   m_ctrl_sts;//得到主站的错误等状态, 修改报文长度和控制源
	ILINK_PACKET_HEAD	m_rx_packet_head;

	CComBase**		m_pCom;
	Uint16			m_des_id;
	//////////////////////////////////////////////////////////////////////////
//	StIlinkDevice m_device[IDLINK_NUM_MAX];

//	Uint32* PCI_BASE_ADDR;

	Uint16 m_mail_packet_offset;
	//////////////////////////
// 	static short FormatIlinkUserPakcet(
// 		StRnPacket* pPacket,
// 		StIlinkSubPacket* sub_packet_list,
// 		Uint8 sub_packet_num,
// 		Uint16& bTotal_num
// 		);

	virtual short SendPacket(StIlinkPacket* pPacket, Uint16& dword_num);
	virtual short RecivePacket(StIlinkPacket* pPacket, Uint16& dword_num);

	short IlinkSetCtrlSrc(Uint8 type);
	short IlinkGetCtrlSrc(Uint8* type);
	short IlinkReturnCtrlSrc(Uint8* type);

	short IlinkGenScanDeivceNum(Uint8* pData, Uint16* byte_num);
	short IlinkGenScanDeviceType(Uint8* pData, Uint16* byte_num);

	short IlinkDecoderPacket(Uint8* pData);
	short IlinkGetPduLength(Uint16& length);
	short IlinkGenPduPacket(Uint8* pData, Uint16* byte_num);
//	short IlinkGetIlinkDeviceMsg(ILINKMSG* msg);

	short IlinkGetDeviceNum(BOOL* num_same, short* device_num);
// 	short IlinkGetModuleInf(Uint8 module_id, StIlinkModuleInf* inf);
// 	short IlinkGetInf(StIlinkInf* inf);
// 	short IlinkRdPduData(StIlinkOpParam* param);
// 	short IlinkWrPduData(StIlinkOpParam* param);

	short IlinkAutoSendOn();
	short IlinkAutoSendOff();

	short IlinkSetDataBaseAddr(unsigned long pAddr);
	short IlinkGetDataBaseAddr(unsigned long* pAddr);
	short IlinkSetSubPacketLength(Uint16 valid_data_size);
	short IlinkSetIlinkLength(Uint8* pData);
};

