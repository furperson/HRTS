#pragma once

#include <string>
#include <vector>
#include <array>


#include <nlohmann/json.hpp>


//

// Вспомогательная структура для мапинга пинов в группы
// (группы могут пересекаться)
// сделать немутабельным в каком-то смысле
// сделать конструктор копирования

struct PinBusGroup {
    std::string bus_name;
    std::vector<int> pins; 
    bool isLSB;

    PinBusGroup(const std::string& name , const std::vector<int>& p , bool lsb = true);
};

class Scenario {
private:
    std::string m_scenarioName;
    int m_testDurationMs;
    int m_stopScenarioPin;
    std::string m_fpgaFirmwareName;
    std::string m_dataFileName;
    std::array<bool, 64> m_pinScanEnable; // Массив из 64 булевых значений
    std::vector<PinBusGroup> m_pinNaming;

public:
    // Конструктор по умолчанию
    Scenario() = delete;

    // Параметризованный конструктор
    Scenario(
        const std::string& scenarioName,
        int testDurationMs,
        int stopScenarioPin,
        const std::string& fpgaFirmwareName,
        const std::string& dataFileName,
        const std::array<bool, 64>& pinScanEnable,
        const std::vector<PinBusGroup>& pinNaming);

    const std::string& getScenarioName() const;
    int getTestDurationMs() const;
    int getStopScenarioPin() const;
    const std::string& getFpgaFirmwareName() const;
    const std::string& getDataFileName() const;
    const std::array<bool, 64>& getPinScanEnable() const;
    bool getPinScanEnable(size_t index) const;
    const std::vector<PinBusGroup>& getPinNaming() const;

    void setScenarioName(const std::string& name);
    void setTestDurationMs(int duration);
    void setStopScenarioPin(int pin);
    void setFpgaFirmwareName(const std::string& firmwareName);
    void setDataFileName(const std::string& dataFile);
    void setPinScanEnable(const std::array<bool, 64>& scanEnable);
    void setPinScanEnable(size_t index, bool value);
    void setPinNaming(const std::vector<PinBusGroup>& naming);
    void addPinBusGroup(const PinBusGroup& group);
};


namespace nlohmann
{
// Специализация adl_serializer для PinBusGroup
template <>
struct adl_serializer<PinBusGroup>
{
    // Преобразование из JSON в PinBusGroup
    static PinBusGroup from_json(const json& j);

    // Преобразование из PinBusGroup в JSON
    // (передаем pbg по значению, как в исходном примере, хотя const& тоже хорошо)
    static void to_json(json& j, PinBusGroup pbg);
};

// Специализация adl_serializer для Scenario
template <>
struct adl_serializer<Scenario>
{
    // Преобразование из JSON в Scenario
    static Scenario from_json(const json& j);

    // Преобразование из Scenario в JSON
    // (передаем config по значению, используем геттеры для доступа к приватным членам)
    static void to_json(json& j, Scenario config);
};
} 