#include "stdafx.h"
#include "XmlCode.h"
#include "BaseReturn_def.h"
#include "fstream"
using namespace std;
// 
// 
// #define CMD_SUCCESS                     0
// 
// #define CMD_ERROR_READ_LEN             -2    /* 读取数据长度错误 */
// #define CMD_ERROR_READ_CHECKSUM        -3    /* 读取数据校验和错误 */
// 
// #define CMD_ERROR_WRITE_BLOCK          -4    /* 写入数据块错误 */
// #define CMD_ERROR_READ_BLOCK           -5    /* 读取数据块错误 */
// 
// #define CMD_ERROR_OPEN                 -6    /* 打开设备错误 */
// #define CMD_ERROR_CLOSE                -6    /* 关闭设备错误 */
// #define CMD_ERROR_DSP_BUSY             -7    /* DSP忙 */
// 
// #define CMD_LOCK_ERROR                 -8    /*多线程资源忙*/
// 
// #define CMD_ERROR_EXECUTE               1
// #define CMD_ERROR_VERSION_NOT_MATCH     3
// #define CMD_ERROR_PARAMETER             7
// #define CMD_ERROR_UNKNOWN               8    /* 不支持的指令 */
//
// typedef enum
// {
// 	RTN_SUCCESS = 0,
// 
// 	RTN_MALLOC_FAIL = -100, /* malloc memory fail */
// 	RTN_FREE_FAIL = -101, /* free memory or delete the object fail */
// 	RTN_NULL_POINT = -102, /* the param point input is null */
// 	RTN_ERR_ORDER = -103, /* call the function order is wrong, some msg isn't validable */
// 	RTN_PCI_NULL = -104, /* the pci address is empty, can't access the pci device*/
// 	RTN_PARAM_OVERFLOW = -105, /* the param input is too larget*/
// 	RTN_LINK_FAIL = -106, /* the two ports both link fail*/
// 	RTN_IMPOSSIBLE_ERR = -107, /* it means the system or same function work wrong*/
// 	RTN_TOPOLOGY_CONFLICT = -108, /* the id conflict*/
// 	RTN_TOPOLOGY_ABNORMAL = -109, /* scan the net abnormal*/
// 	RTN_STATION_ALONE = -110, /* the device no id, it means the device id is 0xF0 */
// 	RTN_WAIT_OBJECT_OVERTIME = -111, /* multi thread wait for object overtime */
// 	RTN_ACCESS_OVERFLOW = -112, /* data[i];  i is larger than the define */
// 	RTN_NO_STATION = -113, /* the station accessed not existent */
// 	RTN_OBJECT_UNCREATED = -114, /* the object not created yet*/
// 	RTN_PARAM_ERR = -115, /* the param input is wrong*/
// 	// RTN_NO_PDU_CFG                    -116, /*No Pdu Cfg*/
// 	RTN_PCI_FPGA_ERR = -117, /*PCI op err or FPGA op err*/
// 	RTN_CHECK_RW_ERR = -118, /*data write to reg, then rd out, and check err */
// 	RTN_REMOTE_UNEABLE = -119, /*the device which will be ctrl by net can't be ctrl by net function*/
// 
// 	RTN_NET_REQ_DATA_NUM_ZERO = -120, /*mail op or pdu op req data num can't be 0*/
// 	RTN_WAIT_NET_OBJECT_OVERTIME = -121, /* net op multi thread wait for object overtime */
// 	RTN_WAIT_NET_RESP_OVERTIME = -122, /* Can't wait for resp */
// 	RTN_WAIT_NET_RESP_ERR = -123, /*wait mailbox op err*/
// 	RTN_INITIAL_ERR = -124, /*initial the device err*/
// 	RTN_PC_NO_READY = -125, /*find the station'pc isn't work*/
// 	RTN_STATION_NO_EXIST = -126,
// 	RTN_MASTER_FUNCTION = -127, /* this funciton only used by master */
// 
// 	RTN_NOT_ALL_RETURN = -128, /* the GT_RN_PtProcessData funciton fail return */
// 	RTN_REQUSET_MAIL_BUS_OVERTIME = -150, /*Requset Mail Bus Err*/
// 	RTN_INSTRCTION_ERR = -151, /*instrctions err*/
// 	RTN_MAIL_RESP_REQ_ERR = -152, /*RN_MailRespReq  err*/
// 	RTN_CTRL_SRC_ERR = -153, /* the controlled source  is error */
// 	RTN_PACKET_ERR = -154, /*packet is error*/
// 	RTN_STATION_ID_ERR = -155, /*the device id is not in the right rang*/
// 	RTN_WAIT_NET_PDU_RESP_OVERTIME = -156, /*net pdu op wait overtime*/
// 
// 	RTN_IDLINK_PACKET_ERR = -200, /*ilink master  decode err! packet_length is not match*/
// 	RTN_IDLINK_PACKET_END_ERR = -201, /* the ending of ilink packet is not 0xFF*/
// 	RTN_IDLINK_TYPER_ERR = -202, /* the type of ilink module is error*/
// 	RTN_IDLINK_LOST_CNT = -203, /* the ilink module has lost connection*/
// 	RTN_IDLINK_CTRL_SRC_ERR = -204, /* the controlled source of ilink module is error */
// 	RTN_IDLINK_UPDATA_ERR = -205, /* the ilink module updata error*/
// 	RTN_IDLINK_NUM_ERR = -206, /* the ilink num larger the IDLINK_MAX_NUM(30) */
// 	RTN_IDLINK_NUM_ZERO = -207, /* the ilink num larger the IDLINK_MAX_NUM(30) */
// 
// 	RTN_NO_PACKET = 301, /* no valid packet */
// 	RTN_RX_ERR_PDU_PACKET = -302, /* ERR PDU PACKET */
// 	RTN_STATE_MECHINE_ERR = -303,
// 	RTN_PCI_DSP_UN_FINISH = 304,
// 	RTN_SEND_ALL_FAIL = -305,
// 	RTN_STATION_CLOSE = 310,
// 	RTN_STATION_RESP_FAIL = 311,
// 
// 	RTN_UPDATA_MODAL_ERR = -330,/* update the modal in normal way fail*/
// 
// 
// 	RTN_NO_MAIL_DATA = 340, /*There is no mail data*/
// 	RTN_NO_PDU_DATA = 341, /*There is no pdu data*/
// 
// 
// 
// 
// 	RTN_FILE_PARAM_NUM_ERR = -500,
// 	RTN_FILE_PARAM_LEN_ERR = -501,
// 	RTN_FILE_MALLOC_FAIL = -502,
// 	RTN_FILE_FREE_FAIL = -503,
// 	RTN_FILE_PARAM_ERR = -504,
// 	RTN_FILE_NOT_EXSITS = 505,
// 	RTN_FILE_CREATE_FAIL = 510,
// 	RTN_FILE_DELETE_FAIL = 511,
// 	RTN_FIFE_CRC_CHECK_ERR = -512,
// 	RTN_FIFE_FUNCTION_ID_RETURN_ERR = -600,
// 
// 	RTN_UPDATE_WAIT_OVERTIME = -700,
// 	RTN_UPDATE_FPGA_OP_ERR = -701,
// 	RTN_UPDATE_CAMPARE_ERR = -702,
// 
// 	RTN_FILE_OPEN_ERR = -900//文件打开失败
// }ENUM_RTN_RETURN;

