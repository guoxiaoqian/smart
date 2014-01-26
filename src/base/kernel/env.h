
#ifndef ENV_H
#define ENV_H

/******system detection*******/
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#   define S_OS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   define S_OS_WIN32
#elif (defined(__linux__) || defined(__linux)) && defined(__x86_64__)
#   define S_OS_LINUX64
#elif (defined(__linux__) || defined(__linux)) && defined(__i686__)
#   define S_OS_LINUX32
#endif

#if defined(S_OS_WIN32) || defined(S_OS_WIN64)
#  define S_OS_WIN
#endif
#if defined(S_OS_LINUX32) || defined(S_OS_LINUX64)
#  define S_OS_LINUX
#endif
/******compiler detection*******/
#if defined(_MSC_VER)
#   define S_CC_MSVC
#elif defined(__GNUC__)
#   define S_CC_GCC
#elif defined(__MINGW32__)
#    define S_CC_MINGW
#  endif

#if defined(__cplusplus)
#   define S_CPP
#endif

//define debug mode
#define S_DEBUG
#ifdef S_DEBUG
#undef NDEBUG
#else
#define NDEBUG
#endif

#endif
