#include <iostream>
using namespace std;

#include "base/thread/thread.h"
#include "base/logger/logger.h"
#include "base/setting/setting.h"
#include "base/thread/timer.h"

class A
{
public:
    void fuck(){cout<<"fuck"<<endl;}
};


int main()
{
    A a;
    STimer timer(&a,&A::fuck,1000);
    timer.start();
    STime::ssleep(20);
    timer.stop();
    return 0;
}

