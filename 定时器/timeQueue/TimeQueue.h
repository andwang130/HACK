//
// Created by wj on 18-10-12.
//

#ifndef MYSQLTEST_TIMEQUEUE_H
#define MYSQLTEST_TIMEQUEUE_H


#include "Timer.h"
#include <sys/epoll.h>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>
//定时任务队列
typedef std::shared_ptr<Timer> timerPrt;
typedef std::map<int,timerPrt> timermMap;
class TimeQueue {
public:
    static TimeQueue * getTimeQueue();
    ~TimeQueue();
    void addTimer(const timerPrt &timer);
    void deleteTimer(const timerPrt &timer);
private:
    void epoll_while();
    std::mutex mutex_;
    TimeQueue();
    static TimeQueue * timeQueue_;
    int epollFd;
    timermMap timermMap_;
    std::vector<struct epoll_event> epoolEvents;
    std::thread t;
};


#endif //MYSQLTEST_TIMEQUEUE_H
