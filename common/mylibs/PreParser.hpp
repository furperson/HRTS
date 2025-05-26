#pragma once

#include <ranges> // Для views::split и других range-адаптеров
#include <string>
#include <string_view> // Для удобства работы с подстроками
#include <vector>

// Токенизация
struct ParsedCMD {
    std::string title;
    std::vector<std::string> args;
};

ParsedCMD PreParse(const std::string str);
