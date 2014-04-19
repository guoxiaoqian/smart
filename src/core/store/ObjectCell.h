#ifndef OBJECTCELL_H
#define OBJECTCELL_H

#include "core/store/Cell.h"
#include "core/store/MoveObject.h"
#include <list>
using namespace std;

namespace smart {

class ObjectCell:public Cell
{
public:
    static int maxObjectNum;
    list<MoveObject> moveObjects;
public:
    ObjectCell();
    void insertMoveObject(MoveObject& object);
    void deleteMoveObject(IDType objID);
    void clear();
};

}

#endif // OBJECTCELL_H
