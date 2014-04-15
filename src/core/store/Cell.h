#ifndef CELL_H
#define CELL_H

#include "core/store/Rect.h"
#include "core/store/MoveObject.h"
#include <list>
using namespace std;

namespace smart{
class Cell:public Rect
{
public:
    IDType cellID;
    list<MoveObject> moveObjects;
public:
    Cell();
    Cell(IDType _cellID,Rect& rect);
    void init(IDType _cellID,Rect& rect);
    void insertMoveObject(MoveObject& object);
    void deleteMoveObject(IDType objID);
};
}
#endif // CELL_H
