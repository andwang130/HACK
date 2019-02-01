//
// Created by wj on 18-10-12.
//

#include "Timer.h"
#include <unistd.h>
Timer::Timer(const TimerCallback &cb, itimerspec itimerspec__,int NumofTimes__):
timerCallback_(cb),
itimerspec_(itimerspec__)
{
    timeFd=timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    itimerspec oldTimerSpec;
    int ret=timerfd_settime(timeFd,0,&itimerspec_,0);
    if(ret==-1)
    {
     std::cout<<ret<<std::endl;
    }
    if(itimerspec_.it_interval.tv_sec==0&&itimerspec_.it_interval.tv_nsec==0)
    {
        NumofTimes=1;
    }
    else
    {
        NumofTimes=NumofTimes__;
    }
    index_=0;

}
void Timer::stop()
{
    itimerspec TimerSpec={0};
    int ret=timerfd_settime(timeFd,0,&TimerSpec,0);
    ::close(timeFd);
}
void Timer::start()
{
    index_++;
    timerCallback_();
}
int Timer::get_fd()
{
    return timeFd;
}