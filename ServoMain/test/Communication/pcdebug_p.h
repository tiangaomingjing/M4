#ifndef PCDEBUG_P_H
#define PCDEBUG_P_H
#include "icom_p.h"

COM_NAMESPACE_BEGIN

class PcDebugPrivate:IComPrivate
{
  Q_DECLARE_PUBLIC(PcDebug)
public:
  PcDebugPrivate();
  virtual ~PcDebugPrivate();
  int test;
};
COM_NAMESPACE_END

#endif // PCDEBUG_P_H

