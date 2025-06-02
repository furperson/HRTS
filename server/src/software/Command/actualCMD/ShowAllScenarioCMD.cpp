#include "Command/actualCMD/headers/ShowAllScenarioCMD.hpp"

void ShowAllScenarioCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 0) {
        if (!(iounit == nullptr)) {
            for (auto& scen : *scenarioStore) {
                iounit->write(scen.getScenarioName() + "\n");
            }
        }
    }
}

void ShowAllScenarioCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const ShowAllContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->scenarioStore = &(tmpContext.scenarioStore);
}

ShowAllContext::ShowAllContext(IOunit& iounit, std::vector<Scenario>& scen)
    : iounit(iounit), scenarioStore(scen) {

      };

ShowAllScenarioCMD::~ShowAllScenarioCMD() {};

ShowAllContext::~ShowAllContext() {};
