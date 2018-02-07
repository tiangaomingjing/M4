//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	base return value define		 									//
//	file				:	BaseReturn_def.h												//
//	Description			:	use for Improving the portability of program				//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		wang.bin(1420)  |	2016/1/20	|	googoltech		|		2016 - 2019			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__GTSD_BASE_RETURN_DEFINE__
#define		__GTSD_BASE_RETURN_DEFINE__

#include "Basetype_def.h"


#define CMD_SUCCESS                     0

#define CMD_ERROR_READ_LEN             -2    /* ��ȡ���ݳ��ȴ��� */
#define CMD_ERROR_READ_CHECKSUM        -3    /* ��ȡ����У��ʹ��� */

#define CMD_ERROR_WRITE_BLOCK          -4    /* д�����ݿ���� */
#define CMD_ERROR_READ_BLOCK           -5    /* ��ȡ���ݿ���� */

#define CMD_ERROR_OPEN                 -6    /* ���豸���� */
#define CMD_ERROR_CLOSE                -6    /* �ر��豸���� */
#define CMD_ERROR_DSP_BUSY             -7    /* DSPæ */

#define CMD_LOCK_ERROR                 -8    /*���߳���Դæ*/

#define CMD_ERROR_EXECUTE               1
#define CMD_ERROR_VERSION_NOT_MATCH     3
#define CMD_ERROR_PARAMETER             7
#define CMD_ERROR_UNKNOWN               8    /* ��֧�ֵ�ָ�� */

#define RTN_SUCCESS						0
#define RTN_MALLOC_FAIL					-100 /* malloc memory fail */
#define RTN_FREE_FAIL					-101 /* free memory or delete the object fail */
#define RTN_NULL_POINT					-102 /* the param point input is null */ 
#define RTN_ERR_ORDER					-103 /* call the function order is wrong, some msg isn't validable */
#define RTN_PCI_NULL					-104 /* the pci address is empty, can't access the pci device*/
#define RTN_PARAM_OVERFLOW				-105 /* the param input is too larget*/
#define RTN_LINK_FAIL					-106 /* the two ports both link fail*/ 
#define RTN_IMPOSSIBLE_ERR				-107 /* it means the system or same function work wrong*/
#define RTN_TOPOLOGY_CONFLICT			-108 /* the id conflict*/
#define RTN_TOPOLOGY_ABNORMAL			-109 /* scan the net abnormal*/
#define RTN_STATION_ALONE				-110 /* the device no id, it means the device id is 0xF0 */
#define RTN_WAIT_OBJECT_OVERTIME		-111 /* multi thread wait for object overtime */
#define RTN_ACCESS_OVERFLOW				-112 /* data[i];  i is larger than the define */
#define RTN_NO_STATION					-113 /* the station accessed not existent */
#define RTN_OBJECT_UNCREATED			-114 /* the object not created yet*/
#define RTN_PARAM_ERR					-115 /* the param input is wrong*/
#define RTN_PDU_CFG_ERR                 -116/*Pdu DMA Cfg Err*/
#define RTN_PCI_FPGA_ERR				-117 /*PCI op err or FPGA op err*/
#define RTN_CHECK_RW_ERR				-118	/*data write to reg, then rd out, and check err */
#define RTN_REMOTE_UNEABLE				-119 /*the device which will be ctrl by net can't be ctrl by net function*/ 

#define RTN_NET_REQ_DATA_NUM_ZERO		-120 /*mail op or pdu op req data num can't be 0*/
#define RTN_WAIT_NET_OBJECT_OVERTIME	-121 /* net op multi thread wait for object overtime */
#define RTN_WAIT_NET_RESP_OVERTIME		-122 /* Can't wait for resp */
#define RTN_WAIT_NET_RESP_ERR			-123 /*wait mailbox op err*/
#define RTN_INITIAL_ERR					-124 /*initial the device err*/
#define RTN_PC_NO_READY					-125 /*find the station'pc isn't work*/ 
#define RTN_STATION_NO_EXIST			-126 
#define RTN_MASTER_FUNCTION				-127 /* this funciton only used by master */

