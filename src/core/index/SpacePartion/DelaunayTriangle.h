#ifndef DELAUNAYTRIANGLE_H
#define DELAUNAYTRIANGLE_H

//职责：根据离散点集合生成一个三角网

#include "core/store/ReferencePoint.h"
#include <vector>
#include <map>
using std::vector;

namespace smart {

class Triangle;
class Vertex:public ReferencePoint
{
public:
    vector<Triangle> triangles;     //该顶点相关的三角形
    Vertex(ReferencePoint& point):ReferencePoint(point){}
    void addTriangle(Triangle& t);
};

class Triangle
{
public:
    IDType triangleID;
    vector<Vertex> vertexs;
    vector<Triangle> adjacentTriangles;
    //求三角形的外接圆心
    Point getCircleCenter();
};

class DelaunayTriangle
{
public:
    DelaunayTriangle();
    void genTriangleNet(vector<Vertex>& vertexs);
};

}

#endif // DELAUNAYTRIANGLE_H
