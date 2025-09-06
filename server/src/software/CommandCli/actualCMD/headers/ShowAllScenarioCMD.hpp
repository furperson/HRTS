#pragma once

#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"

// #include <memory>
#include <vector>

class ShowAllScenarioCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    ShowAllScenarioCMD(InnerFunction& func, IOunit& iounit);
    ~ShowAllScenarioCMD() override;
};
