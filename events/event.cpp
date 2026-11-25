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

Check_file_event::Check_file_event(const File_info &file)
    : Event("file.checking.add"), file_info_(file) {}

const File_info &Check_file_event::get_file_info() {
    return file_info_;
}

Watching_file_event::Watching_file_event(const std::string &path)
: Event("file.watching.tocheck"), file_path_(path) {}

const std::string &Watching_file_event::get_file_path() {
    return file_path_;
}
