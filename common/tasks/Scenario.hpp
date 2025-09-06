#pragma once

#include <array>
#include <chrono>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>



struct PinBusGroup {
    std::string bus_name;
    std::vector<int> pins;
    bool isLSB;

    PinBusGroup();

    PinBusGroup(const std::string& name, const std::vector<int>& p, bool lsb = true);
};

class Scenario {
  private:
    std::string Owner_name_;
    std::string m_scenarioName;
    int m_testDurationMs;
    int m_stopScenarioPin;
    std::string m_fpgaFirmwareName;

    std::array<bool, 64> m_pinScanEnable; // Массив из 64 булевых значений
    std::vector<PinBusGroup> m_pinNaming;

  public:
    // Конструктор по умолчанию
    Scenario() = delete;

    // Параметризованный конструктор
    Scenario(const std::string& scenarioName, int testDurationMs, int stopScenarioPin,
             const std::string& fpgaFirmwareName, const std::array<bool, 64>& pinScanEnable,
             const std::vector<PinBusGroup>& pinNaming, std::string Owner_name_);

    const std::string& getScenarioName() const;
    int getTestDurationMs() const;
    int getStopScenarioPin() const;
    const std::string& getFpgaFirmwareName() const;
    const std::string& getOwnername() const;
    const std::array<bool, 64>& getPinScanEnable() const;
    bool getPinScanEnable(size_t index) const;
    const std::vector<PinBusGroup>& getPinNaming() const;

    void setScenarioName(const std::string& name);
    void setTestDurationMs(int duration);
    void setStopScenarioPin(int pin);
    void setFpgaFirmwareName(const std::string& firmwareName);
    void setPinScanEnable(const std::array<bool, 64>& scanEnable);
    void setPinScanEnable(size_t index, bool value);
    void setPinNaming(const std::vector<PinBusGroup>& naming);
    void addPinBusGroup(const PinBusGroup& group);
};

namespace nlohmann {

// Специализация для PinBusGroup
template <> struct adl_serializer<PinBusGroup> {
    // Функция для преобразования PinBusGroup в JSON
    static void to_json(json& j, const PinBusGroup& pbg) {
        j = json{{"bus_name", pbg.bus_name}, {"pins", pbg.pins}, {"isLSB", pbg.isLSB}};
    }

    // Функция для создания PinBusGroup из JSON
    static PinBusGroup from_json(const json& j) {
        return PinBusGroup(j.at("bus_name").get<std::string>(),
                           j.at("pins").get<std::vector<int>>(),
                           j.value("isLSB", true));
    }
};

// Специализация для Scenario
template <> struct adl_serializer<Scenario> {
    // Функция для преобразования Scenario в JSON
    static void to_json(json& j, const Scenario& s) {
        j = json{
            {"Owner_name_", s.getOwnername()},
            {"scenarioName", s.getScenarioName()},
            {"testDurationMs", s.getTestDurationMs()},
            {"stopScenarioPin", s.getStopScenarioPin()},
            {"fpgaFirmwareName", s.getFpgaFirmwareName()},
            {"pinScanEnable", s.getPinScanEnable()},
            {"pinNaming", s.getPinNaming()}         
                                                     
        };
    }

    // Функция для создания Scenario из JSON
    static Scenario from_json(const json& j) {

        return Scenario(j.at("scenarioName").get<std::string>(), j.at("testDurationMs").get<int>(),
                        j.at("stopScenarioPin").get<int>(),
                        j.at("fpgaFirmwareName").get<std::string>(),
                        j.at("pinScanEnable").get<std::array<bool, 64>>(),
                        j.at("pinNaming")
                            .get<std::vector<PinBusGroup>>() 
                        ,
                        j.at("Owner_name_").get<std::string>());
    }
};

} // namespace nlohmann