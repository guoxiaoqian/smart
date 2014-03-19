#include "Rect.h"

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

void Rect::setRange(CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY)
{
    minX = _minX;
    minY = _minY;
    maxX = _maxX;
    maxY = _maxY;
}

bool Rect::interset(Rect &rect)
{
    return !(rect.minX < minX || rect.minY < minY || rect.maxX > maxX || rect.maxY > maxY);
}

bool Rect::cover(Point &point)
{
    return !(point.coorX < minX || point.coorY < minY || point.coorX > maxX || point.coorY > maxY);
}
