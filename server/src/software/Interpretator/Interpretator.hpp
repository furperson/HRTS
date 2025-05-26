#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

#include "PreParser.hpp"
#include "Command/Command.hpp"
#include <functional>


class Interpretator
{
private:
std::unordered_map<std::string,Command*> commands;
public:
    void processCMD (ParsedCMD&);
    void addCMD(Command&);
    
    Interpretator() = default;
    ~Interpretator() = default;
};
