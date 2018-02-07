#ifndef COMGLOBAL_H
#define COMGLOBAL_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
using namespace std;

#define COM_NAMESPACE_BEGIN namespace ComDriver {
#define COM_NAMESPACE_END }
#define COM_USE_NAMESPACE using namespace ComDriver;

COM_NAMESPACE_BEGIN
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

#define COM_DECL_EXPORT __declspec(dllexport)
#define COM_DECL_IMPORT __declspec(dllimport)

#if defined(COM_SHARED_LIBRARY)
#  define COMSHARED_EXPORT COM_DECL_EXPORT
#else
#  define COMSHARED_EXPORT COM_DECL_IMPORT
#endif

#define COM_PDU_DATA_LEN 4
#define COM_MAX_WAVE_PLOT_NUM 20
#define PLOT_ARRAY_COLUMN_SIZE 10000

#define UN_USED(x) (void)x


typedef		char							int8_t;
typedef		short							int16_t;
typedef		long							int32_t;
typedef		long long						int64_t;

typedef		unsigned char					uint8_t;
typedef		unsigned short					uint16_t;
typedef		unsigned long					uint32_t;
typedef		unsigned long long				uint64_t;
//------------------------------------------------------------------------------------------------
typedef		volatile signed char			vint8_t;
typedef		volatile short					vint16_t;
typedef		volatile long					vint32_t;

typedef		volatile unsigned char			vuint8_t;
typedef		volatile unsigned short			vuint16_t;
typedef		volatile unsigned long			vuint32_t;
//------------------------------------------------------------------------------------------------
typedef		const	uint8_t					cuint8_t;
typedef		const	uint16_t					cuint16_t;
typedef		const	uint32_t					cuint32_t;
//------------------------------------------------------------------------------------------------
typedef std::list<std::vector<double>> CurveList;
typedef std::list<std::vector<double>>::iterator CurveListIterator;
typedef std::list<std::vector<double>>::const_iterator CurveListConstIterator;
typedef std::vector<double> CurveDatas;
typedef std::vector<double>::iterator CurveDatasIterator;
typedef std::vector<double>::const_iterator CurveDatasConstIterator;
typedef int16_t errcode_t;
#define ProcessCallBackHandler void (*processCallBack)(void *argv,short* value)

typedef enum{
  COM_ERR_RANGE=-1,
}ComErrorCode;

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
}ServoTaskMode_t;
typedef enum{
  NET_1000M,
  NET_ERR,
  NET_NOT1000M,
  NET_NOCARD
}NetCardInfo;

typedef enum{
  ICOM_TYPE_PCDEBUG,
  ICOM_TYPE_RNNET,
  ICOM_TYPE_SOCKET,
  ICOM_TYPE_VIRTUAL
}IComType;

typedef enum{
  GENERAL_PDU_WRITE=0,
  GENERAL_PDU_READ=1
}GenPDUMode;

typedef enum{
  EEPROM_CS_POWER,
  EEPROM_CS_CONTROL
}EEPROMSelect;
/* |mode|cmd|len|<-------data------>|
 * |_ _ |_ _|_ _|_ _|_ _|_ _|_ _|_ _|
 * len是指data的长度
 * 1级指令cmd<41  data[0]开始就是数据
 * 2级指令cmd=41  data[0]是2级ID data[1]开始是数据
 * 3与王彬结构体少了前面的3个data,所以在调他的函数时要插多3个word
 * */
typedef struct{
  uint16_t mode;
  uint16_t cmd;
  uint16_t length;
  uint16_t subId;
  int16_t data[COM_PDU_DATA_LEN];//一次最大传64位
}GeneralPDU;
typedef struct{
  uint16_t		bytes;																// variable storage bytes
  uint16_t		ofst;																	// variable storage offset
  uint16_t		base;
}PlotCurveInfo;

typedef struct{
  uint8_t dspIndex;
  uint8_t number;
  uint8_t samplingScale;//1:62.5us 2:125us
  uint8_t enable;//1:enable 0:disable
  vector<PlotCurveInfo>curveInfo;
}PlotControlPrm;
typedef std::vector<PlotCurveInfo>::const_iterator PlotCurveInfoConstIterator;
typedef std::vector<PlotCurveInfo>::iterator PlotCurveInfoIterator;

COM_NAMESPACE_END

#endif // COMGLOBAL_H

