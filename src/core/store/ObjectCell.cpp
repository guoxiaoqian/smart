#include "ObjectCell.h"

namespace smart {

int ObjectCell::maxObjectNum = 256;

ObjectCell::ObjectCell()
{
}

void ObjectCell::insertMoveObject(MoveObject &object)
{
    moveObjects.push_back(object);
}

void ObjectCell::deleteMoveObject(IDType objID)
{
    //TODO:删除移动对象
}

void ObjectCell::clear()
{
    moveObjects.clear();
}
}
