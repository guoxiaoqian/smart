#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

//职责：存储并管理参考点集

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
    void initGrids();
public:
    ReferenceTable();
    void init();
    void reset(vector<ReferencePoint>& points);
    //求最近参考点
    ReferencePoint* getReferencePoint(Point &point);
    vector<ReferencePoint>& getReferencePoints(){return referencePoints;}
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
    void init();
    void updateTable(vector<ReferencePoint> &points);
    ReferenceTable* getNewTable(){return p_newTable;}
    ReferenceTable* getOldTable(){return p_oldTable;}
};

}
#endif // REFERENCETABLE_H
