#ifndef INDEX_H
#define INDEX_H

#include "core/request/UpdateRequest.h"
#include "core/request/RangeQueryRequest.h"
#include "core/request/KNNQueryRequest.h"
#include "core/store/MoveObject.h"
#include <vector>
using std::vector;

namespace smart {

enum IndexMainType{
  INDEX_DYNAMIC = 0,
  INDEX_STATIC = 1
};

class Index
{
public:
    IndexMainType type;
public:
    Index(){}
    virtual ~Index(){}
    virtual void init() = 0;
    virtual ReturnType update(UpdateRequest* p_update) = 0;
    virtual ReturnType query(RangeQueryRequest* p_range,vector<MoveObject>& result) = 0;
    virtual ReturnType query(KNNQueryRequest* p_knn,vector<MoveObject>& result) = 0;
    virtual IDType getThreadID(UpdateRequest* p_update) = 0;
    virtual IDType getThreadID(RangeQueryRequest* p_range) = 0;
    virtual IDType getThreadID(KNNQueryRequest* p_knn) = 0;
    virtual void tune(){}
};

}

#endif // INDEX_H
