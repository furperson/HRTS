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
  public:
    void Offload(Server&, const std::string&);
    void Load(Server&, const std::string&);

    PersistenceManager() = default;
    ~PersistenceManager() = default;
};