#pragma once

struct Task {
    std::string type;
    std::any data;
}

class Task_queue {
    std::queue<Task> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stopped_ = false;
public:
    void push(Task &task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (stopped_) return;
            queue_push(std::move(task));
        }
        cv_notify_one();
    }

    bool pop(Task &task) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] {return !queue_.empty() || stopped_; });
        if (stopped_ && queue_.empty()) {
            return false;
        }
        task = std::move(queue_.front());
        queue_.pop();
        return true;
    }
    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stopped_ = true;
        }
        cv_.notify_all();
    }
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
};
