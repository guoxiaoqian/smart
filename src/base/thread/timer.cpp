#include "timer.h"


void STimer::run()
{
    if(timerType == Timer_OneShot)
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
