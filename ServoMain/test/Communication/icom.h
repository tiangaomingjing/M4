#ifndef ICOM_H
#define ICOM_H
#include <comglobal.h>
using namespace std;

COM_NAMESPACE_BEGIN

class IComPrivate;
class COMSHARED_EXPORT ICom
{
  Q_DECLARE_PRIVATE(ICom)
public:
  ICom(const string &objectName,IComType comType);
  virtual ~ICom();

  string iComObjectName(void) const;
  IComType iComType(void) const;

  void setIComObjectName(const string &objName);
  void setIComType(IComType comtype);

  virtual errcode_t open(ProcessCallBackHandler,void *parameter)=0;
  virtual errcode_t close()=0;

  //----------伺服相关操作------------------------
  virtual errcode_t setServoEnable(uint8_t axis,bool on)=0;
  virtual errcode_t checkServoIsEnable(uint8_t axis,bool &enable)=0;

  virtual errcode_t setServoTaskMode(uint8_t axis,ServoTaskMode_t mode)=0;
  virtual ServoTaskMode_t currentServoTaskMode(uint8_t axis,errcode_t &errCode)=0;

  virtual errcode_t setIdRef(uint8_t axis ,double idRef)=0;
  virtual errcode_t getIdRef(uint8_t axis ,double &value)=0;
  virtual errcode_t setIqRef(uint8_t axis, double iqRef)=0;
  virtual errcode_t getIqRef(uint8_t axis, double &value)=0;
  virtual errcode_t setSpdRef(uint8_t axis,double spdRef)=0;
  virtual errcode_t getSpdRef(uint8_t axis,double &value)=0;
  virtual errcode_t setUdRef(uint8_t axis,double udRef)=0;
  virtual errcode_t getUdRef(uint8_t axis,double &value)=0;
  virtual errcode_t setUqRef(uint8_t axis,double uqRef)=0;
  virtual errcode_t getUqRef(uint8_t axis,double &value)=0;
  virtual errcode_t setUaRef(uint8_t axis,double uaRef)=0;
  virtual errcode_t getUaRef(uint8_t axis,double &value)=0;
  virtual errcode_t setUbRef(uint8_t axis,double ubRef)=0;
  virtual errcode_t getUbRef(uint8_t axis,double &value)=0;
  virtual errcode_t setUcRef(uint8_t axis,double ucRef)=0;
  virtual errcode_t getUcRef(uint8_t axis,double &value)=0;
  virtual errcode_t setPosAdjRef(uint8_t axis,double posAdjRef)=0;
  virtual errcode_t getPosAdjRef(uint8_t axis,double &value)=0;
  virtual errcode_t setPosRef(uint8_t axis,double posRef)=0;

  //--------读写RAM操作------------------
  virtual errcode_t writeRAM(uint8_t axis,uint16_t ofst,uint8_t page,double value ,uint8_t bytesNum);
  virtual errcode_t readRAM(uint8_t axis,uint16_t ofst,uint8_t page,double &value ,uint8_t bytesNum);

  //--------读写铁电FLASH操作------------------
  virtual errcode_t writeFLASH(uint8_t axis,uint16_t ofst,uint8_t page,double value ,uint8_t bytesNum);
  virtual errcode_t readFLASH(uint8_t axis,uint16_t ofst,uint8_t page,double &value ,uint8_t bytesNum);

  //--------读写通用指令-----------
  //!读取后的结果也在pdu里面
  virtual errcode_t sendGeneralCmd(uint8_t axis,GeneralPDU &pdu)=0;

  //---------DSP操作相关---------------------------
  virtual errcode_t readDSPVersion(uint8_t dspInx,uint16_t &version)=0;
  virtual errcode_t readFPGAVersion(uint8_t fpgaInx,uint16_t &version)=0;
  virtual errcode_t readFPGAYearDay(uint8_t fpgaInx,uint16_t &year,uint16_t &day)=0;

  virtual errcode_t hex2LdrFormat(const wstring &hexFile,const wstring &ldrFile)=0;
  virtual errcode_t uartBootHandler(uint8_t dspInx,const wstring &filePath,int32_t baudRate, int16_t cmd, const string& inputKey, ProcessCallBackHandler, void* prm)=0;

  virtual errcode_t resetDSP(uint8_t dspInx)=0;
  virtual bool checkResetFinish(uint8_t dspInx,errcode_t &errCode)=0;

  //----------软件、固件烧写----------------
  virtual errcode_t downLoadDSPFLASH(uint8_t dspInx,const wstring &fileName,ProcessCallBackHandler,void *parameters)=0;
  virtual errcode_t downLoadFPGAFLASH(uint8_t fpgaInx,const wstring &fileName,ProcessCallBackHandler,void *parameters)=0;

  //-----------EEPROM读写---------------------
  virtual errcode_t readEEPROM(uint16_t ofst, uint8_t* value, uint16_t num,uint8_t cs)=0;
  virtual errcode_t writeEEPROM(uint16_t ofst, const uint8_t* value, uint16_t num,uint8_t cs)=0;

  //------------获得网卡信息------------------
  virtual NetCardInfo getNetCardInformation(void)=0;

  //------------画图相关---------------------
  virtual errcode_t startPlot(const PlotControlPrm &ctrPrm)=0;
  virtual errcode_t stopPlot(const PlotControlPrm &ctrPrm)=0;
  virtual errcode_t getPlotData(const PlotControlPrm &ctrPrm,CurveList &curveList)=0;

  //------------FPGA寄存器操作----------------
  virtual errcode_t readFPGAReg(uint8_t fpgaInx,uint16_t address,double &value,uint8_t bytesNum,uint16_t base=0);
  virtual errcode_t writeFPGAReg(uint8_t fpgaInx,uint16_t address,double value,uint8_t bytesNum,uint16_t base=0);

  virtual errcode_t enableCRC(bool enable)=0;

protected:
  //--------读写RAM操作------------------
  virtual errcode_t writeRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)=0;
  virtual errcode_t readRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)=0;
  virtual errcode_t writeRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)=0;
  virtual errcode_t readRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)=0;
  virtual errcode_t writeRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)=0;
  virtual errcode_t readRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)=0;

  //--------读写铁电FLASH操作------------------
  virtual errcode_t writeFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)=0;
  virtual errcode_t readFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)=0;
  virtual errcode_t writeFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)=0;
  virtual errcode_t readFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)=0;
  virtual errcode_t writeFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)=0;
  virtual errcode_t readFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)=0;

  //------------FPGA寄存器操作----------------
  virtual errcode_t readFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t &value,uint16_t base)=0;
  virtual errcode_t writeFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t value,uint16_t base)=0;
  virtual errcode_t readFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t &value,uint16_t base)=0;
  virtual errcode_t writeFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t value,uint16_t base)=0;
  virtual errcode_t readFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t &value,uint16_t base)=0;
  virtual errcode_t writeFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t value,uint16_t base)=0;

protected:
  ICom(IComPrivate &d);
  IComPrivate *const d_ptr;

};

COM_NAMESPACE_END


#endif // ICOM_H
