
#ifndef GLOBAL_H
#define GLOBAL_H

#include "env.h"

namespace smart {


#define SMART_VERSION_STR "0.0.0"
/*
   SMART_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define SMART_VERSION 0x000000
/*
   can be used like #if (SMART_VERSION >= SMART_VERSION_CHECK(4, 4, 0))
*/
#define SMART_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))


/*
   Size-dependent types (architechture-dependent byte order)
*/

typedef signed char sint8;         /* 8 bit signed */
typedef unsigned char suint8;      /* 8 bit unsigned */
typedef short sint16;              /* 16 bit signed */
typedef unsigned short suint16;    /* 16 bit unsigned */
typedef int sint32;                /* 32 bit signed */
typedef unsigned int suint32;      /* 32 bit unsigned */
#if defined(S_OS_WIN) && !defined(S_CC_GCC)
typedef __int64 sint64;            /* 64 bit signed */
typedef unsigned __int64 suint64;  /* 64 bit unsigned */
#else
typedef long long sint64;           /* 64 bit signed */
typedef unsigned long long suint64; /* 64 bit unsigned */
#endif

typedef sint64 slonglong;
typedef suint64 sulonglong;

#ifndef SMART_POINTER_SIZE
#  if defined(S_OS_WIN64)
#   define SMART_POINTER_SIZE 8
#  elif defined(S_OS_WIN32)
#   define SMART_POINTER_SIZE 4
#  endif
#endif

}
#endif//GLOBAL_H
