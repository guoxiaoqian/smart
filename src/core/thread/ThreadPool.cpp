#include "ThreadPool.h"
#include "core/center/Config.h"
#include "core/thread/KNNQueryThread.h"
#include "core/thread/RangeQueryThread.h"
#include "core/thread/AssignThread.h"
#include "core/thread/UpdateThread.h"

ThreadPool* ThreadPool::p_threadPool = NULL;

ThreadPool::ThreadPool()
{
    p_threadPool = this;
}

ThreadPool::~ThreadPool()
{
    for(int i = 0;i < assignThreads.size();++i)
    {
        delete assignThreads[i];
    }
    for(int i = 0;i < updateThreads.size();++i)
    {
        delete updateThreads[i];
    }
    for(int i = 0;i < queryThreads.size();++i)
    {
        delete queryThreads[i];
    }

    for(int i = 0;i < updateQueues.size();++i)
    {
        delete updateQueues[i];
    }
    for(int i = 0;i < queryQueues.size();++i)
    {
        delete queryQueues[i];
    }
}

ThreadPool *ThreadPool::getThreadPool()
{
    return p_threadPool;
}

void ThreadPool::init()
{
    Config* p_config = Config::getConfig();
    AssignThread* p_assignThread = NULL;
    for(int i =0;i<p_config->numOfAssignThreads;++i)
    {
        p_assignThread = new AssignThread();
        p_assignThread->init(i);
        assignThreads.push_back(p_assignThread);
    }
    RequestQueue<Request*> *p_queue = NULL;
    UpdateThread* p_updateThread = NULL;
    for(int i=0;i<p_config->numOfUpdateThreads;++i)
    {
        p_updateThread = new UpdateThread();
        p_queue = new RequestQueue<Request*>();
        updateQueues.push_back(p_queue);
        p_updateThread->init(i,p_queue);
        updateThreads.push_back(p_updateThread);
    }
    if(p_config->queryType == QUERY_RANGE)
    {
        RangeQueryThread* p_rangeQueryThread = NULL;
        for(int i=0;i<p_config->numOfQueryThreads;++i)
        {
            p_rangeQueryThread = new RangeQueryThread();
            p_queue = new RequestQueue<Request*>();
            queryQueues.push_back(p_queue);
            p_rangeQueryThread->init(i,p_queue);
            queryThreads.push_back(p_rangeQueryThread);
        }
    }
    else
    {
        KNNQueryThread* p_knnQueryThread = NULL;
        for(int i=0;i<p_config->numOfQueryThreads;++i)
        {
            p_knnQueryThread = new KNNQueryThread();
            p_queue = new RequestQueue<Request*>();
            queryQueues.push_back(p_queue);
            p_knnQueryThread->init(i,p_queue);
            queryThreads.push_back(p_knnQueryThread);
        }
    }

    SConnectGG(AssignThread::requestReady,UpdateThread::onRequestReady);
    SConnectGG(AssignThread::requestOver,UpdateThread::onRequestOver);
}

void ThreadPool::startAll()
{
    for(int i = 0;i < assignThreads.size();++i)
    {
        assignThreads[i]->start();
    }
    for(int i = 0;i < updateThreads.size();++i)
    {
        updateThreads[i]->start();
    }
    for(int i = 0;i < queryThreads.size();++i)
    {
        queryThreads[i]->start();
    }
}

void ThreadPool::stopAll()
{
    for(int i = 0;i < assignThreads.size();++i)
    {
        assignThreads[i]->stop();
    }
    for(int i = 0;i < updateThreads.size();++i)
    {
        updateThreads[i]->stop();
    }
    for(int i = 0;i < queryThreads.size();++i)
    {
        queryThreads[i]->stop();
    }
}