#define RTN_NOT_ALL_RETURN							-128 /* the GT_RN_PtProcessData funciton fail return */
#define RTN_NUM_NOT_EQUAL							-129 /* the station number of RingNet do not equal  the station number of CFG */

#define RTN_CHECK_STATION_ONLINE_NUM_ERR		-130/*Check ģʽ��û�м�⵽վ��*/
#define RTN_FILE_ERR_OPEN						-131/*�ļ���ʧ��*/
#define	RTN_FILE_OPEN_ERR						RTN_FILE_ERR_OPEN	////�ļ���ʧ��
#define RTN_FILE_ERR_FORMAT						-132/*�ļ���������*/
#define RTN_FILE_ERR_MISSMATCH					-133/*�ļ���Ϣ��ʵ����Ϣ��ƥ��*/
#define RTN_DMALIST_ERR_MISSMATCH				-134/*�����ɵ�DMA������Ϣ��û�ҵ���Ӧ��վ��*/

#define RTN_REQUSET_MAIL_BUS_OVERTIME		-150 /*Requset Mail Bus Err*/
#define RTN_INSTRCTION_ERR							-151 /*instrctions err*/
#define RTN_MAIL_RESP_REQ_ERR						-152 /*RN_MailRespReq  err*/
#define RTN_CTRL_SRC_ERR								-153 /* the controlled source  is error */
#define RTN_PACKET_ERR									-154 /*packet is error*/
#define RTN_STATION_ID_ERR							-155 /*the device id is not in the right rang*/
#define RTN_WAIT_NET_PDU_RESP_OVERTIME	- 156 /*net pdu op wait overtime*/
#define RTN_ETHCAT_ENC_POS_ERR					-157/**/

#define RTN_IDLINK_PACKET_ERR				-200 /*ilink master  decode err! packet_length is not match*/
#define RTN_IDLINK_PACKET_END_ERR		-201 /* the ending of ilink packet is not 0xFF*/
#define RTN_IDLINK_TYPER_ERR					-202 /* the type of ilink module is error*/
#define RTN_IDLINK_LOST_CNT 					-203 /* the ilink module has lost connection*/
#define RTN_IDLINK_CTRL_SRC_ERR			-204 /* the controlled source of ilink module is error */
#define RTN_IDLINK_UPDATA_ERR				-205 /* the ilink module updata error*/
#define RTN_IDLINK_NUM_ERR					-206 /* the ilink num larger the IDLINK_MAX_NUM(30) */
#define RTN_IDLINK_NUM_ZERO					-207 /* the ilink num is zero */

#define RTN_NO_PACKET							301 /* no valid packet */
#define RTN_RX_ERR_PDU_PACKET				-302 /* ERR PDU PACKET */
#define RTN_STATE_MECHINE_ERR				-303 
#define RTN_PCI_DSP_UN_FINISH				304
#define RTN_SEND_ALL_FAIL						-305
#define RTN_STATION_CLOSE					310
#define RTN_STATION_RESP_FAIL				311		

#define RTN_UPDATA_MODAL_ERR			-330 /* update the modal in normal way fail*/

#define RTN_NO_MAIL_DATA						340 /*There is no mail data*/
#define RTN_NO_PDU_DATA						341 /*There is no pdu data*/


