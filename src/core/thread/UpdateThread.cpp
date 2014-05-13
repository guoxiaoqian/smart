#include "UpdateThread.h"
#include "core/request/UpdateRequest.h"

namespace smart {

UpdateThread::UpdateThread()
{
}

UpdateThread::~UpdateThread()
{
}

ReturnType UpdateThread::handleRequest(Request *p_request)
{
    UpdateRequest* p_update = dynamic_cast<UpdateRequest*>(p_request);
    if(p_update)
    {
        return p_index->update(p_update);
    }
    else
        return RETURN_BADPARAM;
}

}
