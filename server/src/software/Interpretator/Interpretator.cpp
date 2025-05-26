#include "Interpretator.hpp"

void Interpretator::processCMD(ParsedCMD& parCMD) {
    if (commands.contains(parCMD.title)) {
        (*commands[parCMD.title]).Execute(parCMD);
    }
};

void Interpretator::addCMD(Command& cmd) {
    if (!commands.contains(cmd.getTitle())) {
        // std::reference_wrapper<Command&> tmpRF(cmd);
        commands[cmd.getTitle()] = &cmd;
    }
};
