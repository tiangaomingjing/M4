#pragma once
//#include "DeviceDataBase.h"
#include "Basetype_def.h"
typedef struct
{
	Uint8 src_id;	// when rd id = src_id, when tx id = des_id; 
	Uint8 src_ch;// when rd ch_id = src_ch, 
	Uint8 cmd;	/*cmd=0(LWR):逻辑寻址写
					cmd = 1(AWR) : 绝对寻址写
					cmd = 2(LMWR) : 逻辑地址映射区寻址写
					cmd = 3(TCWR) : 报文发送配置区寻址写
					cmd = 4(LRD) : 逻辑寻址读
					cmd = 5(ARD) : 绝对寻址读
					cmd = 6(LMRD) : 逻辑地址映射区寻址读
					cmd = 7(TCRD) : 报文发送配置区寻址读 */
	Uint8 resp_req;
	Uint8 resp;	//当数据处理完成后，需要回发。则该值置1.
	Uint8 resp_ok;//
	Uint8 protocol_ext;
	Uint16 length; //有效pData 字节个数
	Uint8* pData;
}
StUserPacket;