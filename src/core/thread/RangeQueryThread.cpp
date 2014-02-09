#include "RangeQueryThread.h"

RangeQueryThread::RangeQueryThread()
{
}

RangeQueryThread::~RangeQueryThread()
{
}

void RangeQueryThread::init(int _thID, RequestQueue<Request *> *_requests)
{
    thID = _thID;
    requests = _requests;
}

void RangeQueryThread::run()
{
}
