#include "CommandCli/actualCMD/headers/ExitCMD.hpp"

void ExitCMD::Execute(ParsedCMD& cmd) {

    if (std::find(cmd.secArgs.begin(), cmd.secArgs.end(), "S") != cmd.secArgs.end()) {
        func.exitServ(1);
    }
    func.exitServ(0);
}

ExitCMD::ExitCMD(InnerFunction& func)
    : CommandCli("exit", "команда exit выходит из программы \n"
                         "--S - выход с сохранением данных(файл рядом \"backup\")"),
      func(func) {};

ExitCMD::~ExitCMD() {};
