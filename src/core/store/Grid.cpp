#include "Grid.h"


Grid::Grid()
{
}

Grid::Grid(CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY,int row,int col):Rect(_minX,_minY,_maxX,_maxY)
{

    resizeCell(row,col);
}

void Grid::initGrid(CoorType _minX, CoorType _minY, CoorType _maxX, CoorType _maxY, int row, int col)
{
    setRange(_minX,_minY,_maxX,_maxY);
    resizeCell(row,col);
}

void Grid::resizeCell(int row, int col)
{
    rowNum = row;
    colNum = col;
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
    for(it_row = cells.begin();it_row!= cells.end();++it_row)
    {
        for(it_col = it_row->begin();it_col!= it_row->end();++it_col)
        {
            it_col->setRange(tmpWidth,tmpWidth+cellWidth,tmpHeight,tmpHeight+cellHeight);
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

Cell* Grid::getCell(int cellID)
{
    int row = cellID / colNum;
    int col = cellID % colNum;
    return getCell(row,col);
}
