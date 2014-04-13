#ifndef KNNQUERYREQUEST_H
#define KNNQUERYREQUEST_H

#include "Request.h"

namespace core{

class KNNQueryRequest : public Request
{
public:
    CoorType posX;
    CoorType posY;
    int knnK;
    TimeType preTime;
public:
    KNNQueryRequest();
    KNNQueryRequest(IDType _objID, TimeType _issueTime,\
                    CoorType _posX,CoorType _posY, \
                    int _knnK, TimeType _preTime = 0);
    friend istream& operator>>(istream& stream,KNNQueryRequest& req);
};

}
#endif // KNNQUERYREQUEST_H
