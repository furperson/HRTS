#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <vector>

class AddTaskCMD : public Command {
  private:
    std::string CMDtitle = "add-task";
    std::string CMDhelp = "Создаёт из сценария задание :  \n AddTask <имя_сценария>";
    /* data */
    IOunit* iounit = nullptr;
    std::vector<Scenario>* scenarioStore = nullptr;
    std::vector<Task>* taskStore = nullptr;

  public:
    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    AddTaskCMD();
    ~AddTaskCMD() override;
};

struct AddTaskContext : public Context {
    AddTaskContext(IOunit&, std::vector<Scenario>&, std::vector<Task>&);
    IOunit& iounit;
    std::vector<Scenario>& scenarioStore;
    std::vector<Task>& taskStore;
    ~AddTaskContext() override;
    AddTaskContext() = delete;
};
