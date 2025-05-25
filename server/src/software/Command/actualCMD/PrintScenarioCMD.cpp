#include "Command/actualCMD/PrintScenarioCMD.hpp"

void PrintScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size()==1) {
        if (!(iounit == nullptr)) {
            auto it = std::find_if(scenarioStore->begin(), scenarioStore->end(),
                                   [&cmd](const Scenario& element) {
                                       return element.getScenarioName() == cmd.args[0];
                                   });
            if (it != scenarioStore->end())
                iounit->write(it->getDataFileName());
        }
    }
}

void PrintScenarioCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("Печатает всю инфу про сценарий");
    }
}

const std::string PrintScenarioCMD::getTitle() {
    return "PrintScenario";
}

void PrintScenarioCMD::AttachContext(Context& context) {
    auto& tmpContext = dynamic_cast<PrntScenContext&>(context);
    this->iounit = &tmpContext.iounit;
    this->scenarioStore = &tmpContext.scenarioStore;
}
