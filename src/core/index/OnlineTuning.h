#ifndef ONLINETUNING_H
#define ONLINETUNING_H

class OnlineTuning
{
private:
    static OnlineTuning * p_onlineTuning;
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void tune();
    static OnlineTuning * getOnlineTuning();
};

#endif // ONLINETUNING_H
