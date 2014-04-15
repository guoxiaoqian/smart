#include "ReferenceTable.h"
#include <limits.h>

namespace smart {

ReferenceTable::ReferenceTable()
{
}

ReferenceTable::ReferenceTable(vector<Point> &points)
{
    init(points);
}

void ReferenceTable::init(vector<Point> &points)
{
    //TODO:计算每个point的泰森多边形外接矩形，并初始化成refpoint,添加

}

void ReferenceTable::reinit(vector<Point> &points)
{
    referencePoints.clear();
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
}
