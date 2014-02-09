#include "timer.h"

STimer::STimer()
{
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

