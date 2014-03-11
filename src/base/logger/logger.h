#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include "base/kernel/env.h"
#include "base/kernel/singleton.hpp"


enum LogType{LOG_ERROR,LOG_WARN,LOG_INFO};

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

#define SLogError(format,...) SGlobalLog::getObject()->printLog(LOG_ERROR,CUR_FILE,CUR_LINE,format,##__VA_ARGS__)
#define SLogWarn(format,...) SGlobalLog::getObject()->printLog(LOG_WARN,CUR_FILE,CUR_LINE,format,##__VA_ARGS__)
#define SLogInfo(format,...) SGlobalLog::getObject()->printLog(LOG_INFO,CUR_FILE,CUR_LINE,format,##__VA_ARGS__)

class SLog
{
private:
    FILE* logFile;
public:
    SLog();
    SLog(const char* fileName);
    ~SLog();
    void printLog(LogType type,const char* file, int line, const char* format,...);
};

//全局日志
class SGlobalLog:public SSingleton<SLog>
{
};

#endif // LOGGER_H

