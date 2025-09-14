#include "CommandCli/actualCMD/headers/AllHelpCMD.hpp"

void AllHelpCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() and cmd.otherArgs.size() == 0 and
        (cmd.oneArgs.size() + cmd.secArgs.size() <= 1)) {

        if ((cmd.oneArgs.size() + cmd.secArgs.size() == 0)) {
            iounit.write("----------------------------\n");
            iounit.write(this->getHelp() + "\n");
        } else if (cmd.secArgs.size() == 1 and cmd.secArgs[0] == "all") {
            auto CMDS = *(interpretator.getCMDS());
            for (auto& [key, value] : CMDS) {
                iounit.write("----------------------------\n");
                iounit.write("Команда: " + key + "\n" + value->getHelp() + "\n");
            }
        } else if (cmd.secArgs.size() == 1 and cmd.secArgs[0] == "list") {
            auto CMDS = *(interpretator.getCMDS());
            for (auto& [key, value] : CMDS) {
                iounit.write("Команда: " + key + "\n");
            }
        } else if (cmd.oneArgs.size() == 1) {
            auto CMDS = *(interpretator.getCMDS());

            if (auto cmdName = cmd.oneArgs.find("cmd"); cmdName != cmd.oneArgs.end()) {
                if (auto curCmd = CMDS.find(cmd.oneArgs[cmdName->first]); curCmd != CMDS.end()) {
                    iounit.write("Команда: " + cmdName->first + "\n" +
                                 CMDS[cmd.oneArgs[cmdName->first]]->getHelp() + "\n");
                } else {
                    throw std::logic_error("invalid args!");
                }
            } else {
                throw std::logic_error("invalid args!");
            }
        } else {
            throw std::logic_error("invalid args!");
        }

    } else {
        throw std::logic_error("invalid args!");
    }
}

AllHelpCMD::AllHelpCMD(InnerFunction& func, IOunit& iounit, Interpretator& interpretator)
    : CommandCli("help", "Команда help выводит справочную информацию \n"
                         "help [--all,-cmd=cmdName , --list]\n"
                         "--all - вывести справочную информацию всех команд \n"
                         "-cmd=cmdName - вывести справочную информацию определённой команды \n"
                         "--list - вывести список доступных команд"),
      func(func), iounit(iounit), interpretator(interpretator) {};

AllHelpCMD::~AllHelpCMD() {};
