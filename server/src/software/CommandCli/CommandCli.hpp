#pragma once
#include "PreParser.hpp"

#include <string>

class CommandCli {
  private:
    std::string CMDtitle;
    std::string CMDhelp;

  public:
    virtual const std::string getTitle();
    virtual const std::string getHelp();

    virtual void Execute(ParsedCMD&) = 0;

    CommandCli(std::string CMDtitle, std::string CMDhelp);
    virtual ~CommandCli();
};
