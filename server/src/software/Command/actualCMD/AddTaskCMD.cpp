#include "Command/actualCMD/headers/AddTaskCMD.hpp"

void AddTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 1)) {
        if (!(iounit == nullptr)) {
            auto it = std::find_if(scenarioStore->begin(), scenarioStore->end(),
                                   [&cmd](const Scenario& element) {
                                       return element.getScenarioName() == cmd.otherArgs[0];
                                   });
            if (it != scenarioStore->end()) {
                std::string taskName = (*it).getScenarioName();
                if (cmd.oneArgs.contains("name"))
                    taskName = cmd.oneArgs["name"];
                Task tmp(*it, taskName);
                taskStore->push_back(tmp);

            } else {
                iounit->write("сценарий не найден \n");
            }
        }
    }
}

void AddTaskCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const AddTaskContext&>(context);
    this->iounit = &tmpContext.iounit;
    this->scenarioStore = &tmpContext.scenarioStore;
    this->taskStore = &tmpContext.taskStore;
}

AddTaskCMD::AddTaskCMD()
    : Command("add-task", "Создаёт из сценария задание :  \n AddTask <имя_сценария>") {};

AddTaskContext::AddTaskContext(IOunit& iounit, std::vector<Scenario>& scen, std::vector<Task>& task)
    : iounit(iounit), scenarioStore(scen), taskStore(task) {

      };

AddTaskCMD::~AddTaskCMD() {};

AddTaskContext::~AddTaskContext() {};
