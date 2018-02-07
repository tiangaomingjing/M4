#pragma once
//#include "DeviceDataBase.h"
#include "Basetype_def.h"

#define					RN_COM_PTC_MODEL_AUTO_END_TX					0
#define					RN_COM_PTC_MODEL_WAIT_ACTIVE					1
#define					RN_COM_PTC_MODEL_WAIT_SYNC						2
#define					RN_COM_PTC_MODEL_AUTO_TX						3

//PDU TX BIT

#define					RN_COM_PTC_SET_DATA_VALID_BIT					1
#define					RN_COM_PTC_CLR_DATA_VALID_BIT					0

#define					RN_COM_PTC_SET_ACTIVE_BIT						1
#define					RN_COM_PTC_CLR_ACTIVE_BIT						0

#define					RN_COM_PTC_SET_CLR_BIT							1
#define					RN_COM_PTC_CLR_CLR_BIT							0

//MAIL TX BIT

#define					RN_COM_MTC_SET_DATA_VALID_BIT					1
#define					RN_COM_MTC_CLR_DATA_VALID_BIT					0

#define					RN_COM_MTC_SET_MAIL_REQ_BIT						1
#define					RN_COM_MTC_CLR_MAIL_REQ_BIT						0

#define					RN_COM_MTC_SET_CLR_BIT							1
#define					RN_COM_MTC_CLR_CLR_BIT							0

//PDU RX BIT

#define					RN_COM_PRC_SET_RD_OVER_BIT						1
#define					RN_COM_PRC_CLR_RD_OVER_BIT						0

#define					RN_COM_PRC_SET_CLR_BIT							1
#define					RN_COM_PRC_CLR_CLR_BIT							0

//MAIL RX BIT

#define					RN_COM_MRC_SET_RD_OVER_BIT						1
#define					RN_COM_MRC_CLR_RD_OVER_BIT						0

#define					RN_COM_MRC_SET_CLR_BIT							1
#define					RN_COM_MRC_CLR_CLR_BIT							0


#define					RN_CNS_LOCAL_ID_SRC_AUTO			0
#define					RN_CNS_LOCAL_ID_SRC_LOCAL			1

#define					RN_CNS_SYNC_OFF						0
#define					RN_CNS_SYNC_ON						1

#define					RN_CNS_DEVICE_ID_UPLIMIT			255
#define					RN_CNS_DEVICE_ID_DOWNLIMIT			0

/////////////////////////////////////

#pragma pack(1)
/////////////REG_RN_PORT_STATUS//////////////////
typedef struct
{
	Uint16				link_up_a : 1;//status[0] = link_up; ��·ͨ��1�����ӣ�0���Ͽ�
	Uint16				offset_valid_a : 1;//status[1] = OFFSET_VALID;1��ƫ����OK
	Uint16				clock_speed_a : 2;//status[3:2] = clock_speed; 2'b10 : ǧ�ף�2'b01:���ף�2��b11:485

	Uint16				duplex_status_a : 1;//status[4] = duplex_status;1��˫����0������
	Uint16				link_status_a : 1;//status[5] = link_status;����ͨ��1������0���Ͽ�
	Uint16				overflow_a : 1;//status[6]=overflow,���������־����ֵ��Ҫclr�������
	Uint16				watch_link_a : 1;//

	Uint16				link_up_b : 1;//
	Uint16				offset_valid_b : 1;//
	Uint16				clock_speed_b : 2;//
	//
	Uint16				duplex_status_b : 1;//
	Uint16				link_status_b : 1;//
	Uint16				overflow_b : 1;//
	Uint16				watch_link_b : 1;//

	Uint16				rsvd_bit16to31 : 16;//
}REG_RN_PORT_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_PORT_STATUS_BIT bit;
}REG_RN_PORT_STATUS;

