#include "UpdateRequest.h"

UpdateRequest::UpdateRequest()
{
}

UpdateRequest::UpdateRequest(RequestType _type, int _objID, int _issueTime, CoorType _posX, CoorType _posY, SpeedType _velX, SpeedType _velY)\
    :Request(_type,_objID,_issueTime),posX(_posX),posY(_posY),velX(_velX),velY(_velY)
{
}

istream& operator>>(istream& stream,UpdateRequest& req)
{
    stream>>req.objID>>req.issueTime>>req.posX>>req.posY>>req.velX>>req.velY;
    return stream;
}
