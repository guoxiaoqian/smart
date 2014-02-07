#ifndef REQUESTSOURCE_H
#define REQUESTSOURCE_H

#include <vector>
using std::vector;
#include "core/center/type.h"
#include "core/request/Request.h"

class RequestSource
{
private:
    void* updateMem;
    void* queryMem;
    template<class T>
    void readFile(const char* fpath,T* p_request,int numOfRecords);
public:
    vector<Request*> requests;    //将所有种类请求按时间顺序排成一条请求序列
public:
    RequestSource();
    ~RequestSource();
    void init();
};

#endif // REQUESTSOURCE_H
