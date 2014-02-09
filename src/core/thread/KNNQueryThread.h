 #ifndef KNNQUERYTHREAD_H
#define KNNQUERYTHREAD_H

#include "core/thread/WorkThread.h"
#include "core/request/RequestQueue.h"
#include "core/request/Request.h"

class KNNQueryThread : public WorkThread
{
private:
    RequestQueue<Request*>* requests;
public:
    KNNQueryThread();
    ~KNNQueryThread();
    void init(int _thID,RequestQueue<Request*>* _requests);
    void run();
};

#endif // KNNQUERYTHREAD_H
