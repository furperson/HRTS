#pragma once

#include "Command/Command.hpp"
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
    std::unordered_map<std::string, Command*> commands;

  public:
    void processCMD(ParsedCMD&);
    void addCMD(Command&);

    const std::unordered_map<std::string, Command*>* getCMDS();

    Interpretator() = delete;
    explicit Interpretator(IOunit&);
    ~Interpretator() = default;
};
