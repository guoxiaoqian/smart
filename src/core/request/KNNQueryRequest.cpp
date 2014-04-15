#include "KNNQueryRequest.h"

namespace smart {

KNNQueryRequest::KNNQueryRequest()
{
    type = REQUEST_KNN_QUERY;
}

KNNQueryRequest::KNNQueryRequest(IDType _objID, TimeType _issueTime,CoorType _posX,CoorType _posY,int _knnK, TimeType _preTime)\
    :Request(REQUEST_KNN_QUERY,_objID,_issueTime),posX(_posX),posY(_posY),knnK(_knnK),preTime(_preTime)
{
}


istream& operator>>(istream& stream,KNNQueryRequest& req)
{
    stream>>req.objID>>req.issueTime>>req.posX>>req.posY>>req.knnK>>req.preTime;
    return stream;
}
}
