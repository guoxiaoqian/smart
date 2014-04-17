#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//职责：求新的参考点集合的位置和密度

#include "base/kernel/singleton.hpp"
#include "core/index/SpacePartition/ReferencePoint.h"
#include <vector>
using std::vector;

namespace smart{

class Histogram:public SSingleton<Histogram>
{
public:
    Histogram();
    void init();
    vector<ReferencePoint> getReferencePoints();
};

}

#endif // HISTOGRAM_H
