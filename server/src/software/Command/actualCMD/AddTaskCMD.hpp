#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <vector>

class AddTaskCMD : public Command {
  private:
    /* data */
    IOunit* iounit  = nullptr;
    std::vector<Scenario>* scenarioStore = nullptr;
    std::vector<Task>* taskStore = nullptr;

  public:
    std::string getTitle() override;
    void getHelp() override;

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    AddTaskCMD() = default;
    ~AddTaskCMD() override ;
};

struct AddTaskContext : public Context {
    AddTaskContext(IOunit&,std::vector<Scenario>&,std::vector<Task>&);
    IOunit& iounit;
    std::vector<Scenario>& scenarioStore;
    std::vector<Task>& taskStore;
    ~AddTaskContext() override ;
    AddTaskContext() = delete;
};
