#include "Command/actualCMD/GlobalHelpCMD.hpp"

void GlobalHelpCMD::Execute(ParsedCMD& cmd) {
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

void GlobalHelpCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("Печатает всю инфу про сценарий \n");
    }
}

std::string GlobalHelpCMD::getTitle() {
    return "PrintScenario";
}

void GlobalHelpCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const GlobalHelpContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->scenarioStore = &(tmpContext.scenarioStore);
}

GlobalHelpContext::GlobalHelpContext(IOunit& iounit,std::vector<Scenario>& scen):iounit(iounit),scenarioStore(scen) {
    
};

GlobalHelpCMD::~GlobalHelpCMD() {};

GlobalHelpContext::~GlobalHelpContext() {};
