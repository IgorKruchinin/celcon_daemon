#pragma once

#include "user.h"

#include <string>

class Authenticated_user : public User {
private:
    std::string session_id_;
public:
    Authenticated_user(const std::string &name, const std::string &surname, const std::string &patronymic, const std::string &post, const Role &role, const std::string &session_id);
    const std::string get_session_id();
};