CXmlCode::CXmlCode()
{
	m_pFile_in = NULL;
	m_pFile_out = NULL;
	column_cnt = 0;
	line_cnt = 0;
	//////////////////////////////////////////////////////////////////////////
	gCode_cnt = 0;
	gSpaceNum = 0;
	gCode_num = 0;
	//////////////////////////////////////////////////////////////////////////
	ReleaseEncodeBuffer();
}


CXmlCode::~CXmlCode()
{
	fstream* pFile = (fstream* )m_pFile_in;
	if (pFile)
	{
		delete pFile;
		m_pFile_in = NULL;
	}
	pFile = (fstream*)m_pFile_out;
	if (pFile)
	{
		delete pFile;
		m_pFile_out = NULL;
	}
	ReleaseEncodeBuffer();
	if (gCode)
	{
		delete gCode;
		gCode = NULL;
	}
}

void CXmlCode::ReleaseEncodeBuffer()
{
	
	if (m_pEncodeBufferList)
	{
		for (int i = 0; i < m_EncodeNum; i++)
		{
			if (m_pEncodeBufferList[i])
			{
				delete m_pEncodeBufferList[i];
				m_pEncodeBufferList[i] = NULL;
			}
		}
		delete m_pEncodeBufferList;
		m_pEncodeBufferList = NULL;
	}
	if (m_pEncodeTypeList)
	{
		delete m_pEncodeTypeList;
		m_pEncodeTypeList = NULL;
	}
	if (m_pEncodeByteNumList)
	{
		delete m_pEncodeByteNumList;
		m_pEncodeByteNumList = NULL;
	}
	m_EncodeNum = 0;
}
short CXmlCode::OpenFile(char* pFileName)
{
	short rtn;
	char des_file_name[100];
	line_cnt = 0;
	write_buffer_cnt = 0;

	rtn = GenDesTempFileName(pFileName, des_file_name, 100);
	if (rtn)
	{
		return rtn;
	}

	if (m_pFile_in == NULL)
	{
		m_pFile_in = new fstream;
		if (m_pFile_in == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
		
	}
	if (m_pFile_out == NULL)
	{
		m_pFile_out = new fstream;
		if (m_pFile_out == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
	}

	fstream* pFile_in;
	fstream* pFile_out;
	pFile_in = (fstream*)m_pFile_in;
	pFile_out = (fstream*)m_pFile_out;

	pFile_in->open(pFileName, ios::in | ios::out | ios::binary);
	if (pFile_in->is_open() == NULL)
	{
		return RTN_FILE_OPEN_ERR;
	}
	pFile_out->open(des_file_name, ios::in | ios::out | ios::binary | ios::ate | ios::trunc);
	if (pFile_out->is_open() == NULL)
	{
		return RTN_FILE_OPEN_ERR;
	}
	return RTN_SUCCESS;
}
short CXmlCode::CloseFile()
{
	fstream* pFile_in;
	fstream* pFile_out;
	pFile_in = (fstream*)m_pFile_in;
	pFile_out = (fstream*)m_pFile_out;

	if (write_buffer_cnt)
	{
		pFile_out->write(write_buffer, write_buffer_cnt);
		write_buffer_cnt = 0;
	}
	if (pFile_in->is_open())
	{
		pFile_in->close();
	}
	if (pFile_out->is_open())
	{
		pFile_out->flush();
		pFile_out->close();
	}
	return RTN_SUCCESS;
}

short CXmlCode::CheckXmlFileFormat(char* buffer, int& len, int& beg, int& end, const int MAX_SIZE)
{
	len = SearchCharIndexForward(buffer, MAX_SIZE, 0);
	if (len < 0)
	{
		return RTN_PARAM_ERR;
	}
	beg = SearchCharIndexForward(buffer, len, '<');
	if (beg == -1)
	{
		return RTN_PARAM_ERR;
	}
	beg += 1;
	end = SearchCharIndexBackward(buffer, len, '>');
	if (end == -1)
	{
		return RTN_PARAM_ERR;
	}
	end = end - 1;
	if (beg >= end)
	{
		return RTN_PARAM_ERR;
	}
	return RTN_SUCCESS;
}
bool CXmlCode::CompareChars(const char* a, const char* b, int num)
{
	for (int i = 0; i < num; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

void CXmlCode::GetLine()
{
	fstream* pFile_in;
	pFile_in = (fstream*)m_pFile_in;

	pFile_in->getline(buffer, MAX_SIZE);
	line_cnt++;
}
short CXmlCode::EncodeFile(int type)
{
	int len = 0;
	int beg, end;
	short rtn;
	while (1)
	{
		GetLine();
		rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
		if (rtn)
			return rtn;
		//////////////////////////////////////////////////////////////////////////
		if (CompareChars(&buffer[beg], "column", SIZE_column))
		{
			column_cnt = 0;
			rtn = EncodeFile_column(type);
			if (rtn)
				return rtn;
		}
		else if (CompareChars(&buffer[beg], "property", SIZE_property))
		{
			rtn = EncodeFile_property(type);
			if (rtn)
				return rtn;
		}
		else if (CompareChars(&buffer[beg], "string", SIZE_string))
		{
			rtn = EncodeFile_string(type);
			if (rtn)
				return rtn;
		}
		else if (CompareChars(&buffer[beg], "item", SIZE_item))
		{
			rtn = EncodeFile_item(type);
			if (rtn)
				return rtn;
		}
		else if (CompareChars(&buffer[beg], "?xml", 4))
		{
			for (int i = 0; i < 17; i++)
			{
				GetLine();
			}
		}
		else if (CompareChars(&buffer[beg], "/widget", 5))
		{
			return RTN_SUCCESS;
		}
	}
	return RTN_PARAM_ERR;
}
void CXmlCode::Write(const char* pData, int num)
{
	fstream* pFile_out;
	pFile_out = (fstream*)m_pFile_out;
	if (write_buffer_cnt + num >= WRITE_BUFFER_SIZE)
	{
		int write_delta = WRITE_BUFFER_SIZE - write_buffer_cnt;
		memcpy(&write_buffer[write_buffer_cnt], pData, write_delta);
		pFile_out->write(write_buffer, WRITE_BUFFER_SIZE);
		write_buffer_cnt = 0;

		num = num - write_delta;
		if(num != 0 )
			Write(&pData[write_delta], num);
	}
	else
	{
		memcpy(&write_buffer[write_buffer_cnt], pData, num);
		write_buffer_cnt = write_buffer_cnt + num;
	}
// 	for (int i = num; i > 0; i--)
// 	{
// 		write_buffer_cnt++;
// 	}
// 	write_buffer_cnt
// 	pFile_out->write(pData, num);
}
short CXmlCode::EncodeFile_column(int type)
{
	//////////////////////////////////////
	// 	<column>
	// 		<property name = "text">
	// 		<string>memberName</string>
	// 		</property>
	// 	</column>
	//////////////////////////////////////
	int len = 0;
	int beg, end;
	short rtn;

	Write(&ENCODE_COLUMN_IN, 1);
	while (1)
	{
		GetLine();
		rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
		if (rtn) return rtn;

		else if (CompareChars(&buffer[beg], "property", SIZE_property))
		{
			rtn = EncodeFile_property(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "column", SIZE_item))
		{
			rtn = EncodeFile_column(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "item", SIZE_item))
		{
			rtn = EncodeFile_item(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "/column", SIZE_column + 1))
		{
			break;
		}
		else
		{
			return RTN_PARAM_ERR;
		}
	}
	Write(&ENCODE_COLUMN_OUT, 1);
	return RTN_SUCCESS;
	///////////////////////////////////////
	// 	int len = 0;
	// 	int beg, end;
	// 	short rtn;
	// 	column_cnt++;
	// 	Write(&ENCODE_COLUMN, 1);
	// 	GetLine();
	// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	// 	if (rtn) return rtn;
	// 
	// 	if (CompareChars(&buffer[beg], "property", SIZE_property) == false)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 
	// 	GetLine();
	// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	// 	if (rtn) return rtn;
	// 
	// 	if (CompareChars(&buffer[beg], "string", SIZE_string) == false)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	///////////////write column context////////
	// 	beg += SearchCharIndexForward(&buffer[beg], len-beg, '>');
	// 	if (beg == -1)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	beg += 1;
	// 	end = beg+SearchCharIndexBackward(&buffer[beg], len-beg, '<');
	// 	if (end == -1)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	end = end - 1;
	// 	if (beg > end + 1)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	if (CompareChars(&buffer[end + 2], "/string", SIZE_string + 1) == false)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	//////////////////////////////////////////////////////////////////////////
	// 	if (end - beg == -1)
	// 	{
	// 		Write(&ENCODE_NONE, 1);
	// 	}
	// 	else
	// 	{
	// 		Write(&buffer[beg], end - beg + 1);
	// 	}
	// 	//////////////////////////////////////////////////////////////////////////
	// 	GetLine();
	// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	// 	if (rtn) return rtn;
	// 
	// 	if (CompareChars(&buffer[beg], "/property", SIZE_property+1) == false)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	GetLine();
	// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	// 	if (rtn) return rtn;
	// 
	// 	if (CompareChars(&buffer[beg], "/column", SIZE_column+1) == false)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	return RTN_SUCCESS;
	///////////////////////////////
}

short CXmlCode::EncodeFile_property(int type)
{
	/*
	<property name="text">
	<string>XmlVersion</string>
	</property>
	*/
	int len = 0;
	int beg, end;
	short rtn;

	GetLine();
	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	if (rtn) return rtn;

	if (CompareChars(&buffer[beg], "string", SIZE_string) == false)
	{
		return RTN_PARAM_ERR;
	}
	///////////////write column context////////
	beg += SearchCharIndexForward(&buffer[beg], len - beg, '>');
	if (beg == -1)
	{
		return RTN_PARAM_ERR;
	}
	beg += 1;
	end = beg + SearchCharIndexBackward(&buffer[beg], len - beg, '<');
	if (end == -1)
	{
		return RTN_PARAM_ERR;
	}
	end = end - 1;
	if (beg > end + 1)
	{
		return RTN_PARAM_ERR;
	}
	if (CompareChars(&buffer[end + 2], "/string", SIZE_string + 1) == false)
	{
		return RTN_PARAM_ERR;
	}
	//////////////////////////////////////////////////////////////////////////
	if (end - beg == -1)
	{
		Write(&ENCODE_NONE, 1);
		Write(&ENCODE_NONE, 1);
	}
	else
	{
		Write(&buffer[beg], end - beg + 1);
		Write(&ENCODE_NONE, 1);
	}
	//////////////////////////////////////////////////////////////////////////
	GetLine();
	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
	if (rtn) return rtn;

	if (CompareChars(&buffer[beg], "/property", SIZE_property + 1) == false)
	{
		return RTN_PARAM_ERR;
	}
	return RTN_SUCCESS;
}

short CXmlCode::EncodeFile_string(int type)
{
// 	int len = 0;
// 	int beg, end;
// 	short rtn;
// 
// 	GetLine();
// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
// 	if (rtn) return rtn;
	return RTN_SUCCESS;
}

short CXmlCode::EncodeFile_item(int type)
{
	/*
	<item>
	<property name="text">
	<string>XmlVersion</string>
	</property>
	<property name="text">
	<string>130</string>
	</property>
	<property name="text">
	<string>Uint16</string>
	</property>
	<property name="text">
	<string>-1</string>
	</property>
	</item>
	*/
	int len = 0;
	int beg, end;
	short rtn;
	Write(&ENCODE_ITEM_IN, 1);
	while (1)
	{
		GetLine();
		rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
		if (rtn) return rtn;

		else if (CompareChars(&buffer[beg], "property", SIZE_property))
		{
			rtn = EncodeFile_property(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "column", SIZE_item))
		{
			rtn = EncodeFile_column(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "item", SIZE_item))
		{
			rtn = EncodeFile_item(type);
			if (rtn) return rtn;
		}
		else if (CompareChars(&buffer[beg], "/item", SIZE_item + 1))
		{
			break;
		}
		else
		{
			return RTN_PARAM_ERR;
		}
	}
	Write(&ENCODE_ITEM_OUT, 1);
	return RTN_SUCCESS;
}

short CXmlCode::SearchCharIndexBackward(const char* pCharA, short len, char tag)
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

short CXmlCode::SearchCharIndexForward(const char* pCharA, short len, char tag)
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

short CXmlCode::GenDesTempFileName(char* src, char* des, int max_size)
{
	if (src == NULL || des == NULL)
	{
		return RTN_NULL_POINT;
	}

	for (int i = 0; i < max_size - 10; i++)
	{
		if (src[i] == 0)
		{
			des[i] = 'b';
			des[i + 1] = 'a';
			des[i + 2] = 't';
			des[i + 3] = 0;
			// 			des[i + 4] = '0';
			// 			des[i + 5] = '0';
			// 			des[i + 6] = 0;
			return RTN_SUCCESS;
		}
		else
		{
			des[i] = src[i];
		}
	}
	return RTN_PARAM_ERR;
}

short CXmlCode::EncodeProcess(char* pFileName, int type, void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn;

	rtn = OpenFile(pFileName);
	if (rtn)
	{
		CloseFile();
		return rtn;
	}
	rtn = EncodeFile(type);
	if (rtn)
	{
		CloseFile();
		return rtn;
	}
	CloseFile();
	return RTN_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////

short CXmlCode::DecodeFile(int type)
{
	short rtn;
	fstream* pFile_in;
	pFile_in = (fstream*)m_pFile_in;

	if (type == 0)
	{
		pData[0] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		pData[1] = "<ui version=\"4.0\">\n";
		pData[2] = "    <class>Form</class>\n";
		pData[3] = "    <widget class=\"QWidget\" name=\"Form\">\n";
		pData[4] = "        <property name=\"geometry\">\n";
		pData[5] = "            <rect>\n";
		pData[6] = "                <x>0</x>\n";
		pData[7] = "                <y>0</y>\n";
		pData[8] = "                <width>400</width>\n";
		pData[9] = "                <height>400</height>\n";
		pData[10] = "            </rect>\n";
		pData[11] = "        </property>\n";
		pData[12] = "        <property name=\"windowTitle\">\n";
		pData[13] = "            <string>Form</string>\n";
		pData[14] = "        </property>\n";
		pData[15] = "        <layout class=\"QVBoxLayout\" name=\"verticalLayout\">\n";
		pData[16] = "            <item>\n";
		pData[17] = "                <widget class=\"QTreeWidget\" name=\"treeWidget\">\n";

		pData[18] = "                </widget>\n";
		pData[19] = "            </item>\n";
		pData[20] = "        </layout>\n";
		pData[21] = "    </widget>\n";
		pData[22] = "    <resources/>\n";
		pData[23] = "    <connections/>\n";
		pData[24] = "</ui>\n";
	}
	else //if (type == 1)
	{
		pData[0] = "<?xml version=\"1.0\" encoding=\"gb2312\" ?>\r\n";
		pData[1] = "<ui version=\"4.0\">\r\n";
		pData[2] = "    <class>Form</class>\r\n";
		pData[3] = "    <widget class=\"QWidget\" name=\"Form\">\r\n";
		pData[4] = "        <property name=\"geometry\">\r\n";
		pData[5] = "            <rect>\r\n";
		pData[6] = "                <x>0</x>\r\n";
		pData[7] = "                <y>0</y>\r\n";
		pData[8] = "                <width>400</width>\r\n";
		pData[9] = "                <height>438</height>\r\n";
		pData[10] = "            </rect>\r\n";
		pData[11] = "        </property>\r\n";
		pData[12] = "        <property name=\"windowTitle\">\r\n";
		pData[13] = "            <string>Form</string>\r\n";
		pData[14] = "        </property>\r\n";
		pData[15] = "        <layout class=\"QVBoxLayout\" name=\"verticalLayout\">\r\n";
		pData[16] = "            <item>\r\n";
		pData[17] = "                <widget class=\"QTreeWidget\" name=\"treeWidget\">\r\n";

		pData[18] = "                </widget>\r\n";
		pData[19] = "            </item>\r\n";
		pData[20] = "        </layout>\r\n";
		pData[21] = "    </widget>\r\n";
		pData[22] = "    <resources />\r\n";
		pData[23] = "    <connections />\r\n";
		pData[24] = "</ui>\r\n";
	}



	line_cnt = 1;
	gCode_cnt = 0;
	for (int i = 0; i < 18; i++)
	{
		string str = pData[i];
		Write(str.c_str(), str.length());
		line_cnt++;
	}
	pFile_in->seekg(0, ios::end);
	gCode_num = (int)pFile_in->tellg();
	pFile_in->seekg(0, ios::beg);
	gCode = new char[gCode_num];
	if (gCode == NULL)
		return RTN_MALLOC_FAIL;
	pFile_in->read(gCode, gCode_num);

	gSpaceNum = 16;
	column_cnt = 0;

	while (gCode_cnt<gCode_num)
	{
		switch (gCode[gCode_cnt])
		{
		case ENCODE_COLUMN_IN:
			rtn = DecodeFile_column(type);
			if (rtn)
				return rtn;
			break;
		case ENCODE_ITEM_IN:
			rtn = DecodeFile_item(type);
			if (rtn)
				return rtn;
			break;
		default:
			return RTN_PARAM_ERR;
			break;

		}
	}
	if (gCode_cnt != gCode_num)
	{
		return RTN_PARAM_ERR;
	}
	for (int i = 18; i < 25; i++)
	{
		string str = pData[i];
		Write(str.c_str(), str.length());
		line_cnt++;
	}
	return RTN_SUCCESS;
}

short CXmlCode::DecodeFile_column(int type)
{
	//////////////////////////////////////
	// 	<column>
	// 		<property name = "text">
	// 		<string>memberName</string>
	// 		</property>
	// 	</column>
	//////////////////////////////////////
	short rtn;
	

	gSpaceNum += 4;
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "<column>\n";
		Write(str, SIZE_column + 3);
	}
	else
	{
		str = "<column>\r\n";
		Write(str, SIZE_column + 4);
	}
	line_cnt++;

	gCode_cnt++;
	while (gCode_cnt < gCode_num && gCode[gCode_cnt] != ENCODE_COLUMN_OUT)
	{
		switch (gCode[gCode_cnt])
		{
			// 		case ENCODE_COLUMN_OUT:
			// 			break;
		case ENCODE_COLUMN_IN:
			rtn = DecodeFile_column(type);
			if (rtn)
				return rtn;
			break;
		case ENCODE_ITEM_IN:
			rtn = DecodeFile_item(type);
			if (rtn)
				return rtn;
			break;
		case ENCODE_ITEM_OUT:
			return RTN_PARAM_ERR;
			break;
		default:
			rtn = DecodeFile_property(type);
			if (rtn)
				return rtn;
			break;
		}
	}
	if (gCode_cnt == gCode_num)
	{
		return RTN_PARAM_ERR;
	}
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "</column>\n";
		Write(str, SIZE_column + 4);
	}
	else
	{
		str = "</column>\r\n";
		Write(str, SIZE_column + 5);
	}
	line_cnt++;

	gCode_cnt++;

	gSpaceNum -= 4;
	return RTN_SUCCESS;
	//////////////////////////////////////////////////////////////////////////
	// 
	// 	short rtn;
	// 	string str;
	// 
	// 	gSpaceNum += 4;
	// 	for (int i = 0; i < gSpaceNum;i++)
	// 	{
	// 		Write(" ", 1);
	// 	}
	// 	str = "<column>\n";
	// 	Write(str.c_str(), str.length()); 
	// 	line_cnt++;
	// 	gCode_cnt++;
	// 
	// 	rtn = DecodeFile_property(type);
	// 	if (rtn)
	// 		return rtn;
	// 	//////////////////////////////////////////////////////////////////////////
	// 	if (gCode_cnt == gCode_num)
	// 	{
	// 		return RTN_PARAM_ERR;
	// 	}
	// 	for (int i = 0; i < gSpaceNum; i++)
	// 	{
	// 		Write(" ", 1);
	// 	}
	// 	str = "</column>\n";
	// 	Write(str.c_str(), str.length());
	// 	line_cnt++;
	// 	
	// 	gSpaceNum -= 4;
	// 	return RTN_SUCCESS;
}

short CXmlCode::DecodeFile_property(int type)
{
	/*
	<property name="text">
	<string>XmlVersion</string>
	</property>
	*/

	gSpaceNum += 4;
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "<property name=\"text\">\n";
		Write(str, SIZE_property + 15);
	}
	else
	{
		str = "<property name=\"text\">\r\n";
		Write(str, SIZE_property + 16);
	}
	line_cnt++;
	//////////////////////////////////////////////////////////////////////////
	gSpaceNum += 4;
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	str = "<string>";
	Write(str, SIZE_string+2);
	while (gCode_cnt<gCode_num && gCode[gCode_cnt] != 0)
	{
		Write(&gCode[gCode_cnt], 1);
		gCode_cnt++;
	}
	if (gCode_cnt == gCode_num)
	{
		return RTN_PARAM_ERR;
	}
	gCode_cnt++;
	//////////////////////////////////////////////////////////////////////////
	if (type == 0)
	{
		str = "</string>\n";
		Write(str, SIZE_string + 4);
	}
	else
	{
		str = "</string>\r\n";
		Write(str, SIZE_string + 5);
	}
	line_cnt++;
	//////////////////////////////////////////////////////////////////////////
	gSpaceNum -= 4;
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "</property>\n";
		Write(str, SIZE_property + 4);
	}
	else
	{
		str = "</property>\r\n";
		Write(str, SIZE_property + 5);

	}
	line_cnt++;

	gSpaceNum -= 4;
	return RTN_SUCCESS;
}

short CXmlCode::DecodeFile_string(int type)
{
// 	int len = 0;
// 	int beg, end;
// 	short rtn;
// 
// 	GetLine();
// 	rtn = CheckXmlFileFormat(buffer, len, beg, end, MAX_SIZE);
// 	if (rtn) return rtn;
	return RTN_SUCCESS;
}

short CXmlCode::DecodeFile_item(int type)
{
	/*
	<item>
	<property name="text">
	<string>XmlVersion</string>
	</property>
	<property name="text">
	<string>130</string>
	</property>
	<property name="text">
	<string>Uint16</string>
	</property>
	<property name="text">
	<string>-1</string>
	</property>
	</item>
	*/
	short rtn;

	gSpaceNum += 4;
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "<item>\n";
		Write(str, SIZE_item + 3);
	}
	else
	{
		str = "<item>\r\n";
		Write(str, SIZE_item + 4);

	}
	line_cnt++;

	gCode_cnt++;
	while (gCode_cnt < gCode_num && gCode[gCode_cnt] != ENCODE_ITEM_OUT)
	{
		switch (gCode[gCode_cnt])
		{
		case ENCODE_COLUMN_OUT:
			return RTN_PARAM_ERR;
			break;
		case ENCODE_COLUMN_IN:
			rtn = DecodeFile_column(type);
			if (rtn)
				return rtn;
			break;
		case ENCODE_ITEM_IN:
			rtn = DecodeFile_item(type);
			if (rtn)
				return rtn;
			// 		case ENCODE_ITEM_OUT:
			break;
		default:
			rtn = DecodeFile_property(type);
			if (rtn)
				return rtn;
			break;
		}
	}
	if (gCode_cnt == gCode_num)
	{
		return RTN_PARAM_ERR;
	}
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < gSpaceNum; i++)
	{
		Write(" ", 1);
	}
	if (type == 0)
	{
		str = "</item>\n";
		Write(str, SIZE_item + 4);
	}
	else
	{
		str = "</item>\r\n";
		Write(str, SIZE_item + 5);

	}
	line_cnt++;

	gCode_cnt++;

	gSpaceNum -= 4;
	return RTN_SUCCESS;
}

