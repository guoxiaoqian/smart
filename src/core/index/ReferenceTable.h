#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

#include "core/store/ReferencePoint.h"
#include "base/kernel/singleton.hpp"
#include <vector>
using namespace std;

class ReferenceTable:public SSingleton<ReferenceTable>
{
public:
    vector<ReferencePoint> referencePoints;
public:
    ReferenceTable();
    void insertReferencePoint(ReferencePoint& point);
    Grid* getGrid(CoorType coorX,CoorType coorY);
};

#endif // REFERENCETABLE_H
