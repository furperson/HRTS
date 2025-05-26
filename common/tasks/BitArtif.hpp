#pragma once 

#include <vector>
#include <array>
#include <nlohmann/json_fwd.hpp> 

// Структура для одного "сэмпла" данных
struct Sample {
    std::array<bool, 64> sampleData; 

    Sample() {
        sampleData.fill(false); // Инициализируем все false по умолчанию
    }
};

// Структура для артефакта, содержащего коллекцию сэмплов
struct BitArtef {
    std::vector<Sample> rawData; 


    BitArtef() = default;
};


void to_json(nlohmann::json& j, const Sample& s);
void from_json(const nlohmann::json& j, Sample& s);


void to_json(nlohmann::json& j, const BitArtef& ba);
void from_json(const nlohmann::json& j, BitArtef& ba);