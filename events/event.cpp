#include "event.h"

Event::Event(const std::string &type, const std::any &data) {
    this->type_ = type;
    this->data_ = data;
    this->timestamp_ = std::chrono::system_clock::now();
}

const std::string &Event::get_type() {
    return type_;
}
const std::any &Event::get_data() {
    return data_;
}
const std::chrono::sys_seconds &Event::get_timestamp() {
    return timestamp_;
}
