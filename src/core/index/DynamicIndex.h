#ifndef DYNAMICINDEX_H
#define DYNAMICINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace core {

class Histogram;
class KeyGen;
class OnlineTuning;
class ReferenceTable;
class ST2BTree;

class DynamicIndex :public base::SSingleton<DynamicIndex>,public Index
{
public:
    Histogram* p_histogram;
    KeyGen* p_keyGen;
    OnlineTuning* p_onlineTuning;
    ReferenceTable* p_referenceTable;
    ST2BTree* p_st2btree;
public:
    DynamicIndex();
    void init();
};

}
#endif // DYNAMICINDEX_H
