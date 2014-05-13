#ifndef ST2GRIDINDEX_H
#define ST2GRIDINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class ST2GridIndex :public SSingleton<ST2GridIndex>, public Index
{
private:
    int updateThreadNum;
    int queryThreadNum;
public:
    ST2GridIndex();
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
#endif // ST2GRIDINDEX_H