short CXmlCode::DecodeProcess(char* pFileName, int type, void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn;

	rtn = OpenFile(pFileName);
	if (rtn)
	{
		CloseFile();
		return rtn;
	}
	rtn = DecodeFile(type);
	if (rtn)
	{
		CloseFile();
		if (gCode)
		{
			delete gCode;
			gCode = NULL;
		}
		return rtn;
	}
	CloseFile();
	if (gCode)
	{
		delete gCode;
		gCode = NULL;
	}
	return RTN_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
short CXmlCode::WriteFile(char* pFileNameList[], int pFileTypeList[], int file_num,
	void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn = RTN_SUCCESS;
	char des_file_name[100];

	fstream src, des;
	const int BUFFER_SIZE = 1 << 10;
	char pSrcData[BUFFER_SIZE];// = NULL;
	char pDesData[BUFFER_SIZE];// = NULL;
	
	for (int i = 0; i < file_num;i++)
	{
		rtn = EncodeProcess(pFileNameList[i], pFileTypeList[i], tpfUpdataProgressPt, ptrv, progress);
		if (rtn != RTN_SUCCESS)
			return rtn;

		rtn = GenDesTempFileName(pFileNameList[i], des_file_name, 100);
		if (rtn != RTN_SUCCESS)
			return rtn;

		rtn = DecodeProcess(des_file_name, pFileTypeList[i], tpfUpdataProgressPt, ptrv, progress);
		if (rtn != RTN_SUCCESS)
			return rtn;

		rtn = GenDesTempFileName(des_file_name, des_file_name, 100);
		if (rtn != RTN_SUCCESS)
			return rtn;

		if (src.is_open())
		{
			src.close();
		}

		if (des.is_open())
		{
			des.close();
		}

		src.open(pFileNameList[i], ios::in | ios::out | ios::binary);
		if (src.is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}

		des.open(des_file_name, ios::in | ios::out | ios::binary);
		if (des.is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}

		src.seekg(0, ios::end);
		int src_length = (int)src.tellg();
		src.seekg(0, ios::beg);

		des.seekg(0, ios::end);
		int des_length = (int)des.tellg();
		des.seekg(0, ios::beg);

		if (src_length != des_length)
		{
			rtn = RTN_PACKET_ERR;
			break;
		}
// 		if (pSrcData)
// 			delete pSrcData;
// 		if (pDesData)
// 			delete pDesData;
// 
// 		pSrcData = new char[des_length];
// 		pDesData = new char[src_length];

		
// 		if (pSrcData == NULL || pDesData == NULL)
// 		{
// 			rtn = RTN_MALLOC_FAIL;
// 			break;
// 		}
		int compare_cnt = 0;
		int compare_num;
		while (1)
		{
			if (src_length > compare_cnt + BUFFER_SIZE)
			{
				compare_num = BUFFER_SIZE;
				src.read(pSrcData, compare_num);
				des.read(pDesData, compare_num);
// 				for (int i = 0; i < compare_num;i++)
// 				{
// 					pDesData[i] = 0;
// 					pSrcData[i] = 1;
// 				}
				compare_cnt += compare_num;
				rtn = memcmp(pDesData, pSrcData, compare_num);
				if (rtn != 0)
				{
					rtn = RTN_PARAM_ERR;
					break;
				}
			}
			else
			{
				compare_num = src_length - compare_cnt;
				src.read(pSrcData, compare_num);
				des.read(pDesData, compare_num);
				compare_cnt += compare_num;
				rtn = memcmp(pDesData, pSrcData, compare_num);
				if (rtn != 0)
				{
					rtn = RTN_PARAM_ERR;
					break;
				}
				break;
			}
		}
// 		src.read(pSrcData, src_length);
// 		des.read(pDesData, des_length);
// 		rtn = memcmp(pDesData, pSrcData, src_length);
// 		if (rtn != 1)
// 		{
// 			rtn = RTN_PARAM_ERR;
// 			break;
// 		}
		//////////////////////////////////////////////////////////////////////////
	}

// 	if (pSrcData)
// 		delete pSrcData;
// 	if (pDesData)
// 		delete pDesData;

	if (src.is_open())
	{
		src.close();
	}
	if (des.is_open())
	{
		des.close();
	}
	if (rtn)
		return rtn;

	rtn = CalcWriteFileSize(pFileNameList, pFileTypeList, file_num);
	if (rtn)
	{
		ReleaseEncodeBuffer();
	}
	return rtn;
}

short CXmlCode::CalcWriteFileSize(char* pFileNameList[], int pFileTypeList[], int file_num)
{
	short rtn = RTN_SUCCESS;
	char des_file_name[100];

	fstream des;
	ReleaseEncodeBuffer();

	m_EncodeNum = file_num;

	m_pEncodeByteNumList = new int[file_num];
	if (m_pEncodeByteNumList == NULL)
	{
		return RTN_MALLOC_FAIL;
	}
	
	m_pEncodeBufferList = new char*[file_num];
	if (m_pEncodeBufferList == NULL)
	{
		return RTN_MALLOC_FAIL;
	}

	m_pEncodeTypeList = new int[file_num];
	if (m_pEncodeTypeList == NULL)
	{
		return RTN_MALLOC_FAIL;
	}


	for (int i = 0; i < file_num;i++)
	{
		m_pEncodeTypeList[i] = pFileTypeList[i];
		rtn = GenDesTempFileName(pFileNameList[i], des_file_name, 100);
		if (rtn != RTN_SUCCESS)
			return rtn;

		des.open(des_file_name, ios::in | ios::out | ios::binary);
		if (des.is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}

		des.seekg(0, ios::end);
		m_pEncodeByteNumList[i] = (int)des.tellg();

		m_pEncodeBufferList[i] = new char[m_pEncodeByteNumList[i]];
		if (m_pEncodeBufferList[i] == NULL)
		{
			rtn = RTN_MALLOC_FAIL;
			break;
		}
		des.seekg(0, ios::beg);
		des.read(m_pEncodeBufferList[i], m_pEncodeByteNumList[i]);
		des.close();
	}
	if (des.is_open())
	{
		des.close();
	}
	return rtn;
}

short CXmlCode::ReadFile(char* pFileNameList[], int pFileTypeList[], int& file_num,
	void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress)
{
	short rtn = RTN_SUCCESS;
	file_num = file_num > m_EncodeNum ? m_EncodeNum : file_num;
	char des_file_name[100];

	fstream* pFile_in;
	fstream* pFile_out;

	if (m_pFile_in == NULL)
	{
		m_pFile_in = new fstream;
		if (m_pFile_in == NULL)
		{
			return RTN_MALLOC_FAIL;
		}

	}
	if (m_pFile_out == NULL)
	{
		m_pFile_out = new fstream;
		if (m_pFile_out == NULL)
		{
			return RTN_MALLOC_FAIL;
		}
	}

	pFile_in = (fstream*)m_pFile_in;
	pFile_out = (fstream*)m_pFile_out;

	for (int i = 0; i < file_num; i++)
	{
		rtn = GenDesTempFileName(pFileNameList[i], des_file_name, 100);
		if (rtn != RTN_SUCCESS)
			return rtn;
		////////////////////////write readout data//////////////////////////////////////////////////
		if (pFile_out->is_open())
		{
			pFile_out->close();
		}

		pFile_out->open(des_file_name, ios::in | ios::out | ios::binary | ios::ate | ios::trunc);
		if (pFile_out->is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}
		pFile_out->write(m_pEncodeBufferList[i], m_pEncodeByteNumList[i]);
		pFile_out->flush();
		pFile_out->close();
		//////////////////////////////////////////////////////////////////////////
		///////////////////////////open file///////////////////////////////////////////////
		pFile_in->open(des_file_name, ios::in | ios::out | ios::binary);
		if (pFile_in->is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}

		pFile_out->open(pFileNameList[i], ios::in | ios::out | ios::binary | ios::ate | ios::trunc);
		if (pFile_out->is_open() == NULL)
		{
			rtn = RTN_FILE_OPEN_ERR;
			break;
		}
		//////////////////////////DecodeFile////////////////////////////////////////////////
		pFileTypeList[i] = m_pEncodeTypeList[i];
		if (gCode)
		{
			delete gCode;
			gCode = NULL;
		}
		
		rtn = DecodeFile(m_pEncodeTypeList[i]);
		if (rtn)
		{
			break;
		}
		CloseFile();
		delete gCode;
		gCode = NULL;

	}
	CloseFile();
	if (gCode)
	{
		delete gCode;
		gCode = NULL;
	}
	return rtn;
	
}
