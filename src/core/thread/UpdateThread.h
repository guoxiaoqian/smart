#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/RequestQueue.h"
#include "core/center/type.h"

class ThreadPool;
class Config;
class Request;
class UpdateRequest;
class SWaitCondation;

class UpdateThread : public WorkThread
{
private:
    static SMutex mutex;
    static SWaitCondation allComplete;
    RequestQueue<Request*>* p_requestQueue;
    static ThreadPool* p_threadPool;
    static Config* p_config;
    static int numOfComplete;
    static bool isWaitForRequest;

    void waitForAllComplete();
public:
    static void onRequestReady();
    static void onRequestOver();
public:
    UpdateThread();
    ~UpdateThread();
    void init(int _thID,RequestQueue<Request*>* _p_requestQueue);
    ReturnType handleUpdate(UpdateRequest* p_update);
    void run();
};

#endif // UPDATETHREAD_H
