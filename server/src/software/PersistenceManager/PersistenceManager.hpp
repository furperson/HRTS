#pragma once

#include "BitArtif.hpp"
#include "ScenSer.hpp"
#include "Task.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

// Класс, занимающийся сохранением данных
// программы и восстановлением состояния системы по запросу
class Server;

class PersistenceManager {
  private:
    /* data */
    Server* server;

  public:
    void Offload(const std::string&); // выгружает весь сервер

    void OffloadScen(const std::string&);
    void OffloadTask(const std::string&);

    void Load(const std::string&); // загружает весь сервер

    void loadScen(const std::string&);
    void loadTask(const std::string&);

    PersistenceManager(Server&);
    ~PersistenceManager() = default;
};