#include "RangeQueryRequest.h"

RangeQueryRequest::RangeQueryRequest()
{
}


istream& operator>>(istream& stream,RangeQueryRequest& req)
{
    stream>>req.objID>>req.issueTime>>req.minX>>req.minY>>req.maxX>>req.maxY>>req.preTime;
    return stream;
}
