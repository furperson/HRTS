#include "Command/actualCMD/headers/ShowAllTask.hpp"

void ShowAllTask::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 0) {
        if (!(iounit == nullptr)) {
            for (auto& task : *taskStore) {
                iounit->write("Task: " + task.getScenario().getScenarioName() + "\n");
                iounit->write("\t Task_state: " + stateToString[task.getState()] + "\n");
                iounit->write("\t Task_Scen_Name: " + task.getScenario().getScenarioName() + "\n");
            }
        }
    }
}

void ShowAllTask::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const ShowAllTaskContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->taskStore = &(tmpContext.taskStore);
}

ShowAllTaskContext::ShowAllTaskContext(IOunit& iounit, std::vector<Task>& task)
    : iounit(iounit), taskStore(task) {

      };

ShowAllTask::~ShowAllTask() {};

ShowAllTaskContext::~ShowAllTaskContext() {};
