#ifndef ONLINETUNING_H
#define ONLINETUNING_H

#include "base/kernel/singleton.hpp"

namespace smart{

class Histogram;
class ReferenceTables;
class ST2BTree;

class OnlineTuning:public SSingleton<OnlineTuning>
{
private:
     Histogram* p_histogram;
     ReferenceTables* p_referenceTables;
     ST2BTree* p_st2btree;
public:
    OnlineTuning();
    ~OnlineTuning();
    void init();
    void tune();
};

}
#endif // ONLINETUNING_H
