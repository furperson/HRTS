#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

#include "PreParser.hpp"
#include "Command/Command.hpp"


class Interpretator
{
private:
std::unordered_map<std::string,Command> handlers;
public:
    void processCMD (ParsedCMD&);
    void addCMD(std::string, Command&);
    Interpretator() = default;
    ~Interpretator() = default;
};
