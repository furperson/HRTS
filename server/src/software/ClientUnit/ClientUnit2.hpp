#pragma once

#include <nlohmann/json.hpp>
#include "InnerFunction/InnerFunction.hpp"
#include "Protocol.hpp" 


#include <vector>
#include <iostream>
#include <functional>
#include <functional>
#include <thread>
#include <atomic>
#include <memory>
#include <cstring>
#include <unordered_map>

#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAX_EVENTS 128
#define READ_BUFFER_SIZE 1024

using json = nlohmann::json;

enum class SocketState {
    UNKNOWN,
    LOGGED
};

void set_nonblocking(int sockfd) ;


class ClientUnit2
{
private:
    ::std::unordered_map<int,SocketState> socketsBase;
    int epollFD;
    int listen_sock;
    std::atomic<bool> _is_running;
    InnerFunction& func;

    // accept connection and put in epoll and map
    std::thread _accept_thread;
    //accept and response clients
    std::thread _worker_thread;

    epoll_event event;

    void _work_loop();

    void _accept_loop();

    void _client_handler();

    std::mutex mapMut;


public:

    bool start_listening(int port);


    void stop_listening();

    
    ClientUnit2(InnerFunction& func);
    ~ClientUnit2();
};

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

// // Получает JSON-объект из сокета
// inline bool receive_json(int sock, json& j) {
//     if (sock < 0) return false;
//     uint32_t len;
//     if (read(sock, &len, sizeof(len)) != sizeof(len)) return false;
//     len = ntohl(len);


//     std::vector<char> buffer(len);
//     if (read(sock, buffer.data(), len) != len) return false;
    
//     try {
//         j = json::parse(buffer);
//         return true;
//     } catch (const json::parse_error& e) {
//         std::cerr << "JSON parse error: " << e.what() << std::endl;
//         return false;
//     }
// }