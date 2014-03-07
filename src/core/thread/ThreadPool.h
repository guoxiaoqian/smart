#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
using std::vector;

#include "core/request/Request.h"
#include "core/request/RequestQueue.h"
#include "core/thread/PeriodTimer.h"

class AssignThread;
class HandleThread;

class ThreadPool
{
private:
    static ThreadPool* p_threadPool;
public:
    vector<AssignThread*> assignThreads;
    vector<HandleThread*> updateThreads;
    vector<HandleThread*> queryThreads;

    vector<RequestQueue<Request*>*> updateQueues;
    vector<RequestQueue<Request*>*> queryQueues;
    PeriodTimer * p_periodTimer;
public:
    ThreadPool();
    ~ThreadPool();
    static ThreadPool* getThreadPool();
    void init();
    void startAll();
    void stopAll();
};

#endif // THREADPOOL_H
