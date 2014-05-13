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
class ThreadRegion;
class ReferencePoint;
class UpdateRequest;
class Histogram:public SSingleton<Histogram>,public Grid<HistoCell>
{
public:
    static int noiseParam;
    static int similarParam;
private:
    vector<DenstyRegion> getDenstyRegions(vector<ReferencePoint>& oldPoints);
    void growDenstyRegion(HistoCell* p_cell, DenstyRegion& region);
    void growThreadRegion(HistoCell* p_cell, ThreadRegion& region);
    void discardNoises(vector<DenstyRegion>& regions);
public:
    Histogram();
    ~Histogram();
    void init();
    //由旧的参考点集合生成新的参考点集合
    vector<ReferencePoint> getReferencePoints(vector<ReferencePoint>& oldPoints);
    //重新划分线程映射区域
    void resetThreadRegion();
    //更新时修改统计内容
    void update(UpdateRequest* p_update);
    //根据点位置获取映射线程的ID
    IDType getThreadID(Point& point);
    //将两个Histogram相加
    Histogram& operator+=(Histogram& gram);
};

}

#endif // HISTOGRAM_H
