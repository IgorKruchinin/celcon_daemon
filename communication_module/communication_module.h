#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../core/event_bus_worker.h"

class Communication_module : public Event_bus_worker {
private:
    int port_;
    std::string cert_file_;
    std::string key_file_;
    int server_fd_;
    SSL_CTX* ctx_;

    std::atomic<bool> running_;
    std::thread acceptor_thread_;

    std::map<int, std::shared_ptr<ClientConnection>> clients_;
    std::mutex clients_mutex_;
    void init_ssl() {
        OPENSSL_init_ssl(0, nullptr);

        const SSL_METHOD* method = TLS_server_method();
        ctx_ = SSL_CTX_new(method);

        SSL_CTX_use_certificate_file(ctx_, cert_file_.c_str(), SSL_FILETYPE_PEM);
        SSL_CTX_use_PrivateKey_file(ctx_, key_file_.c_str(), SSL_FILETYPE_PEM);
        SSL_CTX_check_private_key(ctx_);
    }

    void init_server_socket() {
        server_fd_ = socket(AF_INET, SOCK_STREAM, 0);

        int opt = 1;
        setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port_);

        bind(server_fd_, (struct sockaddr*)&addr, sizeof(addr));
        listen(server_fd_, 128);
    }
public:
    void process_task(const Task &task) override {

    }
};
