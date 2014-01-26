#include <iostream>
#include <typeinfo>

using namespace std;

#include "base/thread/thread.h"
#include "base/logger/logger.h"
#include "base/setting/setting.h"
#include "base/kernel/sig_slot.hpp"
#include "base/thread/thread_timer.h"

class A
{
public:
    void fuck(){cout<<"fuck"<<endl;}
};


int main()
{
    A a;
    SThreadTimer timer(&a,&A::fuck,1000);
    timer.start();
    STime::ssleep(20);
    timer.stop();
    return 0;
}

