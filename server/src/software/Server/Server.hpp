#pragma once

#include "PreParser.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
// #include "SIGINThandle.cpp"
#include "Command/actualCMD/AddTaskCMD.hpp"
#include "Command/actualCMD/LoadDataFromFileCMD.hpp"
#include "Command/actualCMD/OffloadDataToFileCMD.hpp"
#include "Command/actualCMD/PrintScenarioCMD.hpp"
#include "Command/actualCMD/ShowAllScenarioCMD.hpp"
#include "Command/actualCMD/ShowAllTask.hpp"
#include "Command/actualCMD/StartTaskCMD.hpp"
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
    HwUnit hwUnit;
    IOunit ioUnit;
    Interpretator interpetator;
    PersistenceManager persistenceManager;
    bool serverRunning;

  public:
    // запуск сервера
    void startServer(int argc, char* argv[]);

    Server() = default;
    ~Server() = default;
};