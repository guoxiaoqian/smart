#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include "../kernel/env.h"

#define CUR_FILE __FILE__
#define CUR_LINE __LINE__
#define CUR_FUNC __func__

#define SError(format,...) printf("ERROR:"format"\n",##__VA_ARGS__)
#define SWarn(format,...) printf("WARN:"format"\n",##__VA_ARGS__)
#define SInfo(format,...) printf("INFO:"format"\n",##__VA_ARGS__)
#if defined(S_DEBUG)
#   define SDebug(format,...); printf("DEBUG:"format"\n",##__VA_ARGS__);
#   define SReport(format,...); printf("FILE: "__FILE__", LINE: %d:    "format"\n", __LINE__, ##__VA_ARGS__);
#else
#   define SDebug(format,...);
#   define SReport(format,...);
#endif

#define GLOBAL_LOG_ERROR(format,...) SGlobalLog::getLog()->error(CUR_FILE,CUR_LINE,format,##__VA_ARGS__)

class SLog
{
private:
    FILE* logFile;
public:
    SLog();
    SLog(const char* fileName);
    ~SLog();
    void error(const char* file, int line, const char* format,...);
};

class SGlobalLog
{
private:
    static SLog* plog;
public:
    static SLog* getLog();
};

#endif // LOGGER_H

