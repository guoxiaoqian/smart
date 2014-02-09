#ifndef ONLINETUNING_H
#define ONLINETUNING_H

#include "base/thread/timer.h"

class OnlineTuning
{
private:
    STimer* timer;
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void start();
    void onTimer();
};

#endif // ONLINETUNING_H
