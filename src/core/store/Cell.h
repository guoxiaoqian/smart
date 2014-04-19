#ifndef CELL_H
#define CELL_H

#include "core/store/Rect.h"

namespace smart{

class Cell:public Rect
{
public:
    IDType cellID;
public:
    Cell();
    Cell(IDType _cellID,Rect& rect);
    void init(IDType _cellID,Rect& rect);
    IDType getID(){return cellID;}
    virtual void clear(){}
};
}
#endif // CELL_H
