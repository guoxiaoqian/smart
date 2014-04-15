#include "Point.h"
#include <math.h>

namespace smart {

Point::Point()
{
    coorX = 0;
    coorY = 0;
}

Point::Point(CoorType _coorX, CoorType _coorY)
{
    coorX = _coorX;
    coorY = _coorY;
}

void Point::setPoint(Point &point)
{
    coorX = point.coorX;
    coorY = point.coorY;
}

CoorType Point::getDistance(Point &point)
{
    return static_cast<CoorType>(sqrt((point.coorX - coorX)*(point.coorX - coorX) + \
                (point.coorY - coorY)*(point.coorY - coorY)));
}

}
