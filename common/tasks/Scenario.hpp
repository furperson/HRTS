#pragma once

#include <string>
#include <vector>
#include <array>


#include <nlohmann/json.hpp>

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
        const std::array<bool, 64>& pinScanEnable,
        const std::vector<PinBusGroup>& pinNaming);

    const std::string& getScenarioName() const;
    int getTestDurationMs() const;
    int getStopScenarioPin() const;
    const std::string& getFpgaFirmwareName() const;
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
    template <>
    struct adl_serializer<PinBusGroup> {
        // Функция для преобразования PinBusGroup в JSON
        static void to_json(json& j, const PinBusGroup& pbg) {
            j = json{
                {"bus_name", pbg.bus_name},
                {"pins", pbg.pins},
                {"isLSB", pbg.isLSB}
            };
        }

        // Функция для создания PinBusGroup из JSON
        static PinBusGroup from_json(const json& j) {
            return PinBusGroup(
                j.at("bus_name").get<std::string>(),
                j.at("pins").get<std::vector<int>>(),
                // Используем j.value(), чтобы учесть значение по умолчанию для isLSB,
                // если оно отсутствует в JSON
                j.value("isLSB", true) 
            );
        }
    };

    // Специализация для Scenario
    template <>
    struct adl_serializer<Scenario> {
        // Функция для преобразования Scenario в JSON
        static void to_json(json& j, const Scenario& s) {
            j = json{
                {"scenarioName", s.getScenarioName()},
                {"testDurationMs", s.getTestDurationMs()},
                {"stopScenarioPin", s.getStopScenarioPin()},
                {"fpgaFirmwareName", s.getFpgaFirmwareName()},
                {"pinScanEnable", s.getPinScanEnable()}, // std::array сериализуется как JSON массив
                {"pinNaming", s.getPinNaming()}         // std::vector<PinBusGroup> будет использовать adl_serializer для PinBusGroup
            };
        }

        // Функция для создания Scenario из JSON
        static Scenario from_json(const json& j) {
            // Предполагается, что все эти ключи присутствуют в JSON,
            // так как конструктор Scenario требует все эти аргументы.
            // Если какие-то поля могут быть опциональными, потребуется более сложная логика
            // с проверками j.contains() и передачей значений по умолчанию в конструктор,
            // либо изменение конструктора Scenario.
            return Scenario(
                j.at("scenarioName").get<std::string>(),
                j.at("testDurationMs").get<int>(),
                j.at("stopScenarioPin").get<int>(),
                j.at("fpgaFirmwareName").get<std::string>(),
                j.at("pinScanEnable").get<std::array<bool, 64>>(),
                j.at("pinNaming").get<std::vector<PinBusGroup>>() // Использует from_json для PinBusGroup
            );
        }
    };

} // namespace nlohmann
