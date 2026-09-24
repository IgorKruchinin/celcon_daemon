#pragma once

enum class Role {Viewer = 0, Editor = 1, Admin = 2};

class User {
    std::string name_;
    std::string surname_;
    std::string patronymic_;
    std::string post_;
    Role role_;
protected:
    static inline bool check_string(const std::string &str);
public:
    User(const std::string &name, const std::string &surname, const std::string &patronymic, const std::string &post, const Role &role);
    const std::string &get_name();
    const std::string &get_surname();
    const std::string &get_patronymic();
    const std::string &get_post();
    const Role &get_role();
};
