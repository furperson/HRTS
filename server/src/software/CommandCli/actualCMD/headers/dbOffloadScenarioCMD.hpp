#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <vector>

class dbOffloadScenarioCMD : public CommandCli {
  private:
    InnerFunction& func;
    /* data */
    IOunit& iounit;

    std::vector<Scenario>& scenarioStore;
    std::vector<Task>& taskStore;

  public:
    void Execute(ParsedCMD&) override;
    dbOffloadScenarioCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                  std::vector<Task>& taskStore, IOunit& iounit);
    ~dbOffloadScenarioCMD() override;
};
