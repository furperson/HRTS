#include "CommandCli/actualCMD/headers/dbOffloadScenarioCMD.hpp"

void dbOffloadScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 2)) {
        
        auto scen = func.getScen(cmd.otherArgs[0],cmd.otherArgs[1]);

        if(scen && func.dboffloadScenario(cmd.otherArgs[0],scen.value())) {
            iounit.write("УСПЕШНО \n");
        }
        else {
            iounit.write("ОШИБКА, такой task с таким user нет \n");
        }
    }
}

dbOffloadScenarioCMD::dbOffloadScenarioCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                std::vector<Task>& taskStore , IOunit& iounit)
    : CommandCli("db-offload-scen", "загружает scenario на БД :  \n db-offload-scen <имя_user> <имя_scen>"),
      func(func), scenarioStore(scenarioStore),taskStore(taskStore), iounit(iounit) {};

dbOffloadScenarioCMD::~dbOffloadScenarioCMD() {};
