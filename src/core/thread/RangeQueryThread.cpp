#include "RangeQueryThread.h"
#include "core/request/RangeQueryRequest.h"

namespace smart {

RangeQueryThread::RangeQueryThread()
{
}

RangeQueryThread::~RangeQueryThread()
{
}

ReturnType RangeQueryThread::handleRequest(Request *p_request)
{
    RangeQueryRequest* p_range = dynamic_cast<RangeQueryRequest*>(p_request);
    vector<MoveObject> result;
    if(p_range)
    {
        return p_index->query(p_range,result);
    }
    else
        return RETURN_BADPARAM;
}

}
