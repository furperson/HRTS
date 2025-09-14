#pragma once

#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class Server;
class PersistenceManager;

class LoadDataFromFileCMD : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    LoadDataFromFileCMD(InnerFunction& func, IOunit& iounit);
    ~LoadDataFromFileCMD() override;
};