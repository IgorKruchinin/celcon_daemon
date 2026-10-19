#pragma once
#include "task_queue.h"
#include "../config/"

class Queued_worker : public Base_worker {
protected:
    size_t pool_size_;
    Task_queue task_queue_;
    std::vector<std::thread> worker_threads_;
public:
    Queued_worker(const std::string &worker_id, int pool_size, Config &config, Logger &logger)
    : Base_worker(worker_id, config, logger), pool_size_(pool_size > 0 ? pool_size : 1) {}
    virtual ~Queued_worker() {
        stop();
    }
    void start() override {
        Base_worker::start();
        if (is_running()) {
            worker_threads_.reserve(pool_size_);
            for (size_t i = 0; i < pool_size_; ++i) {
                worker_threads_.emplace_back(&Queued_worker::worker_loop, this, i);
            }
            logger_.send_log("Worker " + worker_id_ + " started with " + pool_size_ + " threads", Log_level::Info);
        }
    }
    void pause() override {
        Base_worker::pause();
    }
    void resume() override {
        Base_worker::resume();
    }
    void stop() override {
        task_queue_.stop();
        Base_worker::stop();
        for (auto &t : worker_threads_) {
            if (t.joinable()) {
                t.join();
            }
        }
        worker_threads_.clear();
        logger_.send_log("Worker" + worker_id_ + "fully stopped", Log_level::Info);
    }
    size_t get_queue_size() {
        return task_queue_.size();
    }
    void add_task(const Task &task) {
        task_queue_.push(task);
    }
protected:
    virtual void process_task(const Task &task) = 0;
private:
    void worker_loop(size_t thread_index) {
        Task task;
        while (!should_stop()) {
            if (!wait_if_paused()) {
                break;
            }
            if (task_queue_.pop(task)) {
                try {
                    process_task(task);
                } catch (const std::exception &e) {
                    logger_.send_log("Worker " + worker_id_ + " thread " + thread_index + "crashed with exception: " + e.what(), Log_level::Error);
                } else {
                    logger_.send_log("Worker " + worker_id_ + " thread " + thread_index + "Task Queue is empty", Log_level::Info);
                    break;
                }
            }
        }
    }
};
