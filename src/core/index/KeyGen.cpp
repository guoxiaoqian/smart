#include "KeyGen.h"
#include "core/center/Config.h"

namespace smart{

KeyGen::KeyGen()
{
    p_table = 0;
    periodLen = 0;
}

void KeyGen::init(ReferenceTable* _p_table)
{
    p_table = _p_table;
    Config* p_config = Config::getObject();
    periodLen = p_config->maxUpdateTime;
}

KeyType KeyGen::getKey(Point point, TimeType tup)
{
    KeyType timeKey;
    KeyType spaceKey;
    if(tup%(2*periodLen) < periodLen)        //属于[(2i)T,(2i+1)T)
        timeKey = 0;
    else                                     //属于[(2i+1)T,(2i+2)T)
        timeKey = 1;

    Grid* p_grid = p_table->getReferencePoint(point)->getGrid();
    spaceKey = p_grid->getSpaceKey(point);

    return timeKey * (p_table->getReferencePointNum() * Grid::maxCellNum) + spaceKey;

}

void KeyGen::setReferenceTable(ReferenceTable *_p_table)
{
    p_table = _p_table;
}
}
