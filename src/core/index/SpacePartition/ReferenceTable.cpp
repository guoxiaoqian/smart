#include "ReferenceTable.h"
#include <limits.h>

namespace smart {

ReferenceTable::ReferenceTable()
{
    valid = false;
}

ReferenceTable::ReferenceTable(vector<Point> &points)
{
    init(points);
}

void ReferenceTable::init(vector<Point> &points)
{
    //TODO:计算每个point的泰森多边形外接矩形，并初始化成refpoint,添加

    valid = true;
}

void ReferenceTable::reset(vector<Point> &points)
{
    clear();
    init(points);
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

void ReferenceTables::init(vector<Point>& points)
{
    p_oldTable = new ReferenceTable();
    p_newTable = new ReferenceTable();
    p_newTable->init(points);
}

void ReferenceTables::updateTable(vector<Point> &points)
{
    ReferenceTable* tempTable = p_oldTable;
    p_oldTable = p_newTable;
    p_newTable = tempTable;
    p_newTable->reset(points);
}

}
