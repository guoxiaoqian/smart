#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include "base/thread/thread.h"
#include "core/center/type.h"

class WorkThread : public SThread
{
public:
    int thID;
    static PeriodType period;
public:
    WorkThread();
    virtual void run(){}
};

#endif // WORKTHREAD_H
