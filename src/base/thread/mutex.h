#ifndef MUTEX_H
#define MUTEX_H

#if defined (S_CC_GCC)
#include <pthread.h>
#else
#include "base/3dparty/pthread_win/include/pthread.h"
#endif

namespace base {


typedef pthread_mutex_t MutexType;

class SMutex
{
private:
    MutexType mu;
public:
    SMutex(){pthread_mutex_init(&mu,NULL);}
    ~SMutex(){pthread_mutex_destroy(&mu);}
    MutexType* getMutex(){return &mu;}
    int lock() {return pthread_mutex_lock(&mu);}
    int unlock(){return pthread_mutex_unlock(&mu);}
    int trylock(){return pthread_mutex_trylock(&mu);}
};

}
#endif // MUTEX_H
