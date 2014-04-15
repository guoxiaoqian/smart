#ifndef REQUEST_H
#define REQUEST_H

#include "core/center/type.h"
#include "iostream"
using std::istream;
namespace smart{

class Request
{
public:
    RequestType type;
    IDType objID;
    TimeType issueTime;
public:
    Request();
    virtual ~Request(){}
    Request(RequestType _type,IDType _objID,TimeType _issueTime);
};

}
#endif // REQUEST_H
