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
    static SMutex mutex;
    static SWaitCondation allComplete;
    static SMutex mutex2;
    static SWaitCondation requestCome;
    static SMutex mutex3;
    static SWaitCondation nextPeriod;
    RequestQueue<Request*>* p_requestQueue;
    static ThreadPool* p_threadPool;
    static Config* p_config;

    static int numOfComplete;
    static int numOfWaitRequest;
    static int numOfWaitPeriod;
    static int numOfHandleThreads;

    void waitForAllComplete();
    void waitForRequestCome();
    void waitForNextPeriod();
public:
    static void onRequestReady();
    static void onRequestOver();
    static void onNextPeriod();
public:
    HandleThread();
    void init(int _thID,RequestQueue<Request*>* _p_requestQueue);
    void run(); //override WorkThread
    virtual ReturnType handleRequest(Request*) = 0; //will overrided by successor
};

#endif // HANDLETHREAD_H
