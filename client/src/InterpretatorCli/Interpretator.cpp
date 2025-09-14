#include "Interpretator.hpp"
// поменять механизм прикрепления комманд

void Interpretator::processCMD(ParsedCMD& parCMD) {
    if (commands.contains(parCMD.title)) {
        commands[parCMD.title](parCMD);
    } else {
        iounit->write("Команда " + parCMD.title + " не найдена!\n");
    }
};

void Interpretator::addCMD(std::string name,std::function<int(ParsedCMD&)> func) {
    if (!commands.contains(name)) {
        commands[name] = func;
    }
};

Interpretator::Interpretator(IOunit& io_ref) : iounit(&io_ref) {};

const std::unordered_map<std::string, std::function<int(ParsedCMD&)> >* Interpretator::getCMDS() {
    return &(this->commands);
}