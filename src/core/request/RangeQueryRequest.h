#ifndef RANGEQUERYREQUEST_H
#define RANGEQUERYREQUEST_H

#include "Request.h"

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
    friend istream& operator>>(istream& stream,RangeQueryRequest& req);
};

#endif // RANGEQUERYREQUEST_H
