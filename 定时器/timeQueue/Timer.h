//
// Created by wj on 18-10-12.
//

#ifndef MYSQLTEST_TIMER_H
#define MYSQLTEST_TIMER_H

#include <iostream>
#include <functional>
#include <sys/timerfd.h>
typedef  std::function<void()> TimerCallback;
class Timer
{
public:
    Timer(const TimerCallback &cb, itimerspec itimerspec__,int NumofTimes__);
    void stop();
    void start();
    int get_fd();
    struct itimerspec itimerspec_;
    int NumofTimes;
    int index_;
private:

        int timeFd;
        TimerCallback timerCallback_;
};


#endif //MYSQLTEST_TIMER_H
