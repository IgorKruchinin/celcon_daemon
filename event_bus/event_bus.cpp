#include "event_bus.h"


// Модуль может быть подписан на события разных типов, но также и события разных типов может быть обработано одним handler
void Event_bus::subscribe(const std::string &event_type, Handler handler) {
    if (!event_handlers_.contains(event_type)) {
        this->event_handlers_[event_type] = std::vector<handler>();
    }
    this->event_handlers_[event_type].push_back(handler);
}

void Event_bus::publish(const Event &event) {
    std::string event_type = event.get_type();
    if (event_handlers_.contains(event_type)) {
        for (const Handler &handler: event_handlers_[event_type]) {
            handler(event);
        }
    }
}
