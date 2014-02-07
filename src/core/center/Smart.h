#ifndef SMART_H
#define SMART_H

#include "core/center/Config.h"
#include "core/request/RequestSource.h"
#include "core/index/OnlineTuning.h"
#include "core/thread/ThreadPool.h"

class Smart
{ 
private:
    Config * p_config;
    RequestSource* p_requestSource;
    OnlineTuning * p_onlineTuning;
    ThreadPool * p_threadPool;
public:
    Smart();
    ~Smart();
    void init();
    void start();
};

#endif // SMART_H
