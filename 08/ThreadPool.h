#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <future>

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

class ThreadPool
{
public:
    explicit ThreadPool(size_t pool_size);
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
    friend void thread_func(ThreadPool& pool);
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()> > tasks;
    std::mutex condition_mutex;
    std::condition_variable condition;
    bool terminate = false;
};

void thread_func(ThreadPool& pool){
    while(1){
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(pool.condition_mutex);
            pool.condition.wait(lock, [&pool]{return pool.terminate || !pool.tasks.empty(); });
            if(pool.terminate && pool.tasks.empty()){
                return;
            }
            task = std::move(pool.tasks.front());
            pool.tasks.pop();
        }
        task();
    }
}

ThreadPool::ThreadPool(size_t pool_size){
    for(size_t i = 0; i < pool_size; ++i){
        workers.emplace_back([this]{thread_func(*this); });
    }
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(condition_mutex);
        terminate = true;
    }
    condition.notify_all();
    for(std::thread& worker : workers){
        worker.join();
    }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    using r_type = typename std::invoke_result<Func, Args...>::type;
    auto task = std::make_shared<std::packaged_task<r_type()> >(std::bind(func, args...));
    std::future<r_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(condition_mutex);
        tasks.emplace([task]{(*task)(); });
    }
    condition.notify_one();
    return res;
}

#endif //THREAD_POOL_H
