#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "base/kernel/singleton.hpp"
#include "core/store/Point.h"
#include <vector>
using std::vector;

namespace smart{

class Histogram:public SSingleton<Histogram>
{
public:
    Histogram();
    void init();
    vector<Point> getReferencePoints();
};

}

#endif // HISTOGRAM_H
