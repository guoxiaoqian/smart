#include "Grid.h"

namespace smart {


int Grid::maxCellNum = 1024;


Grid::Grid()
{
}

Grid::Grid(IDType _gridID, Rect &rect, int row, int col):Rect(rect)
{
    gridID = _gridID;
    resizeCell(row,col);
}

void Grid::init(IDType _gridID, Rect &rect, int row, int col)
{
    gridID = _gridID;
    setRange(rect);
    resizeCell(row,col);
}

void Grid::resizeCell(int row, int col)
{
    rowNum = row;
    colNum = col;
    //修改最多cell数
//    if(rowNum*colNum > maxCellNum)
//        maxCellNum = rowNum*colNum;

    cells.clear();
    vector<Cell> tmpCell(colNum);
    for(int i=0;i<rowNum;++i)
        cells.push_back(tmpCell);

    int cellWidth = (maxX-minX)/colNum;
    int cellHeight = (maxY - minY)/rowNum;
    int tmpWidth = 0;
    int tmpHeight = 0;
    vector<vector<Cell> >::iterator it_row;
    vector<Cell>::iterator it_col;
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

Cell* Grid::getCell(int row, int col)
{
    if(row>0 && row<rowNum && col>0 && col<colNum)
        return &cells[row][col];
    else
        return 0;
}

Cell* Grid::getCell(IDType cellID)
{
    //TODO:由希尔伯特编号得到Cell
    int row = cellID / colNum;
    int col = cellID % colNum;
    return getCell(row,col);
}

IDType Grid::getCellID(Point &point)
{
    //TODO:由位置得到希尔伯特编号
    int row = (point.coorY - minY)/((maxY-minY)/rowNum);
    int col = (point.coorY - minX)/((maxX-minX)/colNum);
    return row*colNum+col;
}

KeyType Grid::getSpaceKey(Point& point)
{
    return gridID * maxCellNum + getCellID(point);
}

}
