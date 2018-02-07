#include "stdafx.h"
#include "Ilink.h"


CIlink::CIlink()
{
	m_pCom = NULL;
	m_des_id = 0;
}


CIlink::~CIlink()
{
	m_pCom = NULL;
}


short CIlink::SendPacket(StIlinkPacket* pPacket,Uint16& dword_num)
{
	if (pPacket == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;

	int16 rtn = pCom->ComWrFpgaHandle(FPGA_RN_ILINK_START_OFST, (int16*)pPacket, dword_num, m_des_id, NULL);
	return rtn;

}
short CIlink::RecivePacket(StIlinkPacket* pPacket, Uint16& dword_num)
{
	if (pPacket == NULL)
	{
		return RTN_NULL_POINT;
	}
	if (m_pCom == NULL) return RTN_NULL_POINT;
	CComBase* pCom = *m_pCom;
	if (pCom == NULL) return RTN_OBJECT_UNCREATED;
	int16 rtn = pCom->ComRdFpgaHandle(FPGA_RN_ILINK_START_OFST, (int16*)pPacket, dword_num, m_des_id, NULL);
	return rtn;

}