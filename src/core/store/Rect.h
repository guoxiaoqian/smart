#ifndef RECT_H
#define RECT_H

#include "core/store/Point.h"

class Rect
{
public:
    CoorType minX;
    CoorType minY;
    CoorType maxX;
    CoorType maxY;
public:
    Rect();
    Rect(CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY);
    void setRange(CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY);
    bool intersect(Rect & rect);
    bool cover(Point & point);
};

#endif // RECT_H
