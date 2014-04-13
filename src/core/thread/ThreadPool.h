#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
using std::vector;

#include "core/request/Request.h"
#include "core/request/RequestQueue.h"
#include "core/thread/PeriodTimer.h"
#include "base/kernel/singleton.hpp"

namespace core{
class AssignThread;
class HandleThread;
class Index;

class ThreadPool:public base::SSingleton<ThreadPool>
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
    void init(Index *p_index);
    void startAll();
    void stopAll();
    void waitForAllOver();
    void printThreadStatus();
};
}
#endif // THREADPOOL_H
