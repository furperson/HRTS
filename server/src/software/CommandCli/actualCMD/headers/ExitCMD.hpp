#pragma once
#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "PersistenceManager/PersistenceManager.hpp"

#include <algorithm>

// Выходит из программы ,
class ExitCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */

  public:
    void Execute(ParsedCMD&) override;
    ExitCMD(InnerFunction& func);
    ~ExitCMD() override;
};
