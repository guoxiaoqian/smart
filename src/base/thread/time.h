#ifndef TIME_H
#define TIME_H

#include "../kernel/env.h"
#if defined(S_CC_MSVC)
#   include <windows.h>
#   include "../3dparty/pthread_win/include/pthread.h"
#elif defined(S_CC_GCC)
#   include <unistd.h>
#endif

namespace smart {


class STime
{
public:
    static timespec makeTimespec(time_t secs, long nsecs)
    {
        struct timespec ts;
        ts.tv_sec = secs;
        ts.tv_nsec = nsecs;
        return ts;
    }

#if defined (S_OS_LINUX) && !defined(S_CC_GCC)
    static void ssleep(unsigned long secs)
    {
        nanosleep(makeTimespec(secs, 0));
    }

    static void msleep(unsigned long msecs)
    {
        nanosleep(makeTimespec(msecs / 1000, msecs % 1000 * 1000 * 1000));
    }

    static void usleep(unsigned long usecs)
    {
        nanosleep(makeTimespec(usecs / 1000 / 1000, usecs % (1000*1000) * 1000));
    }
#elif defined(S_OS_WIN) && defined(S_CC_MSVC)
    static void ssleep(unsigned long secs)
    {
        Sleep(secs*1000);
    }

    static void msleep(unsigned long msecs)
    {
        Sleep(msecs);
    }

    static void usleep(unsigned long usecs)
    {
        Sleep(usecs/1000);
    }
#else
    static void ssleep(unsigned long secs)
    {
        sleep(secs);
    }

    static void msleep(unsigned long msecs)
    {
        sleep(msecs/1000);
    }

    static void usleep(unsigned long usecs)
    {
        sleep(usecs/1000000);
    }
#endif

public:
    static const char* getCurTimeStr()
    {
        time_t t;
        time(&t);
        return ctime(&t);
    }

};

}
#endif // TIME_H
