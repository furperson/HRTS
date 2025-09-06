#pragma once

#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class PrintScenarioCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    PrintScenarioCMD(InnerFunction& func, IOunit& iounit);
    ~PrintScenarioCMD() override;
};
