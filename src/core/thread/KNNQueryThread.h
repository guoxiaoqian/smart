 #ifndef KNNQUERYTHREAD_H
#define KNNQUERYTHREAD_H

#include "core/thread/HandleThread.h"

class KNNQueryThread : public HandleThread
{
public:
    KNNQueryThread();
    ~KNNQueryThread();
    ReturnType handleRequest(Request* p_request);
};

#endif // KNNQUERYTHREAD_H
