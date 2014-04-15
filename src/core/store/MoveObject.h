#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include "core/store/Point.h"
namespace smart{
class MoveObject : public Point
{
public:
    SpeedType velX;
    SpeedType velY;
    IDType objID;
    TimeType lastUpdateTime;
public:
    MoveObject();
    MoveObject(int _objID, int _issueTime,CoorType _posX,CoorType _posY,SpeedType _velX,SpeedType _velY);
};
}
#endif // MOVEOBJECT_H
