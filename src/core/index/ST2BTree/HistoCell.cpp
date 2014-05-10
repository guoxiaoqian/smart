#include "HistoCell.h"

namespace smart {

HistoCell::HistoCell()
{
    clear();
}

bool HistoCell::isMarked()
{
    return regionID >= 0;
}

void HistoCell::AddObject(Point &point)
{
    center.setPoint((center.coorX*objectNum+point.coorX)/(objectNum+1),\
                    (center.coorY*objectNum+point.coorY)/(objectNum+1));
    ++objectNum;
}

void HistoCell::clear()
{
    regionID = -1;
    objectNum = 0;
    center = Point(0,0);
}

}
