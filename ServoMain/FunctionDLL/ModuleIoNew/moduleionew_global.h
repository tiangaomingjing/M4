#ifndef MODULEIONEW_GLOBAL_H
#define MODULEIONEW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODULEIONEW_LIBRARY)
#  define MODULEIONEWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODULEIONEWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODULEIONEW_GLOBAL_H