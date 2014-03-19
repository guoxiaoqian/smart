#ifndef REFERENCEPOINT_H
#define REFERENCEPOINT_H

#include "core/store/Grid.h"

class ReferencePoint : public Point
{
public:
    Grid * p_grid;
public:
    ReferencePoint();
};

#endif // REFERENCEPOINT_H
