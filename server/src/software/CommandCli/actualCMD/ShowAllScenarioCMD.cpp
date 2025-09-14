#include "CommandCli/actualCMD/headers/ShowAllScenarioCMD.hpp"

void ShowAllScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 0) {
        iounit.write(func.showScenario("admin"));
    }
}

ShowAllScenarioCMD::ShowAllScenarioCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli("show-scenarios",
                 "Команда show-scenarios выводит список всех сценариев \n show-scenarios"),
      func(func), iounit(iounit) {};

ShowAllScenarioCMD::~ShowAllScenarioCMD() {};
