#ifndef ONLINETUNING_H
#define ONLINETUNING_H

#include "base/kernel/singleton.hpp"

class OnlineTuning:public SSingleton<OnlineTuning>
{
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void tune();
};

#endif // ONLINETUNING_H
