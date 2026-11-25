#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../core/event_bus_worker.h"

class Communication_module : public Event_bus_worker {
public:
    void
    void process_task(const Task &task) override {

    }
};
