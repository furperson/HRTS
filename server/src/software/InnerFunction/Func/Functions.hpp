#pragma once

class Task;
class Scenario;
class HwUnit;
class IOunit;
class DataBaseUnit;
class PersistenceManager;
enum class TaskState;

#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <optional>
#include <sodium.h>

// Функции и Классы,  реализующие внутреннюю логику

namespace inner_ {

class AddTask {
    std::mutex& TaskMut;
    std::mutex& ScenMut;
    std::vector<Task>& taskStore;
    std::vector<Scenario>& scenarioStore;

  public:
    AddTask(std::mutex&, std::mutex&, std::vector<Task>&, std::vector<Scenario>&);
    int operator()(const Task);
    int operator()(const std::string& scenario_name, const std::string& task_name ,     const std::string& Owner_name_);
    int operator()(const std::string& scenario_name , const std::string& Owner_name_);
};


class GetTask {
  std::mutex& TaskMut;
  std::mutex& ScenMut;
  std::vector<Task>& taskStore;
  std::vector<Scenario>& scenarioStore;

public:
  GetTask(std::mutex&, std::mutex&, std::vector<Task>&, std::vector<Scenario>&);
  std::optional<Task> operator()( const std::string& task_name ,     const std::string& Owner_name_);

};

class GetScen {
  std::mutex& TaskMut;
  std::mutex& ScenMut;
  std::vector<Task>& taskStore;
  std::vector<Scenario>& scenarioStore;

public:
  GetScen(std::mutex&, std::mutex&, std::vector<Task>&, std::vector<Scenario>&);
  std::optional<Scenario> operator()( const std::string& scenario_name , const std::string& Owner_name_);

};

class AddScenario {
    std::mutex& ScenMut;
    std::vector<Scenario>& scenarioStore;

  public:
    AddScenario(std::mutex&, std::vector<Scenario>& );
    int operator()(const Scenario& );
};

class DoScript {
    std::mutex mut;
    IOunit& iounit;

  public:
    DoScript(IOunit&);
    int operator()(const std::string&);
};

class ShowScenario {

    std::mutex& ScenMut;
    std::vector<Scenario>& scenarioStore;

  public:
    ShowScenario(std::mutex&, std::vector<Scenario>&);
    std::string operator()( const std::string& Owner_name_);
    std::string operator()(const std::string& , const std::string& Owner_name_);
};

class ShowTask {
    std::mutex& TaskMut;

    std::vector<Task>& taskStore;
    std::map<TaskState, std::string> stateToString;

  public:
    ShowTask(std::mutex&, std::vector<Task>&);
    std::string operator()( const std::string& Owner_name_);
    std::string operator()(const std::string& , const std::string& Owner_name_);
};

class ExitServ {
    PersistenceManager& persistenceManager;

  public:
    ExitServ(PersistenceManager&);

    int operator()(const int&);
};

class ExecTask {
    std::mutex& TaskMut;
    HwUnit& hwunit;
    std::vector<Task>& taskStore;

  public:
    ExecTask(std::mutex&, HwUnit&, std::vector<Task>&);
    int operator()(const std::string& , const std::string& Owner_name_);
};

class LoadServData {
    PersistenceManager& persistenceManager;

  public:
    LoadServData(PersistenceManager&);

    int operator()(const std::string&);
};

class OffloadServData {
    PersistenceManager& persistenceManager;

  public:
    OffloadServData(PersistenceManager&);

    int operator()(const std::string&);
};

class DBloadTask{
  DataBaseUnit& dbunit;
  public:
  DBloadTask(DataBaseUnit&);
  std::optional<Task> operator()(std::string user,std::string Taskname);
};

class DBoffloadTask{
  DataBaseUnit& dbunit;
  public:
  DBoffloadTask(DataBaseUnit&);
  bool operator()(std::string user, Task& task);
};

class DBloadScenario{
  DataBaseUnit& dbunit;
  public:
  DBloadScenario(DataBaseUnit&);
  std::optional<Scenario> operator()(std::string user, std::string Scenarioname);
};

class DBoffloadScenario{
  DataBaseUnit& dbunit;
  public:
  DBoffloadScenario(DataBaseUnit&);

  bool operator()(std::string user, Scenario& scen);
};

class DBverifyUser{
  DataBaseUnit& dbunit;
  public:
  DBverifyUser(DataBaseUnit&);
  bool operator()(std::string user,std::string pswd);
};
} // namespace inner_