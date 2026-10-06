#pragma once
#include <string>
#include "../logger/logger.h"

class Base_worker {
    std::string worker_id_;
    std::atomic<bool> is_running_ = false;
    std::thread worker_thread_;
    Logger &logger_
public:
    Base_worker(const std::string &id, Logger &logger)
    : worker_id_(std::move(id)), logger_(logger) {}
    void start() {
        if (is_running_) return;
        is_running_ = true;
        logger_.send_log(worker_id_ + " started", Log_level::Info);
    }
    virtual ~Base_worker() {
        stop();
    }
};
