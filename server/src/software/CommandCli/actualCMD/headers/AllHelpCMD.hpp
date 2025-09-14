#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "InterpretatorCli/Interpretator.hpp"

class AllHelpCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;
    Interpretator& interpretator;

  public:
    void Execute(ParsedCMD&) override;
    AllHelpCMD(InnerFunction& func, IOunit& iounit, Interpretator& interpretator);
    ~AllHelpCMD() override;
};