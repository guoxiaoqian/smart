#ifndef ONLINETUNING_H
#define ONLINETUNING_H

#include "core/center/Singleton.h"

class OnlineTuning:public Singleton<OnlineTuning>
{
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void tune();
};

#endif // ONLINETUNING_H
