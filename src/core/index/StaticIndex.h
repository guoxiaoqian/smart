#ifndef STATICINDEX_H
#define STATICINDEX_H

#include "core/index/Index.h"

namespace smart {

class StaticIndex :public Index
{
public:
    StaticIndex(){}
    virtual ~StaticIndex(){}
    virtual void init() = 0;
    virtual ReturnType update(UpdateRequest *p_update) = 0;
    virtual ReturnType query(RangeQueryRequest *p_range,vector<MoveObject>& result) = 0;
    virtual ReturnType query(KNNQueryRequest *p_range,vector<MoveObject>& result) = 0;
};

}
#endif // STATICINDEX_H
