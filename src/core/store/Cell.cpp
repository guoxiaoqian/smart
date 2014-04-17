#include "Cell.h"

namespace smart {

int Cell::maxObjectNum = 256;

Cell::Cell()
{    
}

Cell::Cell(IDType _cellID, Rect &rect):\
    Rect(rect),cellID(_cellID)
{
}

void Cell::init(IDType _cellID, Rect &rect)
{
    cellID = _cellID;
    setRange(rect);
}

void Cell::insertMoveObject(MoveObject &object)
{
    moveObjects.push_back(object);
}

void Cell::deleteMoveObject(IDType objID)
{
    //TODO:
}
}
