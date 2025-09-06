
#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cerrno>


using json = nlohmann::json;

class RemoteServiceUnit {
public:

    RemoteServiceUnit();


    ~RemoteServiceUnit();

    bool connect(const std::string& host, int port, int timeout_sec = 5);


    void disconnect();

    bool is_connected() const;

    bool send_request(const json& request, json& response);

private:
    int _socket;
    bool _is_connected;

    bool send_json(const json& j);
    bool receive_json(json& j);
};