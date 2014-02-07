#include "KNNQueryRequest.h"

KNNQueryRequest::KNNQueryRequest()
{
}


istream& operator>>(istream& stream,KNNQueryRequest& req)
{
    stream>>req.objID>>req.issueTime>>req.knnK>>req.preTime;
    return stream;
}
