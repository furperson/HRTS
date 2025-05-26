#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "Task.hpp"
#include "BitArtif.hpp"
#include "ScenSer.hpp"


// Класс, занимающийся сохранением данных 
//программы и восстановлением состояния системы по запросу
class Server;

class PersistenceManager {
  private:
    /* data */
  public:
    void Offload(Server&,const std::string&);
    void Load(Server&,const std::string&);

    PersistenceManager() = default;
    ~PersistenceManager() = default;
};