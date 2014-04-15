#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "base/kernel/singleton.hpp"

namespace smart{

class Histogram:public SSingleton<Histogram>
{
public:
    Histogram();
};

}

#endif // HISTOGRAM_H
