#ifndef TIMER_H
#define TIMER_H

#include "base/kernel/env.h"
#ifdef S_OS_WIN
#   include <windows.h>
#elif defined(S_OS_LINUX)
#   include <unistd.h>
#endif
#include "base/kernel/sig_slot.hpp"

enum TimerType
{
    Timer_OneShot,
    Timer_Repeat
};

class STimer;
typedef void (STimer::*timerFunPtr)(HWND,UINT,UINT,DWORD);
typedef void (STimer::*timerFunPtr2)();

class STimer
{
private:
    unsigned long interval;
    TimerType timerType;
    Signal<> timeOut;
#ifdef S_OS_WIN
    UINT_PTR timerID;
    void callBack(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);
#elif defined(S_OS_LINUX)
    void callBack();
#endif
public:
    STimer();
    template<class T>
    STimer(T *receiver, void (T::*func)(), unsigned long msec, TimerType type = Timer_Repeat):interval(msec),timerType(type)
    {
        SConnect(this,timeOut,receiver,func);
    }
    void start();
    void stop();

};

#endif // TIMER_H
