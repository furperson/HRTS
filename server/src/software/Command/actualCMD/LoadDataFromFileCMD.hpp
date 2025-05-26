#pragma once

#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class Server;
class PersistenceManager;

class LoadDataFromFileCMD : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    Server* server = nullptr;
    PersistenceManager* meng = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    LoadDataFromFileCMD() = default;
    ~LoadDataFromFileCMD() override;
};

struct LoadDataToFileContext : public Context {
    LoadDataToFileContext(IOunit&, Server&, PersistenceManager&);
    IOunit& iounit;
    Server& server;
    PersistenceManager& meng;
    ~LoadDataToFileContext() override;
    LoadDataToFileContext() = delete;
};
