#ifndef RWLOCK_H
#define RWLOCK_H

#if defined (S_CC_GCC)
#include <pthread.h>
#else
#include "base/3dparty/pthread_win/include/pthread.h"
#endif

class SRWLock
{
private:
    pthread_rwlock_t rw;
public:
    SRWLock(){pthread_rwlock_init(&rw,NULL);}
    ~SRWLock(){pthread_rwlock_destroy(&rw);}
    int rdLock(){return pthread_rwlock_rdlock(&rw);}
    int wrlock(){return pthread_rwlock_wrlock(&rw);}
    int tryRdLock(){return pthread_rwlock_tryrdlock(&rw);}
    int tryWrLock(){return pthread_rwlock_trywrlock(&rw);}
    int unlock(){return pthread_rwlock_unlock(&rw);}

};

#endif // RWLOCK_H
