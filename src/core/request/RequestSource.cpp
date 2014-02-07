#include "RequestSource.h"
#include "core/center/Config.h"
#include "core/request/KNNQueryRequest.h"
#include "core/request/RangeQueryRequest.h"
#include "core/request/UpdateRequest.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace  std;

RequestSource::RequestSource()
{
    updateMem = NULL;
    queryMem = NULL;
}

RequestSource::~RequestSource()
{
    operator delete[](updateMem);
    operator delete[](queryMem);
}

bool SortByTime(Request* p_req1,Request* p_req2)
{
    return p_req1->issueTime < p_req2->issueTime;
}

void RequestSource::init()
{
    Config* p_config = Config::getConfig();
    //分配内存
    updateMem = operator new[](p_config->numOfUpdates*sizeof(UpdateRequest));
    if(p_config->queryType == QUERY_RANGE)
        queryMem = operator new[](p_config->numOfQueries*sizeof(RangeQueryRequest));
    else
        queryMem = operator new[](p_config->numOfQueries*sizeof(KNNQueryRequest));

    //读取更新数据
    char fpath[50];
    if(p_config->queryDistribution == DISTRIBUTION_GAUSSIAN)
        sprintf(fpath,"..//data//gaussian//%d//%dK//update.dat",p_config->numOfHotSpots,p_config->numOfObjects/1000);
    else
        sprintf(fpath,"..//data//uniform//%dK//update.dat",p_config->numOfObjects/1000);

    int numOfRecords = p_config->numOfUpdates;
    readFile(fpath,static_cast<UpdateRequest*>(updateMem),numOfRecords);

    //读取查询数据
    if(p_config->queryDistribution == DISTRIBUTION_GAUSSIAN)
        sprintf(fpath,"..//data//gaussian//%d//%dK//query.dat",p_config->numOfHotSpots,p_config->numOfObjects/1000);
    else
        sprintf(fpath,"..//data//uniform//%dK//query.dat",p_config->numOfObjects/1000);

    numOfRecords = p_config->numOfQueries;
    if(p_config->queryType == QUERY_RANGE)
        readFile(fpath,static_cast<RangeQueryRequest*>(queryMem),numOfRecords);
    else
        readFile(fpath,static_cast<KNNQueryRequest*>(queryMem),numOfRecords);

    //按时间顺序排序
    sort(requests.begin(),requests.end(),SortByTime);
}

template<class T>
void RequestSource::readFile(const char* fpath,T* p_request,int numOfRecords)
{
    ifstream inf(fpath);
    if(inf)
    {
        string line;
        istringstream ins(line);
        for(int i=0;i< numOfRecords&& !inf.eof();i++,p_request+=1)
        {
            new (p_request) T();
            //读取ASCII
            getline(inf,line);
            ins>>*p_request;

            requests.push_back(p_request);
        }
        inf.close();
    }
}
