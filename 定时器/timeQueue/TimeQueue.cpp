//
// Created by wj on 18-10-12.
//

#include "TimeQueue.h"
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
TimeQueue * TimeQueue::timeQueue_= nullptr;
TimeQueue::TimeQueue()
{


    epollFd=epoll_create1(0);
    t=std::thread(std::bind(&TimeQueue::epoll_while,this));
}
TimeQueue::~TimeQueue()
{

    t.join();
}
void TimeQueue::addTimer(const timerPrt &timer)
{

    {
        std::lock_guard<std::mutex> lk(mutex_);
        timermMap_[timer->get_fd()]=timer;
    }
    struct epoll_event event;
    event.events=EPOLLIN|EPOLLET;
    event.data.fd=timer->get_fd();
    //event.data.ptr=&*timer;
    int res = epoll_ctl(epollFd, EPOLL_CTL_ADD, timer->get_fd(), &event);
    if(res==-1)
    {

        std::cout<<res<<std::endl;
    }




}

void TimeQueue::deleteTimer(const timerPrt &timer)
{
    {
        std::lock_guard<std::mutex> lk(mutex_);
        timermMap_.erase(timer->get_fd());
    }
    int res=epoll_ctl(epollFd,EPOLL_CTL_DEL,timer->get_fd(),0);
    timer->stop();
    if(res==-1)
    {

    }

}

void TimeQueue::epoll_while()
{
    epoolEvents.resize(16);
    while(true)
    {

        int res=epoll_wait(epollFd,&*epoolEvents.begin(), static_cast<int>(epoolEvents.size()),0);

        for(int i=0;i<res;i++)
        {
            char buf[24];
            memset(buf,0, sizeof(buf));
            timerPrt timer=timermMap_[epoolEvents[i].data.fd];
            ssize_t ret=::read(timer->get_fd(),&buf, sizeof(buf));
            if(ret==-1)
            {
                std::cout<<errno<<std::endl;
            }
            timer->start();
            if(timer->index_==timer->NumofTimes)
            {

                deleteTimer(timer);
            }
            //timerfd_settime(timer->get_fd(),0,&timer->itimerspec_,0);


        }
        if(res==epoolEvents.size())
        {
            epoolEvents.resize(epoolEvents.size()*2);
        }

    }
}
TimeQueue * TimeQueue::getTimeQueue()
{
    if(timeQueue_== nullptr)
    {
        timeQueue_=new TimeQueue();
        return timeQueue_;
    }
    else
    {
        return  timeQueue_;
    }
}

