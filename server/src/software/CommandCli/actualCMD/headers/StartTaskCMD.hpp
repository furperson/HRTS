#pragma once

#include "CommandCli/CommandCli.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class StartTaskCMD : public CommandCli {
  private:
    InnerFunction& func;
    std::string CMDtitle = "start-task";
    std::string CMDhelp = "Отправляет задание на выполнение \n " + CMDtitle + " <Task-name>";
    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    StartTaskCMD(InnerFunction& func, IOunit& iounit);
    ~StartTaskCMD() override;
};
