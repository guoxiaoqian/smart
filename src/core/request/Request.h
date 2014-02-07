#ifndef REQUEST_H
#define REQUEST_H

#include "core/center/type.h"
#include <iostream>
using namespace std;

class Request
{
public:
    RequestType type;
    IDType objID;
    TimeType issueTime;
public:
    Request();
    Request(RequestType _type,int _objID,int _issueTime);
};

#endif // REQUEST_H
