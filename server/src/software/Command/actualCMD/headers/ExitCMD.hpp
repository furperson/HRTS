#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Interpretator/Interpretator.hpp"
#include "PersistenceManager/PersistenceManager.hpp"

#include <algorithm>

// Выходит из программы ,
class ExitCMD : public Command {
  private:
    /* data */
    PersistenceManager* persistenceManager;

  public:
    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    ExitCMD();
    ~ExitCMD() override;
};

struct ExitContext : public Context {
    ExitContext(PersistenceManager&);
    PersistenceManager& persistenceManager;
    ~ExitContext() override;
    ExitContext() = delete;
};
