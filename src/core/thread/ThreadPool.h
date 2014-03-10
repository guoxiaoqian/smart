#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
using std::vector;

#include "core/request/Request.h"
#include "core/request/RequestQueue.h"
#include "core/thread/PeriodTimer.h"
#include "core/center/Singleton.h"


class AssignThread;
class HandleThread;

class ThreadPool:public Singleton<ThreadPool>
{
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
    void init();
    void startAll();
    void stopAll();
    void printThreadStatus();
};

#endif // THREADPOOL_H
