#include "UpdateThread.h"
#include "core/request/UpdateRequest.h"

namespace core {

UpdateThread::UpdateThread()
{
}

UpdateThread::~UpdateThread()
{
}

ReturnType UpdateThread::handleRequest(Request *p_request)
{
    //SDebug("update");
    UpdateRequest* p_update = dynamic_cast<UpdateRequest*>(p_request);
    if(p_update)
    {
        //TODO
        return RETURN_SUCCESS;
    }
    else
        return RETURN_FAIL;
}

}
