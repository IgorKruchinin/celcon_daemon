#pragma once
#include <unordered_map>
#include <string>

class Config {
    std::unordered_map config_parsed_;
    std::string config_path_;
public:
    Config(const std::string &config_path);
    void read_config();
    void create_default_config();
    std::string get_string();
    int get_value();
};
