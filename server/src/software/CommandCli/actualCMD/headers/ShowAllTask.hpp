#pragma once

#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "InnerFunction/InnerFunction.hpp"
#include "Task.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

class ShowAllTask : public CommandCli {
  private:
    InnerFunction& func;

    /* data */
    IOunit& iounit;

  public:
    void Execute(ParsedCMD&) override;
    ShowAllTask(InnerFunction& func, IOunit& iounit);
    ~ShowAllTask() override;
};
