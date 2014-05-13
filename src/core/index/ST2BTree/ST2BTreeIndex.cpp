#include "ST2BTreeIndex.h"
#include "core/index/ST2BTree/Histogram.h"
#include "core/index/ST2BTree/KeyGen.h"
#include "core/index/ST2BTree/OnlineTuning.h"
#include "core/index/ST2BTree/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"

namespace smart {

ST2BTreeIndex::ST2BTreeIndex()
{
    type = INDEX_DYNAMIC;
    p_histogram = NULL;
    p_keyGen = NULL;
    p_onlineTuning = NULL;
    p_referenceTables = NULL;
    p_st2btree = NULL;
}

ST2BTreeIndex::~ST2BTreeIndex()
{
}

void ST2BTreeIndex::init()
{
    p_histogram = Histogram::getObject();
    p_keyGen = KeyGen::getObject();
    p_onlineTuning = OnlineTuning::getObject();
    p_referenceTables = ReferenceTables::getObject();
    p_st2btree = ST2BTree::getObject();

    p_referenceTables->init();
    p_histogram->init();
    p_keyGen->init();\
    p_st2btree->init();
    p_onlineTuning->init();
}

ReturnType ST2BTreeIndex::update(UpdateRequest *p_update)
{
    p_histogram->update(p_update);
    KeyType key = p_keyGen->getKey(p_update);
    return p_st2btree->update(key,p_update);
}

ReturnType ST2BTreeIndex::query(RangeQueryRequest *p_range, vector<MoveObject> &result)
{
    //TODO
}

ReturnType ST2BTreeIndex::query(KNNQueryRequest *p_knn,vector<MoveObject>& result)
{
    //TODO
}

IDType ST2BTreeIndex::getThreadID(UpdateRequest *p_update)
{
    Point point(p_update->posX,p_update->posY);
    return p_histogram->getThreadID(point);
}

IDType ST2BTreeIndex::getThreadID(RangeQueryRequest *p_range)
{
    Point point((p_range->minX+p_range->maxX)/2,(p_range->minY+p_range->maxY)/2);
    return p_histogram->getThreadID(point);
}

IDType ST2BTreeIndex::getThreadID(KNNQueryRequest *p_knn)
{
    Point point(p_knn->posX,p_knn->posY);
    return p_histogram->getThreadID(point);
}

void ST2BTreeIndex::tune()
{
    p_onlineTuning->tune();
}

}
