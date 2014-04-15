#include "RangeQueryRequest.h"

namespace smart {


RangeQueryRequest::RangeQueryRequest()
{
    type = REQUEST_RANGE_QUERY;
}

RangeQueryRequest::RangeQueryRequest(IDType _objID, TimeType _issueTime, CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY, TimeType _preTime)\
    :Request(REQUEST_RANGE_QUERY,_objID,_issueTime),minX(_minX),minY(_minY),maxX(_maxX),maxY(_maxY),preTime(_preTime)
{
}


istream& operator>>(istream& stream,RangeQueryRequest& req)
{
    stream>>req.objID>>req.issueTime>>req.minX>>req.minY>>req.maxX>>req.maxY>>req.preTime;
    return stream;
}
}
