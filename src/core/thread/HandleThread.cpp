#include "HandleThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/UpdateRequest.h"
#include "core/center/Config.h"
#include "core/thread/ThreadPool.h"
#include "base/thread/waitcond.h"
#include "core/index/Index.h"

namespace smart {


Config* HandleThread::p_config = NULL;
Index* HandleThread::p_index = NULL;

volatile int HandleThread::numOfComplete = 0;
volatile int HandleThread::numOfWaitRequest = 0;
volatile int HandleThread::numOfWaitPeriod = 0;
int HandleThread::numOfHandleThreads = 0;

SMutex HandleThread::mutex = SMutex();
SWaitCondation HandleThread::allComplete = SWaitCondation();
SMutex HandleThread::mutex2 = SMutex();
SWaitCondation HandleThread::requestCome = SWaitCondation();
SMutex HandleThread::mutex3 = SMutex();
SWaitCondation HandleThread::periodCome = SWaitCondation();

volatile bool HandleThread::isPeriodComing = false;
volatile bool HandleThread::isRequestOver = false;

HandleThread::HandleThread()
{
    p_requestQueue = NULL;
}

void HandleThread::init(int _thID, RequestQueue<Request *> *_p_requestQueue,Index* _p_index)
{
    thID = _thID;
    p_requestQueue = _p_requestQueue;
    if(!p_index)
    {
        p_index = _p_index;
    }
    if(!p_config)
    {
        p_config = Config::getObject();
        numOfHandleThreads = p_config->numOfUpdateThreads+p_config->numOfQueryThreads;
    }
}

void HandleThread::waitForAllComplete()
{
    mutex.lock();
    ++numOfComplete;
    if(numOfComplete < numOfHandleThreads)
        allComplete.wait(mutex);
    else
    {
        allComplete.wakeAll();
        numOfComplete = 0;
    }
    mutex.unlock();
}

void HandleThread::waitForRequestCome()
{
    mutex2.lock();
    ++numOfWaitRequest;
    requestCome.wait(mutex2);
    mutex2.unlock();
}

void HandleThread::waitForPeriodCome()
{
    SDebug("wait for period!");

    mutex3.lock();
    ++numOfWaitPeriod;
    periodCome.wait(mutex3);
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
    if(isRequestOver == false)
    {
        isRequestOver = true;
        //如果有在等待请求的线程，则都唤醒
        if(numOfWaitRequest >0)
        {
            requestCome.wakeAll();
            numOfWaitRequest = 0;
        }
    }
}

void HandleThread::onPeriodCome()
{
    if(numOfWaitPeriod > 0)
    {
        periodCome.wakeAll();
        numOfWaitPeriod = 0;
        if(isPeriodComing)
            isPeriodComing = false;
    }
}

void HandleThread::pauseForPeriodCome()
{
    if(isPeriodComing == false)
        isPeriodComing = true;
}

void HandleThread::run()
{
    QueueNode<Request*>* p_node=NULL;
    int node_size=0;
    while(isRunning())
    {
        //尝试获取请求数据，获取失败，如果数据已空，直接退出，否则饥饿等待
        while(p_node==NULL && (p_node=p_requestQueue->PopNode()) == NULL)
        {
            if(isRequestOver)
                return;
            else
                waitForRequestCome();
        }

        //正好是本周期的则处理
        if(p_node->period == period)
        {
            int i;
            node_size=p_node->data.size();
            for(i=0;i<node_size&&!isPeriodComing;i++)
            {
                handleRequest(p_node->data[i]);
            }

            //如果处理过程中突然新周期来临，丢弃未处理的
            if(isPeriodComing)
            {
                numOfDiscard = node_size - i;
                numOfSuccess = i;
                waitForPeriodCome();
            }
            else
            {
                numOfSuccess += node_size;
            }
            delete p_node;
            p_node=NULL;
            waitForAllComplete();
        }
        //本周期之后的请求要等周期结束才能开始处理
        else if(p_node->period > period)
        {
            waitForPeriodCome();
        }
        //本周之前的直接丢弃
        else
        {
            numOfDiscard += p_node->data.size();
            delete p_node;
            p_node = NULL;
            waitForAllComplete();
        }
    }
}

}
