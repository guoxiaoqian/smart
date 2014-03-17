#include "AssignThread.h"
#include "core/center/Config.h"
#include "core/thread/ThreadPool.h"
#include "core/request/RequestSource.h"
#include "base/thread/waitcond.h"

SMutex AssignThread::mutex = SMutex();
SWaitCondation AssignThread::allComplete = SWaitCondation();
RequestSource* AssignThread::p_requestSource = NULL;
ThreadPool* AssignThread::p_threadPool = NULL;
Config* AssignThread::p_config = NULL;
int AssignThread::numOfComplete = 0;
SSignal<> AssignThread::requestReady = SSignal<>();
SSignal<> AssignThread::requestOver = SSignal<>();
PeriodType AssignThread::curPeriod = 0;
int AssignThread::numOfSynchTimes = 0;
int AssignThread::countOfSynchTimes = 0;

AssignThread::AssignThread()
{
}

AssignThread::~AssignThread()
{
    for(int i=0;i<p_config->numOfUpdateThreads;++i)
    {
        delete updateResults[i];
    }
    for(int i=0;i<p_config->numOfQueryThreads;++i)
    {
        delete queryResults[i];
    }
}

void AssignThread::waitForAllComplete()
{
    mutex.lock();
    ++numOfComplete;
    if(numOfComplete < p_config->numOfAssignThreads)
        allComplete.wait(mutex);
    else
    {
        //将更新获取的结果插入到更新队列中去
        QueueNode<Request*> *p_node=NULL;
        for(int i=0;i<p_config->numOfUpdateThreads;++i)
        {
            p_node=new QueueNode<Request*>;
            for(int j=0;j<p_config->numOfAssignThreads;++j)
            {
                p_node->InsertData(p_threadPool->assignThreads[j]->updateResults[i]);
                p_node->setPeriod(curPeriod);
                p_threadPool->assignThreads[j]->updateResults[i]->clear();
            }
            p_threadPool->updateQueues[i]->InsertNode(p_node);
        }

        //将查询获取的结果插入到查询队列中去
        for(int i=0;i<p_config->numOfQueryThreads;++i)
        {
            p_node=new QueueNode<Request*>;
            for(int j=0;j<p_config->numOfAssignThreads;++j)
            {
                p_node->InsertData(p_threadPool->assignThreads[j]->queryResults[i]);
                p_node->setPeriod(curPeriod);
                p_threadPool->assignThreads[j]->queryResults[i]->clear();
            }
            p_threadPool->queryQueues[i]->InsertNode(p_node);
        }

        numOfComplete = 0;
        p_requestSource->increaseCurrent(p_config->lenOfRequestBlock*p_config->numOfAssignThreads);

        //更新当前周期
        ++countOfSynchTimes;
        if(countOfSynchTimes == numOfSynchTimes)
        {
            ++curPeriod;
            countOfSynchTimes = 0;
        }

        //唤醒饥饿中的处理线程
        SEMIT requestReady();
        //同步完成，唤醒同类
        allComplete.wakeAll();

    }
    mutex.unlock();
}

void AssignThread::init(int _thID)
{
    thID = _thID;
    if(p_requestSource == NULL || p_threadPool == NULL || p_config == NULL)
    {
        p_requestSource = RequestSource::getObject();
        p_threadPool = ThreadPool::getObject();
        p_config = Config::getObject();
        numOfSynchTimes = p_config->numOfObjects/p_config->lenOfRequestBlock;
    }
    for(int i=0;i<p_config->numOfUpdateThreads;++i)
    {
        updateResults.push_back(new vector<Request*>);
    }
    for(int i=0;i<p_config->numOfQueryThreads;++i)
    {
        queryResults.push_back(new vector<Request*>);
    }
}

void AssignThread::run()
{
    vector<Request*>::iterator begin;
    vector<Request*>::iterator end;
    int lenOfBlock = p_config->lenOfRequestBlock;
    int numOfUpdateThreads = p_config->numOfUpdateThreads;
    int numOfQueryThreads = p_config->numOfQueryThreads;
    int i,j;
    while(isRunning())
    {
        //获取请求数据段
        i=0,j=0;
        if(p_requestSource->getRequest(thID,lenOfBlock,begin,end) == RETURN_SUCCESS)
        {
            //如果数据已过期则直接丢弃
            if(curPeriod >= period)
            {
                //分析并分发请求
                for(;begin<=end;++begin)
                {
                    switch((*begin)->type)
                    {
                    case REQUEST_UPDATE:
                        updateResults[i]->push_back(*begin);
                        i=(i+1)%numOfUpdateThreads;
                        break;
                    case REQUEST_RANGE_QUERY:
                        queryResults[j]->push_back(*begin);
                        j=(j+1)%numOfQueryThreads;
                        break;
                    case REQUEST_KNN_QUERY:
                        queryResults[j]->push_back(*begin);
                        j=(j+1)%numOfQueryThreads;
                        break;
                    default:break;
                    }
                }
                numOfSuccess += lenOfBlock;
            }
            else
            {
                numOfDiscard += lenOfBlock;
            }

            //等待所有完成
            waitForAllComplete();
        }
        else
        {
            //请求数据结束
            SEMIT requestOver();
            return;
        }
    }
}
