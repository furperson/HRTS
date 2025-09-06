#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "InterpretatorCli/Interpretator.hpp"
#include "IOunit/IOunit.hpp"
#include "RemoteServiceUnit/RemoteServiceUnit.hpp"
#include "Scenario.hpp"
#include "Task.hpp"
#include "Protocol.hpp"
#include <algorithm>



class Client {
  private:
  std::string username;
  IOunit iOunit; 
  Interpretator interpretator;
  RemoteServiceUnit remoteService;
  std::vector<Task> taskStore;
  std::vector<Scenario> scenarioStore;


    
  public:

    void init(const int& port,std::string server_ip);

    void run();
    void initCli();
    Client(std::string username);
    ~Client();
};
