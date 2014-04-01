#ifndef REFERENCEPOINT_H
#define REFERENCEPOINT_H

#include "core/store/Grid.h"

class ReferencePoint : public Point
{
private:
    static int instanceCount;
public:
    IDType referencePointID;
    Grid * p_grid;
public:
    ReferencePoint();
    void init();
    Grid* getGrid(){return p_grid;}
};

#endif // REFERENCEPOINT_H
