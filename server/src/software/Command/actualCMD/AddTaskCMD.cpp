#include "Command/actualCMD/headers/AddTaskCMD.hpp"

void AddTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 1) {
        if (!(iounit == nullptr)) {
            auto it = std::find_if(scenarioStore->begin(), scenarioStore->end(),
                                   [&cmd](const Scenario& element) {
                                       return element.getScenarioName() == cmd.args[0];
                                   });
            if (it != scenarioStore->end()) {
                Task tmp(*it);
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

AddTaskContext::AddTaskContext(IOunit& iounit, std::vector<Scenario>& scen, std::vector<Task>& task)
    : iounit(iounit), scenarioStore(scen), taskStore(task) {

      };

AddTaskCMD::~AddTaskCMD() {};

AddTaskContext::~AddTaskContext() {};
