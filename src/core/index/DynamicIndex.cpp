#include "DynamicIndex.h"
#include "core/index/SpacePartition/Histogram.h"
#include "core/index/KeyGen.h"
#include "core/index/OnlineTuning.h"
#include "core/index/SpacePartition/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"

namespace smart {

DynamicIndex::DynamicIndex()
{
    p_histogram = NULL;
    p_keyGen = NULL;
    p_onlineTuning = NULL;
    p_referenceTables = NULL;
    p_st2btree = NULL;
}

DynamicIndex::~DynamicIndex()
{
}

void DynamicIndex::init()
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

ReturnType DynamicIndex::update(UpdateRequest *p_update)
{
}

ReturnType DynamicIndex::query(RangeQueryRequest *p_range)
{
}

ReturnType DynamicIndex::query(KNNQueryRequest *p_range)
{
}

}
