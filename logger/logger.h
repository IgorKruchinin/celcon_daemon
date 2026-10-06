#pragma once
#include <string>

enum class Log_level {Debug = 1, Info = 2, Warning = 3, Error = 4};

#define LOG_DEBUG_PREFIX "[DEBUG]: "
#define LOG_INFO_PREFIX "[INFO]: "
#define LOG_WARNING_PREFIX "[WARNING]: "
#define LOG_ERROR_PREFIX "[ERROR]: "


class Logger {
    const std::string &make_log_msg(const std::string &msg, const Log_level &level);
public:
    void send_log(const std::string &msg, const Log_level &level);
};
