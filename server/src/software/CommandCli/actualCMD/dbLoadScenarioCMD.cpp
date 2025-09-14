#include "CommandCli/actualCMD/headers/dbLoadScenarioCMD.hpp"

void dbLoadScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && (cmd.otherArgs.size() == 2)) {
        auto sc = func.dbloadScenario(cmd.otherArgs[0],cmd.otherArgs[1]);
        if(sc && !func.addScenario(sc.value())) {
            iounit.write("УСПЕШНО \n");
        }
        else {
            iounit.write("ОШИБКА, такой scen с таким user нет \n");
        }
    }
}

dbLoadScenarioCMD::dbLoadScenarioCMD(InnerFunction& func, std::vector<Scenario>& scenarioStore,
                std::vector<Task>& taskStore , IOunit& iounit)
    : CommandCli("db-load-scen", "загружает scenario из БД :  \n db-load-scen <имя_user> <имя_scen>"),
      func(func), scenarioStore(scenarioStore),taskStore(taskStore), iounit(iounit) {};

dbLoadScenarioCMD::~dbLoadScenarioCMD() {};
