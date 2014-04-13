#include "WorkThread.h"

namespace core {


PeriodType WorkThread::period = 0;

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

}
