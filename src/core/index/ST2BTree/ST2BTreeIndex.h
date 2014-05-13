#ifndef ST2BTREEINDEX_H
#define ST2BTREEINDEX_H

#include "base/kernel/singleton.hpp"
#include "core/index/Index.h"

namespace smart {

class Histogram;
class KeyGen;
class OnlineTuning;
class ReferenceTables;
class ST2BTree;

class ST2BTreeIndex :public SSingleton<ST2BTreeIndex>,public Index
{
public:
    Histogram* p_histogram;
    KeyGen* p_keyGen;
    OnlineTuning* p_onlineTuning;
    ReferenceTables* p_referenceTables;
    ST2BTree* p_st2btree;
public:
    ST2BTreeIndex();
    ~ST2BTreeIndex();
    void init();
    ReturnType update(UpdateRequest *p_update);
    ReturnType query(RangeQueryRequest *p_range,vector<MoveObject>& result);
    ReturnType query(KNNQueryRequest *p_knn,vector<MoveObject>& result);
    IDType getThreadID(UpdateRequest* p_update);
    IDType getThreadID(RangeQueryRequest* p_range);
    IDType getThreadID(KNNQueryRequest* p_knn);
    void tune();
};

}
#endif // ST2BTREEINDEX_H
