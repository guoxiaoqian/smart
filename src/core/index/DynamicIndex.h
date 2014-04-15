#ifndef DYNAMICINDEX_H
#define DYNAMICINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class Histogram;
class KeyGen;
class OnlineTuning;
class ReferenceTable;
class ST2BTree;
class Config;

class DynamicIndex :public SSingleton<DynamicIndex>,public Index
{
private:
    int period;
public:
    Histogram* p_histogram;
    KeyGen* p_keyGen;
    OnlineTuning* p_onlineTuning;
    ReferenceTable* p_referenceTable[2];
    ST2BTree* p_st2btree;
    Config* p_config;
public:
    DynamicIndex();
    ~DynamicIndex();
    void init();
    void tune();
};

}
#endif // DYNAMICINDEX_H
