#pragma once

#include "CommandCli/CommandCli.hpp"
#include "IOunit/IOunit.hpp"
#include "PreParser.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

class Interpretator {
  private:
    IOunit* iounit;
    std::unordered_map<std::string, CommandCli*> commands;

  public:
    void processCMD(ParsedCMD&);
    void addCMD(CommandCli&);

    const std::unordered_map<std::string, CommandCli*>* getCMDS();

    Interpretator() = delete;
    explicit Interpretator(IOunit&);
    ~Interpretator() = default;
};
