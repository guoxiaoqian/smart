#ifndef REFERENCEPOINT_H
#define REFERENCEPOINT_H

#include "core/store/Grid.h"
#include <vector>
using std::vector;

namespace smart{

class ReferencePoint : public Point
{
public:
    IDType referencePointID;
    vector<Point> voronoiCell;
    Grid * p_grid;
public:
    ReferencePoint();
    void init(IDType id,Point& point);
    bool initGrid();
    Grid* getGrid(){return p_grid;}
};

}
#endif // REFERENCEPOINT_H
