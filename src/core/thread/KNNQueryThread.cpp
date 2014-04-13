#include "KNNQueryThread.h"
#include "core/request/KNNQueryRequest.h"

namespace core {

KNNQueryThread::KNNQueryThread()
{
}

KNNQueryThread::~KNNQueryThread()
{
}

ReturnType KNNQueryThread::handleRequest(Request *p_request)
{
    KNNQueryRequest* p_knn = dynamic_cast<KNNQueryRequest*>(p_request);
    if(p_knn)
    {
        //TODO
        return RETURN_SUCCESS;
    }
    else
        return RETURN_FAIL;
}

}
