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
    vector<MoveObject> result;
    if(p_knn)
    {
        return p_index->query(p_knn,result);
    }
    else
        return RETURN_FAIL;
}

}
