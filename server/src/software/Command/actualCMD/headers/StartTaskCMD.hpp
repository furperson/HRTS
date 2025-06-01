#pragma once

#include "Command/Command.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class StartTaskCMD : public Command {
  private:
  std::string CMDtitle="start-task";
  std::string CMDhelp="Отправляет задание на выполнение \n "+CMDtitle+" <Task-name>";
    /* data */
    IOunit* iounit = nullptr;
    HwUnit* hwunit = nullptr;
    std::vector<Task>* taskStore = nullptr;

  public:

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    StartTaskCMD() = default;
    ~StartTaskCMD() override;
};

struct StartTaskContext : public Context {
    StartTaskContext(IOunit&, HwUnit&, std::vector<Task>&);
    IOunit& iounit;
    HwUnit& hwunit;
    std::vector<Task>& taskStore;
    ~StartTaskContext() override;
    StartTaskContext() = delete;
};
