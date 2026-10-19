#pragma once

#include "../dto/file_info.h"

struct Task {
    const std::string &type;
};

struct Check_file_task : public Task {
    const File_info &file_info;
};
