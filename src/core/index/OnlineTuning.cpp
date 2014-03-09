#include "OnlineTuning.h"
#include "core/center/Config.h"

OnlineTuning* OnlineTuning::p_onlineTuning = NULL;

OnlineTuning::OnlineTuning()
{
    p_onlineTuning = this;
}

OnlineTuning::~OnlineTuning()
{
}

void OnlineTuning::init()
{
    Config* p_config = Config::getConfig();
}

void OnlineTuning::tune()
{
    //周期性调整
}

OnlineTuning *OnlineTuning::getOnlineTuning()
{
    return p_onlineTuning;
}
