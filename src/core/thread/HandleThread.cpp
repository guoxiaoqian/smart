#include "HandleThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/UpdateRequest.h"
#include "core/center/Config.h"
#include "core/thread/ThreadPool.h"
#include "base/thread/waitcond.h"

ThreadPool* HandleThread::p_threadPool = NULL;
Config* HandleThread::p_config = NULL;

int HandleThread::numOfComplete = 0;
int HandleThread::numOfHandleThreads = 0;
int HandleThread::numOfWaitRequest = 0;
int HandleThread::numOfWaitPeriod = 0;
SMutex HandleThread::mutex = SMutex();
SWaitCondation HandleThread::allComplete = SWaitCondation();
SMutex HandleThread::mutex2 = SMutex();
SWaitCondation HandleThread::requestCome = SWaitCondation();
SMutex HandleThread::mutex3 = SMutex();
SWaitCondation HandleThread::nextPeriod = SWaitCondation();

HandleThread::HandleThread()
{
}

void HandleThread::init(int _thID, RequestQueue<Request *> *_p_requestQueue)
{
    thID = _thID;
    p_requestQueue = _p_requestQueue;
    p_threadPool = ThreadPool::getObject();
    p_config = Config::getObject();
    numOfHandleThreads = p_config->numOfUpdateThreads+p_config->numOfQueryThreads;
}

void HandleThread::waitForAllComplete()
{
    mutex.lock();
    ++numOfComplete;
    if(numOfComplete < numOfHandleThreads)
        allComplete.wait(mutex);
    else
        allComplete.wakeAll();
    mutex.unlock();
}

void HandleThread::waitForRequestCome()
{
    mutex2.lock();
    ++numOfWaitRequest;
    requestCome.wait(mutex2);
    mutex2.unlock();
}

void HandleThread::waitForNextPeriod()
{
    mutex3.lock();
    ++numOfWaitPeriod;
    nextPeriod.wait(mutex3);
    mutex3.unlock();
}

void HandleThread::onRequestReady()
{
    if(numOfWaitRequest >0)
    {
        requestCome.wakeAll();
        numOfWaitRequest = 0;
    }
}

void HandleThread::onRequestOver()
{
}

void HandleThread::onNextPeriod()
{

    ++period;
    if(numOfWaitPeriod > 0)
    {
        nextPeriod.wakeAll();
        numOfWaitPeriod = 0;
    }
}

void HandleThread::run()
{
    QueueNode<Request*>* p_node=NULL;
    int node_size=0;
    while(isRunning())
    {
        while(p_node==NULL && (p_node=p_requestQueue->PopNode()) == NULL)
        {
            //饥饿等待
            waitForRequestCome();
        }

        if(p_node->period == period)
        {
            //正好是本周期的则处理
            node_size=p_node->data.size();
            for(int i=0;i<node_size;i++)
            {
                handleRequest(p_node->data[i]);
            }
            numOfSuccess += node_size;
            delete p_node;
            p_node=NULL;
            //段同步
            waitForAllComplete();
        }
        else if(p_node->period > period)
        {
            //本周期之后的请求要等周期结束才能开始处理
            waitForNextPeriod();
        }
        else
        {
            //本周之前的直接丢弃
            numOfDiscard += p_node->data.size();
            delete p_node;
            p_node = NULL;
        }
    }
}