#define	RTN_VERSION_ERR_RN		-400	//	gt_rn.dll�汾����				
#define	RTN_VERSION_ERR_GTS		-401	//	gts.dll�汾����				
#define	RTN_VERSION_ERR_DMA		-402	//	dma�������ļ��汾����				
#define	RTN_VERSION_ERR_MAP		-403	//	map�������ļ��汾����				
#define	RTN_VERSION_ERR_FPGA	-404	//	FPGA�̼��汾����				
#define	RTN_VERSION_ERR_DSP		-405	//	DSP�̼��汾����				
#define	RTN_VERSION_ERR_CPLD	-406	//	CPLD�̼��汾�汾����				
#define	RTN_VERSION_ERR_FILE	-407	//	���ص��ļ��������ļ���ƥ��				
//#define						    -408    //
//#define						    -409    //
#define	RTN_SYNC_CYLE_LARGE		-410	//	���õ�ͬ�����ڴ��ڿ�֧�ֵ�ͬ������				
#define	RTN_SYNC_CYLE_ERR		-411	//	�������е�ģ�鲻֧��ͬ����������Ϊ500΢��				
#define	RTN_SYNC_CYLE_READ_ERR	-412	//	������ͬ�����ڳ����˹̼�֧�ֵ�ֵ				
//#define						    -413    //
//#define						    -414    //

#define	RTN_VERSION_WARING_RN	400	//gt_rn.dll�汾��������				
#define	RTN_VERSION_WARING_GTS	401	//gts.dll�汾��������				
#define	RTN_VERSION_WARING_DMA	402	//dma�������ļ��汾��������				
#define	RTN_VERSION_WARING_MAP	403	//map�������ļ��汾��������				
#define	RTN_VERSION_WARING_FPGA	404	//FPGA�̼��汾��������				
#define	RTN_VERSION_WARING_DSP	405	//DSP�̼��汾��������				
#define	RTN_VERSION_WARING_CPLD	406	//CPLD�̼��汾�汾��������		


#define RTN_FILE_PARAM_NUM_ERR					-500
#define RTN_FILE_PARAM_LEN_ERR					-501
#define RTN_FILE_MALLOC_FAIL					-502
#define RTN_FILE_FREE_FAIL						-503
#define RTN_FILE_PARAM_ERR						-504
#define RTN_FILE_NOT_EXSITS						505

#define RTN_FILE_CREATE_FAIL					510
#define RTN_FILE_DELETE_FAIL					511
#define RTN_FIFE_CRC_CHECK_ERR					-512

#define RTN_FIFE_FUNCTION_ID_RETURN_ERR			-600

#define RTN_UPDATE_WAIT_OVERTIME				-700
#define RTN_UPDATE_FPGA_OP_ERR					-701
#define RTN_UPDATE_CAMPARE_ERR					-702

#define RTN_DLL_WINCE									-800
#define RTN_DLL_WIN32									-801

#define RTN_XML_STATION_ERR						-900//dma�����ļ���վ�����Ͳ�ƥ��


