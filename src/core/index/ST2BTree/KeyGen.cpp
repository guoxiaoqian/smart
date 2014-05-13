#include "KeyGen.h"
#include "core/center/Config.h"

namespace smart{

KeyGen::KeyGen()
{
    p_tables = NULL;
    periodLen = 0;
}

void KeyGen::init()
{
    Config* p_config = Config::getObject();
    periodLen = p_config->maxUpdateTime;
    p_tables = ReferenceTables::getObject();
}

KeyType KeyGen::getKey(UpdateRequest* p_update)
{
    KeyType timeKey;
    KeyType spaceKey;
    ReferenceTable* p_table = p_tables->getNewTable();
    if(p_update->issueTime%(2*periodLen) < periodLen)        //属于[(2i)T,(2i+1)T)
        timeKey = 0;
    else                                                     //属于[(2i+1)T,(2i+2)T)
        timeKey = 1;

    Point point(p_update->posX,p_update->posY);
    Grid<ObjectCell>* p_grid = p_table->getReferencePoint(point)->getGrid();
    spaceKey = p_grid->getSpaceKey(point);

    return timeKey * (p_table->getReferencePointNum() * Grid<ObjectCell>::maxCellNum) + spaceKey;

}

}
