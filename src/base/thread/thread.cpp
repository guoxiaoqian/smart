#include "thread.h"
#include <stdio.h>


namespace base {

SThread::SThread()
{
    running = false;
    waiting = false;
}

SThread::~SThread()
{
}

//PROTECT

void SThread::wait()
{
    mutex.lock();
    waiting = true;
    cond.wait(mutex);
}

void SThread::exit()
{
    pthread_exit(NULL);
}

void SThread::cancelPoint()
{
    pthread_testcancel();
}

//PUBLIC

void* SThread::threadFun(void* arg)
{
    SThread *thr = reinterpret_cast<SThread *>(arg);
    thr->run();
    return NULL;
}

void SThread::start()
{
    running = true;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&th,&attr,SThread::threadFun,this);
}

void SThread::stop()
{
    running = false;
    over();
}

void SThread::resume()
{
    cond.wake();
    waiting = false;
    mutex.unlock();
}

void SThread::over()
{
    pthread_join(th,NULL);
}

void SThread::cancel()
{
    pthread_cancel(th);
}

void SThread::doOnce(void (*routine)())
{
    pthread_once(&once,routine);
}

bool SThread::equal(SThread &th1)
{
    return pthread_equal(th,th1.getThreadID());
}

}
