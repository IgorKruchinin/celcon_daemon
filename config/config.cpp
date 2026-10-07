#include "config.h"
#include <iostream>
#include "../exceptions/config_exceptions.h"

Config::Config(const std::string &config_path)
    :config_path_(config_path) {}

void Config::read_config() {
    std::ifstream config_file(config_path_);
    std::string config_str;
    while (getline(file, config_str)) {

    }
}

void Config::create_default_config() {
    std::ofstream config_out;
    config_out.open(config_path_);
    if (!in.is_open()) {
        throw Config_create_exception("Failed to open config for create");
    }
    for (const auto &config_record: default_config_) {
        config_out << config_record.first << " " << config_record.second << "\n";
    }
    config_out.close();

}

std::string Config::get_string(const std::string &field_name) {
    return config_parsed_.get(field_name);
}
