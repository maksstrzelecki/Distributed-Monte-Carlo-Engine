#include "JobQueue.hpp"

void JobQueue::add_task(std::shared_ptr<Task> t) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(t);
    }
    cv.notify_one();
}

std::shared_ptr<Task> JobQueue::pop_task() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&](){
        return !q.empty();
    });
    std::shared_ptr<Task> t = q.front();
    q.pop();
    return t;
}
