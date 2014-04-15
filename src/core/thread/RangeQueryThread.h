#ifndef RANGEQUERYTHREAD_H
#define RANGEQUERYTHREAD_H

#include "core/thread/HandleThread.h"

namespace smart{

class RangeQueryThread : public HandleThread
{
public:
    RangeQueryThread();
    ~RangeQueryThread();
    ReturnType handleRequest(Request *p_request);
};
}
#endif // RANGEQUERYTHREAD_H
