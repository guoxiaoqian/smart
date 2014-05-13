#include "PGridIndex.h"

namespace smart {

PGridIndex::PGridIndex()
{
    type = INDEX_STATIC;
}

PGridIndex::~PGridIndex()
{
}

void PGridIndex::init()
{
}

ReturnType PGridIndex::update(UpdateRequest *p_update)
{
}

ReturnType PGridIndex::query(RangeQueryRequest *p_range, vector<MoveObject> &result)
{
}

ReturnType PGridIndex::query(KNNQueryRequest *p_knn, vector<MoveObject> &result)
{
}

IDType PGridIndex::getThreadID(UpdateRequest *p_update)
{

}

IDType PGridIndex::getThreadID(RangeQueryRequest *p_range)
{

}

IDType PGridIndex::getThreadID(KNNQueryRequest *p_knn)
{

}


}
