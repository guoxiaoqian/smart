#include "Smart.h"
#include "core/center/Config.h"
#include "core/request/RequestSource.h"
#include "core/thread/ThreadPool.h"
#include "core/index/ST2Grid/ST2GridIndex.h"
#include "core/index/ST2BTree/ST2BTreeIndex.h"
#include "core/index/PGrid/PGridIndex.h"
#include "base/logger/logger.h"

namespace smart{

Smart::Smart()
{
    p_config = NULL;
    p_requestSource = NULL;
    p_index = NULL;
    p_threadPool = NULL;
}

Smart::~Smart()
{
    delete p_config;
    delete p_requestSource;
    delete p_index;
    delete p_threadPool;
}

void Smart::init()
{
    p_config = Config::getObject();
    //PATH:smart/src/config.ini
    p_config->init("../src/config.ini");
    //数据源初始化
    p_requestSource = RequestSource::getObject();
    p_requestSource->init();
    //索引初始化
    switch(p_config->indexType)
    {
    case INDEX_ST2BTREE:
        p_index = ST2BTreeIndex::getObject();
        break;
    case INDEX_ST2GRID:
        p_index = ST2GridIndex::getObject();
        break;
    case INDEX_PGRID:
        p_index = PGridIndex::getObject();
        break;
    default:
        SError("no correct index!");
        p_index = ST2BTreeIndex::getObject();
    }
    p_index->init();
    //线程初始化
    p_threadPool = ThreadPool::getObject();
    p_threadPool->init(p_index);
}

void Smart::start()
{
    p_threadPool->startAll();
    p_threadPool->waitForAllOver();
}

}
