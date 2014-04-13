#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "base/kernel/singleton.hpp"

namespace core{

class Histogram:public base::SSingleton<Histogram>
{
public:
    Histogram();
};

}

#endif // HISTOGRAM_H
