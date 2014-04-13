#ifndef STATICINDEX_H
#define STATICINDEX_H

#include "core/index/Index.h"
#include "base/kernel/singleton.hpp"

namespace core {

class StaticIndex :public base::SSingleton<StaticIndex>,public Index
{
public:
    StaticIndex();
    void init();
};

}
#endif // STATICINDEX_H