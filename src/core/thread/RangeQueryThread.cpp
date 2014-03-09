#include "RangeQueryThread.h"
#include "core/index/BxTree.h"
#include "core/index/KeyGen.h"

RangeQueryThread::RangeQueryThread()
{
}

RangeQueryThread::~RangeQueryThread()
{
}

ReturnType RangeQueryThread::handleRequest(Request *p_request)
{
    SDebug("range query");
    return RETURN_SUCCESS;
}
