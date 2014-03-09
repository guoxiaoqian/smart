#include "ThreadPool.h"
#include "core/center/Config.h"
#include "core/thread/KNNQueryThread.h"
#include "core/thread/RangeQueryThread.h"
#include "core/thread/AssignThread.h"
#include "core/thread/UpdateThread.h"
#include "core/index/OnlineTuning.h"

ThreadPool* ThreadPool::p_threadPool = NULL;

ThreadPool::ThreadPool()
{
    p_threadPool = this;
    p_periodTimer = NULL;
}

ThreadPool::~ThreadPool()
{
    delete p_periodTimer;

    for(unsigned int i = 0;i < assignThreads.size();++i)
    {
        delete assignThreads[i];
    }
    for(unsigned int i = 0;i < updateThreads.size();++i)
    {
        delete updateThreads[i];
    }
    for(unsigned int i = 0;i < queryThreads.size();++i)
    {
        delete queryThreads[i];
    }

    for(unsigned int i = 0;i < updateQueues.size();++i)
    {
        delete updateQueues[i];
    }
    for(unsigned int i = 0;i < queryQueues.size();++i)
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
    HandleThread* p_updateThread = NULL;
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
        HandleThread* p_rangeQueryThread = NULL;
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
        HandleThread* p_knnQueryThread = NULL;
        for(int i=0;i<p_config->numOfQueryThreads;++i)
        {
            p_knnQueryThread = new KNNQueryThread();
            p_queue = new RequestQueue<Request*>();
            queryQueues.push_back(p_queue);
            p_knnQueryThread->init(i,p_queue);
            queryThreads.push_back(p_knnQueryThread);
        }
    }

    //创建周期定时器
    p_periodTimer = new PeriodTimer;
    p_periodTimer->init(static_cast<unsigned long>(p_config->maxUpdateTime));
    //周期到来时，先暂停所有线程，然后打印线程信息，然后调整索引，最后更新周期并唤醒所有线程
    //p_periodTimer->addListener(HandleThread::AllWait);
    p_periodTimer->addListener(this,&ThreadPool::printThreadStatus);
    p_periodTimer->addListener(OnlineTuning::getOnlineTuning(),&OnlineTuning::tune);
    p_periodTimer->addListener(HandleThread::onNextPeriod);

    SConnectGG(AssignThread::requestReady,HandleThread::onRequestReady);
    SConnectGG(AssignThread::requestOver,HandleThread::onRequestOver);
}

void ThreadPool::startAll()
{
    for(unsigned int i = 0;i < assignThreads.size();++i)
    {
        assignThreads[i]->start();
    }
    for(unsigned int i = 0;i < updateThreads.size();++i)
    {
        updateThreads[i]->start();
    }
    for(unsigned int i = 0;i < queryThreads.size();++i)
    {
        queryThreads[i]->start();
    }
}

void ThreadPool::stopAll()
{
    for(unsigned int i = 0;i < assignThreads.size();++i)
    {
        assignThreads[i]->stop();
    }
    for(unsigned int i = 0;i < updateThreads.size();++i)
    {
        updateThreads[i]->stop();
    }
    for(unsigned int i = 0;i < queryThreads.size();++i)
    {
        queryThreads[i]->stop();
    }
}

void ThreadPool::printThreadStatus()
{
    int sumOfDiscard = 0;
    int sumOfSuccess = 0;
    int tmpDiscard = 0;
    int tmpSuccess = 0;
    for(unsigned int i = 0;i < assignThreads.size();++i)
    {
        assignThreads[i]->getStatus(tmpDiscard,tmpSuccess);
        sumOfDiscard += tmpDiscard;
        sumOfSuccess += tmpSuccess;
    }

    SInfo("period:%d assignDiscard:%d assignSuccess:%d",WorkThread::period,sumOfDiscard,sumOfSuccess);
    sumOfDiscard = 0;
    sumOfSuccess = 0;
    for(unsigned int i = 0;i < updateThreads.size();++i)
    {
        updateThreads[i]->getStatus(tmpDiscard,tmpSuccess);
        sumOfDiscard += tmpDiscard;
        sumOfSuccess += tmpSuccess;
    }
    SInfo("period:%d updateDiscard:%d updateSuccess:%d",WorkThread::period,sumOfDiscard,sumOfSuccess);
    sumOfDiscard = 0;
    sumOfSuccess = 0;
    for(unsigned int i = 0;i < queryThreads.size();++i)
    {
        queryThreads[i]->getStatus(tmpDiscard,tmpSuccess);
        sumOfDiscard += tmpDiscard;
        sumOfSuccess += tmpSuccess;
    }
    SInfo("period:%d queryDiscard:%d querySuccess:%d",WorkThread::period,sumOfDiscard,sumOfSuccess);
}
