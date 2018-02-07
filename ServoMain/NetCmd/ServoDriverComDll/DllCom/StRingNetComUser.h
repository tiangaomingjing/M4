#pragma once
//#include "DeviceDataBase.h"
#include "Basetype_def.h"
typedef struct
{
	Uint8 src_id;	// when rd id = src_id, when tx id = des_id; 
	Uint8 src_ch;// when rd ch_id = src_ch, 
	Uint8 cmd;	/*cmd=0(LWR):�߼�Ѱַд
					cmd = 1(AWR) : ����Ѱַд
					cmd = 2(LMWR) : �߼���ַӳ����Ѱַд
					cmd = 3(TCWR) : ���ķ���������Ѱַд
					cmd = 4(LRD) : �߼�Ѱַ��
					cmd = 5(ARD) : ����Ѱַ��
					cmd = 6(LMRD) : �߼���ַӳ����Ѱַ��
					cmd = 7(TCRD) : ���ķ���������Ѱַ�� */
	Uint8 resp_req;
	Uint8 resp;	//�����ݴ�����ɺ���Ҫ�ط������ֵ��1.
	Uint8 resp_ok;//
	Uint8 protocol_ext;
	Uint16 length; //��ЧpData �ֽڸ���
	Uint8* pData;
}
StUserPacket;