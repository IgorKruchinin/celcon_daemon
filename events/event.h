#pragma once
#include <string>
#include <chrono>

class Event {
    std::string type_;
    std::any data_;
    std::chrono::sys_seconds timestamp_;
public:
    Event(const std::string &type, const std::any &data);
    const std::string &get_type();
    const std::any &get_data();
    const std::chrono::sys_seconds &get_timestamp();
};
