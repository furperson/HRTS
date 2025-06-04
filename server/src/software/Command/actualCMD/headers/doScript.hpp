#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "fstream"

#include <memory>

class doScript : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;

  public:
    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    doScript();
    ~doScript() override;
};

struct doScriptContext : public Context {
    IOunit& iounit;
    doScriptContext(IOunit&);
    ~doScriptContext() override;
    doScriptContext() = delete;
};
