#pragma once

// #include "CommandCli/CommandCli.hpp"
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
    std::unordered_map<std::string, std::function<int(ParsedCMD&)> > commands;

  public:
    void processCMD(ParsedCMD&);
    void addCMD(std::string name,std::function<int(ParsedCMD&)> func);

    const std::unordered_map<std::string, std::function<int(ParsedCMD&)> >* getCMDS();

    Interpretator() = delete;
    explicit Interpretator(IOunit&);
    ~Interpretator() = default;
};
