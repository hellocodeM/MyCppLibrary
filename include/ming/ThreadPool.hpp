#ifndef MING_THREAD_POOL_HPP
#define MING_THREAD_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

namespace ming {

class ThreadPool {
public:
    ThreadPool() : ThreadPool(std::thread::hardware_concurrency()) {}

    ThreadPool(int size) {
        for (int i = 0; i < size; i++) {
            ts_.emplace_back([&] {
                while (true) {
                    std::unique_lock<std::mutex> guard(lock_);
                    cond_.wait(guard, [&] { return !running_ || !tasks_.empty(); });
                    if (!running_) break;
                    auto task = tasks_.front();
                    tasks_.pop();
                    guard.unlock();
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        running_ = false;
        cond_.notify_all();
        for (auto& t : ts_) t.join();
    }

    void Submit(std::function<void(void)> task) {
        std::unique_lock<std::mutex> guard(lock_);
        tasks_.push(task);
        cond_.notify_one();
    }

    void Wait() {
        using namespace std::chrono_literals;
        std::unique_lock<std::mutex> guard(lock_);
        cond_.notify_all();
        while (!tasks_.empty()) {
            cond_.wait_for(guard, 10ms, [&] { return tasks_.empty(); });
        }
    }

private:
    std::vector<std::thread> ts_;
    std::queue<std::function<void(void)>> tasks_;
    std::condition_variable cond_;
    std::mutex lock_;
    volatile bool running_ = true;
};
}
#endif
