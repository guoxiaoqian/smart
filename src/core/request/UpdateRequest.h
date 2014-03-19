#ifndef UPDATEREQUEST_H
#define UPDATEREQUEST_H

#include "Request.h"

class UpdateRequest : public Request
{
public:
    CoorType posX;
    CoorType posY;
    SpeedType velX;
    SpeedType velY;
public:
    UpdateRequest();
    UpdateRequest(int _objID, int _issueTime,CoorType _posX,CoorType _posY,SpeedType _velX,SpeedType _velY);
    friend istream& operator>>(istream& stream,UpdateRequest& req);
};


#endif // UPDATEREQUEST_H
