#ifndef THREADPOOL_H
#define THREADPOOL_H

class ThreadPool
{
public:
    ThreadPool();
    void init();
    void startAll();
    void stopAll();
};

#endif // THREADPOOL_H
