#include "ST2BTreeIndex.h"
#include "core/index/ST2BTree/Histogram.h"
#include "core/index/ST2BTree/KeyGen.h"
#include "core/index/ST2BTree/OnlineTuning.h"
#include "core/index/ST2BTree/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"

namespace smart {

ST2BTreeIndex::ST2BTreeIndex()
{
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

ReturnType ST2BTreeIndex::rangeQuery(RangeQueryRequest *p_range)
{
    //TODO
}

ReturnType ST2BTreeIndex::knnQuery(KNNQueryRequest *p_knn)
{
    //TODO
}

void ST2BTreeIndex::tune()
{
    p_onlineTuning->tune();
}

}
