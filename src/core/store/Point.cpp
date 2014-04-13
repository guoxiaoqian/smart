#include "Point.h"


namespace core {

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

}