// 
// 
// typedef enum
// {
// 	RTN_SUCCESS = 0,
// 
// 	RTN_MALLOC_FAIL = -100 , /* malloc memory fail */
// 	RTN_FREE_FAIL = -101 , /* free memory or delete the object fail */
// 	RTN_NULL_POINT = -102 , /* the param point input is null */
// 	RTN_ERR_ORDER = -103 , /* call the function order is wrong, some msg isn't validable */
// 	RTN_PCI_NULL = -104 , /* the pci address is empty, can't access the pci device*/
// 	RTN_PARAM_OVERFLOW = -105 , /* the param input is too larget*/
// 	RTN_LINK_FAIL = -106 , /* the two ports both link fail*/
// 	RTN_IMPOSSIBLE_ERR = -107 , /* it means the system or same function work wrong*/
// 	RTN_TOPOLOGY_CONFLICT = -108 , /* the id conflict*/
// 	RTN_TOPOLOGY_ABNORMAL = -109 , /* scan the net abnormal*/
// 	RTN_STATION_ALONE = -110 , /* the device no id, it means the device id is 0xF0 */
// 	RTN_WAIT_OBJECT_OVERTIME = -111 , /* multi thread wait for object overtime */
// 	RTN_ACCESS_OVERFLOW = -112 , /* data[i];  i is larger than the define */
// 	RTN_NO_STATION = -113 , /* the station accessed not existent */
// 	RTN_OBJECT_UNCREATED = -114 , /* the object not created yet*/
// 	 RTN_PARAM_ERR = -115 , /* the param input is wrong*/
// 		// RTN_NO_PDU_CFG                    -116, /*No Pdu Cfg*/
// 	RTN_PCI_FPGA_ERR = -117 , /*PCI op err or FPGA op err*/
// 	RTN_CHECK_RW_ERR = -118	, /*data write to reg, then rd out, and check err */
// 	RTN_REMOTE_UNEABLE	= -119 , /*the device which will be ctrl by net can't be ctrl by net function*/ 
// 
// 	RTN_NET_REQ_DATA_NUM_ZERO	=	-120 , /*mail op or pdu op req data num can't be 0*/
// 	RTN_WAIT_NET_OBJECT_OVERTIME =	-121 , /* net op multi thread wait for object overtime */
// 	RTN_WAIT_NET_RESP_OVERTIME	=	-122 , /* Can't wait for resp */
// 	RTN_WAIT_NET_RESP_ERR			=	-123 , /*wait mailbox op err*/
// 	RTN_INITIAL_ERR				=	-124 , /*initial the device err*/
// 	RTN_PC_NO_READY				=	-125 , /*find the station'pc isn't work*/ 
// 	RTN_STATION_NO_EXIST	=		-126, 
// 	RTN_MASTER_FUNCTION	=			-127 , /* this funciton only used by master */
// 
// 	RTN_NOT_ALL_RETURN		=			-128 , /* the GT_RN_PtProcessData funciton fail return */
// 	RTN_REQUSET_MAIL_BUS_OVERTIME =	-150 , /*Requset Mail Bus Err*/
// 	RTN_INSTRCTION_ERR		=					-151 , /*instrctions err*/
// 	RTN_MAIL_RESP_REQ_ERR	=				-152 , /*RN_MailRespReq  err*/
// 	RTN_CTRL_SRC_ERR		=						-153 , /* the controlled source  is error */
// 	RTN_PACKET_ERR			=						-154 , /*packet is error*/
// 	RTN_STATION_ID_ERR		=					-155 , /*the device id is not in the right rang*/
// 	RTN_WAIT_NET_PDU_RESP_OVERTIME = - 156 , /*net pdu op wait overtime*/
// 
// 	RTN_IDLINK_PACKET_ERR		=		-200 , /*ilink master  decode err! packet_length is not match*/
// 	RTN_IDLINK_PACKET_END_ERR	=	-201 , /* the ending of ilink packet is not 0xFF*/
// 	RTN_IDLINK_TYPER_ERR		=		-202 , /* the type of ilink module is error*/
// 	RTN_IDLINK_LOST_CNT 		=		-203 , /* the ilink module has lost connection*/
// 	RTN_IDLINK_CTRL_SRC_ERR	=		-204 , /* the controlled source of ilink module is error */
// 	RTN_IDLINK_UPDATA_ERR		=	-205 , /* the ilink module updata error*/
// 	RTN_IDLINK_NUM_ERR			=	-206 , /* the ilink num larger the IDLINK_MAX_NUM(30) */
// 	RTN_IDLINK_NUM_ZERO		=		-207 , /* the ilink num larger the IDLINK_MAX_NUM(30) */
// 
// 	RTN_NO_PACKET				=	301 , /* no valid packet */
// 	RTN_RX_ERR_PDU_PACKET		=	-302 , /* ERR PDU PACKET */
// 	RTN_STATE_MECHINE_ERR		=	-303, 
// 	RTN_PCI_DSP_UN_FINISH		=	304,
// 	RTN_SEND_ALL_FAIL			=	-305,
// 	RTN_STATION_CLOSE			=	310,
// 	RTN_STATION_RESP_FAIL		=	311	,	
// 
// 	RTN_UPDATA_MODAL_ERR		=	-330 ,/* update the modal in normal way fail*/
// 
// 
// 	RTN_NO_MAIL_DATA =	340, /*There is no mail data*/
// 	RTN_NO_PDU_DATA  =		341, /*There is no pdu data*/
// 
// 
// 
// 
// 	RTN_FILE_PARAM_NUM_ERR		=	-500,
// 	RTN_FILE_PARAM_LEN_ERR		=	-501,
// 	RTN_FILE_MALLOC_FAIL		=	-502,
// 	RTN_FILE_FREE_FAIL			=	-503,
// 	RTN_FILE_PARAM_ERR			=	-504,
// 	RTN_FILE_NOT_EXSITS			=	505,
// 	RTN_FILE_CREATE_FAIL		=	510,
// 	RTN_FILE_DELETE_FAIL		=	511,
// 	RTN_FIFE_CRC_CHECK_ERR		=	-512,
// 	RTN_FIFE_FUNCTION_ID_RETURN_ERR = -600,
// 
// 
// }ENUM_RTN_RETURN;

