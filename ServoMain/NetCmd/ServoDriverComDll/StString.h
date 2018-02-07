#pragma once
#ifdef SERVODRIVERCOMDLL_EXPORTS
#define SERVODRIVERCOMDLL_API __declspec(dllexport)
#else
#define SERVODRIVERCOMDLL_API __declspec(dllimport)
#endif

#define ST_STRING_MAX_SIZE 300

class SERVODRIVERCOMDLL_API StString
{
public:
	StString(void);
	StString(StString &a);
	StString(LPCTSTR a);
	~StString(void);
public:

protected:
	//	WCHAR* m_pData;
	WCHAR  m_pData[ST_STRING_MAX_SIZE + 1];
	int m_len;//cnt in WCHAR;
public:
	void Clear();
	LPCTSTR GetLPCSTR();
	short SetStSting(LPCTSTR pSrca);

	friend short SearchWCHARIndexBackward(CONST WCHAR* pCharA, short len, WCHAR tag);
	friend short SearchWCHARIndexForward(CONST WCHAR* pCharA, short len, WCHAR tag);
	friend short GetLPCSTRLen(LPCTSTR pSrca, short* len);

	inline short GetStStringLen();

	short LpStrAdd(LPCTSTR pSrca, LPCTSTR pSrcb);

	//////////////////////////////////////////////////////////////////////////
	friend StString GetSubString(const StString& a, unsigned short beg, unsigned short end);//[beg, end]
	//////////////////////////////////////////////////////////////////////////
	void operator = (StString& a);
	void operator = (LPCTSTR pSrca);

	void operator += (StString& a);
	void operator += (LPCTSTR pSrca);
	friend StString operator + (StString& a, StString& b);
	friend StString operator + (LPCTSTR a, StString& b);
	friend StString operator + (StString& a, LPCTSTR b);
	friend bool operator == (StString& a, StString& b);

	//////////////////////////////////////////////////////////////////////////
	friend short GetFilePathFileName(LPCTSTR pSrca, StString& path, StString& file);

};

