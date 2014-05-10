#ifndef INDEX_H
#define INDEX_H

#include "core/request/UpdateRequest.h"
#include "core/request/RangeQueryRequest.h"
#include "core/request/KNNQueryRequest.h"
#include "core/store/MoveObject.h"
#include <vector>
using std::vector;

namespace smart {

class Index
{
public:
    Index(){}
    virtual ~Index(){}
    virtual void init() = 0;
    virtual ReturnType update(UpdateRequest* p_update) = 0;
    virtual ReturnType rangeQuery(RangeQueryRequest* p_range,vector<MoveObject>& result) = 0;
    virtual ReturnType knnQuery(KNNQueryRequest* p_knn,vector<MoveObject>& result) = 0;
};

}

#endif // INDEX_H
