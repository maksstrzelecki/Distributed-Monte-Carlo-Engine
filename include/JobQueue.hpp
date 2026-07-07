#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

#include "Task.hpp"

class JobQueue {
private:
    std::queue<std::shared_ptr<Task>> q;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void add_task(std::shared_ptr<Task> t);
    std::shared_ptr<Task> pop_task();
};