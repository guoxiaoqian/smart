#include "MoveObject.h"

namespace core {


MoveObject::MoveObject()
{
}

MoveObject::MoveObject(int _objID, int _issueTime, CoorType _posX, CoorType _posY, SpeedType _velX, SpeedType _velY):\
Point(_posX,_posY),velX(_velX),velY(_velY),objID(_objID),lastUpdateTime(_issueTime)
{
}

}
