#include "Rect.h"


namespace smart {

Rect::Rect()
{
}

Rect::Rect(CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY)
{
    minX = _minX;
    minY = _minY;
    maxX = _maxX;
    maxY = _maxY;
}

void Rect::setRange(Rect &rect)
{
    minX = rect.minX;
    minY = rect.minY;
    maxX = rect.maxX;
    maxY = rect.maxY;
}

bool Rect::intersect(Rect &rect)
{
    return !(rect.minX < minX || rect.minY < minY || rect.maxX > maxX || rect.maxY > maxY);
}

bool Rect::cover(Point &point)
{
    return !(point.coorX < minX || point.coorY < minY || point.coorX > maxX || point.coorY > maxY);
}

Square::Square(Rect &rect)
{
    CoorType width = rect.getWidth();
    CoorType height = rect.getHeight();
    if(width > height)
    {
        CoorType extra = (width - height)/2;
        minY = rect.minY - extra;
        maxY = rect.maxY + extra;
        minX = rect.minX;
        maxX = rect.maxX;
    }
    else if(width < height)
    {
        CoorType extra = (height - width)/2;
        minX = rect.minX - extra;
        maxX = rect.maxX + extra;
        minY = rect.minY;
        maxY = rect.maxY;
    }
    else
    {
        setRange(rect);
    }
}

}
