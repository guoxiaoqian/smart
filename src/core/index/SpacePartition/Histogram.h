#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//职责：求新的参考点集合的位置和密度

#include "base/kernel/singleton.hpp"
#include "core/store/Grid.h"
#include <vector>
using std::vector;

namespace smart{

class HistoCell;
class DenstyRegion;
class ReferencePoint;
class UpdateRequest;
class Histogram:public SSingleton<Histogram>
{
public:
    static int colNum;
    static int rowNum;
    static int noiseParam;
    static int similarParam;
    Grid<HistoCell>* p_gram;
private:
    vector<DenstyRegion> getRegions(vector<ReferencePoint>& oldPoints);
    void growRegion(HistoCell* p_cell, DenstyRegion& region);
    void discardNoises(vector<DenstyRegion>& regions);
public:
    Histogram();
    ~Histogram();
    void init();
    vector<ReferencePoint> getReferencePoints(vector<ReferencePoint>& oldPoints);
    void update(UpdateRequest* p_update);
};

}

#endif // HISTOGRAM_H
