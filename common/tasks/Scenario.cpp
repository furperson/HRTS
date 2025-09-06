#include "Scenario.hpp"

PinBusGroup::PinBusGroup(const std::string& name, const std::vector<int>& p, bool lsb)
    : bus_name(name), pins(p), isLSB(lsb) {
}
PinBusGroup::PinBusGroup(){};

//     // m_stopScenarioPin  = -1 = oотключен режим остановки по пину
// Scenario::Scenario()
//     : m_testDurationMs(0), m_stopScenarioPin(-1) // Инициализация по умолчанию
// {
//     m_pinScanEnable.fill(false); // По умолчанию все пины не сканируются
// }

// Параметризованный конструктор
Scenario::Scenario(const std::string& scenarioName, int testDurationMs, int stopScenarioPin,
                   const std::string& fpgaFirmwareName, const std::array<bool, 64>& pinScanEnable,
                   const std::vector<PinBusGroup>& pinNaming , std::string Owner_name_)
    : m_scenarioName(scenarioName), m_testDurationMs(testDurationMs),
      m_stopScenarioPin(stopScenarioPin), m_fpgaFirmwareName(fpgaFirmwareName),
      m_pinScanEnable(pinScanEnable), m_pinNaming(pinNaming), Owner_name_(Owner_name_) {
}

// Геттеры
const std::string& Scenario::getScenarioName() const {
    return m_scenarioName;
}

const std::string& Scenario::getOwnername() const{
return Owner_name_;
}

int Scenario::getTestDurationMs() const {
    return m_testDurationMs;
}

int Scenario::getStopScenarioPin() const {
    return m_stopScenarioPin;
}

const std::string& Scenario::getFpgaFirmwareName() const {
    return m_fpgaFirmwareName;
}

const std::array<bool, 64>& Scenario::getPinScanEnable() const {
    return m_pinScanEnable;
}

bool Scenario::getPinScanEnable(size_t index) const {
    if (index < m_pinScanEnable.size()) {
        return m_pinScanEnable[index];
    }
    return false;
}

const std::vector<PinBusGroup>& Scenario::getPinNaming() const {
    return m_pinNaming;
}

// Сеттеры
void Scenario::setScenarioName(const std::string& name) {
    m_scenarioName = name;
}

void Scenario::setTestDurationMs(int duration) {
    m_testDurationMs = duration;
}

void Scenario::setStopScenarioPin(int pin) {
    m_stopScenarioPin = pin;
}

void Scenario::setFpgaFirmwareName(const std::string& firmwareName) {
    m_fpgaFirmwareName = firmwareName;
}

void Scenario::setPinScanEnable(const std::array<bool, 64>& scanEnable) {
    m_pinScanEnable = scanEnable;
}

void Scenario::setPinScanEnable(size_t index, bool value) {
    if (index < m_pinScanEnable.size()) {
        m_pinScanEnable[index] = value;
    } else {
        // std::cerr << "Error: PinScanEnable index out of bounds for setting." << std::endl;
    }
}

void Scenario::setPinNaming(const std::vector<PinBusGroup>& naming) {
    m_pinNaming = naming;
}

void Scenario::addPinBusGroup(const PinBusGroup& group) {
    m_pinNaming.push_back(group);
}
