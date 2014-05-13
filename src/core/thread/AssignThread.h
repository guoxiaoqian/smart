#ifndef ASSIGNTHREAD_H
#define ASSIGNTHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/Request.h"
#include "base/kernel/sig_slot.hpp"
#include <vector>
using std::vector;

namespace smart{
class SMutex;
class SWaitCondation;
class ThreadPool;
class RequestSource;

class AssignThread : public WorkThread
{
private:
    static SMutex mutex;
    static SWaitCondation allComplete;
    static RequestSource* p_requestSource;
    static ThreadPool* p_threadPool;
    static int numOfComplete;
    static PeriodType curPeriod;//正在分配的请求所属的周期
    static int numOfSynchTimes;//一周期内需要同步次数
    static int countOfSynchTimes;//已经同步的次数
    void waitForAllComplete();
    vector<vector<Request*>*> updateResults;
    vector<vector<Request*>*> queryResults;
public://信号
    static SSignal<> requestReady;
    static SSignal<> requestOver;
public:
    AssignThread();
    ~AssignThread();
    void init(int _thID);
    void run();
};
}
#endif // ASSIGNTHREAD_H
