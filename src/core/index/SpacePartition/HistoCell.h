#ifndef HISTOCELL_H
#define HISTOCELL_H

#include "core/store/Cell.h"

namespace smart {

class HistoCell : public Cell
{
public:
    IDType regionID;
    int objectNum;
    Point center;
public:
    HistoCell();
    void setRegionID(IDType _regionID){regionID = _regionID;}
    bool isMarked();
    void AddObject(Point& point);
    void clear();
};

}
#endif // HISTOCELL_H
