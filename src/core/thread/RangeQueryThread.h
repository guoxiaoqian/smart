#ifndef RANGEQUERYTHREAD_H
#define RANGEQUERYTHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/Request.h"

class RangeQueryThread : public WorkThread
{
private:
    RequestQueue<Request*>* requests;
public:
    RangeQueryThread();
    ~RangeQueryThread();
    void init(int _thID,RequestQueue<Request*>* _requests);
    void run();
};

#endif // RANGEQUERYTHREAD_H
