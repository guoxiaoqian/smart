#include "KNNQueryThread.h"

KNNQueryThread::KNNQueryThread()
{
}

KNNQueryThread::~KNNQueryThread()
{
}

void KNNQueryThread::init(int _thID, RequestQueue<Request *> *_requests)
{
    thID = _thID;
    requests = _requests;
}

void KNNQueryThread::run()
{
}
