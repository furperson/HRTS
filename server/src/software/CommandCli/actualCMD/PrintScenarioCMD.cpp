#include "CommandCli/actualCMD/headers/PrintScenarioCMD.hpp"

void PrintScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        std::string tmp = func.showScenario(cmd.otherArgs[0],"admin");
        if (tmp == "") {
            iounit.write("сценарий не найден \n");
        } else {
            iounit.write(tmp);
        }
    }
}

PrintScenarioCMD::PrintScenarioCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli("print-scenario",
                 "Команда print-scenario выводит сценарий \n print-scenario <имя_сценария>"),
      func(func), iounit(iounit) {};

PrintScenarioCMD::~PrintScenarioCMD() {};
