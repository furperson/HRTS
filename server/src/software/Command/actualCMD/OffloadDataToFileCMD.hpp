#pragma once

#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"

#include <memory>
#include <vector>

class Server;
class PersistenceManager;

class OffloadDataToFileCMD : public Command {
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
    OffloadDataToFileCMD() = default;
    ~OffloadDataToFileCMD() override;
};

struct OffloadDataToFileContext : public Context {
    OffloadDataToFileContext(IOunit&, Server&, PersistenceManager&);
    IOunit& iounit;
    Server& server;
    PersistenceManager& meng;
    ~OffloadDataToFileContext() override;
    OffloadDataToFileContext() = delete;
};
