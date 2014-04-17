#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

//职责：根据三角形网生成泰森多边形
#include <vector>
using std::vector;

namespace smart {

class ReferencePoint;

class VoronoiDiagram
{
public:
    VoronoiDiagram();
    //生成泰森多边形
    static void genDiagram(vector<ReferencePoint> &points);
};

}
#endif // VORONOIDIAGRAM_H
