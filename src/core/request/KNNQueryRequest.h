#ifndef KNNQUERYREQUEST_H
#define KNNQUERYREQUEST_H

#include "Request.h"

class KNNQueryRequest : public Request
{
public:
    int knnK;
    TimeType preTime;
public:
    KNNQueryRequest();
    friend istream& operator>>(istream& stream,KNNQueryRequest& req);
};

#endif // KNNQUERYREQUEST_H
