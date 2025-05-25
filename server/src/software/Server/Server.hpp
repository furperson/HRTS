#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "PreParser.hpp"
#include "SIGINThandle.cpp"
#include "Interpretator/Interpretator.hpp"
#include "Scenario.hpp"
#include "Task.hpp"
#include "IOunit/IOunit.hpp"
#include "HwUnit/HwUnit.hpp"

class Server 
{
    private:
    std::vector<Task> taskStore;
    std::vector<Scenario> scenarioStore;
    HwUnit hwUnit;
    IOunit ioUnit;
    Interpretator interpetator;

    public:
    //запуск сервера
    void startServer();
    
};