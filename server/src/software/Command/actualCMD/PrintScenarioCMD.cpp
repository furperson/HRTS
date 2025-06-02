#include "Command/actualCMD/headers/PrintScenarioCMD.hpp"

void PrintScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        if (!(iounit == nullptr)) {
            auto it = std::find_if(scenarioStore->begin(), scenarioStore->end(),
                                   [&cmd](const Scenario& element) {
                                       return element.getScenarioName() == cmd.otherArgs[0];
                                   });
            if (it != scenarioStore->end()) {
                iounit->write(it->getScenarioName());
            } else {
                iounit->write("сценарий не найден \n");
            }
        }
    }
}

void PrintScenarioCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const PrntScenContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->scenarioStore = &(tmpContext.scenarioStore);
}

PrntScenContext::PrntScenContext(IOunit& iounit, std::vector<Scenario>& scen)
    : iounit(iounit), scenarioStore(scen) {

      };

PrintScenarioCMD::~PrintScenarioCMD() {};

PrntScenContext::~PrntScenContext() {};
