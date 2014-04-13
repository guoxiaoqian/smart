#ifndef RANGEQUERYREQUEST_H
#define RANGEQUERYREQUEST_H

#include "Request.h"

namespace core{

class RangeQueryRequest : public Request
{
public:
    CoorType minX;
    CoorType minY;
    CoorType maxX;
    CoorType maxY;
    TimeType preTime;
public:
    RangeQueryRequest();
    RangeQueryRequest(IDType _objID, TimeType _issueTime,CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY, TimeType _preTime = 0);
    friend istream& operator>>(istream& stream,RangeQueryRequest& req);
};

}
#endif // RANGEQUERYREQUEST_H
