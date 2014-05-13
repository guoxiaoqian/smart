#include "OnlineTuning.h"
#include "core/center/Config.h"
#include "core/index/ST2BTree/Histogram.h"
#include "core/index/ST2BTree/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"

namespace smart{

OnlineTuning::OnlineTuning()
{
    p_histogram = NULL;
    p_referenceTables = NULL;
    p_st2btree = NULL;
}

OnlineTuning::~OnlineTuning()
{
}

void OnlineTuning::init()
{
    p_histogram = Histogram::getObject();
    p_referenceTables = ReferenceTables::getObject();
    p_st2btree = ST2BTree::getObject();
}

void OnlineTuning::tune()
{
    //根据统计获取新的参考点位置和密度
    vector<ReferencePoint>& oldPoints = p_referenceTables->getNewTable()->getReferencePoints();
    vector<ReferencePoint> newPoints = p_histogram->getReferencePoints(oldPoints);
    //重新划分线程映射区域
    p_histogram->resetThreadRegion();
    //更新参考点表和相应的Grid
    p_referenceTables->updateTable(newPoints);

    //旋转ST2BTree
    p_st2btree->rotate();
}

}
