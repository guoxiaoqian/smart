#ifndef DENSTYREGION_H
#define DENSTYREGION_H

#include "core/index/SpacePartition/HistoCell.h"
#include <vector>
using std::vector;

//职责：根据密度聚集Cell

namespace smart {

class DenstyRegion
{
public:
    static int similarParam;
    IDType regionID;
    vector<HistoCell*> cells;
    int maxNumInCell;
    int minNumInCell;
public:
    DenstyRegion(IDType _regionID);
    void addCell(HistoCell* p_cell);
    Point getCenter();
    float getDensty();
    IDType getID(){return regionID;}
    bool isSimilar(HistoCell* p_cell);
    bool isEmpty(){return maxNumInCell == 0;}
    int getCellNum(){return cells.size();}
};

}
#endif // DENSTYREGION_H
