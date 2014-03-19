#include "Cell.h"

Cell::Cell()
{    
}

Cell::Cell(CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY):Rect(_minX,_minY,_maxX,_maxY)
{
}

void Cell::insertMoveObject(MoveObject &object)
{
    moveObjects.push_back(object);
}

void Cell::deleteMoveObject(IDType objID)
{
}
