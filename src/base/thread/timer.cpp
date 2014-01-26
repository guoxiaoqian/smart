#include "timer.h"


void STimer::run()
{
    if(timerType == Timer_OneShot)
    {
        STime::msleep(interval);
        SEmit timeOut();
    }
    else
        while(isRunning())
        {
            STime::msleep(interval);
            SEmit timeOut();
        }
}
