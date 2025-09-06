#include "CommandCli/actualCMD/headers/dbLoadTaskCMD.hpp"

void dbLoadTaskCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 2)) {
        auto ts = func.dbloadTask(cmd.otherArgs[0],cmd.otherArgs[1]);
        if(ts && !func.addTask(ts.value())) {
            iounit.write("УСПЕШНО \n");
        }
        else {
            iounit.write("ОШИБКА, такой task с таким user нет \n");
        }
    }
}

dbLoadTaskCMD::dbLoadTaskCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                std::vector<Task>& taskStore , IOunit& iounit)
    : CommandCli("db-load-task", "загружает task из БД :  \n db-load-task <имя_user> <имя_task>"),
      func(func), scenarioStore(scenarioStore),taskStore(taskStore), iounit(iounit) {};

dbLoadTaskCMD::~dbLoadTaskCMD() {};
