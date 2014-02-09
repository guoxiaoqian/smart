//  example

//class A
//{
//public:
//    void fuck(){cout<<"fuck"<<endl;}
//};
//int main()
//{
//    A a;
//    STimer timer(&a,&A::fuck,1000);
//    timer.start();
//    STime::ssleep(20);
//    timer.stop();
//    return 0;
//}


#ifndef TIMER_H
#define TIMER_H

#include "base/kernel/sig_slot.hpp"
#include "base/thread/thread.h"
#include "base/thread/time.h"

enum TimerType
{
    TIMER_ONESHOT,
    TIMER_REPEAT
};


class STimer:public SThread
{
private:
    unsigned long interval;
    TimerType timerType;
    SSignal<> timeOut;
public:
    STimer();
    template<class T>
    STimer(T *receiver, void (T::*func)(), unsigned long msec, TimerType type):interval(msec),timerType(type)
    {
        SConnectMM(this,timeOut,receiver,func);
    }

    template<class T>
    void init(T *receiver, void (T::*func)(), unsigned long msec, TimerType type)
    {
        interval=msec;
        timerType=type;
        SConnectMM(this,timeOut,receiver,func);
    }
    void run();
};

#endif // TIMER_H
