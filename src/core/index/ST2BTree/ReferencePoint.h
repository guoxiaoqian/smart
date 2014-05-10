#ifndef REFERENCEPOINT_H
#define REFERENCEPOINT_H

#include "core/store/Grid.h"
#include "core/store/ObjectCell.h"
#include <vector>
using std::vector;

namespace smart{

class ReferencePoint : public Point
{
public:
    IDType referencePointID;
    vector<Point> voronoiCell;
    float densty;
    Grid<ObjectCell> * p_grid;
public:
    ReferencePoint();
    ~ReferencePoint();
    ReferencePoint(IDType id, Point &point);
    void init(IDType id,Point& point);
    bool initGrid();
    Grid<ObjectCell>* getGrid(){return p_grid;}
    void setDensty(float _densty){densty = _densty;}
};

}
#endif // REFERENCEPOINT_H
