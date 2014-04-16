#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

#include "core/index/SpacePartition/ReferencePoint.h"
#include "base/kernel/singleton.hpp"
#include <vector>
using namespace std;

namespace smart{

class ReferenceTable
{
public:
    vector<ReferencePoint> referencePoints;
    bool valid;
public:
    ReferenceTable();
    ReferenceTable(vector<Point>& points);
    void init(vector<Point>& points);
    void reset(vector<Point>& points);
    //求最近参考点
    ReferencePoint* getReferencePoint(Point &point);
    unsigned int getReferencePointNum(){return referencePoints.size();}
    bool isValid(){return valid;}
    void clear(){referencePoints.clear();}
};

class ReferenceTables:public SSingleton<ReferenceTables>
{
public:
    ReferenceTable* p_oldTable;
    ReferenceTable* p_newTable;

    ReferenceTables();
    ~ReferenceTables();
    void init(vector<Point> &points);
    void updateTable(vector<Point> &points);
    ReferenceTable* getNewTable(){return p_newTable;}
    ReferenceTable* getOldTable(){return p_oldTable;}
};

}
#endif // REFERENCETABLE_H
