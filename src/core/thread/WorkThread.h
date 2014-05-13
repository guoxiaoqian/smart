#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include "base/thread/thread.h"
#include "core/center/type.h"
#include "core/index/Index.h"
#include "core/center/Config.h"

namespace smart{

class WorkThread : public SThread
{
public:
    int thID;
    static Index* p_index;
    static Config* p_config;
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
    static void init(Index* _p_index);
};
}
#endif // WORKTHREAD_H
