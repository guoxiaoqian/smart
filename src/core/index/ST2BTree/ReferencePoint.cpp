#include "ReferencePoint.h"
#include "core/center/Config.h"
#include <algorithm>

namespace smart {

ReferencePoint::ReferencePoint()
{
    referencePointID = -1;
    densty = -1;
    p_grid = 0;
}

ReferencePoint::~ReferencePoint()
{
    //delete p_grid;
}

ReferencePoint::ReferencePoint(IDType id, Point &point):Point(point),referencePointID(id)
{
}

void ReferencePoint::init(IDType id, Point &point)
{
    referencePointID = id;
    setPoint(point);
}

bool SortByCoorX(Point p1,Point p2)
{
    return p1.coorX < p2.coorX;
}
bool SortByCoorY(Point p1,Point p2)
{
    return p1.coorY < p2.coorY;
}

bool ReferencePoint::initGrid()
{
    unsigned int vertexNum = voronoiCell.size();
    if(vertexNum == 0)
        return false;
    //计算泰森多边形外接矩形
    sort(voronoiCell.begin(),voronoiCell.end(),SortByCoorX);
    CoorType minX = voronoiCell[0].coorX;
    CoorType maxX = voronoiCell[vertexNum-1].coorX;
    sort(voronoiCell.begin(),voronoiCell.end(),SortByCoorY);
    CoorType minY = voronoiCell[0].coorY;
    CoorType maxY = voronoiCell[vertexNum-1].coorY;

    Rect rect(minX,minY,maxX,maxY);
    //由密度（每平方单位对象数）决定格网粒度
    if(densty > 0)
    {
        CoorType cellWidth = static_cast<CoorType>(sqrt(ObjectCell::maxObjectNum/densty));
        int col = rect.getWidth() / cellWidth;
        int row = rect.getHeight() / cellWidth;
        p_grid = new Grid<ObjectCell>(referencePointID,rect,row,col);
    }
    else
    {
        p_grid = new Grid<ObjectCell>(referencePointID,rect);
    }
    return true;
}

}
