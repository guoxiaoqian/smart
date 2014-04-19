#ifndef STATICINDEX_H
#define STATICINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace smart {

class StaticIndex :public SSingleton<StaticIndex>,public Index
{
public:
    StaticIndex();
    void init();
    ReturnType update(UpdateRequest *p_update);
    ReturnType query(RangeQueryRequest *p_range);
    ReturnType query(KNNQueryRequest *p_range);
};

}
#endif // STATICINDEX_H
