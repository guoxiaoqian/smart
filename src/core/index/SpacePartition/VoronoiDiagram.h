#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

//职责：根据三角形网生成泰森多边形

#include "core/index/SpacePartition/DelaunayTriangle.h"
#include "core/store/Rect.h"
#include <map>

namespace smart {

using std::vector;
using std::map;

class Polygon
{
public:
    Vertex center;
    vector<Point> border;
    //获取外接矩形
    Rect getOutRect();
};

class VoronoiDiagram
{
public:
    //顶点与多边形的映射，供查询
    map<IDType,Polygon> diagram;
public:
    VoronoiDiagram();
    //生成泰森多边形
    void genDiagram(vector<Vertex> vertexs);
};

}
#endif // VORONOIDIAGRAM_H
