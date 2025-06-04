#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Interpretator/Interpretator.hpp"
#include "ScenSer.hpp"

#include <nlohmann/json.hpp>

class ScenarioMakeCMD : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    std::vector<Scenario>* scenarioStore;

  public:
    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    ScenarioMakeCMD();
    ~ScenarioMakeCMD() override;
};

struct ScenarioMakeContext : public Context {
    IOunit& iounit;
    std::vector<Scenario>& scenarioStore;
    ScenarioMakeContext(IOunit&, std::vector<Scenario>&);
    ~ScenarioMakeContext() override;
    ScenarioMakeContext() = delete;
};
