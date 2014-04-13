#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

#include "core/store/ReferencePoint.h"
#include "base/kernel/singleton.hpp"
#include <vector>
using namespace std;

namespace core{

class ReferenceTable:public base::SSingleton<ReferenceTable>
{
public:
    vector<ReferencePoint> referencePoints;
public:
    ReferenceTable();
    void insertReferencePoint(ReferencePoint& point);
    ReferencePoint* getReferencePoint(CoorType coorX,CoorType coorY);
    unsigned int getReferencePointNum(){return referencePoints.size();}
};

}
#endif // REFERENCETABLE_H
