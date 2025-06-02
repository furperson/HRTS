#include "Command/actualCMD/headers/StartTaskCMD.hpp"

void StartTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        auto it = std::find_if(taskStore->begin(), taskStore->end(), [&cmd](const Task& element) {
            return element.getScenario().getScenarioName() == cmd.otherArgs[0];
        });
        if (it != taskStore->end()) {
            hwunit->putTask(*it);
        } else {
            iounit->write("Задание не найдено \n");
        }
    }
}

void StartTaskCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const StartTaskContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->hwunit = &(tmpContext.hwunit);
    this->taskStore = &(tmpContext.taskStore);
}

StartTaskContext::StartTaskContext(IOunit& iounit, HwUnit& hwunit, std::vector<Task>& task)
    : iounit(iounit), hwunit(hwunit), taskStore(task) {

      };

StartTaskCMD::~StartTaskCMD() {};

StartTaskContext::~StartTaskContext() {};
