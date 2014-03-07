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

    STimer(unsigned long msec,TimerType type=TIMER_REPEAT);

    void init(unsigned long msec,TimerType type=TIMER_REPEAT);

    template<class T>
    void addListener(T *receiver, void (T::*func)())
    {
        SConnectMM(this,timeOut,receiver,func);
    }
    void addListener(void (*func)());
    void run();
};

#endif // TIMER_H
