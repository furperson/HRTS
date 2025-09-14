// ClientUnit.cpp
#include "ClientUnit/ClientUnit.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

ClientUnit::ClientUnit(size_t thread_pool_size,InnerFunction& func ) 
    : _listen_socket(-1), _is_running(false), func(func) {
    _thread_pool = std::make_unique<ThreadPool>(thread_pool_size);
}

ClientUnit::~ClientUnit() {
    stop_listening();
}


void ClientUnit::stop_listening() {
    if (!_is_running.exchange(false)) return;

    if (_listen_socket != -1) {
        shutdown(_listen_socket, SHUT_RDWR);
        close(_listen_socket);
        _listen_socket = -1;
    }
    if (_accept_thread.joinable()) {
        _accept_thread.join();
    }
}

bool ClientUnit::start_listening(int port) {
    if (_is_running) {
        std::cerr << "[ClientUnit] Already listening." << std::endl;
        return true;
    }

    _listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_listen_socket < 0) { return false; }
    
    int opt = 1;
    setsockopt(_listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(_listen_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        close(_listen_socket);
        return false;
    }
    
    if (listen(_listen_socket, 10) < 0) {
        close(_listen_socket);
        return false;
    }

    _is_running = true;
    _accept_thread = std::thread(&ClientUnit::_accept_loop, this);
    std::cout << "[ClientUnit] Started and listening on port " << port << std::endl;
    return true;
}

void ClientUnit::clientHandle(int client_socket){
    std::cout << "TEST :" << client_socket  << std::endl;
    json in;
    receive_json(client_socket,in);
    Message msg = in;
    Resp rsp;
    switch (msg.cmds)
    {
    case Commands::GET_SCENARIO_LIST: 
        rsp.code=200;
        rsp.data = func.showScenario() ;
        /* code */
        break;
    
    default:
        break;
    }

    send_json(client_socket,rsp);
    std::cout << "TEST :" << in  << std::endl;
        close(client_socket);
};

void ClientUnit::_accept_loop() {
    while (_is_running) {
        int client_socket = accept(_listen_socket, nullptr, nullptr);
        if (client_socket < 0) {
            if (!_is_running) break;
            continue;
        }

        std::cout << "[ClientUnit] Connection accepted on socket " << client_socket << std::endl;

        _thread_pool->enqueue([client_socket, this]() { this->clientHandle(client_socket); });
    }
}

