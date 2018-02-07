#ifndef PCDEBUG_H
#define PCDEBUG_H
#include "icom.h"

COM_NAMESPACE_BEGIN
class PcDebugPrivate;

class COMSHARED_EXPORT PcDebug:public ICom
{
  Q_DECLARE_PRIVATE(PcDebug)
public:
  PcDebug();
  ~PcDebug();

  errcode_t open(void(*processCallBack)(void *, short *), void *parameter)override;
  errcode_t close()override;

  //------伺服操作相关---------
  errcode_t setServoEnable(uint8_t axis, bool on)override;
  errcode_t checkServoIsEnable(uint8_t axis,bool &enable) override;

  errcode_t setServoTaskMode(uint8_t axis,ServoTaskMode_t mode);
  ServoTaskMode_t currentServoTaskMode(uint8_t axis,errcode_t &errcode);

  errcode_t setIdRef(uint8_t axis ,double idRef)override;
  errcode_t getIdRef(uint8_t axis ,double &value)override;
  errcode_t setIqRef(uint8_t axis, double iqRef)override;
  errcode_t getIqRef(uint8_t axis, double &value)override;
  errcode_t setSpdRef(uint8_t axis,double spdRef)override;
  errcode_t getSpdRef(uint8_t axis,double &value)override;
  errcode_t setUdRef(uint8_t axis,double udRef)override;
  errcode_t getUdRef(uint8_t axis,double &value)override;
  errcode_t setUqRef(uint8_t axis,double uqRef)override;
  errcode_t getUqRef(uint8_t axis,double &value)override;
  errcode_t setUaRef(uint8_t axis,double uaRef)override;
  errcode_t getUaRef(uint8_t axis,double &value)override;
  errcode_t setUbRef(uint8_t axis,double ubRef)override;
  errcode_t getUbRef(uint8_t axis,double &value)override;
  errcode_t setUcRef(uint8_t axis,double ucRef)override;
  errcode_t getUcRef(uint8_t axis,double &value)override;
  errcode_t setPosAdjRef(uint8_t axis,double posAdjRef)override;
  errcode_t getPosAdjRef(uint8_t axis,double &value)override;
  errcode_t setPosRef(uint8_t axis,double posRef)override;

  //--------读写通用指令-----------
  //!读取后的结果也在pdu里面
  errcode_t sendGeneralCmd(uint8_t axis, GeneralPDU &pdu)override;
  //---------DSP操作相关---------------------------
  errcode_t readDSPVersion(uint8_t dspInx,uint16_t &version)override;
  errcode_t readFPGAVersion(uint8_t fpgaInx,uint16_t &version)override;
  errcode_t readFPGAYearDay(uint8_t fpgaInx,uint16_t &year,uint16_t &day)override;

  errcode_t hex2LdrFormat(const wstring &hexFile,const wstring &ldrFile)override;
  errcode_t uartBootHandler(uint8_t dspInx,const wstring &filePath,int32_t baudRate, int16_t cmd, const string& inputKey, ProcessCallBackHandler, void* prm)override;

  errcode_t resetDSP(uint8_t dspInx)override;
  bool checkResetFinish(uint8_t dspInx,errcode_t &errCode)override;

  //----------软件、固件烧写----------------
  errcode_t downLoadDSPFLASH(uint8_t dspInx,const wstring &fileName,ProcessCallBackHandler,void *parameters)override;
  errcode_t downLoadFPGAFLASH(uint8_t fpgaInx,const wstring &fileName,ProcessCallBackHandler,void *parameters)override;

  //-----------EEPROM读写---------------------
  errcode_t readEEPROM(uint16_t ofst, uint8_t* value, uint16_t num,uint8_t cs)override;
  errcode_t writeEEPROM(uint16_t ofst, const uint8_t* value, uint16_t num,uint8_t cs)override;

  //------------获得网卡信息------------------
  NetCardInfo getNetCardInformation(void)override;

  //------------画图相关---------------------
  errcode_t startPlot(const PlotControlPrm &ctrPrm)override;
  errcode_t stopPlot(const PlotControlPrm &ctrPrm)override;
  errcode_t getPlotData(const PlotControlPrm &ctrPrm,CurveList &curveList)override;

  errcode_t enableCRC(bool enable)override;


protected:
  //--------读写RAM操作------------------
  errcode_t writeRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)override;
  errcode_t readRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)override;
  errcode_t writeRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)override;
  errcode_t readRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)override;
  errcode_t writeRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)override;
  errcode_t readRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)override;

  //--------读写铁电FLASH操作------------------
  errcode_t writeFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)override;
  errcode_t readFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)override;
  errcode_t writeFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)override;
  errcode_t readFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)override;
  errcode_t writeFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)override;
  errcode_t readFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)override;

  //------------FPGA寄存器操作----------------
  errcode_t readFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t &value,uint16_t base)override;
  errcode_t writeFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t value,uint16_t base)override;
  errcode_t readFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t &value,uint16_t base)override;
  errcode_t writeFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t value,uint16_t base)override;
  errcode_t readFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t &value,uint16_t base)override;
  errcode_t writeFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t value,uint16_t base)override;

};
COM_NAMESPACE_END

#endif // PCDEBUG_H
