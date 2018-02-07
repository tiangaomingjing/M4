#pragma once
#include "Basetype_def.h"
//////////////////////////////////

#define					ADDR_ILINK_CFG_AI						0x200
#define					ADDR_ILINK_CFG_AO						0x260
#define					ADDR_ILINK_CFG_UPDATA					0x2D0
#define					ADDR_ILINK_CFG_BESY						0x2D1
#define					ADDR_ILINK_AO_VALUE						0x002
#define					ADDR_ILINK_DO_VALUE						0x002

#define                 ILINK_SIZE_AI_CFG             (96)//16*6
#define                 ILINK_SIZE_AO_CFG             (96)//16*6

typedef struct
{
	Uint8				Offset_L : 8;//偏移
	Uint8				Offset_H : 8;//偏移
}ILINK_OFFSET_BIT;
typedef union
{
	Uint16				all;
	ILINK_OFFSET_BIT	offset;//偏移
}ILINK_OFFSET;


typedef struct
{
	Uint8				Scaling_L : 8;//增益
	Uint8				Scaling_H : 8;//增益
}ILINK_SCALLING_BIT;
typedef union
{
	Uint16				all;
	ILINK_SCALLING_BIT	scaling;//偏移
}ILINK_SCALLING;

typedef struct
{
	Uint8				ErrVal_L : 8;//
	Uint8				ErrVal_H : 8;//
}ILINK_ERR_VAL_BIT;
typedef union
{
	Uint16				all;//
	ILINK_ERR_VAL_BIT	bit;//
}ILINK_ERR_VAL;
typedef struct
{
	Uint8				ErrMode : 8;//断线后的通信状态
	ILINK_ERR_VAL       RrrVal;
	Uint8				revsd : 8;//
}ILINK_ERR;


////////ILINK_AO_CFG///////////////////
typedef struct
{
	Uint8				AO_Range : 8;//8 模拟量通道输出
	ILINK_OFFSET		AO_Offset;//16
	ILINK_SCALLING		AO_Scaling;//16
	ILINK_ERR			AO_err;//32
	short				default_value : 16;//
	Uint8				revsd0 : 8;//
}ILINK_AO_CHANNL;

#define ILINK_NUM_AO_CHANNL (6)
typedef struct
{
	ILINK_AO_CHANNL		iLink_AO_Channl[ILINK_NUM_AO_CHANNL];
}ILINK_AO_CFG;

////////ILINK_AI_CFG///////////////////
typedef struct
{
	Uint8				AI_Range;//8 模拟量通道输出
	ILINK_OFFSET		AI_Offset;//16
	ILINK_SCALLING		AI_Scaling;//16
	Uint8				revsd0;//
	Uint16				revsd1;//
}ILINK_AI_CHANNL;

#define ILINK_NUM_AI_CHANNL (6)
typedef struct
{
	ILINK_AI_CHANNL		iLink_AI_Channl[ILINK_NUM_AI_CHANNL];
}ILINK_AI_CFG;

// typedef struct
// {
// 	Uint8				port0_status	: 1;
// 	Uint8				port1_status	: 1;
// 	Uint8				device_err		: 1;
// 	Uint8				com_err			: 1;
// 	Uint8				type_err		: 1;
// 	Uint8				resp_ok			: 1;
// 	Uint8				port2_status	: 1;
// 	Uint8				rvsd_bit7		: 1;
// }DEVICE_STATUS;

// typedef union 
// {	
// 	Uint8 all;
// 	REG_ILINK_DEVICE_STATUS_BIT bit;
// 
// }REG_ILINK_DEVICE_STATUS;

///////////////ILINK_STATUS///////////////////////////////////////////
typedef struct
{
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
	Uint16				revsd0 : 10;
	Uint16				auto_send_en : 1;//
	Uint16				err_clr : 1;//(清除0x10)
	Uint16				link_status : 1;//( 只读)
	Uint16				ctrl_src_mask : 1;//该值仅本地配置，只有该值为1时，ctrl_src才会被修改	length只有对应的控制方，才能修改。
	Uint16				ctrl_src : 1;//ctrl_src:（默认为1）该值仅本地配置。0：表示所有状态由本地址控制，1：表示所有状态由远程控制
	Uint16				rx_ok : 1;//(只读)
}ILINK_STATUS;

//////////////////////////////////////////////////////////////////////////
//#define					DEBUG_ING											1
// #define					 BASE_OFFSET									(0x0000)
// #define					 PCI_BASE_OFFSET							    (0x0000)
// 
// #define					RES_ILINK_PCI_BASE_ADDR 					(Uint32*)(PCI_BASE_ADDR+PCI_BASE_OFFSET+0x0000*INCREMENT_PCI_VALUE)
// #define					RES_ILINK_MASTER_VERSION	  				(Uint32*)(RES_ILINK_PCI_BASE_ADDR+0x0000/INCREMENT_PCI_VALUE)
// #define					RES_ILINK_MASTER_STATUS	  					(Uint32*)(RES_ILINK_PCI_BASE_ADDR+0x000C/INCREMENT_PCI_VALUE)
// #define					RES_ILINK_PACKET_HEAD		  				(Uint32*)(RES_ILINK_PCI_BASE_ADDR+0x00010/INCREMENT_PCI_VALUE)
// #define					RES_ILINK_PACETS_DATA					  	(Uint32*)(RES_ILINK_PCI_BASE_ADDR+0x00014/INCREMENT_PCI_VALUE)
/////////////////////////////////////////////
//#define					ADDR_ILINK_PCI_BASE_ADDR 					(PCI_BASE_ADDR+PCI_BASE_OFFSET+0x0000*INCREMENT_PCI_VALUE)

