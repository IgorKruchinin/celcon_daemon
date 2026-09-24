#include "auth_user.h"

Authenticated_user::Authenticated_user(const std::string &name, const std::string &surname, const std::string &patronymic, const std::string &post, const Role &role, const std::string &session_id)
: User(name, surname, patronymic, post, role) {
    if (!check_string(session_id)) {

    }
    session_id_ = session_id;
}
