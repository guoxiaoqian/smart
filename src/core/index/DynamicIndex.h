#ifndef DYNAMICINDEX_H
#define DYNAMICINDEX_H

#include "core/index/Index.h"

namespace smart {


class DynamicIndex :public Index
{
public:
    DynamicIndex(){}
    virtual ~DynamicIndex(){}
    virtual void init() = 0;
    virtual ReturnType update(UpdateRequest *p_update) = 0;
    virtual ReturnType rangeQuery(RangeQueryRequest *p_range,vector<MoveObject>& result) = 0;
    virtual ReturnType knnQuery(KNNQueryRequest *p_knn,vector<MoveObject>& result) = 0;
    virtual void tune() = 0;
};

}
#endif // DYNAMICINDEX_H