//#define RTN_SUCCESS				0
//
//#define RTN_MALLOC_FAIL			-100 /* malloc memory fail */
//#define RTN_FREE_FAIL			-101 /* free memory or delete the object fail */
//#define RTN_NULL_POINT			-102 /* the param point input is null */ 
//#define RTN_ERR_ORDER			-103 /* call the function order is wrong, some msg isn't validable */
//#define RTN_PCI_NULL			-104 /* the pci address is empty, can't access the pci device*/
//#define RTN_PARAM_OVERFLOW		-105 /* the param input is too larget*/
//#define RTN_LINK_FAIL			-106 /* the two ports both link fail*/ 
//#define RTN_IMPOSSIBLE_ERR		-107 /* it means the system or same function work wrong*/
//#define RTN_TOPOLOGY_CONFLICT	-108 /* the id conflict*/
//#define RTN_TOPOLOGY_ABNORMAL	-109 /* scan the net abnormal*/
//#define RTN_STATION_ALONE		-110 /* the device no id, it means the device id is 0xF0 */
//#define RTN_WAIT_OBJECT_OVERTIME	-111 /* multi thread wait for object overtime */
//#define RTN_ACCESS_OVERFLOW			-112 /* data[i];  i is larger than the define */
//#define RTN_NO_STATION					-113 /* the station accessed not existent */
//#define RTN_OBJECT_UNCREATED			-114 /* the object not created yet*/
//#define RTN_PARAM_ERR						-115 /* the param input is wrong*/
////#define RTN_NO_PDU_CFG                    -116/*No Pdu Cfg*/
//#define RTN_PCI_FPGA_ERR					-117 /*PCI op err or FPGA op err*/
//#define RTN_CHECK_RW_ERR				-118	/*data write to reg, then rd out, and check err */
//#define RTN_REMOTE_UNEABLE				-119 /*the device which will be ctrl by net can't be ctrl by net function*/ 
//
//#define RTN_NET_REQ_DATA_NUM_ZERO		-120 /*mail op or pdu op req data num can't be 0*/
//#define RTN_WAIT_NET_OBJECT_OVERTIME	-121 /* net op multi thread wait for object overtime */
//#define RTN_WAIT_NET_RESP_OVERTIME		-122 /* Can't wait for resp */
//#define RTN_WAIT_NET_RESP_ERR				-123 /*wait mailbox op err*/
//#define RTN_INITIAL_ERR					-124 /*initial the device err*/
//#define RTN_PC_NO_READY					-125 /*find the station'pc isn't work*/ 
//#define RTN_STATION_NO_EXIST			-126 
//#define RTN_MASTER_FUNCTION				-127 /* this funciton only used by master */
//
//#define RTN_NOT_ALL_RETURN					-128 /* the GT_RN_PtProcessData funciton fail return */
//#define RTN_REQUSET_MAIL_BUS_OVERTIME	-150 /*Requset Mail Bus Err*/
//#define RTN_INSTRCTION_ERR							-151 /*instrctions err*/
//#define RTN_MAIL_RESP_REQ_ERR					-152 /*RN_MailRespReq  err*/
//#define RTN_CTRL_SRC_ERR								-153 /* the controlled source  is error */
//#define RTN_PACKET_ERR									-154 /*packet is error*/
//#define RTN_STATION_ID_ERR							-155 /*the device id is not in the right rang*/
//#define RTN_WAIT_NET_PDU_RESP_OVERTIME - 156 /*net pdu op wait overtime*/
//
//#define RTN_IDLINK_PACKET_ERR				-200 /*ilink master  decode err! packet_length is not match*/
//#define RTN_IDLINK_PACKET_END_ERR		-201 /* the ending of ilink packet is not 0xFF*/
//#define RTN_IDLINK_TYPER_ERR				-202 /* the type of ilink module is error*/
//#define RTN_IDLINK_LOST_CNT 				-203 /* the ilink module has lost connection*/
//#define RTN_IDLINK_CTRL_SRC_ERR			-204 /* the controlled source of ilink module is error */
//#define RTN_IDLINK_UPDATA_ERR			-205 /* the ilink module updata error*/
//#define RTN_IDLINK_NUM_ERR				-206 /* the ilink num larger the IDLINK_MAX_NUM(30) */
//#define RTN_IDLINK_NUM_ZERO				-207 /* the ilink num larger the IDLINK_MAX_NUM(30) */
//
//#define RTN_NO_PACKET					301 /* no valid packet */
//#define RTN_RX_ERR_PDU_PACKET			-302 /* ERR PDU PACKET */
//#define RTN_STATE_MECHINE_ERR			-303 
//#define RTN_PCI_DSP_UN_FINISH			304
//#define RTN_SEND_ALL_FAIL				-305
//#define RTN_STATION_CLOSE				310
//#define RTN_STATION_RESP_FAIL			311		
//
//#define RTN_UPDATA_MODAL_ERR			-330 /* update the modal in normal way fail*/
//
//
//#define RTN_NO_MAIL_DATA	340 /*There is no mail data*/
//#define RTN_NO_PDU_DATA		341 /*There is no pdu data*/
//
#define MAX_STATION_NUM 256
#define IDLINK_NUM_MAX     30 /*ÿ������һ�����ܴ���ģ�������Ŀ*/
//
//
//#define RTN_FILE_PARAM_NUM_ERR			-500
//#define RTN_FILE_PARAM_LEN_ERR			-501
//#define RTN_FILE_MALLOC_FAIL			-502
//#define RTN_FILE_FREE_FAIL				-503
//#define RTN_FILE_PARAM_ERR				-504
//#define RTN_FILE_NOT_EXSITS				505
//#define RTN_FILE_CREATE_FAIL			510
//#define RTN_FILE_DELETE_FAIL			511
//#define RTN_FIFE_CRC_CHECK_ERR			-512
//#define RTN_FIFE_FUNCTION_ID_RETURN_ERR -600


