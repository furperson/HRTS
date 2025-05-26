#include "Command/actualCMD/StartTaskCMD.hpp"

void StartTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 1) {
        auto it = std::find_if(taskStore->begin(), taskStore->end(), [&cmd](const Task& element) {
            return element.getScenario().getScenarioName() == cmd.args[0];
        });
        if (it != taskStore->end()) {
            hwunit->putTask(*it);
        } else {
            iounit->write("Задание не найдено \n");
        }
    }
}

void StartTaskCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("выполняет задачу \n");
    }
}

std::string StartTaskCMD::getTitle() {
    return "StartTask";
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
