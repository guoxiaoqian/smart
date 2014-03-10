#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "core/center/Singleton.h"

class Histogram:public Singleton<Histogram>
{
public:
    Histogram();
};

#endif // HISTOGRAM_H
