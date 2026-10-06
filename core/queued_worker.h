#pragma once
#include "task_queue.h"

class Queued_worker : public Base_worker {
protected:
    size_t pool_size_;
    Task_queue task_queue_;
    std::vector<std::thread> worker_threads_;
public:
};
