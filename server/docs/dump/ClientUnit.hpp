
#pragma once

#include <functional>
#include <thread>
#include <atomic>
#include <memory>
#include <nlohmann/json.hpp>

#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Protocol.hpp" 

#include "InnerFunction/InnerFunction.hpp"

#include "ThreadPool.hpp" 

using json = nlohmann::json;

inline bool send_json(int sock, const json& j) {
    if (sock < 0) return false;
    try {
        std::string json_str = j.dump();
        uint32_t len = htonl(json_str.length());
        if (send(sock, &len, sizeof(len), 0) == -1) return false;
        if (send(sock, json_str.c_str(), json_str.length(), 0) == -1) return false;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error during JSON serialization: " << e.what() << std::endl;
        return false;
    }
}

// Получает JSON-объект из сокета
inline bool receive_json(int sock, json& j) {
    if (sock < 0) return false;
    uint32_t len;
    if (read(sock, &len, sizeof(len)) != sizeof(len)) return false;
    len = ntohl(len);


    std::vector<char> buffer(len);
    if (read(sock, buffer.data(), len) != len) return false;
    
    try {
        j = json::parse(buffer);
        return true;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
}

class ClientUnit {
public:

    ClientUnit(size_t thread_pool_size , InnerFunction& func);

    ~ClientUnit();

    bool start_listening(int port);


    void stop_listening();

private:
    InnerFunction& func;

    void _accept_loop();
    
    int _listen_socket;
    std::atomic<bool> _is_running;

    std::thread _accept_thread;
    std::unique_ptr<ThreadPool> _thread_pool;

    void clientHandle(int client_socket);
};