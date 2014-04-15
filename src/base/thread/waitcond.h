#ifndef WAITCOND_H
#define WAITCOND_H

#include "mutex.h"
#include "time.h"


namespace smart {

class SWaitCondation
{
private:
    timespec ts;
    pthread_cond_t cond;
public:
    SWaitCondation(){pthread_cond_init(&cond,NULL);}
    ~SWaitCondation(){pthread_cond_destroy(&cond);}
    int wait(SMutex& mutex){return pthread_cond_wait(&cond,mutex.getMutex());}
    int timedWait(SMutex& mutex,unsigned long msecs)
    {
        ts = STime::makeTimespec(msecs / 1000, msecs % 1000 * 1000 * 1000);
        return pthread_cond_timedwait(&cond,mutex.getMutex(),&ts);
    }
    int wake(){return pthread_cond_signal(&cond);}
    int wakeAll(){return pthread_cond_broadcast(&cond);}
};

}
#endif // WAITCOND_H
