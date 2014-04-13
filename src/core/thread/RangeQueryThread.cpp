#include "RangeQueryThread.h"
#include "core/request/RangeQueryRequest.h"

namespace core {

RangeQueryThread::RangeQueryThread()
{
}

RangeQueryThread::~RangeQueryThread()
{
}

ReturnType RangeQueryThread::handleRequest(Request *p_request)
{
    //SDebug("range query");
    RangeQueryRequest* p_range = dynamic_cast<RangeQueryRequest*>(p_request);
    if(p_range)
    {
        //TODO
        return RETURN_SUCCESS;
    }
    else
        return RETURN_FAIL;
}

}
