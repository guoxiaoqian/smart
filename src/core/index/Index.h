#ifndef INDEX_H
#define INDEX_H

#include "core/request/UpdateRequest.h"
#include "core/request/RangeQueryRequest.h"
#include "core/request/KNNQueryRequest.h"

namespace smart {

class Index
{
public:
    Index();
    virtual ~Index(){}
    virtual void init() = 0;
    virtual ReturnType update(UpdateRequest* p_update) = 0;
    virtual ReturnType query(RangeQueryRequest* p_range) = 0;
    virtual ReturnType query(KNNQueryRequest* p_knn) = 0;
};

}

#endif // INDEX_H
