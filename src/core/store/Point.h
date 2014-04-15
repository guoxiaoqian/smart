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
    Point(CoorType _coorX,CoorType _coorY):coorX(_coorX),coorY(_coorY){}
    void setPoint(Point& point);
    void setPoint(CoorType _coorX,CoorType _coorY);
    CoorType getDistance(Point& point);
};
}
#endif // POINT_H
