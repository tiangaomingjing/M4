#ifndef ICOM_P_H
#define ICOM_P_H
#include "comglobal.h"
using namespace COM;
namespace NetDriver
{
class ICom;
class IComPrivate
{
  Q_DECLARE_PUBLIC(ICom)
 public:
   IComPrivate();
  virtual ~IComPrivate();
protected:
  ICom *q_ptr;
};
}

#endif // ICOM_P_H

