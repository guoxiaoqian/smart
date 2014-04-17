#ifndef RECT_H
#define RECT_H

#include "core/store/Point.h"

namespace smart{

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
    void setRange(Rect& rect);
    bool intersect(Rect & rect);
    bool cover(Point & point);
    CoorType getWidth(){return maxX - minX;}
    CoorType getHeight(){return maxY - minY;}
};

class Square:public Rect
{
public:
    Square(Rect& rect);
};

}//namespace smart

#endif // RECT_H
