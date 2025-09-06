#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <vector>

class dbLoadTaskCMD : public CommandCli {
  private:
    InnerFunction& func;
    /* data */
    IOunit& iounit;

    std::vector<Scenario>& scenarioStore;
    std::vector<Task>& taskStore;

  public:
    void Execute(ParsedCMD&) override;
    dbLoadTaskCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                  std::vector<Task>& taskStore, IOunit& iounit);
    ~dbLoadTaskCMD() override;
};
