#include "Cell.h"

Cell::Cell()
{    
}

Cell::Cell(IDType _cellID, CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY):\
    cellID(_cellID),Rect(_minX,_minY,_maxX,_maxY)
{
}

void Cell::init(IDType _cellID, CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY)
{
    cellID = _cellID;
    setRange(_minX,_minY,_maxX,_maxY);
}

void Cell::insertMoveObject(MoveObject &object)
{
    moveObjects.push_back(object);
}

void Cell::deleteMoveObject(IDType objID)
{
    //TODO:
}
