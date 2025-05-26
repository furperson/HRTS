#pragma once

#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class PrintScenarioCMD : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    std::vector<Scenario>* scenarioStore = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    PrintScenarioCMD() = default;
    ~PrintScenarioCMD() override;
};

struct PrntScenContext : public Context {
    PrntScenContext(IOunit&, std::vector<Scenario>&);
    IOunit& iounit;
    std::vector<Scenario>& scenarioStore;
    ~PrntScenContext() override;
    PrntScenContext() = delete;
};
