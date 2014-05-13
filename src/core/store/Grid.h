#ifndef GRID_H
#define GRID_H

#include "core/store/Rect.h"
#include "core/store/Cell.h"
#include "base/3dparty/hilbert/include/hilbert.h"
#include <math.h>
#include <vector>
using std::vector;

namespace smart{

template<class CellType>
class Grid:public Rect
{
public:
    static int maxCellNum;
    IDType gridID;
    int rowNum;
    int colNum;
    vector<vector<CellType> > cells;
    typedef typename vector<vector<CellType> >::iterator RowIterator;
    typedef typename vector<CellType>::iterator ColIterator;
    typedef vector<vector<CellType> >  CellSetType;
public:
    Grid(){}
    Grid(IDType _gridID,Rect& rect,int row = 10,int col = 10);
    void init(IDType _gridID,Rect& rect,int row = 10,int col = 10);
    void resizeCell(int row,int col);
    CellType* getCell(int row,int col);
    CellType* getCell(IDType cellID);
    CellType* getCell(Point& point);
    vector<CellType*> getNeighborCells(IDType cellID);
    IDType getCellID(Point& point);
    KeyType getSpaceKey(Point &point);
    RowIterator getRowBegin(){return cells.begin();}
    RowIterator getRowEnd(){return cells.end();}
    int getRowNum(){return rowNum;}
    int getColNum(){return colNum;}
    CellSetType& getAllCell(){return cells;}
    bool same(Grid<CellType> &grid);
    void clear();
};

template<class CellType>
int Grid<CellType>::maxCellNum = 1024;

template<class CellType>
Grid<CellType>::Grid(IDType _gridID, Rect &rect, int row, int col):Rect(rect),gridID(_gridID)
{
    resizeCell(row,col);
}

template<class CellType>
void Grid<CellType>::init(IDType _gridID, Rect &rect, int row, int col)
{
    gridID = _gridID;
    setRange(rect);
    resizeCell(row,col);
}

template<class CellType>
void Grid<CellType>::resizeCell(int row, int col)
{
    rowNum = row;
    colNum = col;

    cells.clear();
    vector<CellType> tmpCell(colNum);
    for(int i=0;i<rowNum;++i)
        cells.push_back(tmpCell);

    int cellWidth = getWidth()/colNum;
    int cellHeight = getHeight()/rowNum;
    int tmpWidth = 0;
    int tmpHeight = 0;

    typename vector<vector<CellType> >::iterator it_row;
    typename vector<CellType>::iterator it_col;
    int i,j;
    for(i=0,it_row = cells.begin();it_row!= cells.end();++it_row,++i)
    {
        for(j=0,it_col = it_row->begin();it_col!= it_row->end();++it_col,++j)
        {
            Rect rect(tmpWidth,tmpWidth+cellWidth,tmpHeight,tmpHeight+cellHeight);
            it_col->init(i*colNum+j,rect);
            tmpWidth+=cellWidth;
        }
        tmpWidth = 0;
        tmpHeight += cellHeight;
    }
}

template<class CellType>
CellType* Grid<CellType>::getCell(int row, int col)
{
    if(row>0 && row<rowNum && col>0 && col<colNum)
        return &cells[row][col];
    else
        return 0;
}

template<class CellType>
CellType* Grid<CellType>::getCell(IDType cellID)
{
    //TODO:由希尔伯特编号得到Cell，暂时如下

    int row = cellID / colNum;
    int col = cellID % colNum;
    return getCell(row,col);
}
template<class CellType>
CellType *Grid<CellType>::getCell(Point &point)
{
    int row = (point.coorY - minY)/((maxY-minY)/rowNum);
    int col = (point.coorY - minX)/((maxX-minX)/colNum);
    return &cells[row][col];
}

template<class CellType>
vector<CellType *> Grid<CellType>::getNeighborCells(IDType cellID)
{
    vector<CellType*> result;
    int row = cellID / colNum;
    int col = cellID % colNum;
    CellType* p_cell = 0;
    if(col-1>0)
    {
        p_cell = getCell(row,col-1);
        result.push_back(p_cell);
    }
    if(row-1>0)
    {
        p_cell = getCell(row-1,col);
        result.push_back(p_cell);
    }
    if(col+1< colNum)
    {
        p_cell = getCell(row,col+1);
        result.push_back(p_cell);
    }
    if(row+1< rowNum)
    {
        p_cell = getCell(row+1,col);
        result.push_back(p_cell);
    }
    return result;
}

template<class CellType>
IDType Grid<CellType>::getCellID(Point &point)
{
    //TODO:由位置得到希尔伯特编号,暂时如下

    int row = (point.coorY - minY)/((maxY-minY)/rowNum);
    int col = (point.coorY - minX)/((maxX-minX)/colNum);
    return row*colNum+col;
}

template<class CellType>
KeyType Grid<CellType>::getSpaceKey(Point& point)
{
    return gridID * maxCellNum + getCellID(point);
}

template<class CellType>
bool Grid<CellType>::same(Grid<CellType>& grid)
{
    return rowNum == grid.getRowNum() && colNum == grid.getColNum() &&\
            Rect::same(grid);
}

template<class CellType>
void Grid<CellType>::clear()
{
    typename vector<vector<CellType> >::iterator it_row;
    typename vector<CellType>::iterator it_col;
    for(it_row = cells.begin();it_row!= cells.end();++it_row)
    {
        for(it_col = it_row->begin();it_col!= it_row->end();++it_col)
        {
            it_col->clear();
        }
    }
}

}//namespace core

#endif // GRID_H
