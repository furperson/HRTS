#include "Interpretator.hpp"
// поменять механизм прикрепления комманд

void Interpretator::processCMD(ParsedCMD& parCMD) {
    if (commands.contains(parCMD.title)) {
        (*commands[parCMD.title])
            .Execute(parCMD); // можно написать красивее ,используя не оператор квадратные скобки
    } else {
        iounit->write("Команда " + parCMD.title + " не найдена!\n");
    }
};

void Interpretator::addCMD(CommandCli& cmd) {
    if (!commands.contains(cmd.getTitle())) {
        // std::reference_wrapper<CommandCli&> tmpRF(cmd);
        commands[cmd.getTitle()] = &cmd;
    }
};

Interpretator::Interpretator(IOunit& io_ref) : iounit(&io_ref) {};

const std::unordered_map<std::string, CommandCli*>* Interpretator::getCMDS() {
    return &(this->commands);
}