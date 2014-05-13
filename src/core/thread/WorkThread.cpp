#include "WorkThread.h"

namespace smart {


PeriodType WorkThread::period = 0;
Index* WorkThread::p_index = NULL;
Config* WorkThread::p_config = NULL;

WorkThread::WorkThread()
{
    numOfDiscard = 0;
    numOfSuccess = 0;
}

void WorkThread::getStatus(int &discard, int &success)
{
    discard = numOfDiscard;
    success = numOfSuccess;
    numOfDiscard = 0;
    numOfSuccess = 0;
}

void WorkThread::increasePeriod()
{
    ++period;
}

void WorkThread::init(Index *_p_index)
{
    p_index = _p_index;
    p_config = Config::getObject();
}

}
