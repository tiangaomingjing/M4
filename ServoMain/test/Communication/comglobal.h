#ifndef COMGLOBAL_H
#define COMGLOBAL_H
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
namespace COM
{
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//									BASIC DATA TYPE DEFINITION
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
template <typename T> static inline T *qGetPtrHelper(T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper(const Wrapper &p) { return p.data(); }

#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private;

#define Q_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define Q_D(Class) Class##Private * const d = d_func()
#define Q_Q(Class) Class * const q = q_func()

#define PDU_DATA_LEN 5
#define MAX_WAVE_PLOT_NUM 16

typedef		char							int8;
typedef		short							int16;
typedef		long							int32;
typedef		long long						int64;

typedef		unsigned char					Uint8;
typedef		unsigned short					Uint16;
typedef		unsigned long					Uint32;
typedef		unsigned long long				Uint64;
//------------------------------------------------------------------------------------------------
typedef		volatile signed char			vint8;
typedef		volatile short					vint16;
typedef		volatile long					vint32;

typedef		volatile unsigned char			vUint8;
typedef		volatile unsigned short			vUint16;
typedef		volatile unsigned long			vUint32;
//------------------------------------------------------------------------------------------------
typedef		const	Uint8					CUint8;
typedef		const	Uint16					CUint16;
typedef		const	Uint32					CUint32;
//------------------------------------------------------------------------------------------------
typedef enum{
  TASK_MODE_IDLE,
  TASK_MODE_ADC,
  TASK_MODE_POS_ADJ,
  TASK_MODE_CUR_OPEN,
  TASK_MODE_CUR_CLOSE,
  TASK_MODE_VEL_CLOSE,
  TASK_MODE_VEL_OPEN,
  TASK_MODE_VEL_CLOSE2,
  TASK_MODE_POS_FIX,
  TASK_MODE_POS_FOL,
  TASK_MODE_DB,
  TASK_MODE_CUR_FOL,
}ServoTaskMode;
typedef enum{
  NET_1000M,
  NET_ERR,
  NET_NOT1000M,
  NET_NOCARD
}NetCardInfo;

/* |mode|cmd|len|<-------data------>|
 * |_ _ |_ _|_ _|_ _|_ _|_ _|_ _|_ _|
 * len是指data的长度
 * 1级指令cmd<41  data[0]开始就是数据
 * 2级指令cmd=41  data[0]是2级ID data[1]开始是数据
 * */
typedef struct{
  Uint16 mode;
  Uint16 cmd;
  Uint16 length;
  int16 data[PDU_DATA_LEN];
}GeneralPDU;
typedef struct{
  Uint16		bytes;																// variable storage bytes
  Uint16		ofst;																	// variable storage offset
  Uint16		base;
}PlotCurveInfo;
typedef struct{
  Uint8 number;
  Uint8 samplingScale;//1:62.5us 2:125us
  Uint8 enable;//1:enable 0:disable
  PlotCurveInfo curveInfo[MAX_WAVE_PLOT_NUM];
}PlotControlPrm;
}

#endif // COMGLOBAL_H

