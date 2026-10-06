#pragma once
#include <unordered_map>
#include <string>

class Config {
    std::unordered_map<std::string, std::string> config_parsed_;
    std::string config_path_ = "/etc/celcon.conf";
    static std::unordered_map<std::string, std::string> default_config_ = {
        {"checksum_threads", "4"},
        {"connection_port", "1234"}, // Уточнить порт демона
        {"debugging_events", "false"},
        {"log_sql_queries", "false"},
        {"dbms", "mysql"},
        {"syslog_logging", "true"},
        {"database_logging", "true"},
        {"file_logging", "true"},
        {"log_path", "/var/log/celcon.log"}
    };
public:
    Config(const std::string &config_path);
    void read_config();
    void create_default_config();
    std::string get_string(const std::string &field_name);
    int get_value(const std::string &field_name);
    bool get_bool(const std::string &field_name);
};
