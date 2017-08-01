#pragma once

#include "Basetype_def.h"
#include "RnServoAxiMapping.h"
#include "RingNetInterface.h"
// 
// struct StChunk
// {
// 	struct StChunk *next;
// 	Uint32 addr;
// 	vector<Uint8> data;
// 	StChunk() : next(NULL), addr(0) {}
// };
// 
// struct StImage
// {
// 	StChunk *first_chunk, *last_chunk;
// 	Uint32 len;
// 	Uint32 max_addr;
// 	Uint32 range_start, range_len;
// 	Uint32 alignment;
// 	StImage(Uint32 range_start, Uint32 range_len, Uint32 alignment)
// 		: first_chunk(NULL), last_chunk(NULL), len(0), max_addr(0),
// 		range_start(range_start), range_len(range_len), alignment(alignment) {}
// 	~StImage();
// };
// 
// class CRnSerialPort
// {
// public:
// 	CRnSerialPort();
// 	~CRnSerialPort();
// private:
// //	const int16 IHEX_ADDR_ERROR = 5;
// 
// 	enum Action {
// 		AC_NONE = 0,
// 		AC_PROGRAM,
// 		AC_LOAD,
// 		AC_WRITE_KEY,
// 		AC_ERASE,
// 		AC_ERASE_USER,
// 	} action;
// protected:
// 	CRnServoAxiMapping* m_pMapping;
// 	CRingNetInterface* m_pDriver;
// protected:
// protected:
// 	const int16						GTSD_DSP_WRITE = 0;					  //dsp定义的读写	
// 	const int16						GTSD_DSP_READ = 1;
// 
// 	// pcdebug 地址为dsp与fpga之间通信的fpga地址，不同的dsp对应不同的fpga地址。
// 	const Uint16					DSPA_COMADDR = 0x0400;				 //地址为short地址
// 	const Uint16					DSPB_COMADDR = 0x8400;
// 
// 	const Uint16					FPGA_DSPA_BASEADDR = 0;
// 	const Uint16					FPGA_DSPB_BASEADDR = 0x8000;				//short地址
// 
// 	const int16						COM_AXIS_MAX = 240;					//轴最大个数为4	
// 
// 	const int16						GTSD_DSP_A = 0;
// 	const int16						GTSD_DSP_B = 1;
// 	const int16						GTSD_DSP_C = 2;
// 
// 	const Uint16						PLOTWAVE_DSPA_NUM_ADDR = 0x0006;
// 	const Uint16						PLOTWAVE_DSPB_NUM_ADDR = 0x8006;
// 
// 	const Uint16						PLOTWAVE_DSPA_DATA_ADDR = 0x0600;//0x0800//
// 	const Uint16						PLOTWAVE_DSPB_DATA_ADDR = 0x8600;//0x8800//
// 
// 	const Uint16						FPGA_VERSION = 0x0000;
// 
// 	//等环网能访问的FPGA地址
// 	//////////////////////////////////////////////////////////////////////////
// 	//uart 基地址定义
// 	//pcdebug 地址和 等环网挂的地址不同
// 	const Uint16					FPGA_DSPA_UART_PCDEBUG_BASEADDR = 0x0380;
// 	const Uint16					FPGA_DSPB_UART_PCDEBUG_BASEADDR = 0x8380;
// 
// 	//等环网地址
// 	const Uint16					FPGA_DSPA_UART_RNNET_BASEADDR = 0x0800;
// 	const Uint16					FPGA_DSPB_UART_RNNET_BASEADDR = 0x8800;
// 
// 	//下面地址是偏移地址，两个dsp对应的偏移一致，基地址不同,偏移都是byte地址，下面使用的时候需要右移一位
// 	const int16						FPGA_UART_CONFIG_W = 0x00; //读 / 写 包控制设置
// 	const int16						FPGA_UART_CONFIG_R = 0x00;
// 	//写时
// 	//D8 - D10:传输数据位宽，
// 	//3’b100 : 5bit;
// 	//3’b101: 6bit;
// 	//3’b110: 7bit
// 	//3’b111 : 8bit;
// 	//D11:停止位设置
// 	//1’b0：1bit;
// 	//2’b1：2bit;
// 	//D12 - D13:奇偶校验设置
// 	//2’b01：奇校验；
// 	//2’b10 : 偶校验；
// 	//其他：无校验；
// 	//D15 - D14 : 保留
// 
// 	//读时
// 	//D14 - D14:保留
// 	//D15：模块使能状态
// 	//1：模块使能
// 	//0：模块关闭
// 
// 	const int16						FPGA_UART_TX_STATE_R = 0x02; //串口FIFO状态寄存器
// 	//D9 - D0：当前TX FIFO个数
// 	//D10：发送TX FIFO写满标志位
// 	//为1表示发送FIFO写满；
// 	//为0表示未满；
// 	//D11 : 接收TX FIFO空标志位
// 	//	  为1表示接受FIFO为空；
// 	//	  为0表示接受FIFO非空；
// 	//D12 : TX FIFO发生过写溢出
// 	//D13 - D15：保留；
// 
// 	const int16						FPGA_UART_BAUDRATE_WR = 0x04; //波特率设置
// 
// 	const int16						FPGA_UART_STARTEND_W = 0x06;
// 
// 	const int16						FPGA_UART_RX_STATE_R = 0x06;
// 
// 	const int16						FPGA_UART_SEND_FIFO_W = 0x08; //串口发送FIFO
// 	//应用层向FIFO写入准备发送的数据
// 	//D7 - D0:为写入的数据；根据数据位宽设置，确定有效位：
// 	//比如 传输数据位宽设定为3’b100，即传输数据位宽为5位（D4 - D0），D7 - D5补0；
// 	//D15 - D8 : 保留（补0）
// 
// 	const int16						FPGA_UART_RECEIVE_FIFO_R = 0x08; //串口接收FIFO寄存器
// 	//串口接收的的16位并行数据（低8位有效）
// 	//根据数据位宽设置，确定有效位：
// 	//比如 传输数据位宽设定为3’b100，即8位并行数据高5位有效，低三位无意义
// 
// 
// 	const double					FPGA_CLOCK = 125000000.0;
// 
// public:
// 	short Initial(CRnServoAxiMapping* pMapping, CRingNetInterface* pDriver);
// public:
// 	short open(int16 axis, int32 baudRate);
// 	short close(int16 axis);
// 	short read(int16 axis, Uint8 *buf, int32 length, int32 *length_read);
// 	short write(int16 axis, Uint8 *buf, int32 length, int32 *length_written);
// 
// 	short downloadBootStream(int16 axis, string& inputKey, int16 cmd, string& filename, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
// 	short send_ldr_img(int16 axis, string& inputKey, string& filename, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
// 	int16 parse_key(string& inputKey, Uint8 key[16]);
// 	StImage* read_img(string& filename, Uint32 range_start, Uint32 range_len, Uint32 alignment);
// 	int32 pad(int32 len, int32 align);
// 	short do_autobaud(int16 axis, Uint8 c, Uint8 *buf, Uint32 len);
// 	short do_ldr_autobaud(int16 axis);
// 	short send_erase_cmd(int16 axis, void(*tpfUpdataProgressPt)(void*, int16*), void* ptrv, int16& progress);
// 
// private:
// 	bool status;
// 	int32 baudrate;
// };
// 
// 
// int hex_read_callback(void *ctxt, const Uint8 *buf, Uint32 addr, Uint32 len);

