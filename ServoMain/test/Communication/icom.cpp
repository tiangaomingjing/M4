#include "icom.h"
#include "icom_p.h"

COM_USE_NAMESPACE

//private class
IComPrivate::IComPrivate()
{

}
IComPrivate::~IComPrivate()
{

}

ICom::ICom(const string &objectName,IComType comType):d_ptr(new IComPrivate())
{
  Q_D(ICom);
  d->q_ptr=this;
  d->m_objectName=objectName;
  d->m_comType=comType;

}
ICom::~ICom()
{
  delete d_ptr;
}

string ICom::iComObjectName(void) const
{
  Q_D(const ICom);
  return d->m_objectName;
}

IComType ICom::iComType(void) const
{
  Q_D(const ICom);
  return d->m_comType;
}
void ICom::setIComObjectName(const string &objName)
{
  Q_D(ICom);
  d->m_objectName=objName;
}

void ICom::setIComType(IComType comtype)
{
  Q_D(ICom);
  d->m_comType=comtype;
}

ICom::ICom(IComPrivate &d):d_ptr(&d)
{
  d_ptr->q_ptr=this;
}

errcode_t ICom::writeRAM(uint8_t axis,uint16_t ofst,uint8_t page,double value ,uint8_t bytesNum)
{
  errcode_t ret=1;
  switch (bytesNum)
  {
  case 2:
    ret=writeRAM16(axis,ofst,page,(int16_t)value);
    break;
  case 4:
    ret=writeRAM32(axis,ofst,page,(int32_t)value);
    break;
  case 8:
    ret=writeRAM64(axis,ofst,page,(int64_t)value);
    break;
  default:
    ret=writeRAM16(axis,ofst,page,(int16_t)value);
    break;
  }
  return ret;
}

errcode_t ICom::readRAM(uint8_t axis,uint16_t ofst,uint8_t page,double &value ,uint8_t bytesNum)
{
  errcode_t ret=-1;
  switch (bytesNum)
  {
  case 2:
    {
      int16_t v;
      ret=readRAM16(axis,ofst,page,v);
      value=v;
    }
    break;
  case 4:
    {
      int32_t v;
      ret=readRAM32(axis,ofst,page,v);
      value=v;
    }
    break;
  case 8:
    {
      int64_t v;
      ret=readRAM64(axis,ofst,page,v);
      value=v;
    }
    break;
  default:
    {
      int16_t v;
      ret=readRAM16(axis,ofst,page,v);
      value=v;
    }
    break;
  }
  return ret;
}

errcode_t ICom::writeFLASH(uint8_t axis,uint16_t ofst,uint8_t page,double value ,uint8_t bytesNum)
{
  errcode_t ret=-1;
  switch (bytesNum)
  {
  case 2:
    ret=writeFLASH16(axis,ofst,page,(int16_t)value);
    break;
  case 4:
    ret=writeFLASH32(axis,ofst,page,(int32_t)value);
    break;
  case 8:
    ret=writeFLASH64(axis,ofst,page,(int64_t)value);
    break;
  default:
    ret=writeFLASH16(axis,ofst,page,(int16_t)value);
    break;
  }
  return ret;
}

errcode_t ICom::readFLASH(uint8_t axis,uint16_t ofst,uint8_t page,double &value ,uint8_t bytesNum)
{
  errcode_t ret=-1;
  switch (bytesNum)
  {
  case 2:
    {
      int16_t v;
      ret=readFLASH16(axis,ofst,page,v);
      value=v;
    }
    break;
  case 4:
    {
      int32_t v;
      ret=readFLASH32(axis,ofst,page,v);
      value=v;
    }
    break;
  case 8:
    {
      int64_t v;
      ret=readFLASH64(axis,ofst,page,v);
      value=v;
    }
    break;
  default:
    {
      int16_t v;
      ret=readFLASH16(axis,ofst,page,v);
      value=v;
    }
    break;
  }
  return ret;
}
errcode_t ICom::readFPGAReg(uint8_t fpgaInx,uint16_t address,double &value,uint8_t bytesNum,uint16_t base)
{
  errcode_t ret=-1;
  switch (bytesNum)
  {
  case 2:
    {
      int16_t v;
      ret=readFPGAReg16(fpgaInx,address,v,base);
      value=v;
    }
    break;
  case 4:
    {
      int32_t v;
      ret=readFPGAReg32(fpgaInx,address,v,base);
      value=v;
    }
    break;
  case 8:
    {
      int64_t v;
      ret=readFPGAReg64(fpgaInx,address,v,base);
      value=v;
    }
    break;
  default:
    {
      int16_t v;
      ret=readFPGAReg16(fpgaInx,address,v,base);
      value=v;
    }
    break;
  }
  return ret;
}

errcode_t ICom::writeFPGAReg(uint8_t fpgaInx,uint16_t address,double value,uint8_t bytesNum,uint16_t base)
{
  errcode_t ret=-1;
  switch (bytesNum)
  {
  case 2:
    ret=writeFPGAReg16(fpgaInx,address,(int16_t)value,base);
    break;
  case 4:
    ret=writeFPGAReg32(fpgaInx,address,(int32_t)value,base);
    break;
  case 8:
    ret=writeFPGAReg64(fpgaInx,address,(int64_t)value,base);
    break;
  default:
    ret=writeFPGAReg16(fpgaInx,address,(int16_t)value,base);
    break;
  }
  return ret;
}
