#include "OnlineTuning.h"
#include "core/center/Config.h"
#include "core/index/Histogram.h"
#include "core/index/SpacePartition/ReferenceTable.h"
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
    //TODO周期性调整

    //切换新旧参考点表
    p_referenceTables->switchTable();
    //根据统计获取新的参考点位置和密度
    vector<ReferencePoint> points = p_histogram->getReferencePoints();

    //更新参考点表和相应的Grid
    p_referenceTables->updateTable(points);

    //旋转ST2BTree
    p_st2btree->rotate();
}

}
