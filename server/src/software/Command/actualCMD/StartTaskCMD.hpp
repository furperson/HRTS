#pragma once

#include "Command/Command.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class StartTaskCMD : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    HwUnit* hwunit = nullptr;
    std::vector<Task>* taskStore = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

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
