#include "BitArtif.hpp"

#include <nlohmann/json.hpp> // Полное определение json

// Для Sample
void to_json(nlohmann::json& j, const Sample& s) {
    // std::array<bool, N> будет автоматически сериализован в JSON массив булевых значений
    j = nlohmann::json{{"sampleData", s.sampleData}};
}

void from_json(const nlohmann::json& j, Sample& s) {
    // nlohmann/json умеет десериализовывать JSON массив в std::array
    j.at("sampleData").get_to(s.sampleData);
}

// Для BitArtef
void to_json(nlohmann::json& j, const BitArtef& ba) {
    // std::vector<Sample> будет сериализован как массив JSON-объектов,
    // для каждого из которых будет вызван to_json(j, const Sample&)
    j = nlohmann::json{{"rawData", ba.rawData}};
}

void from_json(const nlohmann::json& j, BitArtef& ba) {
    // nlohmann/json вызовет from_json(const json&, Sample&) для каждого элемента массива "rawData"
    j.at("rawData").get_to(ba.rawData);
}