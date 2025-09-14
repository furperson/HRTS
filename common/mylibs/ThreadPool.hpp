#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args){

        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
    
            std::unique_lock<std::mutex> lock(queue_mutex);
    
    
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            
    
            tasks.emplace([task]() { task(); });
        } 
        
    
        condition.notify_one();
    }

private:

    std::vector<std::thread> workers;

    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};


