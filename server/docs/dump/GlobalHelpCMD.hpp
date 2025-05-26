#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"
#include <memory> 

#include <vector>

class GlobalHelpCMD : public Command {
  private:
    /* data */
    IOunit* iounit  = nullptr;
    std::vector<Scenario>* scenarioStore = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    GlobalHelpCMD() = default;
    ~GlobalHelpCMD() override ;
};

struct GlobalHelpContext : public Context {
    GlobalHelpContext(IOunit&,std::vector<Scenario>&);
    ~GlobalHelpContext() override ;
    GlobalHelpContext() = delete;
};
