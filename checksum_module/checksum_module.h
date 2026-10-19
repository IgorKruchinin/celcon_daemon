#pragma once

#include <string>
#include <openssl/evp.h>

#include "../core/queued_worker.h"
#include "../dto/task.h"
#include "../dto/file_info.h"

class Checksum_module : Event_bus_worker {
private:

    std::string hash_file_evp(const std::string& path, const EVP_MD* md) {
        std::ifstream file(path, std::ios::binary);
        if (!file) return "";

        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(ctx, md, nullptr);

        char buffer[4096];
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
            EVP_DigestUpdate(ctx, buffer, file.gcount());
        }

        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int len = 0;
        EVP_DigestFinal_ex(ctx, hash, &len);
        EVP_MD_CTX_free(ctx);

        std::stringstream ss;
        for (unsigned i = 0; i < len; ++i)
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        return ss.str();
    }

    void process_task(const Task &task) override {
        if (task.type == "check.file" && auto &check_task = dynamic_cast<const Check_file_task>(&task)) {
            std::string real_hash;
            if (check_task.file_info.algorithm == Checksum_algorithm::SHA256) {
                real_hash = hash_file_evp(check_task->file_info.path, EVP_sha256());
            } else if (check_task->file_info.algorithm == Checksum_algorithm::SHA1) {
                real_hash = hash_file_evp(check_task->file_info.path, EVP_sha1());
            } else if (check_task->file_info.algorithm == Checksum_algorithm::MD5) {
                real_hash = hash_file_evp(check_task->file_info.path, EVP_md5());
            }
            if (real_hash == check_task->file_info.reference_hash) {
                checksum_matching(check_task->file_info);
            } else {
                checksum_unmatching(check_task->file_info);
            }
        } else {
            logger_.send_log("Checksum_module: incorret task got for processing: " + task.type, Log_level::Warning);
        }
    }
    void checksum_matching(const File_info &file) {
        Event_bus_worker::publish_event(Event("file.checksum.matching"));
    }
    void checksum_unmatching(const File_info &file) {
        Event_bus_worker::publish_event(Event("file.checksum.unmatching"));
    }
    void add_checking_file(const File_info &file) {
        Check_file_task check_task;
        check_task.type = "file.check";
        check_task.file_info = file;
        Queued_worker::add_task(check_task);
    }
    void handle_add_file_event(const Event &event) {
        if (event.get_type() == "file.checking.add" && auto &check_event = dynamic_cast<const Check_file_event>(&event)) {
            Check_file_task check_task;
            check_task.type = "check.file";
            check_task.file_info = check_event->get_file_info();
            Event_bus_worker::publish_event(Event("file.checking.pending"));
        } else {
            logger_.send_log("Checksum_module: incorrect event attempted for handle: " + event.type, Log_level::Warning);
        }
    }
    void handle_check_file_first(const Event &event) {
        if (event.get_type() == "file.checking.add" && auto &check_event = dynamic_cast<const Check_file_event>(&event)) {
            Check_file_task check_task;
            check_task.type = "check.file";
            check_task.file_info = check_event->get_file_info(); // ЗАПИСАТЬ В БАЗУ ДАННЫХ ЭТАЛОННЫЙ ХЭШ!!!!!!!!!!
            Event_bus_worker::publish_event(Event("file.checking.pending"));
        } else {
            logger_.send_log("Checksum_module: incorrect event attempted for handle: " + event.type, Log_level::Warning);
        }
    }
public:
    Checksum_module(const std::string &worker_id, int pool_size, Config &config, Logger &logger, Event_bus event_bus)
    : Event_bus_worker(worker_id, pool_size, config, logger, event_bus) {
        init_events();
    }
    void init_events() {
        Event_bus_worker::subscribe_to_event("file.checking.add", [this](const Event &event) {
            handle_add_file_event(const Event &event);
        });
    }
};
