#include "event_bus.h"

void Event_bus::subscribe(const Event &event, Handler handler) {
    if (!event_handlers_.contains(event)) {
        this->event_handlers_[event] = std::list<handler>();
    }
    this->event_handlers_[event].push_back(handler);
}

void Event_bus::publish(const Event &event) {
    if (event_handlers_.contains(event)) {
        for (const Handler &handler: event_handlers_[event]) {
            handler(event);
        }
    }
}
