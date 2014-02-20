#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include "core/thread/HandleThread.h"


class UpdateThread : public HandleThread
{
public:
    UpdateThread();
    ~UpdateThread();
    ReturnType handleRequest(Request* p_request);
};

#endif // UPDATETHREAD_H
