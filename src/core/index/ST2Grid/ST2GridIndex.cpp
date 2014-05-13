#include "ST2GridIndex.h"
#include "core/center/Config.h"

namespace smart {

ST2GridIndex::ST2GridIndex()
{
     type = INDEX_DYNAMIC;
}

void ST2GridIndex::init()
{
    Config* p_config = Config::getObject();
    updateThreadNum = p_config->numOfUpdateThreads;
    queryThreadNum = p_config->numOfQueryThreads;
}

ReturnType ST2GridIndex::update(UpdateRequest *p_update)
{
    //TODO
    return RETURN_SUCCESS;
}

ReturnType ST2GridIndex::query(RangeQueryRequest *p_range, vector<MoveObject> &result)
{
    //TODO
    return RETURN_SUCCESS;
}

ReturnType ST2GridIndex::query(KNNQueryRequest *p_knn, vector<MoveObject> &result)
{
    //TODO
    return RETURN_SUCCESS;
}

IDType ST2GridIndex::getThreadID(UpdateRequest *p_update)
{
    //TODO 从Histogram获取映射线程的ID
    //暂时使用轮询法
    static int updateThreadID = -1;
    updateThreadID = (updateThreadID+1)% updateThreadNum;
    return updateThreadID;
}

IDType ST2GridIndex::getThreadID(RangeQueryRequest *p_range)
{
    //TODO 从Histogram获取映射线程的ID
    //暂时使用轮询法
    static int queryThreadID = -1;
    queryThreadID = (queryThreadID+1)% queryThreadNum;
    return queryThreadID;
}

IDType ST2GridIndex::getThreadID(KNNQueryRequest *p_knn)
{
    //TODO 从Histogram获取映射线程的ID
    //暂时使用轮询法
    static int queryThreadID = -1;
    queryThreadID = (queryThreadID+1)% queryThreadNum;
    return queryThreadID;
}

void ST2GridIndex::tune()
{
    //TODO 索引调整过程
}

}
