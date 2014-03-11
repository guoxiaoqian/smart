#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "base/kernel/singleton.hpp"

class Histogram:public SSingleton<Histogram>
{
public:
    Histogram();
};

#endif // HISTOGRAM_H
