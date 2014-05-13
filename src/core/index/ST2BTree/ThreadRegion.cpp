#include "ThreadRegion.h"

namespace smart {

ThreadRegion::ThreadRegion()
{
}


void ThreadRegion::addCell(HistoCell *p_cell)
{
    total+=p_cell->getObjectNum();
    p_cell->setThreadID(threadID);
}

}
