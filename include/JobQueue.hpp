#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Task.hpp"

class JobQueue {
private:
    std::queue<Task> q;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void add_task(Task& t);
    Task pop_task();
};