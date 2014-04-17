#ifndef DYNAMICINDEX_H
#define DYNAMICINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class Histogram;
class KeyGen;
class OnlineTuning;
class ReferenceTables;
class ST2BTree;

class DynamicIndex :public SSingleton<DynamicIndex>,public Index
{
public:
    Histogram* p_histogram;
    KeyGen* p_keyGen;
    OnlineTuning* p_onlineTuning;
    ReferenceTables* p_referenceTables;
    ST2BTree* p_st2btree;
public:
    DynamicIndex();
    ~DynamicIndex();
    void init();
    void update(UpdateRequest *p_update);
    void query(RangeQueryRequest *p_range);
    void query(KNNQueryRequest *p_range);
};

}
#endif // DYNAMICINDEX_H
