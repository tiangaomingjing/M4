#ifndef CFGBRAKE_GLOBAL_H
#define CFGBRAKE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CFGBRAKE_LIBRARY)
#  define CFGBRAKESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CFGBRAKESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CFGBRAKE_GLOBAL_H