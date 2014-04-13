#ifndef ONLINETUNING_H
#define ONLINETUNING_H

#include "base/kernel/singleton.hpp"

namespace core{

class OnlineTuning:public base::SSingleton<OnlineTuning>
{
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void tune();
};

}
#endif // ONLINETUNING_H
