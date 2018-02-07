#include "pcdebug.h"
#include "pcdebug_p.h"
#include "comglobal.h"
#include "ServoDriverComDll.h"

COM_USE_NAMESPACE

PcDebugPrivate::PcDebugPrivate():IComPrivate()
{

}
PcDebugPrivate::~PcDebugPrivate()
{

}

PcDebug::PcDebug():ICom(*new PcDebugPrivate())
{
  Q_D(PcDebug);
  d->m_objectName="PcDebug";
//  d->m_comType=ICOM_TYPE_PCDEBUG;
  d->m_comType=ICOM_TYPE_RNNET;
}
PcDebug::~PcDebug()
{

}

errcode_t PcDebug::open(void (*processCallBack)(void *, short *), void *parameter)
{
  Q_D(PcDebug);
  int16_t ret=GTSD_CMD_Open(processCallBack,parameter,d->m_comType);
  return ret;
}

errcode_t PcDebug::close()
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Close(d->m_comType);
  return ret;
}

errcode_t PcDebug::setServoEnable(uint8_t axis, bool on)
{
  Q_D(PcDebug);

  int16_t ret=-1;
  if(on)
    ret=GTSD_CMD_SetServoOn(axis,d->m_comType);
  else
    ret=GTSD_CMD_SetServoOff(axis,d->m_comType);
  return ret;
}

errcode_t PcDebug::checkServoIsEnable(uint8_t axis, bool &enable)
{
  Q_D(PcDebug);

  int16_t ret=-1;
  SERVO_STATE state;
  ret=GTSD_CMD_GetServoState(axis,&state,d->m_comType);
  if(state.serv_ready!=0)
    enable=true;
  else
    enable=false;
  return ret;
}

errcode_t PcDebug::setServoTaskMode(uint8_t axis,ServoTaskMode_t mode)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetServoTaskMode(axis,(ServoTaskMode)mode ,d->m_comType);
  return ret;
}

ServoTaskMode_t PcDebug::currentServoTaskMode(uint8_t axis,errcode_t &errcode)
{
  Q_D(PcDebug);
  SERVO_MODE mode;
  int16_t ret=-1;
  ret=GTSD_CMD_GetServoTaskMode(axis,&mode,d->m_comType);
  errcode=ret;

  return ServoTaskMode_t(mode.usr_mode);
}

