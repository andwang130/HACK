//
// Created by meidai on 18-8-8.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H
#include <vector>               // std::vector
#include <queue>                // std::queue
#include <memory>               // std::make_shared
#include <stdexcept>            // std::runtime_error
#include <thread>               // std::thread
#include <mutex>                // std::mutex,        std::unique_lock
#include <condition_variable>   // std::condition_variable
#include <future>               // std::future,       std::packaged_task
#include <functional>           // std::function,     std::bind
#include <utility>              // std::move,         std::forward

class ThreadPool
{
public:
    //num 创建线程的个数
    ThreadPool(unsigned int threads);
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // 需要持续追踪线程来保证可以使用 join
    std::vector< std::thread > workers;
    // 任务队列
    std::queue< std::function<void()> > tasks;

    // 同步相关
    std::mutex queue_mutex;             // 互斥锁
    std::condition_variable condition;  // 互斥条件变量

    // 停止相关
    bool stop;
};


#endif //THREADPOOL_THREADPOOL_H
