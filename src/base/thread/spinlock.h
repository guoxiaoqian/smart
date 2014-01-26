#ifndef SPINLOCK_H
#define SPINLOCK_H

#if defined (S_CC_GCC)
#include <pthread.h>
#else
#include "base/3dparty/pthread_win/include/pthread.h"
#endif

class SSpinLock
{
private:
    pthread_spinlock_t spin;
public:
    SSpinLock(){pthread_spin_init(&spin,0);}
    ~SSpinLock(){pthread_spin_destroy(&spin);}
    int lock(){return pthread_spin_lock(&spin);}
    int unlock(){return pthread_spin_unlock(&spin);}
    int trylock(){return pthread_spin_trylock(&spin);}
};

#endif // SPINLOCK_H
