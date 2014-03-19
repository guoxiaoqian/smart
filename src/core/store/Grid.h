#ifndef GRID_H
#define GRID_H

#include "core/store/Rect.h"
#include "core/store/Cell.h"
#include <vector>

class Grid:public Rect
{
public:
    int rowNum;
    int colNum;
    vector<vector<Cell> > cells;
public:
    Grid();
    Grid(CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY,int row = 10,int col = 10);
    void initGrid(CoorType _minX,CoorType _minY,CoorType _maxX,CoorType _maxY,int row = 10,int col = 10);
    void resizeCell(int row,int col);
    Cell* getCell(int row,int col);
    Cell* getCell(int cellID);
};

#endif // GRID_H
