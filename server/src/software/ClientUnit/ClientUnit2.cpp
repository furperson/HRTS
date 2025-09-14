#include "ClientUnit/ClientUnit2.hpp"

ClientUnit2::ClientUnit2(InnerFunction& func) : func(func), _is_running(false) {
}

void ClientUnit2::stop_listening() {
    if (!_is_running.exchange(false))
        return;

    if (listen_sock != -1) {
        shutdown(listen_sock, SHUT_RDWR);
        close(listen_sock);
        listen_sock = -1;
    }
    if (_accept_thread.joinable()) {
        _accept_thread.join();
    }
    if (_worker_thread.joinable()) {
        _worker_thread.join();
    }
}

bool ClientUnit2::start_listening(int port) {
    epollFD = epoll_create1(0);
    if (_is_running) {
        return true;
    }

    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(listen_sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
        close(listen_sock);
        return false;
    }

    if (listen(listen_sock, 10) < 0) {
        close(listen_sock);
        return false;
    }

    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    _is_running = true;
    _accept_thread = std::thread(&ClientUnit2::_accept_loop, this);
    _worker_thread = std::thread(&ClientUnit2::_work_loop, this);

    return true;
}

void ClientUnit2::_accept_loop() {
    while (_is_running) {
        int client_socket = accept(listen_sock, nullptr, nullptr);
        if (client_socket < 0) {
            if (!_is_running)
                break;
            continue;
        }
        {
            std::lock_guard<std::mutex> guard(mapMut);
            socketsBase[client_socket] = SocketState::UNKNOWN;
        }
        set_nonblocking(client_socket);
        event.data.fd = client_socket;
        event.events = EPOLLIN | EPOLLET;

        if (epoll_ctl(epollFD, EPOLL_CTL_ADD, client_socket, &event) < 0) {
            close(client_socket);
            close(epollFD);
            std::cerr << errno;
        }
    }
}

void ClientUnit2::_work_loop() {

    std::vector<epoll_event> events(MAX_EVENTS);

    while (true) {
        int num_events = epoll_wait(epollFD, events.data(), MAX_EVENTS, -1);
        if (num_events < 0) {
            continue;
        }

        for (int i = 0; i < num_events; ++i) {

            int client_sock = events[i].data.fd;
            std::vector<char> buffer(READ_BUFFER_SIZE);

            while (true) {
                ssize_t bytes_read = read(client_sock, buffer.data(), READ_BUFFER_SIZE);
                if (bytes_read == 0) {
                    epoll_ctl(epollFD, EPOLL_CTL_DEL, client_sock, nullptr);
                    {
                        std::lock_guard<std::mutex> guard(mapMut);
                        socketsBase.erase(client_sock);
                    }
                    close(client_sock);
                    break;
                } else if (bytes_read < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // Все данные из буфера вычитаны
                        break;
                    }
                    epoll_ctl(epollFD, EPOLL_CTL_DEL, client_sock, nullptr);

                    close(client_sock);
                    break;
                } else {

                    buffer.erase(buffer.begin(), buffer.begin() + 4);
                    ;
                    json inJ = json::parse(buffer);
                    Message msg = inJ;
                    if (socketsBase[client_sock] == SocketState::UNKNOWN) {
                        if (msg.cmds == Commands::LOGGING) {
                            std::string usr = msg.data["user"];
                            std::string passwd = msg.data["passwd"];
                            if (func.dbverifyUser(usr, passwd)) {
                                Resp rsp(256, json::object());
                                send_json(client_sock, rsp);
                                std::lock_guard<std::mutex> guard(mapMut);
                                socketsBase[client_sock] = SocketState::LOGGED;
                                
                            } else {
                                Resp rsp(0, json::object());
                                send_json(client_sock, rsp);
                            }
                        } else {
                            // клиент не выполнил протокол
                            epoll_ctl(epollFD, EPOLL_CTL_DEL, client_sock, nullptr);
                            {
                                std::lock_guard<std::mutex> guard(mapMut);
                                socketsBase.erase(client_sock);
                            }
                            close(client_sock);
                            break;
                        }
                    } else {
                        Resp rspN(0, json::object());
                        switch (msg.cmds) {
                        case Commands::GET_TASK:
                            rspN.code =1;
                                 send_json(client_sock, rspN);
                            break;
                        case Commands::GET_SCENARIO:
                            break;
                        case Commands::RUN_TASK:
                            break;
                        case Commands::GET_TASK_LIST:
                            break;
                        case Commands::GET_SCENARIO_LIST:
                            break;
                        default:
                            break;
                        }
                    }

                    std::cout << inJ << std::endl;
                }
            }
        }
    }
};

void set_nonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
    }
}

ClientUnit2::~ClientUnit2() {
    stop_listening();
}