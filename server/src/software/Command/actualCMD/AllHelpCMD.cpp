#include "Command/actualCMD/headers/AllHelpCMD.hpp"

void AllHelpCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() and cmd.otherArgs.size() == 0 and
        (cmd.oneArgs.size() + cmd.secArgs.size() <= 1)) {
        if (!(iounit == nullptr)) {
            if ((cmd.oneArgs.size() + cmd.secArgs.size() == 0)) {
                iounit->write("----------------------------\n");
                iounit->write(this->getHelp() + "\n");
            } else if (cmd.secArgs.size() == 1 and cmd.secArgs[0] == "all") {
                auto CMDS = *(interpretator->getCMDS());
                for (auto& [key, value] : CMDS) {
                    iounit->write("----------------------------\n");
                    iounit->write("Команда: " + key + "\n" + value->getHelp() + "\n");
                }
            } else if (cmd.secArgs.size() == 1 and cmd.secArgs[0] == "list") {
                auto CMDS = *(interpretator->getCMDS());
                for (auto& [key, value] : CMDS) {
                    iounit->write("Команда: " + key + "\n");
                }
            } else if (cmd.oneArgs.size() == 1) {
                auto CMDS = *(interpretator->getCMDS());

                if (auto cmdName = cmd.oneArgs.find("cmd"); cmdName != cmd.oneArgs.end()) {
                    if (auto curCmd = CMDS.find(cmd.oneArgs[cmdName->first]);
                        curCmd != CMDS.end()) {
                        iounit->write("Команда: " + cmdName->first + "\n" +
                                      CMDS[cmd.oneArgs[cmdName->first]]->getHelp() + "\n");
                    } else {
                        throw InvalidArgsCMD("invalid args!");
                    }
                } else {
                    throw InvalidArgsCMD("invalid args!");
                }
            } else {
                throw InvalidArgsCMD("invalid args!");
            }
        }
    } else {
        throw InvalidArgsCMD("invalid args!");
    }
}

void AllHelpCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const AllHelpContext&>(context);
    this->iounit = &tmpContext.iounit;
    this->interpretator = &tmpContext.interpretator;
}

AllHelpContext::AllHelpContext(IOunit& iounit, Interpretator& inter)
    : iounit(iounit), interpretator(inter) {

      };

AllHelpCMD::AllHelpCMD()
    : Command("help", "Команда help выводит справочную информацию \n"
                      "help [--all,-cmd=cmdName , --list]\n"
                      "--all - вывести справочную информацию всех команд \n"
                      "-cmd=cmdName - вывести справочную информацию определённой команды \n"
                      "--list - вывести список доступных команд") {};

AllHelpCMD::~AllHelpCMD() {};

AllHelpContext::~AllHelpContext() {};
