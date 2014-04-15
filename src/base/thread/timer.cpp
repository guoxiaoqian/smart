#include "timer.h"

namespace smart {

STimer::STimer()
{
}

STimer::STimer(unsigned long msec, TimerType type)
{
    interval=msec;
    timerType=type;
}

void STimer::init(unsigned long msec, TimerType type)
{
    interval=msec;
    timerType=type;
}

void STimer::addListener(void (*func)())
{
     SConnectMG(this,timeOut,func);
}


void STimer::run()
{
    if(timerType == TIMER_ONESHOT)
    {
        STime::msleep(interval);
        SEMIT timeOut();
    }
    else
        while(isRunning())
        {
            STime::msleep(interval);
            SEMIT timeOut();
        }
}

}
