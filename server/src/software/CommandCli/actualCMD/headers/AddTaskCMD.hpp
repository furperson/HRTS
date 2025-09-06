#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <vector>

class AddTaskCMD : public CommandCli {
  private:
    InnerFunction& func;

    std::string CMDtitle = "add-task";
    std::string CMDhelp = "Создаёт из сценария задание :  \n AddTask <имя_сценария>";
    /* data */
    IOunit& iounit;
    // std::vector<Scenario>& scenarioStore;
    // std::vector<Task>& taskStore;

  public:
    void Execute(ParsedCMD&) override;
    AddTaskCMD(InnerFunction& func, IOunit& iounit);
    ~AddTaskCMD() override;
};
