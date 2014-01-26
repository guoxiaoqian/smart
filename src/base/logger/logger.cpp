#include "logger.h"
#include <stdarg.h>
#include <time.h>

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

void SLog::error(const char* file, int line, const char *format,...)
{
    time_t t;
    time(&t);
    fprintf(logFile,"\n------------------ERROR-----------------\n");
    fprintf(logFile,"when:  %s",ctime(&t));
    fprintf(logFile,"where: %s ,line %d\n",file,line);
    fprintf(logFile,"what:  ");
    va_list args;
    va_start(args, format);
    vfprintf(logFile,format, args);
    va_end(args);
    fprintf(logFile,"\n----------------------------------------\n");
}

SLog* SGlobalLog::plog = NULL;

SLog *SGlobalLog::getLog()
{
    if(SGlobalLog::plog == NULL)
    {
        plog = new SLog();
    }
    return plog;
}
