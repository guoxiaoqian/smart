#include "Smart.h"
#include "core/center/Config.h"
#include "core/request/RequestSource.h"
#include "core/thread/ThreadPool.h"
#include "core/index/DynamicIndex.h"

namespace smart{

Smart::Smart()
{
    p_config = NULL;
    p_requestSource = NULL;
    p_index = NULL;
    p_threadPool = NULL;
}

Smart::~Smart()
{
    delete p_config;
    delete p_requestSource;
    delete p_index;
    delete p_threadPool;
}

void Smart::init()
{
    p_config = Config::getObject();
    //PATH:smart/src/config.ini
    p_config->init("../src/config.ini");
    //数据源初始化
    p_requestSource = RequestSource::getObject();
    p_requestSource->init();
    //索引初始化
    p_index = DynamicIndex::getObject();
    p_index->init();
    //线程初始化
    p_threadPool = ThreadPool::getObject();
    p_threadPool->init(p_index);
}

void Smart::start()
{
    p_threadPool->startAll();
    p_threadPool->waitForAllOver();
}

}
