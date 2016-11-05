#ifndef MANAGERDLL_GLOBAL_H
#define MANAGERDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MANAGERDLL_LIBRARY)
#  define MANAGERDLLSHARED_EXPORT Q_DECL_EXPORT __stdcall
#else
#  define MANAGERDLLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MANAGERDLL_GLOBAL_H
