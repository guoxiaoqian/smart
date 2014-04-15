#include "DynamicIndex.h"
#include "core/index/Histogram.h"
#include "core/index/KeyGen.h"
#include "core/index/OnlineTuning.h"
#include "core/index/SpacePartition/ReferenceTable.h"
#include "core/index/ST2BTree/ST2BTree.h"
#include "core/center/Config.h"

namespace smart {

DynamicIndex::DynamicIndex()
{
    period = 0;
    p_histogram = NULL;
    p_keyGen = NULL;
    p_onlineTuning = NULL;
    p_referenceTable[0]=NULL;
    p_referenceTable[1]=NULL;
    p_st2btree = NULL;
    p_config = NULL;
}

DynamicIndex::~DynamicIndex()
{
    delete p_referenceTable[0];
    delete p_referenceTable[1];
}

void DynamicIndex::init()
{
    p_histogram = Histogram::getObject();
    p_keyGen = KeyGen::getObject();
    p_onlineTuning = OnlineTuning::getObject();
    p_referenceTable[0] = new ReferenceTable();
    p_referenceTable[1] = new ReferenceTable();
    p_st2btree = ST2BTree::getObject();
    p_config = Config::getObject();

    CoorType minX = p_config->minCoorX;
    CoorType minY = p_config->minCoorY;
    CoorType maxX = p_config->maxCoorX;
    CoorType maxY = p_config->maxCoorY;
    //预设4个参考点，将整个空间四均分
    vector<Point> points;
    points.push_back(Point(minX+(maxX-minX)/4,maxY-(maxY-minY)/4));
    points.push_back(Point(maxX-(maxX-minX)/4,maxY-(maxY-minY)/4));
    points.push_back(Point(minX+(maxX-minX)/4,minY+(maxY-minY)/4));
    points.push_back(Point(maxX-(maxX-minX)/4,minY+(maxY-minY)/4));
    p_referenceTable[period]->init(points);

    p_histogram->init();
    p_keyGen->init(p_referenceTable[period]);
    p_onlineTuning->init();
    p_st2btree->init();

}

void DynamicIndex::tune()
{
    //切换当前参考点表
    period = (period+1)%2;
    p_keyGen->setReferenceTable(p_referenceTable[period]);
    p_onlineTuning->tune();
}

}
