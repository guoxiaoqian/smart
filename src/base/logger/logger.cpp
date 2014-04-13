#include "logger.h"
#include <stdarg.h>
#include <time.h>



namespace base {

SLog::SLog()
{
    logFile = fopen("log.txt","a+");
    if(logFile == NULL)
        perror("open file fail");
}

SLog::SLog(const char *fileName)
{
    logFile = fopen(fileName,"a+");
    if(logFile == NULL)
        perror("open file fail");
}

SLog::~SLog()
{
    if(logFile!=NULL)
        fclose(logFile);
}

void SLog::printLog(LogType type, const char *file, int line, const char *format,...)
{
    time_t t;
    time(&t);
    switch (type)
    {
    case LOG_ERROR:
        fprintf(logFile,"\n------------------ERROR-----------------\n");
        break;
    case LOG_WARN:
        fprintf(logFile,"\n------------------WARN------------------\n");
        break;
    case LOG_INFO:
        fprintf(logFile,"\n------------------INFO------------------\n");
        break;
    default:break;
    }
    fprintf(logFile,"when:  %s",ctime(&t));
    fprintf(logFile,"where: %s ,line %d\n",file,line);
    fprintf(logFile,"what:  ");
    va_list args;
    va_start(args, format);
    vfprintf(logFile,format, args);
    va_end(args);
    fprintf(logFile,"\n----------------------------------------\n");
}

}
