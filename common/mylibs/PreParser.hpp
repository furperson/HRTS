#pragma once
#include <string>
// #include <string_view> // Для удобства работы с подстроками
#include <vector>
#include <map>
#include <expected>
// "some thing" - одна строка


struct ParsedCMD {
    std::string title;
    std::vector<std::string> otherArgs;
    std::map<std::string,std::string> oneArgs; //args like -files=test
    std::vector<std::string> secArgs; //args like --help

};


std::expected<ParsedCMD,std::string> PreParse(const std::string str);
