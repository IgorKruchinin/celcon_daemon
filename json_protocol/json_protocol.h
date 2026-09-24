#pragma once

#include "../dto/auth_user.h"

#include <string>

class JSON_protocol {
public:
    static inline const std::string &gen_auth_response_success(Authenticated_user user);
    static inline const std::string &gen_error_unauthorized();
    static inline const std::string &gen_error_forbidden();

};
