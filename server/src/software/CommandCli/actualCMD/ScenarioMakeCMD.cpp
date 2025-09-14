#include "CommandCli/actualCMD/headers/ScenarioMakeCMD.hpp"

using json = nlohmann::json;

void ScenarioMakeCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle()) {
        if (cmd.oneArgs.contains("json")) {
            try {
                json j_root = json::parse(cmd.oneArgs["json"]);
                if (j_root.contains("scenario")) {
                    func.addScenario(j_root["scenario"]);
                } else {
                    iounit.write("неправильный json!\n");
                }
            } catch (const json::parse_error& e) {
                iounit.write("неправильный json!\n");
            }

        } else {
            std::string scenarioName;
            int testDurationMs;
            int stopScenarioPin = -1;
            std::string fpgaFirmwareName;

            std::array<bool, 64> m_pinScanEnable;
            std::fill(std::begin(m_pinScanEnable), std::end(m_pinScanEnable), 0);
            std::vector<PinBusGroup> m_pinNaming;
            iounit.write("Имя сценария: ");
            scenarioName = iounit.readLine();
            iounit.write("Длительность сценария в МС : ");
            testDurationMs = stoi(iounit.readLine());
            iounit.write("Имя прошивки: ");
            fpgaFirmwareName = iounit.readLine();
            func.addScenario(Scenario(scenarioName, testDurationMs, stopScenarioPin,
                                      fpgaFirmwareName, m_pinScanEnable, m_pinNaming, "admin"));
        }
    }
}

ScenarioMakeCMD::ScenarioMakeCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli(
          "make-scenario",
          "создания сценария\n если без аргументов, то войдёт в режим интерактивного создания \n"
          "-json=<json> - создания сценария из json представления"),
      func(func), iounit(iounit) {};

ScenarioMakeCMD::~ScenarioMakeCMD() {};