const int32			Rt_Success					=	0x0000;					//ͨ�÷��سɹ�

//-------------------------------------------------------------------------------------------------
//pcdebug Э��ʹ�� ����ethcatЭ����Զ������Э��

const int32			Net_Rt_Execute_Fail			=	0x0001;					//dsp�����ִ�д���
const int32			Net_Rt_Execute_Success		=	0x0002;					//dsp�����ִ�гɹ�
const int32			Net_Rt_Parameter_invalid	=   0x0003;					//dsp����ز�����Ч
const int32			Net_Rt_Instruction_invalid	=	0x0004;					//dsp�����ָ����Ч
const int32			Net_Rt_Other_Error			=	0x0005;					//dsp�����ָ����Ч

const int32 		Net_Rt_Index_Unmatch		=	0x0006;					//����ֵƥ��ʧ��
const int32 		Net_Rt_Receive_Unknow_Data	=	0x0007;					//δ֪��������
const int32 		Net_Rt_Receive_DLenth_short =	0x0008;					//�������ݳ��ȹ���

const int32 		Net_Rt_Not_Find_Net_Device	=	0x0009;					//û���ҵ������豸
const int32 		Net_Rt_Not_Get_Net_DevList	=	0x000A;					//�������豸�б�ʧ��
const int32 		Net_Rt_Adapter_Not_Match	=	0x000B;					//�豸�б��е����ƺ��豸��ƥ��
const int32 		Net_Rt_Open_Device_Err		=	0x000C;                 //�������豸����
const int32 		Net_Rt_Complie_Err			=	0x000d;					//�������
const int32 		Net_Rt_SetFilter_Err		=	0x000e;					//�����˲�������

