#include "task_queue.h"

void Task_queue::push(Task &task) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stopped_) return;
        queue_push(std::move(task));
    }
    cv_notify_one();
}

bool Task_queue::pop(Task &task) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] {return !queue_.empty() || stopped_; });
    if (stopped_ && queue_.empty()) {
        return false;
    }
    task = std::move(queue_.front());
    queue_.pop();
    return true;
}
void Task_queue::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stopped_ = true;
    }
    cv_.notify_all();
}
size_t Task_queue::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}
bool Task_queue::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue.empty();
}
