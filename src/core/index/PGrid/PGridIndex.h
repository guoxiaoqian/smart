#ifndef PGRIDINDEX_H
#define PGRIDINDEX_H

#include "core/index/StaticIndex.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class PGridIndex : public StaticIndex,public SSingleton<PGridIndex>
{
public:
    PGridIndex();
    ~PGridIndex();
    void init();
    ReturnType update(UpdateRequest *p_update);
    ReturnType rangeQuery(RangeQueryRequest *p_range,vector<MoveObject>& result);
    ReturnType knnQuery(KNNQueryRequest *p_knn,vector<MoveObject>& result);
};

}
#endif // PGRIDINDEX_H
