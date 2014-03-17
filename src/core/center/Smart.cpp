#include "Smart.h"

Smart::Smart()
{
    p_config = NULL;
    p_requestSource = NULL;
    p_onlineTuning = NULL;
    p_threadPool = NULL;
}

Smart::~Smart()
{
    delete p_config;
    delete p_requestSource;
    delete p_onlineTuning;
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
    p_onlineTuning = OnlineTuning::getObject();
    p_onlineTuning->init();
    //线程初始化
    p_threadPool = ThreadPool::getObject();
    p_threadPool->init();
}

void Smart::start()
{
    p_threadPool->startAll();
    p_threadPool->waitForAllOver();
}
