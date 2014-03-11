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
    p_config = new Config();
    //PATH:smart/src/config.ini
    p_config->init("../src/config.ini");
    //数据源初始化
    p_requestSource = new RequestSource();
    p_requestSource->init();
    //索引初始化
    p_onlineTuning = new OnlineTuning();
    p_onlineTuning->init();
    //线程初始化
    p_threadPool = new ThreadPool();
    p_threadPool->init();
}

void Smart::start()
{
    p_threadPool->startAll();
}
