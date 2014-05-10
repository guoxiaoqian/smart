#ifndef ST2GRIDINDEX_H
#define ST2GRIDINDEX_H

#include "core/index/DynamicIndex.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class ST2GridIndex : public DynamicIndex,public SSingleton<ST2GridIndex>
{
public:
    ST2GridIndex();
    void init();
    ReturnType update(UpdateRequest *p_update);
    ReturnType rangeQuery(RangeQueryRequest *p_range,vector<MoveObject>& result);
    ReturnType knnQuery(KNNQueryRequest *p_knn,vector<MoveObject>& result);
    void tune();
};

}
#endif // ST2GRIDINDEX_H
