#include "ReferencePoint.h"


namespace smart {

ReferencePoint::ReferencePoint()
{
    referencePointID = -1;
    p_grid = 0;
}

void ReferencePoint::init(IDType id, Point &point, Rect& rect)
{
    referencePointID = id;
    setPoint(point);
    p_grid = new Grid(id,rect);
}

bool ReferencePoint::isValid()
{
    return (referencePointID!=-1)&&p_grid;
}

}
