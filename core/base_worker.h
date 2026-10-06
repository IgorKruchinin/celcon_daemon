#pragma once
#include <string>
#include <mutex>
#include "../logger/logger.h"

enum class Worker_state {
    STOPPED,
    RUNNING,
    PAUSED,
    STOPPING
};

class Base_worker {
protected:
    std::string worker_id_;
    std::atomic<Worker_state> state_ = Worker_state::STOPPED;
    std::mutex pause_mutex_;
    std::condition_variable pause_cv_;
    Logger &logger_;
    virtual void on_start() {};
    virtual void on_pause() {};
    virtual void on_resume() {};
    virtual void on_stop() {};
public:
    Base_worker(const std::string &id, Logger &logger);
    const std::string &get_id() const;
    const Worker_state &get_state() const;
    void start();
    void pause();
    void resume();
    void stop();
    bool is_running() const;
    virtual ~Base_worker();
};
