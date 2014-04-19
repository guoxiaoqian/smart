#include "DenstyRegion.h"
#include "core/index/SpacePartition/Histogram.h"
#include <math.h>

namespace smart {

DenstyRegion::DenstyRegion(IDType _regionID)
{
    regionID = _regionID;
    maxNumInCell = 0;
    minNumInCell = 0;
}


void DenstyRegion::addCell(HistoCell* p_cell)
{
    p_cell->setRegionID(regionID);
    int objectNum = p_cell->objectNum;
    cells.push_back(p_cell);
    if(maxNumInCell == 0)
    {
       maxNumInCell = minNumInCell = objectNum;
    }
    else
    {
        if(maxNumInCell < objectNum)
            maxNumInCell = objectNum;
        else if(minNumInCell > objectNum)
            minNumInCell = objectNum;
    }
}

Point DenstyRegion::getCenter()
{
    Point point(0,0);
    for(vector<HistoCell*>::iterator it= cells.begin(); it!= cells.end();++it)
    {
        point=point+(*it)->center;
    }
    point.setPoint(point.coorX/getCellNum(),point.coorY/getCellNum());
    return point;
}

float DenstyRegion::getDensty()
{
    //计算区域面积
    CoorType area = cells[0]->getArea()*getCellNum();
    //计算区域内对象数量
    int objectNum = 0;
    for(vector<HistoCell*>::iterator it= cells.begin(); it!= cells.end();++it)
    {
        objectNum+=(*it)->objectNum;
    }
    return (float)objectNum/area;
}

bool DenstyRegion::isSimilar(HistoCell *p_cell)
{
    return abs(p_cell->objectNum-maxNumInCell) <= Histogram::similarParam &&\
            abs(p_cell->objectNum-minNumInCell) <= Histogram::similarParam;
}

}
