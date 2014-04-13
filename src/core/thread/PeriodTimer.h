#ifndef PERIODTIMER_H
#define PERIODTIMER_H

#include "base/thread/timer.h"
namespace core{
class PeriodTimer : public base::STimer
{
public:
    PeriodTimer();
};
}
#endif // PERIODTIMER_H
