#include "HandleThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/UpdateRequest.h"
#include "core/center/Config.h"
#include "core/thread/ThreadPool.h"
#include "base/thread/waitcond.h"

ThreadPool* HandleThread::p_threadPool = NULL;
Config* HandleThread::p_config = NULL;
int HandleThread::numOfComplete = 0;
SMutex HandleThread::mutex = SMutex();
SWaitCondation HandleThread::allComplete = SWaitCondation();
bool HandleThread::isWaitForRequest = true;

HandleThread::HandleThread()
{
}

void HandleThread::init(int _thID, RequestQueue<Request *> *_p_requestQueue)
{
    thID = _thID;
    p_requestQueue = _p_requestQueue;
    p_threadPool = ThreadPool::getThreadPool();
    p_config = Config::getConfig();
}

void HandleThread::waitForAllComplete()
{
    mutex.lock();
    ++numOfComplete;
    if(numOfComplete < p_config->numOfUpdateThreads+p_config->numOfQueryThreads)
        allComplete.wait(mutex);
    else
        allComplete.wakeAll();
    mutex.unlock();
}

void HandleThread::onRequestReady()
{
    if(isWaitForRequest == true)
    {
        allComplete.wakeAll();
    }
}

void HandleThread::onRequestOver()
{
}

void HandleThread::run()
{
    QueueNode<Request*>* p_node=NULL;
    int node_size=0;
    while(isRunning())
    {
        while(!(p_node=p_requestQueue->PopNode()))
        {
            //等待请求
            isWaitForRequest = true;
            waitForAllComplete();
            isWaitForRequest = false;
        }

        node_size=p_node->data.size();
        for(int i=0;i<node_size;i++)
        {
            handleRequest(p_node->data[i]);
        }
        delete p_node;
        p_node=NULL;
        //段同步
        waitForAllComplete();
    }
}
