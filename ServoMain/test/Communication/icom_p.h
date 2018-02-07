#ifndef ICOM_P_H
#define ICOM_P_H
#include "comglobal.h"
COM_NAMESPACE_BEGIN

class ICom;
class IComPrivate
{
  Q_DECLARE_PUBLIC(ICom)
 public:
   IComPrivate();
  virtual ~IComPrivate();
protected:
  ICom *q_ptr;
  std::string m_objectName;
  IComType m_comType;
};

COM_NAMESPACE_END

#endif // ICOM_P_H