const int32 		Net_Rt_Send_Err				=	0x000f;                 //�����ʧ��
const int32 		Net_Rt_Receive_Err			=	0x0010;				    //��������ʧ��

const int32			Net_Rt_Not_Enough_Space		=	0x0011;					//�����������ռ䲻��
const int32 		Net_Rt_Net_DevListLenth_Err =	0x0012;					//�����豸�б��ȴ���
const int32 		Net_Rt_Pointer_Invalid		=	0x0013;				    //����ָ����Ч
const int32 		Net_Rt_MBTOWC_Err			=	0x0014;					//���ֽ�ת��Ϊ���ַ�����
const int32 		Net_Rt_Not_Find_ScanDevice	=	0x0015;					//û�д�ɨ�赽���豸�б����ҵ�����Ӧ���豸
const int32 		Net_Rt_Send_Data_TooLong	=	0x0016;					//�������ݳ��ȳ���1023��bytes��
const int32 		Net_Rt_Timeout				=	0x0017;					//�ȴ���ʱ
const int32 		Net_Rt_Mac_Err				=	0x0018;					//MAC��ַ����
const int32 		Net_Rt_Flag_Err				=	0x0019;					//��д��ɱ�־λδ��
const int32 		Net_Rt_CreateObj_Err		=	0x001A;					//�����������

const int32 		Net_Rt_Lock_Err				=	0x001B;					//LOCK ERR
const int32 		Net_Rt_param_Err			=	0x001c;					//param ERR

const int32			Net_Rt_SerialPort_Err		=	0x001d;					//serial port ERR   
const int32			Net_Rt_eeprom_Err			=	0x001e;					//eeprom port ERR

//--------------------------------------------------------------------------------------------

//�Ȼ������ض���

const int32 		RN_Rt_Receive_DLenth_short	= 0x0008;					//�������ݳ��ȹ���
const int32 		RN_Net_Rt_Send_Data_TooLong	= 0x0016;					//�������ݳ��ȹ���
const int32 		RN_Net_Rt_Send_Err			= 0x000f;					//�����ʧ��
const int32 		RN_Net_Rt_Timeout			= 0x0017;					//�ȴ���ʱ
const int32 		RN_Net_Rt_CreateObj_Err		= 0x001A;					//�����������
const int32 		RN_Net_Rt_Complie_Err		= 0x000d;					//�������
const int32 		RN_Net_Rt_SetFilter_Err		= 0x000e;					//�����˲�������


//socket���ض���

const int32 		SOCKET_Rt_CreateObj_Err		= 0x001A;					//�����������
const int32 		SOCKET_Rt_Open_Device_Err	= 0x000C;					//�������豸����
const int32 		SOCKET_Rt_Com_Err			= 0x001F;					//socketͨ�ų���
const int32 		SOCKET_Rt_Timeout			= 0x0017;					//�ȴ���ʱ
const int32 		SOCKET_Rt_Send_Err			= 0x000f;					//�����ʧ��

#endif