#include "timer.h"

STimer::STimer()
{
}

void STimer::start()
{
#if defined (S_OS_WIN)
    timerFunPtr fun = &STimer::callBack;
    timerID = SetTimer(NULL,1,interval,(void WINAPI (*)(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime))fun);
#elif defined(S_OS_LINUX)
    timeFunPtr2 fun = &STimer::callBack;
    signal(SIGALRM,(void (*)())fun);
    alarm(interval);
#endif
}

void STimer::stop()
{
#ifdef S_OS_WIN
    KillTimer(NULL,timerID);
#endif
}

#ifdef S_OS_WIN
void STimer::callBack(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
{
    SEmit timeOut();
    if(timerType == Timer_OneShot)
        stop();
}
#elif defined(S_OS_LINUX)
void STimer::callBack()
{
    SEmit timeOut();
    if(timerType == Timer_OneShot)
        stop();
    else
        alarm(interval);
}
#endif

