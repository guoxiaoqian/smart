#ifndef PGRIDINDEX_H
#define PGRIDINDEX_H

#include "core/index/index.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class PGridIndex : public SSingleton<PGridIndex>,public Index
{
public:
    PGridIndex();
    ~PGridIndex();
    void init();
    ReturnType update(UpdateRequest *p_update);
    ReturnType query(RangeQueryRequest *p_range,vector<MoveObject>& result);
    ReturnType query(KNNQueryRequest *p_knn,vector<MoveObject>& result);
    IDType getThreadID(UpdateRequest* p_update);
    IDType getThreadID(RangeQueryRequest* p_range);
    IDType getThreadID(KNNQueryRequest* p_knn);
};

}
#endif // PGRIDINDEX_H
