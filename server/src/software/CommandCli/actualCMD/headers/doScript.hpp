#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "fstream"

#include <memory>

class doScript : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    doScript(InnerFunction& func, IOunit& iounit);
    ~doScript() override;
};
