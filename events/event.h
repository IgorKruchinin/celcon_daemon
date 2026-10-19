#pragma once
#include <string>
#include <chrono>

#include "../dto/file_info.h"

class Event {
    std::string type_;
    std::chrono::sys_seconds timestamp_;
public:
    Event(const std::string &type);
    const std::string &get_type();
    const std::chrono::sys_seconds &get_timestamp();
};

class Check_file_event : public Event {
    File_info file_info_;
public:
    Check_file_event(const File_info &file);
    const File_info &get_file_info();
};
