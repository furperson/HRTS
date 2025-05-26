#pragma once

#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"
#include <memory> 

#include <vector>

class ShowAllScenarioCMD : public Command {
  private:
    /* data */
    IOunit* iounit  = nullptr;
    std::vector<Scenario>* scenarioStore = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    ShowAllScenarioCMD() = default;
    ~ShowAllScenarioCMD() override ;
};

struct ShowAllContext : public Context {
    ShowAllContext(IOunit&,std::vector<Scenario>&);
    IOunit& iounit;
    std::vector<Scenario>& scenarioStore;
    ~ShowAllContext() override ;
    ShowAllContext() = delete;
};
