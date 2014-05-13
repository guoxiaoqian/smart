#ifndef THREADREGION_H
#define THREADREGION_H

#include "core/index/ST2BTree/HistoCell.h"

namespace smart{

class ThreadRegion
{
public:
    IDType threadID;
    int limit;
    int total;
public:
    ThreadRegion();
    void setLimit(int _limit){limit = _limit;}
    void addCell(HistoCell* p_cell);
    bool isFull(){return total>=limit;}

};

}
#endif // THREADREGION_H
