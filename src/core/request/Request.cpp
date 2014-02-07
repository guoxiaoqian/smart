#include "Request.h"

Request::Request()
{
}

Request::Request(RequestType _type, int _objID, int _issueTime):type(_type),objID(_objID),issueTime(_issueTime)
{
}

