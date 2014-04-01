#include "ReferenceTable.h"
#include "base/tool/Fun.h"
#include <limits.h>

ReferenceTable::ReferenceTable()
{
}

void ReferenceTable::insertReferencePoint(ReferencePoint &point)
{
    referencePoints.push_back(point);
}


//根据坐标找到最近的参照点
Grid *ReferenceTable::getGrid(CoorType coorX, CoorType coorY)
{
    vector<ReferencePoint>::iterator it_tmp;
    vector<ReferencePoint>::iterator it_min;
    double minDistance = LONG_MAX;
    double tmpDistance;
    for(it_tmp = referencePoints.begin();it_tmp != referencePoints.end();++it_tmp)
    {
        if((tmpDistance = Fun::getDistance(coorX,coorY,it_tmp->coorX,it_tmp->coorY)) < minDistance)
        {
            minDistance = tmpDistance;
            it_min = it_tmp;
        }
    }
    return it_min->getGrid();
}
