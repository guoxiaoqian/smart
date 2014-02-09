#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include "base/thread/thread.h"

class WorkThread : public SThread
{
public:
    int thID;
public:
    WorkThread();
    virtual void run(){}
};

#endif // WORKTHREAD_H
