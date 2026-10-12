#pragma once

#include "../core/queued_worker.h"

class Checksum_module : Queued_worker {
public:
    Checksum_module(std::string id, int pool_size = 4, Config &config, Logger &logger)
    : Queued_worker(std::move(id, pool_size, config, logger)) {}
protected:
    void process_task(const Task &task) {
        if (task.type == "check.file") {

        }
    }
    void handle_add_file_event(const Event &event) {

    }
    const Event &emiss_pending_event() {

    }
};
