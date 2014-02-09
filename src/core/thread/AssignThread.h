#ifndef ASSIGNTHREAD_H
#define ASSIGNTHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/Request.h"
#include "base/kernel/sig_slot.hpp"
#include <vector>
using std::vector;

class SMutex;
class SWaitCondation;
class ThreadPool;
class RequestSource;
class Config;

class AssignThread : public WorkThread
{
private:
    static SMutex mutex;
    static SWaitCondation allComplete;
    static RequestSource* p_requestSource;
    static ThreadPool* p_threadPool;
    static Config* p_config;
    static int numOfComplete;
    void waitForAllComplete();
    vector<vector<Request*>*> updateResults;
    vector<vector<Request*>*> queryResults;
public:
    static SSignal<> requestReady;
    static SSignal<> requestOver;
public:
    AssignThread();
    ~AssignThread();
    void init(int _thID);
    void run();
};

#endif // ASSIGNTHREAD_H
