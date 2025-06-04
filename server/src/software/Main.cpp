#include "Server/Server.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    Server server;

    /*тестовые данные*/
    std::string scenarioName1 = "Full_Scan_Test";
    int testDurationMs1 = 30000; // 30 секунд
    int stopScenarioPin1 = 63;   // Последний пин как стоп-пин
    std::string fpgaFirmwareName1 = "full_scan_v1.2.bit";

    std::array<bool, 64> pinScanEnable1;
    pinScanEnable1.fill(true); // Включить сканирование всех пинов

    std::vector<PinBusGroup> pinNaming1;
    pinNaming1.emplace_back("DATA_BUS_LOW", std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7}, true);
    pinNaming1.emplace_back("DATA_BUS_HIGH", std::vector<int>{8, 9, 10, 11, 12, 13, 14, 15}, true);
    pinNaming1.emplace_back("ADDR_BUS", std::vector<int>{16, 17, 18, 19, 20}, false);
    pinNaming1.emplace_back("CONTROL_SIG", std::vector<int>{60, 61, 62}, true);

    Scenario scenario1(scenarioName1, testDurationMs1, stopScenarioPin1, fpgaFirmwareName1,
                       pinScanEnable1, pinNaming1);

    // --- Создание второго тестового сценария ---
    std::string scenarioName2 = "Partial_I2C_Test";
    int testDurationMs2 = 5000; // 5 секунд
    int stopScenarioPin2 = -1;

    std::string fpgaFirmwareName2 = "i2c_tester_fw_alpha.bin";

    std::array<bool, 64> pinScanEnable2{}; // Инициализация всех false
    pinScanEnable2[10] = true;             // SCL
    pinScanEnable2[11] = true;             // SDA
    pinScanEnable2[0] = true;

    std::vector<PinBusGroup> pinNaming2;
    pinNaming2.emplace_back("I2C1_SCL", std::vector<int>{10}, true); // Один пин в группе
    pinNaming2.emplace_back("I2C1_SDA", std::vector<int>{11}, true);

    Scenario scenario2(scenarioName2, testDurationMs2, stopScenarioPin2, fpgaFirmwareName2,
                       pinScanEnable2, pinNaming2);

    scenario2.addPinBusGroup(PinBusGroup("DEBUG_ACTIVITY", {0}));

    // 3. Create Task 1 object
    Task task1(scenario1, "Task1");
    // Optionally set other Task properties
    task1.setProcessingStartTime(std::time(nullptr)); // Set start time to now

    server.scenarioStore.push_back(scenario2);
    // server.scenarioStore.push_back(scenario1);
    // server.taskStore.push_back(task1);

    server.startServer(argc, argv);
}
