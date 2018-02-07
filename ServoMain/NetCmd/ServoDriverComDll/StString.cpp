#include "stdafx.h"
#include "StString.h"


StString::StString(void)
{
	m_len = 0;
}
StString::StString(StString &a)
{
	short len = a.GetStStringLen();
	if (len == 0)
	{
		m_len = 0;
	}
	//////////////////////////////////////////////////////////////////////////
	if (len > ST_STRING_MAX_SIZE) return;
	memcpy(m_pData, a.GetLPCSTR(), (len + 1)*sizeof(WCHAR));
	m_len = len;
}


StString::StString(LPCTSTR a)
{
	if (a == NULL)
	{
		m_len = 0;
	}
	else
	{
		short len = 0;
		GetLPCSTRLen(a, &len);
		if (len > ST_STRING_MAX_SIZE) return;
		m_len = len;
		memcpy(m_pData, a, sizeof(WCHAR)*(m_len + 1));
	}
}
StString::~StString(void)
{
}

void StString::Clear()
{
	m_len = 0;
}
LPCTSTR StString::GetLPCSTR()
{
	return (LPCTSTR)m_pData;
}

short StString::SetStSting(LPCTSTR pSrca)
{
	short len_a = 0;
	if (pSrca == NULL)
	{
		m_len = 0;
		return 0;
	}

	GetLPCSTRLen(pSrca, &len_a);
	CONST WCHAR* pCharA = (CONST WCHAR*)(pSrca);
	if (len_a > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////
	memcpy(m_pData, pCharA, sizeof(WCHAR)*(len_a + 1));
	m_len = len_a;
	return 0;
}

short SearchWCHARIndexBackward(CONST WCHAR* pCharA, short len, WCHAR tag)
{
	for (short i = len - 1; i >= 0; i--)
	{
		if (pCharA[i] == tag)
		{
			return i;
		}
	}
	return -1;
};

short SearchWCHARIndexForward(CONST WCHAR* pCharA, short len, WCHAR tag)
{
	for (short i = 0; i < len; i++)
	{
		if (pCharA[i] == tag)
		{
			return i;
		}
	}
	return -1;
};

short GetFilePathFileName(LPCTSTR pSrca, StString& path, StString& file)
{
	short len_a = 0;
	if (pSrca == NULL)
	{
		path.Clear();
		file.Clear();
		return 0;
	}
	else GetLPCSTRLen(pSrca, &len_a);

	short index = SearchWCHARIndexBackward((CONST WCHAR*)(pSrca), len_a, L'\\');
// 	short index = SearchWCHARIndexBackward((CONST WCHAR*)(pSrca), len_a, L'.');
// 	if (index == -1) //find not file name
// 	{
// 		if (len_a > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////
// 		memcpy(path.m_pData, (CONST WCHAR*)(pSrca), sizeof(WCHAR)*(len_a + 1));
// 		path.m_len = len_a;
// 
// 		file.Clear();
// 		return 0;
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 	index = SearchWCHARIndexBackward((CONST WCHAR*)(pSrca), index + 1, L'\\');
	if (index == -1) //only file name
	{
		path.Clear();
		if (len_a > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////
		memcpy(file.m_pData, (CONST WCHAR*)(pSrca), sizeof(WCHAR)*(len_a + 1));
		file.m_len = len_a;
		return 0;
	}
	else
	{
		if (index > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////
		memcpy(path.m_pData, (CONST WCHAR*)(pSrca), sizeof(WCHAR)*(index));
		path.m_pData[index] = 0x0;

		if (len_a - index - 1 > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////
		memcpy(file.m_pData, (CONST WCHAR*)(pSrca)+index + 1, sizeof(WCHAR)*(len_a - index));

		path.m_len = index;
		file.m_len = len_a - index - 1;
		return 0;
	}
}

short StString::LpStrAdd(LPCTSTR pSrca, LPCTSTR pSrcb)
{
	short len_a = 0;
	short len_b = 0;
	short len_c = 0;
	if (pSrca) GetLPCSTRLen(pSrca, &len_a);
	if (pSrcb) GetLPCSTRLen(pSrcb, &len_b);

	CONST WCHAR* pCharA = (CONST WCHAR*)(pSrca);
	CONST WCHAR* pCharB = (CONST WCHAR*)(pSrcb);
	len_c = len_a + len_b;
	if (len_c > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////

	memcpy(m_pData, pCharA, sizeof(WCHAR)*len_a);
	memcpy(m_pData + len_a, pCharB, sizeof(WCHAR)*(len_b + 1));
	return 0;
}


short GetLPCSTRLen(LPCTSTR pSrca, short* len)
{
	if (pSrca == NULL)
	{
		*len = 0;
		return 0;
	}
#ifdef  UNICODE                         // r_winnt
	*len = 0;
	CONST WCHAR* pCharA = (CONST WCHAR*)(pSrca);
	while (pCharA[*len] != 0x0000)
	{
		(*len)++;
	}
	return 0;
#else
	return RTN_IMPOSSIBLE_ERR;
#endif
}
short StString::GetStStringLen()
{
	return m_len;
}
StString GetSubString(const StString& a, unsigned short beg, unsigned short end)//[beg, end]
{
	StString c;
	if (beg < a.m_len && end < a.m_len && beg <= end)
	{
		c.m_len = end - beg + 1;
		memcpy(c.m_pData, a.m_pData + beg, sizeof(WCHAR)*c.m_len);
		c.m_pData[c.m_len] = 0x0;
	}
	return c;
}

void StString::operator = (StString& a)
{
	short len = a.GetStStringLen();
	if (len == 0)
	{
		m_len = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	memcpy(m_pData, a.GetLPCSTR(), (len + 1)*sizeof(WCHAR));
	m_len = len;
}

void StString::operator = (LPCTSTR pSrca)
{
	short len;
	GetLPCSTRLen(pSrca, &len);
	if (len == 0)
	{
		m_len = 0;
		return;
	}
	else
	{
		m_len = len;
		if (len > ST_STRING_MAX_SIZE) return;//////////////////////////////////////////////////////////////////////////
		memcpy(m_pData, pSrca, sizeof(WCHAR)*(len + 1));
		return;
	}

}
void StString::operator += (StString& b)
{
	short len_b = b.GetStStringLen();
	if (len_b == 0) return;

	short len_a = m_len;

	short len_c = len_a + len_b;

	CONST WCHAR* pCharA = (CONST WCHAR*)(m_pData);
	CONST WCHAR* pCharB = (CONST WCHAR*)(b.GetLPCSTR());

	if (len_c > ST_STRING_MAX_SIZE) return;//////////////////////////////////////////////////////////////////////////
	memcpy(m_pData + len_a, pCharB, sizeof(WCHAR)*(len_b + 1));
	m_len = len_c;

	return;

}
void StString::operator += (LPCTSTR pSrca)
{
	short len_b;
	GetLPCSTRLen(pSrca, &len_b);
	if (len_b == 0) return;

	short len_a = m_len;

	short len_c = len_a + len_b;

	CONST WCHAR* pCharA = (CONST WCHAR*)(m_pData);
	CONST WCHAR* pCharB = (CONST WCHAR*)(pSrca);

	if (len_c > ST_STRING_MAX_SIZE) return;//////////////////////////////////////////////////////////////////////////
	memcpy(m_pData + len_a, pCharB, sizeof(WCHAR)*(len_b + 1));
	m_len = len_c;

	return;
}

StString operator + (StString& a, StString& b)
{
	short len_a = a.m_len;
	short len_b = b.m_len;
	if (len_a == 0) return b;
	else if (len_b == NULL) return a;
	else
	{
		StString c;
		c.m_len = len_a + len_b;

		CONST WCHAR* pCharA = (CONST WCHAR*)(a.m_pData);
		CONST WCHAR* pCharB = (CONST WCHAR*)(b.m_pData);
		if (c.m_len > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////

		memcpy(c.m_pData, a.m_pData, sizeof(WCHAR)*len_a);
		memcpy(c.m_pData + len_a, b.m_pData, sizeof(WCHAR)*(len_b + 1));
		return c;
	}
}

StString operator + (LPCTSTR a, StString& b)
{
	short len_a;
	short len_b;
	GetLPCSTRLen(a, &len_a);
	len_b = b.m_len;
	if (len_a == 0) return b;
	else if (len_b == 0) return a;
	else
	{
		StString c;
		c.m_len = len_a + len_b;

		CONST WCHAR* pCharA = (CONST WCHAR*)(a);
		CONST WCHAR* pCharB = (CONST WCHAR*)(b.m_pData);
		if (c.m_len > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////

		memcpy(c.m_pData, a, sizeof(WCHAR)*len_a);
		memcpy(c.m_pData + len_a, b.m_pData, sizeof(WCHAR)*(len_b + 1));
		return c;
	}
	return b;
}
StString operator + (StString& a, LPCTSTR b)
{
	short len_a;
	short len_b;

	len_a = a.m_len;
	GetLPCSTRLen(b, &len_b);
	if (len_a == 0) return b;
	else if (len_b == 0) return a;
	else
	{
		StString c;
		c.m_len = len_a + len_b;

		CONST WCHAR* pCharA = (CONST WCHAR*)(a.m_pData);
		CONST WCHAR* pCharB = (CONST WCHAR*)(b);
		if (c.m_len > ST_STRING_MAX_SIZE) return 0;//////////////////////////////////////////////////////////////////////////

		memcpy(c.m_pData, a.m_pData, sizeof(WCHAR)*len_a);
		memcpy(c.m_pData + len_a, b, sizeof(WCHAR)*(len_b + 1));
		return c;
	}
	return a;
}

bool operator == (StString& a, StString& b)
{
	if (a.m_len == b.m_len)
	{
		return (memcmp(a.m_pData, b.m_pData, (a.m_len + 1)*sizeof(WCHAR)) == 0);
	}
	return false;
}