///////////////REG_RN_NET_RUN_STATUS//////////////////
typedef struct
{
	Uint16				dc_status : 2;//00���ر�״̬ 	01������״̬		10��ƫ�����		11�����ڴ���
	Uint16				sync_on : 1;//��ֵֻ����վ���Բ�����Ч������վ���޸ĸ�ֵ�����塣��վд1ʹ��ϵͳ��ͬ�����ܡ�	1��ͬ������	0��û��ͬ��
	Uint16				mac_tx_overflow_a : 1;//1:macport_a��������ȡfifo oveflow���������clr���

	Uint16				mac_tx_underflow_a : 1;//1:macport_a��������ȡfifo underflow���������clr���
	Uint16				mac_tx_packet_err_a : 1;//1:mac port_a�����������"���������clr���
	Uint16				local_id_src : 1;//��ֵ�����ڱ����޸ģ���������û�й���ǰ��0�Զ����䣬1���ط��� 0 : auto, 1 : local

	Uint16				offset_calc_rst : 1;//

	Uint16				rsvd_bit8to9 : 2;

	Uint16				rollback_valid : 1;

	Uint16				mac_tx_overflow_b : 1;
	Uint16				mac_tx_underflow_b : 1;
	Uint16				mac_tx_packet_err_b : 1;

	Uint16				station_ready : 1;

	Uint16				master_flag : 1;//1����ʾ��վ��Ϊ��վ������Ϊ��վ

	Uint16				rsvd_bit16to31 : 16;//
}REG_RN_NET_RUN_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_NET_RUN_STATUS_BIT bit;
}REG_RN_NET_RUN_STATUS;


