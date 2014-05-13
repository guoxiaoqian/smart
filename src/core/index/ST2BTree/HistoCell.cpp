#include "HistoCell.h"

namespace smart {

HistoCell::HistoCell()
{
    clear();
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
    threadID = -1;
    objectNum = 0;
    center = Point(0,0);
}

HistoCell &HistoCell::operator+=(HistoCell &cell)
{
    Point center2 = cell.getCenter();
    int objectNum2 = cell.getObjectNum();
    center.setPoint((center.coorX*objectNum + center2.coorX*objectNum2)/(objectNum+objectNum2),\
                    (center.coorY*objectNum + center2.coorY*objectNum2)/(objectNum+objectNum2));
    objectNum+=objectNum2;
    return *this;
}

}
