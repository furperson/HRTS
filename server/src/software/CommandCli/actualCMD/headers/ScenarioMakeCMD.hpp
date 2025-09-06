#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "InterpretatorCli/Interpretator.hpp"
#include "ScenSer.hpp"

#include <nlohmann/json.hpp>

class ScenarioMakeCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    ScenarioMakeCMD(InnerFunction& func, IOunit& iounit);
    ~ScenarioMakeCMD() override;
};