////////////////REG_RN_SYNC_CYCLE/////////////////////////////
typedef struct
{
	Uint16				sync_cycle : 16;//ֻ����վ�����޸ģ�����վ��ֻ����
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_SYNC_CYCLE_BIT;


typedef union
{
	Uint32 all;
	REG_RN_SYNC_CYCLE_BIT bit;
}REG_RN_SYNC_CYCLE;


////////////////REG_RN_ONLINE_MSG/////////////////////////////
typedef struct
{
	Uint8				device_id : 8;//��local_id_srcΪ�Զ�����ʱ����ֵ�Զ�����ֵ�������ֵ��д��	���Զ�����ʱ��auto_id = 8'hf0;��ʾ��û�з��䡣

	Uint8				device_num : 8;//����վ������������Լ�����
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_ONLINE_MSG_BIT;

typedef union
{
	Uint32 all;
	REG_RN_ONLINE_MSG_BIT bit;
}REG_RN_ONLINE_MSG;

////////////////REG_RN_CRC_OK_CNT_A_L/////////////////////////////
typedef struct
{
	Uint16				crc_ok_cnt_a_l : 16;//�ڲ�����֤crc_ok_cnt_a[15:0]��crc_ok_cnt_a[31:16]��һ���ԡ�
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_OK_CNT_A_L_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CRC_OK_CNT_A_L_BIT bit;

}REG_RN_CRC_OK_CNT_A_L;


////////////////REG_RN_CRC_OK_CNT_A_H/////////////////////////////
typedef struct
{
	Uint16				crc_ok_cnt_a_h : 16;//�ڲ�����֤crc_ok_cnt_a[15:0]��crc_ok_cnt_a[31:16]��һ���ԡ�
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_OK_CNT_A_H_BIT;


typedef union
{
	Uint32 all;
	REG_RN_CRC_OK_CNT_A_H_BIT bit;

}REG_RN_CRC_OK_CNT_A_H;


////////////////REG_RN_CRC_ERR_CNT_A/////////////////////////////
typedef struct
{
	Uint16				crc_err_cnt_a : 16;//��ֵ��¼�ϵ��Ĵ����ۼƣ��������
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_ERR_CNT_A_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CRC_ERR_CNT_A_BIT bit;
}REG_RN_CRC_ERR_CNT_A;

///////////////REG_RN_STATION_MSG/////////////////////////////
typedef struct
{
	Uint16				station_msg : 16;
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_STATION_MSG_BIT;

typedef union
{
	Uint32 all;
	REG_RN_STATION_MSG_BIT bit;
}REG_RN_STATION_MSG;

////////////////REG_RN_CRC_OK_CNT_B_L/////////////////////////////
typedef struct
{
	Uint16				crc_ok_cnt_b_l : 16;//
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_OK_CNT_B_L_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CRC_OK_CNT_B_L_BIT bit;

}REG_RN_CRC_OK_CNT_B_L;
////////////////REG_RN_CRC_OK_CNT_B_H/////////////////////////////
typedef struct
{
	Uint16				crc_ok_cnt_b_h : 16;
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_OK_CNT_B_H_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CRC_OK_CNT_B_H_BIT bit;
}REG_RN_CRC_OK_CNT_B_H;


////////////////REG_RN_CRC_ERR_CNT_B/////////////////////////////
typedef struct
{
	Uint16				crc_err_cnt_b : 16;
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_CRC_ERR_CNT_B_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CRC_ERR_CNT_B_BIT bit;

}REG_RN_CRC_ERR_CNT_B;

////////////////REG_RN_STATION_ID/////////////////////////////
typedef struct
{
	Uint8				station_id_auto : 8;
	Uint8				station_id_set : 8;
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_STATION_ID_BIT;

typedef union
{
	Uint32 all;
	REG_RN_STATION_ID_BIT bit;

}REG_RN_STATION_ID;

///////////////////FPGA DMA////////////////////////////
////////////////REG_RN_DMA_MAIN_CTRL_STATUS/////////////////////////////
typedef struct
{
	Uint16				pdu_en : 1;//��remote_cfg_en = 1ʱ����ֵ�ɶ���д�����߸�ֵ���ɶ���
	Uint16				remote_cfg_en : 1;//��ֵ����������
	Uint16				clr : 1;//��remote_cfg_en = 1,��ֵ�ɶ���д�����߽��ɶ�����ֵ��Ϊ0���������
	Uint16				pdu_active_err : 1;//1����ʾ��һ������DMAÿһִ����ɣ��ַ����µ����󡣸�ֵ�ᱻ���档��clrд1�����

	Uint16				pdu_check_sum_err : 1;//1����������PDU��������ָ��У��ʹ��󣬸ñ��Ĳ��ᱻ���͡���ֵ�ᱻ���档дclr
	Uint16				pdu_packet_size_zero : 1;//1����������PDU�������ݳ���Ϊ0���ñ��Ĳ��ᱻ���͡���ֵ�ᱻ���档дclr

	Uint16				pdu_tx_map_model : 1;//0:����ԭ��ģʽ��1����ַ+����
	Uint16				pdu_rx_map_model : 1;//0:����ԭ��ģʽ��1����ַ+����
	//
	Uint16				pdu_num : 8;//��ʾÿһ��������Ҫ���͵�PDU���ĸ���	��remote_cfg_en = 1ʱ����ֵ�ɶ���д�����߸�ֵ���ɶ���

	Uint16				rsvd_bit16to31 : 16;//
}REG_RN_DMA_MAIN_CTRL_STATUS_BIT;


typedef union
{
	Uint32 all;
	REG_RN_DMA_MAIN_CTRL_STATUS_BIT bit;
}REG_RN_DMA_MAIN_CTRL_STATUS;

////////////////REG_RN_DMA_CFG_SET_ADDR/////////////////////////////
typedef struct
{
	Uint16				cfg_addr : 16;//����Ҫ����dma��cfg��ʱ����ֵδ�趨�ĵ�ַ��ʼֵ����ÿһ��	����DMA_CFG_OP_DATAʱ���õ�ַ���Զ���1��
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_DMA_CFG_SET_ADDR_BIT;

typedef union
{
	Uint32 all;
	REG_RN_DMA_CFG_SET_ADDR_BIT bit;
}REG_RN_DMA_CFG_SET_ADDR;

////////////////REG_RN_DMA_CFG_OP_DATA/////////////////////////////
typedef struct
{
	Uint16				cfg_data : 16;//ÿһ�ζ�����д����DMA_CFG_OP_DATAʱ��cfg_addr���Լ�1��
	Uint16				rsvd_bit16to31 : 16;
}REG_RN_DMA_CFG_OP_DATA_BIT;

typedef union
{
	Uint32 all;
	REG_RN_DMA_CFG_OP_DATA_BIT bit;
}REG_RN_DMA_CFG_OP_DATA;


//////////////////MODAL CHANGE////////////////////////////
////////////////REG_RN_MODAL_CTRL_STATUS/////////////////////////////
typedef struct
{
	Uint16				ctrl_src : 1;//0 for local, 1 for remote��ֵ���������á�0����ʾ����״̬�ɱ���ַ���ƣ�1����ʾ����״̬��Զ�̿��ơ�
	Uint16				ctrl_src_mask : 1;//��ֵ���������ã�ֻ�и�ֵΪ1ʱ��ctrl_src�Żᱻ�޸�
	Uint16				change_en : 1;//����ֵΪ1��ģ̬�л��Ż���Ч����state����IDLE����Ч��������ֹͣ�л�
	Uint16				change_en_mask : 1;//����ֵΪ1��change_en�Żᱻ�޸�

	Uint16				state : 3;//�л�״̬��		IDLE = 0,             WILL_CHANGE = 1,			WAIT_TIME = 2,       NORMAL_WAIT_SYNC = 3,      			FAST_WAIT_SYNC = 4   STOP = 5,                OVER = 6;
	Uint16				change_stop : 1;//������normalģʽʱ����status����WILL_CHANGE����WAIT_TIMEʱ������ֹͣ�л�������ʱ����Ч��д1��Ч����ֵ�Զ������

	Uint16				lock_sys_time : 1;//д1���浱ǰϵͳʱ�䣬����sys_time.
	Uint16				lock_type : 1;//0��LOCK_NOW 1: LOCK_SYNC
	Uint16				lock_type_mask : 1;//

	Uint16				rsvd_bit9to15 : 7;//

	Uint16				rsvd_bit16to31 : 16;//
}REG_RN_MODAL_CTRL_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MODAL_CTRL_STATUS_BIT bit;

}REG_RN_MODAL_CTRL_STATUS;
////////////////REG_RN_SYS_TMIE_L////////////////////////////
typedef struct
{
	Uint32				sys_time_l : 16;

	Uint32				rsvd_bit16to31 : 16;
}REG_RN_SYS_TMIE_L_BIT;

typedef union
{
	Uint32 all;
	REG_RN_SYS_TMIE_L_BIT bit;
}REG_RN_SYS_TMIE_L;
////////////////REG_RN_SYS_TMIE_H////////////////////////////
typedef struct
{
	Uint32				sys_time_h : 16;

	Uint32				rsvd_bit16to31 : 16;
}REG_RN_SYS_TMIE_H_BIT;

typedef union
{
	Uint32 all;
	REG_RN_SYS_TMIE_H_BIT bit;

}REG_RN_SYS_TMIE_H;



////////////////REG_RN_FAST_NEXT////////////////////////////
typedef struct
{
	Uint16				fast_next : 16;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_FAST_NEXT_BIT;

typedef union
{
	Uint32 all;
	REG_RN_FAST_NEXT_BIT bit;

}REG_RN_FAST_NEXT;



////////////////REG_RN_NORMAL_NEXT////////////////////////////
typedef struct
{
	Uint16				normal_next : 16;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_NORMAL_NEXT_BIT;

typedef union
{
	Uint32 all;
	REG_RN_NORMAL_NEXT_BIT bit;

}REG_RN_NORMAL_NEXT;


////////////////REG_RN_CHANGE_TIME_L////////////////////////////
typedef struct
{
	Uint32				change_time_l : 16;

	Uint32				rsvd_bit16to31 : 16;
}REG_RN_CHANGE_TIME_L_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CHANGE_TIME_L_BIT bit;
}REG_RN_CHANGE_TIME_L;


////////////////REG_RN_CHANGE_TIME_H////////////////////////////
typedef struct
{
	Uint32				change_time_h : 16;

	Uint32				rsvd_bit16to31 : 16;
}REG_RN_CHANGE_TIME_H_BIT;

typedef union
{
	Uint32 all;
	REG_RN_CHANGE_TIME_H_BIT bit;

}REG_RN_CHANGE_TIME_H;



////////////////REG_RN_MODAL_NOW////////////////////////////
typedef struct
{
	Uint16				modal_now : 16;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_MODAL_NOW_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MODAL_NOW_BIT bit;
}REG_RN_MODAL_NOW;

////////////////////PDU_CTRL MAIL_CTRL//////////////////////////////////////
////////////////REG_RN_PDU_TX_CTRL////////////////////////////
typedef struct
{
	Uint16				clr : 1;//д1���PDU_TX_STATUS����״̬λ
	Uint16				rsvd_bit1to11 : 11;//

	Uint16				active : 1;//����WAIT_ACTIVEģʽ��д1��Ч��������һ�η��ͣ���buffer�����������ı��Ķ����ͳ�ȥ��ֱ��buffer�ղ�ֹͣ
	Uint16				data_valid : 1;//д1��һ���������ķ��Ѿ�����FPGA

	Uint16				model : 2;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_PDU_TX_CTRL_BIT;

typedef union
{
	Uint32 all;
	REG_RN_PDU_TX_CTRL_BIT bit;

}REG_RN_PDU_TX_CTRL;


////////////////REG_RN_PDU_TX_STATUS////////////////////////////
typedef struct
{
	Uint16				bf_cnt : 11;//��ǰbuffer��ʹ��״̬
	Uint16				rsvd_bit11 : 1;

	Uint16				underflow : 1;///1���������������͵�ʱ����ִ���
	Uint16				overflow : 1;//1��buffer overflow��clr���

	Uint16				model : 2;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_PDU_TX_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_PDU_TX_STATUS_BIT bit;

}REG_RN_PDU_TX_STATUS;

////////////////REG_RN_MAIL_TX_CTRL////////////////////////////
typedef struct
{
	Uint16				clr : 1;//д1�������MAIL_TX_STATUS״̬λ��
	Uint16				rsvd_bit1to10 : 10;

	Uint16				mail_req : 1;//д1��ʾ��������һ��mailbox����
	Uint16				rsvd_bit12 : 1;
	Uint16				data_valid : 1;//д1��һ���������ķ��Ѿ�����FPGA��

	Uint16				rsvd_bit14to15 : 2;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_MAIL_TX_CTRL_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MAIL_TX_CTRL_BIT bit;

}REG_RN_MAIL_TX_CTRL;


////////////////REG_RN_MAIL_TX_STATUS////////////////////////////
typedef struct
{
	Uint16				rx_bus_arb : 4;//��ǰrx bus�����������ߡ���rx_bus_arb���λΪ1���Ǳ�ʾ��ǰ�������mailbox������Ϊpdu����������£�rx_bus_arb[2]��Ϊ0

	Uint16				rsvd_bit4 : 1;

	Uint16				tx_bus_arb : 2;
	Uint16				tx_mail_bus_arb : 2;
	Uint16				tx_mail_req_ing : 1;//��ǰͨ����������tx mailbox����

	Uint16				mail_over : 1;//1���ñ����Ѿ����������硣

	Uint16				mail_ready : 1;//1�����mailboxȨ�ޣ�����PFGA�����ա�
	Uint16				underflow : 1;//1���������������͵�ʱ����ִ���
	Uint16				overflow : 1;//1��buffer overflow��clr���


	Uint16				rx_mail_bus_arb : 2;//��ǰrx mailbox����������

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_MAIL_TX_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MAIL_TX_STATUS_BIT bit;

}REG_RN_MAIL_TX_STATUS;


///////////
////////////////REG_RN_PDU_RX_CTRL////////////////////////////
typedef struct
{
	Uint16				clr : 1;//д1�������״̬λ�����⣬���buffer���б��ģ���ͬʱ����ñ���
	Uint16				rd_over : 1;//

	Uint16				rsvd_bit2to15 : 14;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_PDU_RX_CTRL_BIT;


typedef union
{
	Uint32 all;
	REG_RN_PDU_RX_CTRL_BIT bit;
}REG_RN_PDU_RX_CTRL;

////////////////REG_RN_PDU_RX_STATUS////////////////////////////
typedef struct
{
	Uint16				bf_cnt : 11;//��ǰbuffer��ʹ��״̬
	//  [4/5/2017 googol]
	Uint16				packet_cnt : 5;//��ǰbuffer�����������������ĸ���
	// 		Uint16				packet_cnt			: 4;//��ǰbuffer�����������������ĸ���
	// 
	// 		Uint16				rsvd_bit15			: 1;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_PDU_RX_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_PDU_RX_STATUS_BIT bit;

}REG_RN_PDU_RX_STATUS;

////////////////REG_RN_MAIL_RX_CTRL////////////////////////////
typedef struct
{
	Uint16				clr : 1;//д1�������״̬λ�����⣬���buffer���б��ģ���ͬʱ����ñ���
	Uint16				rd_over : 1;

	Uint16				rsvd_bit2to15 : 14;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_MAIL_RX_CTRL_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MAIL_RX_CTRL_BIT bit;

}REG_RN_MAIL_RX_CTRL;


////////////////REG_RN_MAIL_RX_STATUS////////////////////////////
typedef struct
{
	Uint16				rx_mail_valid : 1;//ָʾ�Ƿ��б��ĵȴ�����
	Uint16				dll_rx_num : 10;

	Uint16				rsvd_bit11to15 : 5;

	Uint16				rsvd_bit16to31 : 16;
}REG_RN_MAIL_RX_STATUS_BIT;

typedef union
{
	Uint32 all;
	REG_RN_MAIL_RX_STATUS_BIT bit;
}REG_RN_MAIL_RX_STATUS;

//////////////////////////////////////
struct COMMON_NET_STATUS
{
	REG_RN_PORT_STATUS		m_port_status;
	REG_RN_NET_RUN_STATUS	m_net_run_status;
	REG_RN_SYNC_CYCLE		m_sync_cycle;
	REG_RN_ONLINE_MSG		m_online_msg;
	REG_RN_CRC_OK_CNT_A_L	m_crc_ok_cnt_a_l;
	REG_RN_CRC_OK_CNT_A_H	m_crc_ok_cnt_a_h;
	REG_RN_CRC_ERR_CNT_A	m_crc_err_cnt_a;
	REG_RN_STATION_MSG		m_station_msg;

	REG_RN_CRC_OK_CNT_B_L	m_crc_ok_cnt_b_l;
	REG_RN_CRC_OK_CNT_B_H	m_crc_ok_cnt_b_h;
	REG_RN_CRC_ERR_CNT_B	m_crc_err_cnt_b;
	REG_RN_STATION_ID		m_station_id;
};

struct FPGA_DMA
{
	REG_RN_DMA_MAIN_CTRL_STATUS		m_dma_main_ctrl_status;
	REG_RN_DMA_CFG_SET_ADDR			m_dma_cfg_set_addr;
	REG_RN_DMA_CFG_OP_DATA			m_dma_cfg_op_data;
};

struct MODAL_CHANGE
{
	REG_RN_MODAL_CTRL_STATUS		m_modal_ctrl_status;
	REG_RN_SYS_TMIE_L				m_sys_time_l;
	REG_RN_SYS_TMIE_H				m_sys_time_h;
	REG_RN_FAST_NEXT				m_fast_next;
	REG_RN_NORMAL_NEXT				m_normal_next;
	REG_RN_CHANGE_TIME_L			m_change_time_l;
	REG_RN_CHANGE_TIME_H			m_change_time_h;
	REG_RN_MODAL_NOW				m_modal_now;
};

//  [6/23/2016 googol]
////
//////////////////////INT_MSG////////////////////////////////////////////////////
typedef struct
{
	//////////////////////////////////
	Uint8				pdu_rx_valid : 1; // 
	Uint8				pdu_tx_valid : 1;
	Uint8				mail_rx_valid : 1; //
	Uint8				rsvd_bit3to7 : 5;

	Uint8				round_valid : 1;
	Uint8				fine_valid : 1;
	Uint32				rsvd_bit10to31 : 22;

}REG_NET_INT_MSG_BIT;


typedef union
{
	Uint32 all;
	REG_NET_INT_MSG_BIT bit;

}REG_NET_INT_MSG;
//  [6/23/2016 googol]

//////////////////////////////

typedef struct
{
	Uint32 data0;
	Uint32 data1;
}PACKET_HEAD_ALL;

typedef union
{
	Uint8			des_id : 8;
	Uint8			src_id : 8;
}PACKET_HEAD_ID;

typedef struct
{
	Uint8				checksum : 8;// this var isn't used in rx/tx packet, except pdu dma cfg
	PACKET_HEAD_ID		id;             //����ԴID/Ŀ��ID��

	Uint8				len_bit8 : 1;//�����������ݳ���1λ
	Uint8				des_ch : 3;//the ch which  ����FPGA DMAͨ����user[2:0]����Ϊ0��	user[5:3]����DSPͨ��������
	Uint8				src_ch : 3;//����FPGA DMAͨ����user[2:0]����Ϊ0��	user[5:3]����DSPͨ��������
	Uint8				rsvd_bit7_a : 1;//

	Uint8				len_low : 8;//�����������ݳ��ȵ�8λ
	//////////////////////////////////
	Uint8				cmd : 3;/*cmd=0(LWR):�߼�Ѱַд
								cmd=1(AWR):����Ѱַд
								cmd=2(LMWR):�߼���ַӳ����Ѱַд
								cmd=3(TCWR):���ķ���������Ѱַд
								cmd=4(LRD):�߼�Ѱַ��
								cmd=5(ARD):����Ѱַ��
								cmd=6(LMRD):�߼���ַӳ����Ѱַ��
								cmd=7(TCRD):���ķ���������Ѱַ��*/
	Uint8				delta : 1;//delta[0:0]DMA���ʵ�ַ����ֵ 0��ÿ�η���ͬһ����ַ��	1��ÿ�η��ʶ��ۼ�1
	Uint8				resp_req : 1;//resp_req =0:����Ҫ����Ӧ��	resp_req =1:��Ҫ����Ӧ�𡣵�cmd=4,5,6,7,resp_req����Ϊ1.
	Uint8				resp : 1;//
	Uint8				num_bit8 : 1;//
	Uint8				resp_ok : 1;//

	Uint8				num_low : 8;//DMAѰַ����
	Uint16			start_addr;             //DMA������ַ
}PACKET_HEAD_BIT;

typedef union
{
	PACKET_HEAD_ALL all;
	PACKET_HEAD_BIT bit;
}RN_PACKET_HEAD;

typedef struct
{
	Uint8		packet_type; //
	// 								RN_PACKET_TX_MAIL_RD	0
	// 								RN_PACKET_TX_MAIL_WR	1
	// 
	// 								RN_PACKET_RX_MAIL_WR	2
	// 								RN_PACKET_RX_MAIL_WR	3
	// 
	// 								RN_PACKET_TX_PDU_WR		1
	// 								RN_PACKET_RX_PDU_WR		2

	RN_PACKET_HEAD* pHead;
	Uint16		length;
	Uint8		pData[512];
}RN_PACKET;
////////////////PDU DMA/////////////////////
typedef struct
{
	//////////////////////////////////
	Uint8				rd_en : 1; // this bit must be 1 now

	Uint8				rd_delta : 1; //
	Uint8				rd_cmd : 2; //
	Uint8				rsvd_bit4 : 1;
	Uint8				rd_num_src : 1;// 0 decide by inner, 1: by outside
	Uint8				rd_num_bit8 : 1;
	Uint8				rsvd_bit7 : 1;

	Uint8				rd_num_low : 8;
	Uint16			rd_start_addr;
}RN_PACKET_PDU_DMA_CFG_HEAD_BIT;

typedef union
{
	Uint32 data0;
	RN_PACKET_PDU_DMA_CFG_HEAD_BIT bit;

}RN_PACKET_PDU_DMA_CFG_HEAD;

typedef struct
{
	RN_PACKET_PDU_DMA_CFG_HEAD dma_cfg_head;
	RN_PACKET_HEAD packet_head;
}RN_PACKET_PDU_DMA_CFG;

#pragma pack()