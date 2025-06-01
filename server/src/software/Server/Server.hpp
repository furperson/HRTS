#pragma once

#include "PreParser.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
// #include "SIGINThandle.cpp"
#include "Command/actualCMD/headers/AddTaskCMD.hpp"
#include "Command/actualCMD/headers/LoadDataFromFileCMD.hpp"
#include "Command/actualCMD/headers/OffloadDataToFileCMD.hpp"
#include "Command/actualCMD/headers/PrintScenarioCMD.hpp"
#include "Command/actualCMD/headers/ShowAllScenarioCMD.hpp"
#include "Command/actualCMD/headers/ShowAllTask.hpp"
#include "Command/actualCMD/headers/StartTaskCMD.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "Interpretator/Interpretator.hpp"
#include "PersistenceManager/PersistenceManager.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

class Server {
  private:
    friend PersistenceManager;
    friend int main(int argc, char* argv[]); // для тестов

    std::vector<Task> taskStore;
    std::vector<Scenario> scenarioStore;
    IOunit ioUnit;
    HwUnit hwUnit;
    PersistenceManager persistenceManager;
    Interpretator interpetator;
    bool serverRunning;

  public:
    // запуск сервера
    void startServer(int argc, char* argv[]);

    Server();
    ~Server() = default;
};