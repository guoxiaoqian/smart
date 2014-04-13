#ifndef REQUESTSOURCE_H
#define REQUESTSOURCE_H

#include <vector>
using std::vector;
#include "core/request/Request.h"
#include "base/kernel/singleton.hpp"

namespace core{

class RequestSource:public base::SSingleton<RequestSource>
{
private:
    void* updateMem;
    void* queryMem;
    vector<Request*>::iterator it_current;
    template<class T>
    void readFile(const char* fpath,T* p_request,int numOfRecords);
public:
    vector<Request*> requests;    //将所有种类请求按时间顺序排成一条请求序列    
public:
    RequestSource();
    ~RequestSource();
    ReturnType getRequest(int thID,int num,vector<Request*>::iterator& begin,vector<Request*>::iterator& end);
    void increaseCurrent(int num);
    void init();

};

}
#endif // REQUESTSOURCE_H
