#include "ReferencePoint.h"

int ReferencePoint::instanceCount = 0;

ReferencePoint::ReferencePoint()
{
    referencePointID = instanceCount;
    p_grid = 0;
    ++instanceCount;
}

void ReferencePoint::init()
{
    //TODO:计算出grid的范围
    CoorType xmin = 0;
    CoorType ymin = 0;
    CoorType xmax = 0;
    CoorType ymax = 0;

    p_grid = new Grid(referencePointID,xmin,ymin,xmax,ymax);
}
