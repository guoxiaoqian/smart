#include "UpdateThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/UpdateRequest.h"
#include "core/center/Config.h"
#include "core/thread/ThreadPool.h"
#include "base/thread/waitcond.h"

ThreadPool* UpdateThread::p_threadPool = NULL;
Config* UpdateThread::p_config = NULL;
int UpdateThread::numOfComplete = 0;
SMutex UpdateThread::mutex = SMutex();
SWaitCondation UpdateThread::allComplete = SWaitCondation();
bool UpdateThread::isWaitForRequest = true;

void UpdateThread::waitForAllComplete()
{
    mutex.lock();
    ++numOfComplete;
    if(numOfComplete < p_config->numOfUpdateThreads)
        allComplete.wait(mutex);
    else
        allComplete.wakeAll();
    mutex.unlock();
}


UpdateThread::UpdateThread()
{
}

UpdateThread::~UpdateThread()
{
}

void UpdateThread::init(int _thID, RequestQueue<Request *> *_p_requestQueue)
{
    thID = _thID;
    p_requestQueue = _p_requestQueue;
    p_threadPool = ThreadPool::getThreadPool();
    p_config = Config::getConfig();
}

ReturnType UpdateThread::handleUpdate(UpdateRequest *p_update)
{
    return RETURN_SUCCESS;
}

void UpdateThread::run()
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
            handleUpdate(static_cast<UpdateRequest*>(p_node->data[i]));
        }
        delete p_node;
        p_node=NULL;
        //段同步
        waitForAllComplete();
    }
}


void UpdateThread::onRequestReady()
{
    if(isWaitForRequest == true)
    {
        allComplete.wakeAll();
    }
}

void UpdateThread::onRequestOver()
{
}