errcode_t PcDebug::setIdRef(uint8_t axis ,double idRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetIdRef(axis, idRef, d->m_comType);
  return ret;
}
errcode_t PcDebug::getIdRef(uint8_t axis ,double &value)
{
  Q_D(PcDebug);

  ID_STATE idState;
  int16_t ret=GTSD_CMD_GetIdRef(axis,&idState,d->m_comType);
  value=idState.ctl_id_ref;
  return ret;
}
errcode_t PcDebug::setIqRef(uint8_t axis, double iqRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetIqRef(axis,iqRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getIqRef(uint8_t axis, double &value)
{
  Q_D(PcDebug);

  IQ_STATE iqState;
  int16_t ret=GTSD_CMD_GetIqRef(axis,&iqState,d->m_comType);
  value=iqState.ctl_iq_ref;
  return ret;
}
errcode_t PcDebug::setSpdRef(uint8_t axis,double spdRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetSpdRef(axis,spdRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getSpdRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  SPD_STATE spdState;
  int16_t ret=GTSD_CMD_GetSpdRef(axis,&spdState,d->m_comType);
  value=spdState.ctl_spd_ref;
  return ret;
}
errcode_t PcDebug::setUdRef(uint8_t axis,double udRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetUdRef(axis,udRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getUdRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  UD_STATE udState;
  int16_t ret=GTSD_CMD_GetUdRef(axis,&udState,d->m_comType);
  value=udState.cur_ud;
  return ret;
}
errcode_t PcDebug::setUqRef(uint8_t axis,double uqRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetUqRef(axis,uqRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getUqRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  UQ_STATE uq;
  int16_t ret=GTSD_CMD_GetUqRef(axis,&uq,d->m_comType);
  value=uq.cur_uq;
  return ret;
}
errcode_t PcDebug::setUaRef(uint8_t axis,double uaRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetUaRef(axis,uaRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getUaRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  UA_STATE ua;
  int16_t ret=GTSD_CMD_GetUaRef(axis,&ua,d->m_comType);
  value=ua.cur_ua;
  return ret;
}
errcode_t PcDebug::setUbRef(uint8_t axis,double ubRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetUbRef(axis,ubRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getUbRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  UB_STATE ub;
  int16_t ret=GTSD_CMD_GetUbRef(axis,&ub,d->m_comType);
  value=ub.cur_ub;
  return ret;
}
errcode_t PcDebug::setUcRef(uint8_t axis,double ucRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetUcRef(axis,ucRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getUcRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  UC_STATE uc;
  int16_t ret=GTSD_CMD_GetUcRef(axis,&uc,d->m_comType);
  value=uc.cur_uc;
  return ret;
}
errcode_t PcDebug::setPosAdjRef(uint8_t axis,double posAdjRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetPosAdjRef(axis,posAdjRef,d->m_comType);
  return ret;
}
errcode_t PcDebug::getPosAdjRef(uint8_t axis,double &value)
{
  Q_D(PcDebug);

  POS_ADJ_STATE pos;
  int16_t ret=GTSD_CMD_GetPosAdjRef(axis,&pos,d->m_comType);
  value=pos.rsv_pos_in;
  return ret;
}
errcode_t PcDebug::setPosRef(uint8_t axis,double posRef)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_SetPosRef(axis,int32(posRef),d->m_comType);
  return ret;
}
errcode_t PcDebug::sendGeneralCmd(uint8_t axis, GeneralPDU &pdu)
{
  Q_D(PcDebug);

  GENERALFUNCTION func;
  errno_t err;
  int16_t buf[16]={0};
  //王彬data[0],data[1],data[2]存放协议的东西
  if(pdu.subId>0)//有二级ID
  {
    buf[3]=pdu.subId;
    err=memcpy_s(&buf[4],sizeof(buf)*sizeof(int16_t),pdu.data,pdu.length*sizeof(int16_t));
    if(err)
    {
      printf("Error executing memcpy_s.\n");
      return err;
    }
    func.dataLenth=pdu.length+1+3;
  }
  else
  {
    err=memcpy_s(&buf[3],sizeof(buf)*sizeof(int16_t),pdu.data,pdu.length*sizeof(int16_t));
    if(err)
    {
      printf("Error executing memcpy_s.\n");
      return err;
    }
    func.dataLenth=pdu.length+3;
  }
  func.cmd=pdu.cmd;
  func.mode=pdu.mode;

  func.data=buf;
  int16_t ret=GTSD_CMD_ProcessorGeneralFunc(axis, &func, d->m_comType);
  if(ret!=0)
  {
    ret=GTSD_CMD_ProcessorGeneralFunc(axis, &func, d->m_comType);
    if(ret!=0)
      return ret;
  }
  if(pdu.mode==GENERAL_PDU_READ)//1:为读    0：写
  {
    if(pdu.subId>0)
    {
      memcpy_s(pdu.data,sizeof(pdu.data)*sizeof(int16_t),&buf[1],pdu.length*sizeof(int16_t));
    }
    else
    {
      memcpy_s(pdu.data,sizeof(pdu.data)*sizeof(int16_t),&buf[0],pdu.length*sizeof(int16_t));
    }
  }

  return ret;
}

errcode_t PcDebug::readDSPVersion(uint8_t dspInx,uint16_t &version)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_ReadProcessorVersion(dspInx*2,version,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFPGAVersion(uint8_t fpgaInx,uint16_t &version)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_ReadFirmwareVersion(fpgaInx,version,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFPGAYearDay(uint8_t fpgaInx,uint16_t &year,uint16_t &day)
{
  Q_D(PcDebug);

  VERSION v;
  int16_t ret=GTSD_CMD_ReadFpgaVersion(fpgaInx,&v,d->m_comType);
  year=v.usYear;
  day=v.usMonthDay;
  return ret;
}

errcode_t PcDebug::hex2LdrFormat(const wstring &hexFile,const wstring &ldrFile)
{
  Q_D(PcDebug);

  wstring hex=hexFile;
  wstring ldr=ldrFile;
  int16_t ret=GTSD_CMD_Hex2Ldr(hex,ldr,d->m_comType);
  return ret;
}

errcode_t PcDebug::uartBootHandler(uint8_t dspInx,const wstring &filePath,int32_t baudRate, int16_t cmd, const string& inputKey, ProcessCallBackHandler, void* prm)
{
  Q_D(PcDebug);

  wstring file=filePath;
  string key=inputKey;
  int16_t ret=GTSD_CMD_ProcessorUartBootHandler(dspInx*2,file,\
                                                baudRate,cmd,key,\
                                                processCallBack,prm,d->m_comType);
  return ret;
}

errcode_t PcDebug::resetDSP(uint8_t dspInx)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_ResetSystem(dspInx*2,d->m_comType);
  return ret;
}

bool PcDebug::checkResetFinish(uint8_t dspInx, errcode_t &errCode)
{
  Q_D(PcDebug);

  bool finish=false;
  int16_t ret=GTSD_CMD_ResetSystem(dspInx*2,finish,d->m_comType);
  errCode=ret;
  return finish;
}
errcode_t PcDebug::downLoadDSPFLASH(uint8_t dspInx, const wstring &fileName, void (*processCallBack)(void *, short *), void *parameters)
{
  Q_D(PcDebug);

  wstring file=fileName;
  int16_t ret=GTSD_CMD_ProcessorFlashHandler(dspInx*2,file,processCallBack,parameters,d->m_comType);
  return ret;
}

errcode_t PcDebug::downLoadFPGAFLASH(uint8_t fpgaInx, const wstring &fileName, void (*processCallBack)(void *, short *), void *parameters)
{
  Q_D(PcDebug);

  wstring file=fileName;
  int16_t ret=GTSD_CMD_FirmwareFlashHandler(fpgaInx,file,processCallBack,parameters,d->m_comType);
  return ret;
}
errcode_t PcDebug::readEEPROM(uint16_t ofst, uint8_t* value, uint16_t num,uint8_t cs)
{
  Q_D(PcDebug);

  int16_t ret=-1;
  EEPROMSelect select=EEPROMSelect(cs);
  switch (select)
  {
  case EEPROM_CS_CONTROL:
    ret=GTSD_CMD_ReadEEPROM(0,ofst,value,num,d->m_comType);
    break;
  case EEPROM_CS_POWER:
    ret=GTSD_CMD_ReadEEPROMExt(0,ofst,value,num,d->m_comType);
    break;
  default:
    ret=GTSD_CMD_ReadEEPROM(0,ofst,value,num,d->m_comType);
    break;
  }

  return ret;
}

errcode_t PcDebug::writeEEPROM(uint16_t ofst, const uint8_t* value, uint16_t num,uint8_t cs)
{
  Q_D(PcDebug);

  int16_t ret=-1;
  EEPROMSelect select=EEPROMSelect(cs);
  uint8_t* ptr=new uint8_t[num];
  memcpy_s(ptr,num,value,num);
  switch (select)
  {
  case EEPROM_CS_CONTROL:
    ret=GTSD_CMD_WriteEEPROM(0,ofst,ptr,num,d->m_comType);
    break;
  case EEPROM_CS_POWER:
    ret=GTSD_CMD_WriteEEPROMExt(0,ofst,ptr,num,d->m_comType);
    break;
  default:
    ret=GTSD_CMD_WriteEEPROM(0,ofst,ptr,num,d->m_comType);
    break;
  }

  delete ptr;
  return ret;
}

NetCardInfo PcDebug::getNetCardInformation()
{
  NetCardInfo carInf;
  carInf=NetCardInfo(GTSD_CMD_GetNetCardMsg());
  return carInf;
}
errcode_t PcDebug::startPlot(const PlotControlPrm &ctrPrm)
{
  Q_D(PcDebug);
  int16_t ret=-1;
  WAVE_BUF_PRM bufPrm;
  bufPrm.cmd.bit.ENP=1;
  bufPrm.cmd.bit.TIM=ctrPrm.samplingScale;
  bufPrm.cmd.bit.NUM=ctrPrm.number;
  if(ctrPrm.number>ctrPrm.curveInfo.size())
    return COM_ERR_RANGE;
  PlotCurveInfoConstIterator cIt=ctrPrm.curveInfo.cbegin();
  int i=0;
  for(;cIt!=ctrPrm.curveInfo.cend();cIt++)
  {
    bufPrm.inf[i].base=(*cIt).base;
    bufPrm.inf[i].bytes=(*cIt).bytes;
    bufPrm.inf[i].ofst=(*cIt).ofst;
    i++;
  }

  int16_t axis=ctrPrm.dspIndex*2;
  ret=GTSD_CMD_StartPlot(axis,bufPrm,d->m_comType);
  return ret;
}

errcode_t PcDebug::stopPlot(const PlotControlPrm &ctrPrm)
{
  Q_D(PcDebug);
  int16_t ret=-1;
  WAVE_BUF_PRM bufPrm;
  bufPrm.cmd.bit.ENP=0;
  bufPrm.cmd.bit.TIM=ctrPrm.samplingScale;
  bufPrm.cmd.bit.NUM=ctrPrm.number;

  if(ctrPrm.number>ctrPrm.curveInfo.size())
    return COM_ERR_RANGE;
  PlotCurveInfoConstIterator cIt=ctrPrm.curveInfo.cbegin();
  int i=0;
  for(;cIt!=ctrPrm.curveInfo.cend();cIt++)
  {
    bufPrm.inf[i].base=(*cIt).base;
    bufPrm.inf[i].bytes=(*cIt).bytes;
    bufPrm.inf[i].ofst=(*cIt).ofst;
    i++;
  }

  int16_t axis=ctrPrm.dspIndex*2;
  ret=GTSD_CMD_StopPlot(axis,bufPrm,d->m_comType);
  return ret;
}

errcode_t PcDebug::getPlotData(const PlotControlPrm &ctrPrm, CurveList &curveList)
{
  Q_D(PcDebug);
  errcode_t ret=-1;
  int16_t axis=ctrPrm.dspIndex*2;
  int32_t retNumber;
  double *ptr;

  curveList.clear();
  ret=GTSD_CMD_PcGetWaveData(axis, &ptr, retNumber,d->m_comType);

  if(retNumber>0)
  {
    for(int i=0;i<ctrPrm.number;i++)
    {
      CurveDatas curveDatas;
      double value;
      for(int col=0;col<retNumber;col++)
      {
        value=*(ptr+i*PLOT_ARRAY_COLUMN_SIZE+col);
        curveDatas.push_back(value);
      }
      curveList.push_back(curveDatas);
    }
  }
  return ret;
}

errcode_t PcDebug::enableCRC(bool enable)
{
  //mode :1 force to on
  //mode: 2 force to off
  if(enable)
    GTSD_CMD_FroceCheckMode(1);
  else
    GTSD_CMD_FroceCheckMode(2);
  return 0;
}




//----------------------------------protected------------------------
//--------读写RAM操作------------------
errcode_t PcDebug::writeRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Write16BitByAdr(axis,ofst,value,&page,d->m_comType);
  return ret;
}

errcode_t PcDebug::readRAM16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Read16BitByAdr(axis,ofst,&value,&page,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Write32BitByAdr(axis,ofst,value,&page,d->m_comType);
  return ret;
}

errcode_t PcDebug::readRAM32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Read32BitByAdr(axis,ofst,&value,&page,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Write64BitByAdr(axis,ofst,value,&page,d->m_comType);
  return ret;
}

errcode_t PcDebug::readRAM64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)
{
  Q_D(PcDebug);

  int16_t ret=GTSD_CMD_Read64BitByAdr(axis,ofst,&value,&page,d->m_comType);
  return ret;
}

//--------读写铁电FLASH操作------------------
errcode_t PcDebug::writeFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Write16BitByAdr(axis,ofst,value,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFLASH16(uint8_t axis,uint16_t ofst,uint8_t page,int16_t &value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Read16BitByAdr(axis,ofst,&value,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Write32BitByAdr(axis,ofst,value,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFLASH32(uint8_t axis,uint16_t ofst,uint8_t page,int32_t &value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Read32BitByAdr(axis,ofst,&value,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Write64BitByAdr(axis,ofst,value,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFLASH64(uint8_t axis,uint16_t ofst,uint8_t page,int64_t &value)
{
  Q_D(PcDebug);

  UN_USED(page);
  int16_t ret=GTSD_CMD_Fram_Read64BitByAdr(axis,ofst,&value,d->m_comType);
  return ret;
}

//------------FPGA寄存器操作----------------
errcode_t PcDebug::readFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t &value,uint16_t base)
{
  Q_D(PcDebug);

  UN_USED(base);
  int16_t ret=GTSD_CMD_Get16bitFPGAByAddr(fpgaInx,address,&value,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeFPGAReg16(uint8_t fpgaInx,uint16_t address,int16_t value,uint16_t base)
{
  Q_D(PcDebug);

  UN_USED(base);
  int16_t ret=GTSD_CMD_Set16bitFPGAByAddr(fpgaInx,address,value,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t &value,uint16_t base)
{
  Q_D(PcDebug);

  UN_USED(base);
  int16_t ret=GTSD_CMD_Get32bitFPGAByAddr(fpgaInx,address,&value,d->m_comType);
  return ret;
}

errcode_t PcDebug::writeFPGAReg32(uint8_t fpgaInx,uint16_t address,int32_t value,uint16_t base)
{
  Q_D(PcDebug);

  UN_USED(base);
  int16_t ret=GTSD_CMD_Set32bitFPGAByAddr(fpgaInx,address,value,d->m_comType);
  return ret;
}

errcode_t PcDebug::readFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t &value,uint16_t base)
{
  UN_USED(fpgaInx);
  UN_USED(address);
  UN_USED(value);
  UN_USED(base);
  return -1;
}

errcode_t PcDebug::writeFPGAReg64(uint8_t fpgaInx,uint16_t address,int64_t value,uint16_t base)
{
  UN_USED(fpgaInx);
  UN_USED(address);
  UN_USED(value);
  UN_USED(base);
  return -1;
}
