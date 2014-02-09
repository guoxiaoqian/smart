#include "OnlineTuning.h"
#include "core/center/Config.h"

OnlineTuning::OnlineTuning()
{
    timer = NULL;
}

OnlineTuning::~OnlineTuning()
{
    timer->stop();
    delete timer;
}

void OnlineTuning::init()
{
    Config* p_config = Config::getConfig();
    timer = new STimer(this,&OnlineTuning::onTimer,static_cast<unsigned long>(p_config->maxUpdateTime),TIMER_REPEAT);
}

void OnlineTuning::start()
{
    timer->start();
}

void OnlineTuning::onTimer()
{
    //self-tune
}
