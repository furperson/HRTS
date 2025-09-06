#include "CommandCli/actualCMD/headers/StartTaskCMD.hpp"

void StartTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        if (func.execTask(cmd.otherArgs[0],"admin")) {
            iounit.write("Задание не найдено \n");
        }
    }
}

StartTaskCMD::StartTaskCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli("start-task", "Отправляет задание на выполнение \n start-task <Task-name>"),
      func(func), iounit(iounit) {};

StartTaskCMD::~StartTaskCMD() {};
