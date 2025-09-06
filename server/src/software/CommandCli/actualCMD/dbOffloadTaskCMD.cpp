#include "CommandCli/actualCMD/headers/dbOffloadTaskCMD.hpp"

void dbOffloadTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 2)) {
        auto tsk = func.getTask(cmd.otherArgs[0],cmd.otherArgs[1]);

        if(func.dboffloadTask(cmd.otherArgs[0],tsk.value())) {
            iounit.write("УСПЕШНО \n");
        }
        else {
            iounit.write("ОШИБКА, такой task с таким user нет \n");
        }
    }
}

dbOffloadTaskCMD::dbOffloadTaskCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                std::vector<Task>& taskStore , IOunit& iounit)
    : CommandCli("db-offload-task", "загружает task на БД :  \n db-offload-task <имя_user> <имя_task>"),
      func(func), scenarioStore(scenarioStore),taskStore(taskStore), iounit(iounit) {};

dbOffloadTaskCMD::~dbOffloadTaskCMD() {};
