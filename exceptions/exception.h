#pragma once
#include <string>

class Exception {
    std::string message_;
public:
    Exception(const std::string &message)
    :message_(message) {}
    virtual const std::string &get_message() const {
        return message_;
    }
};
