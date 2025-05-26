#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "PreParser.hpp"
// #include "SIGINThandle.cpp"
#include "Interpretator/Interpretator.hpp"
#include "Scenario.hpp"
#include "Task.hpp"
#include "IOunit/IOunit.hpp"
#include "HwUnit/HwUnit.hpp"
#include "PersistenceManager/PersistenceManager.hpp"

#include "Command/actualCMD/AddTaskCMD.hpp"
#include "Command/actualCMD/LoadDataFromFileCMD.hpp"
#include "Command/actualCMD/OffloadDataToFileCMD.hpp"
#include "Command/actualCMD/PrintScenarioCMD.hpp"
#include "Command/actualCMD/ShowAllScenarioCMD.hpp"
#include "Command/actualCMD/ShowAllTask.hpp"
#include "Command/actualCMD/StartTaskCMD.hpp"


class Server 
{
    private:
    friend PersistenceManager;
    friend int main (int argc, char* argv[]); // для тестов

    std::vector<Task> taskStore;
    std::vector<Scenario> scenarioStore;
    HwUnit hwUnit;
    IOunit ioUnit;
    Interpretator interpetator;
    PersistenceManager persistenceManager;
    bool serverRunning;

    public:
    //запуск сервера
    void startServer(int argc, char* argv[]);

    Server()=default;
    ~Server()=default;

    
};