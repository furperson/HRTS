
#include "RemoteServiceUnit.hpp"




RemoteServiceUnit::RemoteServiceUnit() : _socket(-1), _is_connected(false) {}

RemoteServiceUnit::~RemoteServiceUnit() {
    if (_is_connected) {
        disconnect();
    }
}

void RemoteServiceUnit::disconnect() {
    if (_socket != -1) {
        close(_socket);
        _socket = -1;
    }
    _is_connected = false;
    std::cout << "[Client] Отсоединение !" << std::endl;
}

bool RemoteServiceUnit::is_connected() const {
    return _is_connected;
}

bool RemoteServiceUnit::connect(const std::string& host, int port, int timeout_sec) {
    if (_is_connected) {
        std::cout << "[Client] Сервер уже подключение." << std::endl;
        return true;
    }

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        perror("[Client] Ошибка создания Сокета!");
        return false;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr << "[Client] Неправильный адрес !" << std::endl;
        close(_socket);
        _socket = -1;
        return false;
    }


    long arg = fcntl(_socket, F_GETFL, NULL);
    arg |= O_NONBLOCK;
    fcntl(_socket, F_SETFL, arg);

    int connect_res = ::connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    if (connect_res < 0) {
        if (errno == EINPROGRESS) {
            fd_set write_fds;
            struct timeval timeout;

            FD_ZERO(&write_fds);
            FD_SET(_socket, &write_fds);

            timeout.tv_sec = timeout_sec;
            timeout.tv_usec = 0;

            int sel_res = select(_socket + 1, NULL, &write_fds, NULL, &timeout);
            
            if (sel_res <= 0) {
                if (sel_res == 0) {
                    std::cerr << "[Client] Превышено время ожидания подключения" << std::endl;
                } else {
                    perror("[Client] select error");
                }
                close(_socket);
                _socket = -1;
                return false;
            }

            int so_error;
            socklen_t len = sizeof(so_error);
            getsockopt(_socket, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error != 0) {
                std::cerr << "[Client] Ошибка подключения!: " << strerror(so_error) << std::endl;
                close(_socket);
                _socket = -1;
                return false;
            }
        } else {
            perror("[Client] connect error");
            close(_socket);
            _socket = -1;
            return false;
        }
    }

    // Возвращаем сокет в блокирующий режим
    arg = fcntl(_socket, F_GETFL, NULL);
    arg &= (~O_NONBLOCK);
    fcntl(_socket, F_SETFL, arg);
    
    _is_connected = true;
    std::cout << "[Client] Удачное соединение с  " << host << ":" << port << std::endl;
    return true;
}

bool RemoteServiceUnit::send_request(const json& request, json& response) {
    if (!_is_connected) {
        std::cerr << "[Client] Ошибка ,не соединён с сервером" << std::endl;
        return false;
    }

    if (!send_json(request)) {
        std::cerr << "[Client] отправка не была успешна! отсоединяюсь" << std::endl;
        disconnect(); 
        return false;
    }
    
    if (!receive_json(response)) {
        std::cerr << "[Client] ответ не получен! отсоединяюсь " << std::endl;
        disconnect();
        return false;
    }
    
    return true;
}




bool RemoteServiceUnit::send_json(const json& j) {
    std::string json_str = j.dump();
    uint32_t len = htonl(json_str.length());
    if (send(_socket, &len, sizeof(len), 0) == -1) return false;
    if (send(_socket, json_str.c_str(), json_str.length(), 0) == -1) return false;
    return true;
}

bool RemoteServiceUnit::receive_json(json& j) {
    uint32_t len;
    // Проверяем, что read вернул ровно sizeof(len) байт
    if (read(_socket, &len, sizeof(len)) != sizeof(len)) return false;
    len = ntohl(len);

 

    std::vector<char> buffer(len);
    // Проверяем, что read вернул ровно len байт
    if (read(_socket, buffer.data(), len) != len) return false;
    

    try {
        j = json::parse(buffer);
    } catch (const json::parse_error& e) {
        std::cerr << "[Client] JSON parse error: " << e.what() << std::endl;
        return false;
    }
    return true;
}