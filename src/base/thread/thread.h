
//How to use or test

//class ThreadA:public SThread
//{
//public:
//    void run()
//    {
//        for(int i=0;i<10;++i)
//        {
//            if(i == 5)
//                wait();
//            cout<<"child A thread run\n";
//        }
//    }
//};
//int main()
//{
//    ThreadA thA;
//    thA.start();
//    STime::ssleep(5);
//    thA.resume();
//    thA.over();
//    return 0;
//}


#ifndef THREAD_H
#define THREAD_H

#include "base/kernel/global.h"
#include "waitcond.h"

typedef pthread_t SThreadID;

class SThread
{
private:
    SThreadID th;
    SMutex mutex;
    SWaitCondation cond;
    pthread_once_t once;
    volatile int running;
    volatile int waiting;
protected:
    void wait();
    void exit();
    void cancelPoint();
public:
    SThread();
    virtual ~SThread();
    static void* threadFun(void* arg);

    void start();
    void stop();
    void resume();
    void over();
    void cancel();
    void doOnce(void (*routine)(void));
    bool equal(SThread& th1);
    SThreadID getThreadID() {return th;}
    bool isRunning() {return running;}
    bool isWaiting() {return waiting;}
    virtual void run() = 0;
};

#endif//THREAD_H
