#ifndef HISTOCELL_H
#define HISTOCELL_H

#include "core/store/Cell.h"

namespace smart {

class HistoCell : public Cell
{
public:
    IDType regionID;
    IDType threadID;
    int objectNum;
    Point center;
public:
    HistoCell();
    void setRegionID(IDType _regionID){regionID = _regionID;}
    bool isMarkedRegion(){return regionID >= 0;}
    void setThreadID(IDType _threadID){threadID = _threadID;}
    bool isMarkedThread(){return threadID >= 0;}
    void AddObject(Point& point);
    int getObjectNum(){return objectNum;}
    Point& getCenter(){return center;}
    IDType getRegionID(){return regionID;}
    IDType getThreadID(){return threadID;}
    void clear();

    HistoCell& operator+=(HistoCell& cell);
};

}
#endif // HISTOCELL_H
