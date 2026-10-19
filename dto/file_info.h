#pragma once

enum class Checksum_algorithm {MD5 = 1, SHA1 = 2, SHA256 = 3};

struct File_info {
    const std::string &path;
    Checksum_algorithm algorithm;
    const std::string &reference_hash;
    long user_id = 0;
};
