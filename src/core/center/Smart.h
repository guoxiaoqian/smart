#ifndef SMART_H
#define SMART_H

namespace core {

class Config;
class RequestSource;
class Index;
class ThreadPool;

class Smart
{ 
private:
    Config * p_config;
    RequestSource* p_requestSource;
    Index * p_index;
    ThreadPool * p_threadPool;
public:
    Smart();
    ~Smart();
    void init();
    void start();
};

}

#endif // SMART_H
