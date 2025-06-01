#include "Command/Command.hpp"

Command::~Command() {};

Context::~Context() {};

std::string Command::getHelp(){
    return this->CMDhelp;
};
std::string Command::getTitle(){
    return this->CMDtitle;
};