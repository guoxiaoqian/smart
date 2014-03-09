#ifndef RANGEQUERYTHREAD_H
#define RANGEQUERYTHREAD_H

#include "core/thread/HandleThread.h"
class BxTree;
class KeyGen;

class RangeQueryThread : public HandleThread
{
private:
    //索引
    KeyGen * p_keyGen;
    BxTree * p_bxTree;
public:
    RangeQueryThread();
    ~RangeQueryThread();
    ReturnType handleRequest(Request *p_request);
};

#endif // RANGEQUERYTHREAD_H
