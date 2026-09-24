#include "user.h"

User(const std::string &name, const std::string &surname, const std::string &patronymic, const std::string &post, const Role &role) {
    if (!check_string(name) || !check_string(surname) || !check_string(patronymic) || !check_string(post)) {

    }
    name_ = name;
    surname_ = surname;
    patronymic_ = patronymic;
    post_ = post;
    role_ = role;
}

const std::string &User::get_name() {
    return name_;
}
const std::string &User::get_surname() {
    return surame_;
}
const std::string &User::get_patronymic() {
    return patronymic_;
}
const std::string &User::get_post() {
    return post_;
}
const std::string &User::get_role() {
    return role_;
}

bool User::check_string(const std::string &str) {

}
