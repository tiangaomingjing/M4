#ifndef ICOM_H
#define ICOM_H
#include <comglobal.h>
using namespace COM;
using namespace std;

namespace NetDriver
{

#define ProcessCallBackHandler void (*processCallBack)(void *argv,int16* value)

class IComPrivate;
class ICom
{
  Q_DECLARE_PRIVATE(ICom)
public:
  ICom();
  virtual ~ICom();

  virtual bool open(ProcessCallBackHandler,void *parameter)=0;
  virtual void close()=0;

  //----------伺服相关操作------------------------
  virtual bool setServoEnable(bool on)=0;
  virtual bool checkServoIsEnable()=0;

  virtual bool setServoTaskMode(int16 axis,ServoTaskMode mode)=0;
  virtual ServoTaskMode currentServoTaskMode(int16 axis)=0;

  virtual bool setIdRef(int16 axis ,double idRef)=0;
  virtual bool getIdRef(int16 axis ,double &value);
  virtual bool setIqRef(int16 axis, double iqRef)=0;
  virtual bool getIqRef(int16 axis, double &value)=0;
  virtual bool setSpdRef(int16 axis,double spdRef)=0;
  virtual bool getSpdRef(int16 axis,double &value)=0;
  virtual bool setUdRef(int16 axis,double udRef)=0;
  virtual bool getUdRef(int16 axis,double &value)=0;
  virtual bool setUqRef(int16 axis,double uqRef)=0;
  virtual bool getUqRef(int16 axis,double &value)=0;
  virtual bool setUaRef(int16 axis,double uaRef)=0;
  virtual bool getUaRef(int16 axis,double &value)=0;
  virtual bool setUbRef(int16 axis,double ubRef)=0;
  virtual bool getUbRef(int16 axis,double &value)=0;
  virtual bool setUcRef(int16 axis,double ucRef)=0;
  virtual bool getUcRef(int16 axis,double &value)=0;
  virtual bool setPosAdjRef(int16 axis,double posAdjRef)=0;
  virtual bool getPosAdjRef(int16 axis,double &value)=0;
  virtual bool setPosRef(int16 axis,double posRef)=0;

  //--------读写RAM操作------------------
  virtual bool writeRAM(int16 axis,int16 ofst,Uint8 page,double value ,Uint8 wordNum)=0;
  virtual bool readRAM(int16 axis,int16 ofst,Uint8 page,double &value ,Uint8 wordNum)=0;

  //--------读写铁电FLASH操作------------------
  virtual bool writeFLASH(int16 axis,int16 ofst,Uint8 page,double value ,Uint8 wordNum)=0;
  virtual bool readFLASH(int16 axis,int16 ofst,Uint8 page,double &value ,Uint8 wordNum)=0;

  //--------读写通用指令-----------
  //!读取后的结果也在pdu里面
  virtual bool sendGeneralCmd(int16 axis,GeneralPDU &pdu)=0;

  //---------DSP操作相关---------------------------
  virtual bool readDSPVersion(int16 dspInx,Uint16 &version)=0;
  virtual bool readFPGAVersion(int16 fpgaInx,Uint16 &version)=0;
  virtual bool readFPGAYearDay(int16,Uint16 &year,Uint16 &day)=0;

  virtual bool hex2LdrFormat(const wstring &hexFile,const wstring &ldrFile)=0;
  virtual bool uartBootHandler(int16 dspInx,const wstring &filePath,int32 baudRate, int16 cmd, const string& inputKey, ProcessCallBackHandler, void* prm)=0;

  virtual bool resetDSP(int16 dspInx)=0;
  virtual bool checkResetFinish(int16 dspInx)=0;

  //-----------EEPROM读写---------------------
  virtual bool readEEPROM(Uint16 ofst, Uint8* value, Uint16 num,Uint8 cs)=0;
  virtual bool writeEEPROM(Uint16 ofst, const Uint8* value, Uint16 num,Uint8 cs)=0;

  //------------获得网卡信息------------------
  virtual NetCardInfo getNetCardInformation(void)=0;

protected:
  ICom(IComPrivate &d);
  IComPrivate *const d_ptr;

};

}


#endif // ICOM_H
