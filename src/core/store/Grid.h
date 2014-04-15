#ifndef GRID_H
#define GRID_H

#include "core/store/Rect.h"
#include "core/store/Cell.h"
#include "base/3dparty/hilbert/include/hilbert.h"
#include <vector>
namespace smart{
class Grid:public Rect
{
public:
    static int maxCellNum;
    IDType gridID;
    int rowNum;
    int colNum;
    vector<vector<Cell> > cells;
public:
    Grid();
    Grid(IDType _gridID,Rect& rect,int row = 10,int col = 10);
    void init(IDType _gridID,Rect& rect,int row = 10,int col = 10);
    void resizeCell(int row,int col);
    Cell* getCell(int row,int col);
    Cell* getCell(IDType cellID);
    IDType getCellID(Point& point);
    KeyType getSpaceKey(Point &point);
};
}
#endif // GRID_H