///////////////////////////this addr is calc by byte ////////////////////
#define					ADDR_ILINK_MAX_PATH_ONLINE					0x120
#define					ADDR_ILINK_PRE_PATH_DELAY					0x122
#define					ADDR_ILINK_PATH_NUM							0x124
#define					ADDR_ILINK_DEVICE_ID						0x126
#define					ADDR_ILINK_SYNC_ON_CTRL						0x128	
#define					ADDR_ILINK_CLR_PORT_ERR	           0x110


#define DEIVCE_PORT2_16I_16O   0x01
#define DEIVCE_PORT2_6AD_6DA 0x02
#define DEIVCE_PORT2_16I_10O   0x03
#define DEVICE_PORT2_8I_8O      0xF0
#define DEVICE_PORT3_8I_8O      0xF1

//#define IDLINK_NUM_MAX 32

#define ILINK_PDU	0
#define ILINK_MAIL	1

#define ILINK_DEVICE_ID_AUTO	0
#define ILINK_DEVICE_ID_MUNAL	1

///////////REG_ILINK_DEVICE_STATUS//////////////////////
typedef struct
{
	Uint8				port0_status : 1;
	Uint8				port1_status : 1;
	Uint8				device_err : 1;
	Uint8				com_err : 1;
	Uint8				type_err : 1;
	Uint8				resp_ok : 1;
	Uint8				port2_status : 1;
	Uint8				rvsd_bit7 : 1;
}REG_ILINK_DEVICE_STATUS_BIT;

typedef union
{
	Uint8 all;
	REG_ILINK_DEVICE_STATUS_BIT bit;

}REG_ILINK_DEVICE_STATUS;


//////////////ILINK_DEVICE_PDU_HEAD///////////////////

typedef struct
{
	//byte0
	Uint8						length : 7;
	Uint8						type : 1;//byte1

	Uint8						device_id;//
	//byte2  //byte3
	Uint8						device_type;
	REG_ILINK_DEVICE_STATUS		device_status;
}ILINK_DEVICE_PDU_HEAD_BIT;

typedef union
{
	Uint32 all;
	ILINK_DEVICE_PDU_HEAD_BIT bit;

}ILINK_DEVICE_PDU_HEAD;


//////////////////////////////////////
typedef struct
{
	Uint16 max_path_online : 9;
	Uint16 max_path_online_rvsd : 7;
}ILINK_REG_MAX_PATH_ONLINE_ALL_BIT;

typedef union
{
	Uint16 max_path_online_all;
	ILINK_REG_MAX_PATH_ONLINE_ALL_BIT bit;

}ILINK_REG_MAX_PATH_ONLINE_ALL;

//////////////////////////////////////////

typedef struct
{
	Uint16 path_num : 9;
	Uint16 path_num_rvsd : 7;
}ILINK_REG_PATH_NUM_BIT;

typedef union
{
	Uint16 path_num_all;
	ILINK_REG_PATH_NUM_BIT bit;
}ILINK_REG_PATH_NUM;

////////////////////////////

typedef struct
{
	Uint16 device_id_auto : 9;
	Uint16 device_id_set : 7;
}ILINK_REG_DEVICE_ID_BIT;


typedef union
{
	Uint16 device_id;
	ILINK_REG_DEVICE_ID_BIT bit;
}ILINK_REG_DEVICE_ID;

//////////////////////////////////////////

typedef struct
{
	Uint16 sync_on : 1;
	Uint16 device_id_set : 1;////0 auto, 1: munal;
	Uint16 sync_ctrl_rvsd : 14;
}ILINK_REG_SYNC_CTRL_SYATUS_BIT;

typedef union
{
	Uint16 sync_ctrl_status;
	ILINK_REG_SYNC_CTRL_SYATUS_BIT bit;

}ILINK_REG_SYNC_CTRL_SYATUS;

//////////////////////////////////////////////////////////////////////////

typedef struct
{
	ILINK_REG_MAX_PATH_ONLINE_ALL	max_path_online;
	Uint16							pre_path_delay;
	ILINK_REG_PATH_NUM				path_num;
	ILINK_REG_DEVICE_ID				device_id;
	ILINK_REG_SYNC_CTRL_SYATUS		sync_ctrl_status;
}ILINK_DEVICE_SYNC_MSG;

///////////////////////////////////



typedef struct
{
	ILINK_DEVICE_SYNC_MSG m_sync_msg;

	Uint8 m_device_msg[2];

	Uint8  m_data_size;


	Uint8* m_pWrData;
	Uint8* m_pRdData;

	Uint16 m_buffer_offset;
	ILINK_DEVICE_PDU_HEAD m_pdu_head;

	///////add by luo.mj///////////////////////
	ILINK_AO_CFG m_ao_cfg;
	ILINK_AI_CFG m_ai_cfg;
	Uint16       m_DO_Val;
	Uint16		m_set_val[ILINK_NUM_AO_CHANNL];
	/////// end luo /////////////////////////////
}StIlinkDevice;


short ILinkDeviceCreate(StIlinkDevice* pIlinkDevice);
short ILinkDeviceDetete(StIlinkDevice* pIlinkDevice);

short IlinkDeviceDecodePduHead(StIlinkDevice* pIlinkDevice, Uint8* pData);
short IlinkDeviceSetLength(StIlinkDevice* pIlinkDevice, Uint8 len);
class CIlinkDevice
{
public:
	CIlinkDevice();
	~CIlinkDevice();
};


