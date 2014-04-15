#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include "base/thread/thread.h"
#include "core/center/type.h"

namespace smart{

class WorkThread : public SThread
{
public:
    int thID;
    static PeriodType period;
protected:
    //线程状态
    int numOfDiscard;//丢弃数据的个数
    int numOfSuccess;//处理数据的个数
public:
    WorkThread();
    virtual void run(){}
    void getStatus(int & discard,int & success);
    static void increasePeriod();
};
}
#endif // WORKTHREAD_H
