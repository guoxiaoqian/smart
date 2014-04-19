#include "KNNQueryThread.h"
#include "core/request/KNNQueryRequest.h"

namespace smart {

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
        return RETURN_SUCCESS;
        //return p_index->query(p_knn);
    }
    else
        return RETURN_FAIL;
}

}
