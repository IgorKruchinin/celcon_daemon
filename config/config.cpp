#include "config.h"


Config::Config(const std::string &config_path)
    :config_path_(config_path) {}

void Config::read_config() {
    std::ifstream config_file(config_path_);
    std::string config_str;
    while (getline(file, config_str)) {

    }
}
