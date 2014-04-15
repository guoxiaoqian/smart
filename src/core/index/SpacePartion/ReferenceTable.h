#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

#include "core/store/ReferencePoint.h"
#include "base/kernel/singleton.hpp"
#include <vector>
using namespace std;

namespace smart{

class ReferenceTable:public SSingleton<ReferenceTable>
{
public:
    vector<ReferencePoint> referencePoints;
public:
    ReferenceTable();
    ReferenceTable(vector<Point>& points);
    void init(vector<Point>& points);
    void reinit(vector<Point>& points);
    //求最近参考点
    ReferencePoint* getReferencePoint(Point &point);
    unsigned int getReferencePointNum(){return referencePoints.size();}
};

}
#endif // REFERENCETABLE_H
