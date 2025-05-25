#pragma once

#include <string>
#include <vector>
#include <ranges> // Для views::split и других range-адаптеров
#include <string_view> // Для удобства работы с подстроками

//Токенизация  
struct ParsedCMD
{
    std::string title;
    std::vector<std::string> args;
};


ParsedCMD PreParse(const std::string str);
