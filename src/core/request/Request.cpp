#include "Request.h"

namespace smart {


Request::Request()
{
}

Request::Request(RequestType _type, IDType _objID, TimeType _issueTime):type(_type),objID(_objID),issueTime(_issueTime)
{
}

}
