#include "KeyGen.h"
#include "core/center/Config.h"

namespace core{
KeyGen::KeyGen()
{
    p_table = 0;
    periodLen = 0;
}

void KeyGen::init()
{
    Config* p_config = Config::getObject();
    periodLen = p_config->maxUpdateTime;
    p_table = ReferenceTable::getObject();
}

KeyType KeyGen::getKey(CoorType coorX, CoorType coorY, TimeType tup)
{
    KeyType timeKey;
    KeyType spaceKey;
    if(tup%(2*periodLen) < periodLen)        //属于[(2i)T,(2i+1)T)
        timeKey = 0;
    else                                     //属于[(2i+1)T,(2i+2)T)
        timeKey = 1;

    Grid* p_grid = p_table->getReferencePoint(coorX,coorY)->getGrid();
    spaceKey = p_grid->getSpaceKey(coorX,coorY);

    return timeKey * (p_table->getReferencePointNum() * Grid::maxCellNum) + spaceKey;

}
}
