#include <iostream>
#include "TimeQueue.h"
#include <random>
#include "Timer.h"
#include <string.h>
using namespace std;
void func(int i)
{
    cout<<i<<endl;
    std::cout<<"定时任务"<<std::endl;
}
int main() {
    //初始化驱动

    TimeQueue *timeQueue = TimeQueue::getTimeQueue();

    itimerspec itimerspec_;
    memset(&itimerspec_,0, sizeof(itimerspec_));
    itimerspec_.it_interval.tv_sec=10;
    itimerspec_.it_interval.tv_nsec=1;
    itimerspec_.it_value.tv_sec=5;
    itimerspec_.it_value.tv_nsec=10;

    std::default_random_engine e;
    std::uniform_int_distribution<int> u(10, 20); //随机数分布对象
    itimerspec_.it_value.tv_sec=u(e);

    for (int i=0;i<10;i++)
    {

        itimerspec_.it_value.tv_sec=u(e);
        Timer timer_(std::bind(func,itimerspec_.it_value.tv_sec), itimerspec_,10);
        timeQueue->addTimer(std::make_shared<Timer>(timer_));
    }
    cin.get();

    return 0;
}