#include "Command/Command.hpp"

Command::Command(std::string CMDtitle, std::string CMDhelp)
    : CMDtitle(CMDtitle), CMDhelp(CMDhelp) {};

Command::~Command() {};

Context::~Context() {};

const std::string Command::getHelp() {
    return this->CMDhelp;
};
const std::string Command::getTitle() {
    return this->CMDtitle;
};