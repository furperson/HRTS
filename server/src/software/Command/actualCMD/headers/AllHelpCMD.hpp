#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Interpretator/Interpretator.hpp"

class AllHelpCMD : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    Interpretator* interpretator = nullptr;

  public:
    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    AllHelpCMD();
    ~AllHelpCMD() override;
};

struct AllHelpContext : public Context {
    IOunit& iounit;
    Interpretator& interpretator;
    AllHelpContext(IOunit&, Interpretator&);
    ~AllHelpContext() override;
    AllHelpContext() = delete;
};
