#ifndef POINT_H
#define POINT_H

#include "core/center/type.h"
namespace core{
class Point
{
public:
    CoorType coorX;
    CoorType coorY;
public:
    Point();
    Point(CoorType _coorX,CoorType _coorY);
};
}
#endif // POINT_H
