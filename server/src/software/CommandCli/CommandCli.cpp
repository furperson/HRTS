#include "CommandCli/CommandCli.hpp"

CommandCli::CommandCli(std::string CMDtitle, std::string CMDhelp)
    : CMDtitle(CMDtitle), CMDhelp(CMDhelp) {};

CommandCli::~CommandCli() {};

const std::string CommandCli::getHelp() {
    return this->CMDhelp;
};
const std::string CommandCli::getTitle() {
    return this->CMDtitle;
};