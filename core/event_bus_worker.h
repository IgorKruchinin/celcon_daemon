#pragma once
#include "queued_worker.h"
#include "../event_bus/event_bus.h"

class Event_bus_worker : public Queued_worker {
private:
    Event_bus &event_bus_;
protected:
    void subscribe_to_event(const std::string &event_type, Handler handler) {
        event_bus_.subscribe(event_type, handler);
    }
    void publish_event(const Event &event) {
        event_bus_.publish(const Event &event);
    }
public:
    Event_bus_worker(const std::string &worker_id, int pool_size, Config &config, Logger &logger, Event_bus event_bus)
    : Queued_worker(const std::string &worker_id, int pool_size, Config &config, Logger &logger), event_bus_(event_bus) {}
};
