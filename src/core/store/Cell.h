#ifndef CELL_H
#define CELL_H

#include "core/store/Rect.h"
#include "core/store/MoveObject.h"
#include <list>
using namespace std;


class Cell:public Rect
{
public:
    IDType cellID;
    list<MoveObject> moveObjects;
public:
    Cell();
    Cell(IDType _cellID,CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY);
    void init(IDType _cellID,CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY);
    void insertMoveObject(MoveObject& object);
    void deleteMoveObject(IDType objID);
};

#endif // CELL_H
