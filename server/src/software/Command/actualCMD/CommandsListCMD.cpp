#include "Command/actualCMD/CommandsListCMD.hpp"

void CommandsListCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 1) {
        if (!(iounit == nullptr)) {
            auto it = std::find_if(scenarioStore->begin(), scenarioStore->end(),
                                   [&cmd](const Scenario& element) {
                                       return element.getScenarioName() == cmd.args[0];
                                   });
            if (it != scenarioStore->end()) {
                iounit->write(it->getScenarioName());
            } else {
                iounit->write("сценарий не найден \n");
            }
        }
    }
}

void CommandsListCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("Печатает всю инфу про сценарий \n");
    }
}

std::string CommandsListCMD::getTitle() {
    return "PrintScenario";
}

void CommandsListCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const CommandsListContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->scenarioStore = &(tmpContext.scenarioStore);
}

CommandsListContext::CommandsListContext(IOunit& iounit, std::vector<Scenario>& scen)
    : iounit(iounit), scenarioStore(scen) {

      };

CommandsListCMD::~CommandsListCMD() {};

CommandsListContext::~CommandsListContext() {};
