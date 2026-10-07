#pragma once
#include "exception.h"

class Config_read_exception: public Exception {
public:
    Config_read_exception(const std::string &message)
    :Exception{message} {}
    const std::string &get_message() const override {
        return "Config read exception: " + Exception::get_message();
    }
};

class Config_create_exception: public Exception {
public:
    Config_create_exception(const std::string &message)
    :Exception{message} {}
    const std::string &get_message() const override {
        return "Create config exception: " + Exception::get_message();
    }
};
