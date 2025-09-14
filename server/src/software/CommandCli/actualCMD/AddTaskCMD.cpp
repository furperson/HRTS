#include "CommandCli/actualCMD/headers/AddTaskCMD.hpp"

void AddTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 1)) {
        if (cmd.oneArgs.contains("name")) {
            if (func.addTask(cmd.otherArgs[0], cmd.oneArgs["name"])) {
                iounit.write("сценарий не найден \n");
            }
        } else if (func.addTask(cmd.otherArgs[0],"admin")) {
            iounit.write("сценарий не найден \n");
        }
    }
}

AddTaskCMD::AddTaskCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli("add-task", "Создаёт из сценария задание :  \n AddTask <имя_сценария>"),
      func(func), iounit(iounit) {};

AddTaskCMD::~AddTaskCMD() {};
