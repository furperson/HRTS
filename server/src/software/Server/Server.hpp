#pragma once

#include "PreParser.hpp"

#include <atomic>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
// #include "SIGINThandle.cpp"
#include "ClientUnit/ClientUnit2.hpp"
#include "CommandCli/actualCMD/headers/AddTaskCMD.hpp"
#include "CommandCli/actualCMD/headers/AllHelpCMD.hpp"
#include "CommandCli/actualCMD/headers/ExitCMD.hpp"
#include "CommandCli/actualCMD/headers/LoadDataFromFileCMD.hpp"
#include "CommandCli/actualCMD/headers/OffloadDataToFileCMD.hpp"
#include "CommandCli/actualCMD/headers/PrintScenarioCMD.hpp"
#include "CommandCli/actualCMD/headers/ScenarioMakeCMD.hpp"
#include "CommandCli/actualCMD/headers/ShowAllScenarioCMD.hpp"
#include "CommandCli/actualCMD/headers/ShowAllTask.hpp"
#include "CommandCli/actualCMD/headers/StartTaskCMD.hpp"
#include "CommandCli/actualCMD/headers/dbLoadScenarioCMD.hpp"
#include "CommandCli/actualCMD/headers/dbLoadTaskCMD.hpp"
#include "CommandCli/actualCMD/headers/dbOffloadScenarioCMD.hpp"
#include "CommandCli/actualCMD/headers/dbOffloadTaskCMD.hpp"
#include "CommandCli/actualCMD/headers/doScript.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "InterpretatorCli/Interpretator.hpp"
#include "PersistenceManager/PersistenceManager.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

class Server {
  private:
    friend PersistenceManager;

    enum class ServerStatus { SERVER_RUNNING, SERVER_READY, SERVER_STOP };

    std::vector<Task> taskStore;
    std::vector<Scenario> scenarioStore;
    IOunit ioUnit;
    HwUnit hwUnit;
    PersistenceManager persistenceManager;
    Interpretator interpetator;
    ClientUnit2 clientU;
    DataBaseUnit dataBaseUnit;

    InnerFunction func;

    std::atomic<ServerStatus> serverStatus;

    AddTaskCMD addTaskCMD;
    LoadDataFromFileCMD loadDataFromFileCMD;
    OffloadDataToFileCMD offloadDataToFileCMD;
    PrintScenarioCMD printScenarioCMD;
    ShowAllScenarioCMD showAllScenarioCMD;
    ShowAllTask showAllTask;
    StartTaskCMD startTaskCMD;
    AllHelpCMD allHelpCMD;
    ExitCMD exitCMD;
    ScenarioMakeCMD scenarioMakeCMD;
    doScript doscript;

    dbLoadTaskCMD dbloadTaskCMD;
    dbOffloadTaskCMD dboffloadTaskCMD;
    dbLoadScenarioCMD dbloadScenarioCMD;
    dbOffloadScenarioCMD dboffloadScenarioCMD;

    void initCli();
    void initClientHandlers(int port);
    void initDataBaseConnect(); // не факт что нужен

  public:
    // запуск сервера
    void init(int port);
    void startServer(int argc, char* argv[]);

    Server() = delete;
    Server(int argc, char* argv[]);
    ~Server() = default;
};