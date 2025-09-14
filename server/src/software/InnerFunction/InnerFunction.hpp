#pragma once

#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/Func/Functions.hpp"
#include "InterpretatorCli/Interpretator.hpp"
#include "PersistenceManager/PersistenceManager.hpp"
#include "Scenario.hpp"
#include "Task.hpp"
#include "DataBaseUnit/DataBaseUnit.hpp"

#include <functional>

class Server;
// Задача класса - предоставлять интерфейс бизнес логики для всех остальных компонентов

class InnerFunction {
  private:
    std::mutex taskMutex;
    std::mutex scenMutex;
    Server& server;
    std::vector<Task>& taskStore;
    std::vector<Scenario>& scenarioStore;
    IOunit& ioUnit;
    HwUnit& hwUnit;
    PersistenceManager& persistenceManager;
    Interpretator& interpetator;
    DataBaseUnit& dataBaseUnit;

  public:
    inner_::AddTask addTask;
    inner_::AddScenario addScenario;
    inner_::DoScript doScript;
    inner_::ShowScenario showScenario;
    inner_::ShowTask showTask;
    inner_::ExitServ exitServ;
    inner_::ExecTask execTask;
    inner_::LoadServData loadServData;
    inner_::OffloadServData offloadServData;
    inner_::GetTask getTask;
    inner_::GetScen getScen;

    inner_::DBloadTask dbloadTask;
    inner_::DBoffloadTask dboffloadTask;
    inner_::DBloadScenario dbloadScenario;
    inner_::DBoffloadScenario dboffloadScenario;
    inner_::DBverifyUser dbverifyUser;

    InnerFunction() = delete;
    InnerFunction(Server&, std::vector<Task>&, std::vector<Scenario>&, IOunit&, HwUnit&,
                  PersistenceManager&, Interpretator&, DataBaseUnit&);
    ~InnerFunction();
};
