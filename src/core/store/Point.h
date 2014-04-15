#ifndef POINT_H
#define POINT_H

#include "core/center/type.h"
namespace smart{
class Point
{
public:
    CoorType coorX;
    CoorType coorY;
public:
    Point();
    Point(CoorType _coorX,CoorType _coorY);
    void setPoint(Point& point);
    CoorType getDistance(Point& point);
};
}
#endif // POINT_H
