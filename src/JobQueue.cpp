#include "JobQueue.hpp"

void JobQueue::add_task(Task& t) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(t);
    }
    cv.notify_one();
}

Task JobQueue::pop_task() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&](){
        return !q.empty();
    });
    Task t = q.front();
    q.pop();
    return t;
}
