#pragma once
class CXmlCode
{
public:
	CXmlCode();
	~CXmlCode();

public:

	static const int MAX_SIZE = 256;
	static const int WRITE_BUFFER_SIZE = 1024;

	static const char ENCODE_COLUMN_IN = (char)0x80;
	static const char ENCODE_COLUMN_OUT = (char)0x81;
	static const char ENCODE_ITEM_IN = (char)0x82;
	static const char ENCODE_ITEM_OUT = (char)0x83;
	//const char ENCODE_ITEM = (char)0x84;
	static const char ENCODE_NONE = (char)0x00;
	static const char ENCODE_SPACE = ' ';
	static const char ENCODE_LINE = '\n';

	static const int SIZE_property = 8;
	static const int SIZE_string = 6;
	static const int SIZE_column = 6;
	static const int SIZE_item = 4;
	
protected:
	void* m_pFile_in; //read file
	void* m_pFile_out;//write file

	char buffer[MAX_SIZE];

	int column_cnt;
	int line_cnt;
  const char* str;
//////////////////////////////////////////////////////////////////////////
	char write_buffer[WRITE_BUFFER_SIZE];
	int write_buffer_cnt;

  const char* pData[100];
 	char* gCode;
	int gCode_cnt;
	int gSpaceNum;
	int gCode_num;

	char** m_pEncodeBufferList;
	int* m_pEncodeByteNumList;
	int* m_pEncodeTypeList;
	int m_EncodeNum;

protected:

	short CXmlCode::OpenFile(char* pFileName);
	short CXmlCode::CloseFile();
	short CXmlCode::GenDesTempFileName(char* src, char* des, int max_size);

	short CXmlCode::CheckXmlFileFormat(char* buffer, int& len, int& beg, int& end, const int MAX_SIZE);
	void CXmlCode::GetLine();
	inline void CXmlCode::Write(const char* pData, int num);

	short CXmlCode::EncodeFile(int type);
	short CXmlCode::EncodeFile_column(int type);
	short CXmlCode::EncodeFile_property(int type);
	short CXmlCode::EncodeFile_string(int type);
	short CXmlCode::EncodeFile_item(int type);
	//////////////////////////////////////////////////////////////////////////
	short CXmlCode::DecodeFile(int type);
	short CXmlCode::DecodeFile_column(int type);

	short CXmlCode::DecodeFile_property(int type);

	short CXmlCode::DecodeFile_string(int type);
	short CXmlCode::DecodeFile_item(int type);
	void CXmlCode::ReleaseEncodeBuffer();
	short CXmlCode::CalcWriteFileSize(char* pFileNameList[], int pFileTypeList[], int file_num);
	//////////////////////////////////////////////////////////////////////////
public:
	short CXmlCode::EncodeProcess(char* pFileName, int type,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

	short CXmlCode::DecodeProcess(char* pFileName, int type, 
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);
public:
	virtual short CXmlCode::WriteFile(char* pFileNameList[], int pFileTypeList[], int file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);

	virtual short CXmlCode::ReadFile(char* pFileNameList[], int pFileTypeList[], int& file_num,
		void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);
public:
	static short CXmlCode::SearchCharIndexBackward(const char* pCharA, short len, char tag);
	static short CXmlCode::SearchCharIndexForward(const char* pCharA, short len, char tag);
  static bool CXmlCode::CompareChars(const char* a, const char* b, int num);
};

