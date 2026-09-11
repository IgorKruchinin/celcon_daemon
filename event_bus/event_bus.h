#pragma once
#include <map>
#include <vector>
#include <functional>

#include "../events/event.h"

using Handler = std::function<void(Event)>;

class Event_bus {
    std::map<std::string, std::vector<Handler>> event_handlers_;
public:
    void subscribe(const std::string &event_type, Handler handler);
    void publish(const Event &event);
};
