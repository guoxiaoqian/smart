#include "ReferenceTable.h"
#include "core/center/Config.h"
#include "core/index/ST2BTree/VoronoiDiagram.h"
#include <limits.h>

namespace smart {

void ReferenceTable::initGrids()
{
    VoronoiDiagram::genDiagram(referencePoints);
    for(vector<ReferencePoint>::iterator it = referencePoints.begin();it!= referencePoints.end();++it)
    {
        it->initGrid();
    }
}

ReferenceTable::ReferenceTable()
{
    valid = false;
}

void ReferenceTable::init()
{
    valid = true;

    Config* p_config = Config::getObject();
    CoorType minX = p_config->minCoorX;
    CoorType minY = p_config->minCoorY;
    CoorType maxX = p_config->maxCoorX;
    CoorType maxY = p_config->maxCoorY;
    //预设4个参考点，将整个空间四均分
    Point point(minX+(maxX-minX)/4,maxY-(maxY-minY)/4);
    ReferencePoint rp(0,point);
    referencePoints.push_back(rp);
    point.setPoint(maxX-(maxX-minX)/4,maxY-(maxY-minY)/4);
    rp.init(1,point);
    referencePoints.push_back(rp);
    point.setPoint(minX+(maxX-minX)/4,minY+(maxY-minY)/4);
    rp.init(2,point);
    referencePoints.push_back(rp);
    point.setPoint(maxX-(maxX-minX)/4,minY+(maxY-minY)/4);
    rp.init(3,point);
    referencePoints.push_back(rp);

    initGrids();
}

void ReferenceTable::reset(vector<ReferencePoint> &points)
{
    referencePoints = points;

    initGrids();
}


//根据坐标找到最近的参照点
ReferencePoint* ReferenceTable::getReferencePoint(Point& point)
{
    vector<ReferencePoint>::iterator it_tmp;
    vector<ReferencePoint>::iterator it_min;
    double minDistance = LONG_MAX;
    double tmpDistance;
    for(it_tmp = referencePoints.begin();it_tmp != referencePoints.end();++it_tmp)
    {
        if((tmpDistance = point.getDistance(*it_tmp)) < minDistance)
        {
            minDistance = tmpDistance;
            it_min = it_tmp;
        }
    }
    return &(*it_min);
}

ReferenceTables::ReferenceTables()
{
    p_oldTable = 0;
    p_newTable = 0;
}

ReferenceTables::~ReferenceTables()
{
    delete p_oldTable;
    delete p_newTable;
}

void ReferenceTables::init()
{
    p_oldTable = new ReferenceTable();
    p_newTable = new ReferenceTable();
    p_newTable->init();
}

void ReferenceTables::updateTable(vector<ReferencePoint> &points)
{
    //用points初始化新的Table
    ReferenceTable* tempTable = p_oldTable;
    p_oldTable = p_newTable;
    p_newTable = tempTable;
    p_newTable->reset(points);
}

}
