#include "RequestSource.h"
#include "core/center/Config.h"
#include "core/request/KNNQueryRequest.h"
#include "core/request/RangeQueryRequest.h"
#include "core/request/UpdateRequest.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace  std;


namespace smart {

RequestSource::RequestSource()
{
    updateMem = NULL;
    queryMem = NULL;
}

RequestSource::~RequestSource()
{
    for(vector<Request*>::iterator it = requests.begin();it!=requests.end();++it)
    {
        (*it)->~Request();
    }
    operator delete[](updateMem);
    operator delete[](queryMem);
}

ReturnType RequestSource::getRequest(int thID,int num,vector<Request*>::iterator &begin, vector<Request*>::iterator &end)
{
    begin = it_current + thID * num;
    if(requests.end() - begin < num)
    {
        return RETURN_FAIL;
    }
    end = begin+num-1;
    return RETURN_SUCCESS;
}

void RequestSource::increaseCurrent(int num)
{
    it_current+=num;
}

bool SortByTime(Request* p_req1,Request* p_req2)
{
    return p_req1->issueTime < p_req2->issueTime;
}

void RequestSource::init()
{
    Config* p_config = Config::getObject();
    //分配内存
    updateMem = operator new[](p_config->numOfUpdates*sizeof(UpdateRequest));
    if(p_config->queryType == QUERY_RANGE)
        queryMem = operator new[](p_config->numOfQueries*sizeof(RangeQueryRequest));
    else
        queryMem = operator new[](p_config->numOfQueries*sizeof(KNNQueryRequest));

    //读取更新数据
    char fpath[50];
    if(p_config->distributionType == DISTRIBUTION_GAUSSIAN)
        sprintf(fpath,"../data/gaussian/%d/%dK/update.dat",p_config->numOfHotspots,p_config->numOfObjects/1000);
    else
        sprintf(fpath,"../data/uniform/%dK/update.dat",p_config->numOfObjects/1000);

    int numOfRecords = p_config->numOfUpdates;
    readFile(fpath,static_cast<UpdateRequest*>(updateMem),numOfRecords);

    //读取查询数据
    if(p_config->distributionType == DISTRIBUTION_GAUSSIAN)
        sprintf(fpath,"../data/gaussian/%d/%dK/query.dat",p_config->numOfHotspots,p_config->numOfObjects/1000);
    else
        sprintf(fpath,"../data/uniform/%dK/query.dat",p_config->numOfObjects/1000);

    numOfRecords = p_config->numOfQueries;
    if(p_config->queryType == QUERY_RANGE)
        readFile(fpath,static_cast<RangeQueryRequest*>(queryMem),numOfRecords);
    else
        readFile(fpath,static_cast<KNNQueryRequest*>(queryMem),numOfRecords);

    //按时间顺序排序
    sort(requests.begin(),requests.end(),SortByTime);
    it_current = requests.begin();
}

template<class T>
void RequestSource::readFile(const char* fpath,T* p_request,int numOfRecords)
{
    ifstream inf(fpath);
    if(inf)
    {
        string line;
        for(int i=0;i< numOfRecords&& !inf.eof();++i,++p_request)
        {
            new (p_request) T();
            //读取ASCII
            getline(inf,line);
            istringstream ins(line);
            ins>>*p_request;

            requests.push_back(p_request);
        }
        inf.close();
    }
}
}
