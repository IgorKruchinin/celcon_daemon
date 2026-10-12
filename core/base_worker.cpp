#include "base_worker.h"
#include <string>
#include <mutex>

Base_worker::Base_worker(const std::string &id, Config &config, Logger &logger)
: worker_id_(std::move(id)), config_(config), logger_(logger) {}

const std::string &get_id() const {
    return worker_id_;
}

const Worker_state &Base_worker::get_state() const {
    return state_.load();
}

void Base_worker::start() {
    Worker_state expected = Worker_state::STOPPED;
    if (state_.compare_exchange_strong(expected, Worker_state::RUNNING)) {
        logger_.send_log(worker_id_ + " started", Log_level::Info);
        on_start();
    }
}

void Base_worker::pause() {
    Worker_state expected = Worker_state::RUNNING;
    if (state_.compare_exchange_strong(expected, Worker_state::PAUSED)) {
        logger_.send_log(worker_id_ + " paused", Log_level::Info);
        on_pause();
    }
}

void Base_worker::resume() {
    Worker_state expected = Worker_state::PAUSED;
    if (state_.compare_exchange_strong(expected, Worker_state::RUNNING)) {
        logger_.send_log(worker_id_ + " resumed", Log_level::Info);
        on_resume();
    }
}

void Base_worker::stop() {
    Worker_state current = state_.load();
    if (current == Worker_state::STOPPED || current == Worker_state::STOPPING) {
        return;
    }
    state_.store(Worker_state::STOPPING);
    logger_.send_log(worker_id_ + " stopping...", Log_level::Info);
    pause_cv_.notify_all();
    on_stop();
    state_.store(Worker_state::STOPPED);
    logger_.send_log(worker_id_ + " stopped", Log_level::Info);

}

bool Base_worker::is_running() const {
    return state_.load() == Worker_state::RUNNING;
}

bool Base_worker::wait_if_paused() {
    std::unique_lock<std::mutex> lock(pause_mutex_);
    pause_cv_.wait(lock, [this] {
        Worker_state s = state_.load();
        return s != Worker_state::PAUSED;
    });
    Worker_state s = state_.load();
    return (s == Worker_state::RUNNING);
}

virtual ~Base_worker::Base_worker() {
    stop();
}
