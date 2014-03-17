#ifndef HANDLETHREAD_H
#define HANDLETHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/RequestQueue.h"
#include "core/center/type.h"
#include "base/logger/logger.h"

class ThreadPool;
class Config;
class Request;
class UpdateRequest;
class SWaitCondation;

class HandleThread : public WorkThread
{
private:
    //使用条件变量
    static SMutex mutex;
    static SWaitCondation allComplete;
    static SMutex mutex2;
    static SWaitCondation requestCome;
    static SMutex mutex3;
    static SWaitCondation periodCome;
    static Config* p_config;

    static volatile int numOfComplete;
    static volatile int numOfWaitRequest;
    static volatile int numOfWaitPeriod;
    static int numOfHandleThreads;

    RequestQueue<Request*>* p_requestQueue;
    static volatile bool isPeriodComing;
    static volatile bool isRequestOver;

    void waitForAllComplete();
    void waitForRequestCome();
    void waitForPeriodCome();
public:
    static void onRequestReady();
    static void onRequestOver();
    static void onPeriodCome();
    static void pauseForPeriodCome();
public:
    HandleThread();
    void init(int _thID,RequestQueue<Request*>* _p_requestQueue);
    void run();
    virtual ReturnType handleRequest(Request*) = 0;
};

#endif // HANDLETHREAD_H
