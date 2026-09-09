#pragma once
#include <map>
#include <list>
#include <functional>

#include "event.h"

using Handler = std::function<void(Event)>;

class Event_bus {
    std::map<Event, std::list<Handler>> event_handlers_;
public:
    void subscribe(const Event &event, Handler handler);
    void publish(const Event &event);
};
