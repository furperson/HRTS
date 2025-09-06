#include "InnerFunction/InnerFunction.hpp"

#include "Server/Server.hpp"

InnerFunction::InnerFunction(Server& server, std::vector<Task>& taskStore,
                             std::vector<Scenario>& scenarioStore, IOunit& ioUnit, HwUnit& hwUnit,
                             PersistenceManager& persistenceManager, Interpretator& interpetator,
                             DataBaseUnit& dataBaseUnit)
    : server(server), taskStore(taskStore), scenarioStore(scenarioStore), ioUnit(ioUnit),
      hwUnit(hwUnit), persistenceManager(persistenceManager), interpetator(interpetator),
      addTask(taskMutex, scenMutex, taskStore, scenarioStore),
      addScenario(scenMutex, scenarioStore), doScript(ioUnit),
      showScenario(scenMutex, scenarioStore), showTask(taskMutex, taskStore),
      exitServ(persistenceManager), execTask(taskMutex, hwUnit, taskStore),
      loadServData(persistenceManager), offloadServData(persistenceManager),
      dataBaseUnit(dataBaseUnit), dbloadTask(dataBaseUnit), dboffloadTask(dataBaseUnit),
      dbloadScenario(dataBaseUnit), dboffloadScenario(dataBaseUnit), dbverifyUser(dataBaseUnit),
      getTask(taskMutex, scenMutex, taskStore, scenarioStore),
      getScen(taskMutex, scenMutex, taskStore, scenarioStore) {};

InnerFunction::~InnerFunction() {};
