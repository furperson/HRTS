#include "CommandCli/actualCMD/headers/ShowAllTask.hpp"

void ShowAllTask::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 0) {
        iounit.write(func.showTask("admin"));
    }
}

ShowAllTask::ShowAllTask(InnerFunction& func, IOunit& iounit)
    : CommandCli("show-all-task", "Команда show-all-task выводит все задания  \n show-all-task"),
      func(func), iounit(iounit) {};

ShowAllTask::~ShowAllTask() {};
