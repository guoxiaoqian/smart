#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
using std::vector;

#include "core/thread/WorkThread.h"
#include "core/request/Request.h"
#include "core/request/RequestQueue.h"

class AssignThread;
class UpdateThread;

class ThreadPool
{
public:
    static ThreadPool* p_threadPool;
public:
    vector<AssignThread*> assignThreads;
    vector<UpdateThread*> updateThreads;
    vector<WorkThread*> queryThreads;

    vector<RequestQueue<Request*>*> updateQueues;
    vector<RequestQueue<Request*>*> queryQueues;

    typedef vector<WorkThread*>::iterator ThreadPtrPtr;
public:
    ThreadPool();
    ~ThreadPool();
    static ThreadPool* getThreadPool();
    void init();
    void startAll();
    void stopAll();
};

#endif // THREADPOOL_H
