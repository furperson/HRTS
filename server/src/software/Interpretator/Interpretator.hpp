#pragma once

#include "Command/Command.hpp"
#include "PreParser.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

class Interpretator {
  private:
    std::unordered_map<std::string, Command*> commands;

  public:
    void processCMD(ParsedCMD&);
    void addCMD(Command&);

    Interpretator() = default;
    ~Interpretator() = default;
};
