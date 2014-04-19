#include "Cell.h"

namespace smart {

Cell::Cell()
{    
}

Cell::Cell(IDType _cellID, Rect &rect):\
    Rect(rect),cellID(_cellID)
{
}

void Cell::init(IDType _cellID, Rect &rect)
{
    cellID = _cellID;
    setRange(rect);
}

}
