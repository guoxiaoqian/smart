#include "DynamicIndex.h"
#include "core/index/Histogram.h"
#include "core/index/KeyGen.h"
#include "core/index/OnlineTuning.h"
#include "core/index/SpacePartion/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"

namespace smart {

DynamicIndex::DynamicIndex()
{
    p_histogram = Histogram::getObject();
    p_keyGen = KeyGen::getObject();
    p_onlineTuning = OnlineTuning::getObject();
    p_referenceTable = ReferenceTable::getObject();
    p_st2btree = ST2BTree::getObject();
}

void DynamicIndex::init()
{
}

}
