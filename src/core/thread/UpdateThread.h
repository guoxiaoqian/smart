#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include "core/thread/HandleThread.h"
class BxTree;
class Histogram;
class KeyGen;

class UpdateThread : public HandleThread
{
private:
    //索引
    Histogram * p_histogram;
    KeyGen * p_keyGen;
    BxTree * p_bxTree;
public:
    UpdateThread();
    ~UpdateThread();
    ReturnType handleRequest(Request* p_request);
};

#endif // UPDATETHREAD_H
