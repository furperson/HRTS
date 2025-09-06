#pragma once

#include <stdexcept> 
#include "nlohmann/json.hpp"

enum class Commands {
    LOGGING,
    GET_TASK,
    GET_SCENARIO,
    GET_TASK_LIST,
    GET_SCENARIO_LIST,
    RUN_TASK
};

struct Message {
    Commands cmds;
    nlohmann::json data;
};



inline void to_json(nlohmann::json& j, const Message& msg) {
    std::string command_str;
    switch (msg.cmds) {
        case Commands::LOGGING:     command_str = "LOGGING";     break;
        case Commands::GET_TASK:     command_str = "GET_TASK";     break;
        case Commands::GET_SCENARIO: command_str = "GET_SCENARIO"; break;
        case Commands::RUN_TASK:     command_str = "RUN_TASK";     break;
        case Commands::GET_TASK_LIST: command_str = "GET_TASK_LIST"; break;
        case Commands::GET_SCENARIO_LIST: command_str = "GET_SCENARIO_LIST"; break;
        default:                     command_str = "UNKNOWN";      break;
    }

    j = nlohmann::json{
        {"command", command_str},
        {"data", msg.data}
    };
}

inline void from_json(const nlohmann::json& j, Message& msg) {

    std::string command_str = j.at("command").get<std::string>();

    if (command_str == "GET_TASK") {
        msg.cmds = Commands::GET_TASK;
    } else if (command_str == "GET_SCENARIO") {
        msg.cmds = Commands::GET_SCENARIO;
    } else if (command_str == "LOGGING") {
        msg.cmds = Commands::LOGGING;
    } else if (command_str == "RUN_TASK") {
        msg.cmds = Commands::RUN_TASK;
    } else if (command_str == "GET_TASK_LIST") {
        msg.cmds = Commands::GET_TASK_LIST;
    } else if (command_str == "GET_SCENARIO_LIST") {
        msg.cmds = Commands::GET_SCENARIO_LIST;
    } else {
        throw std::invalid_argument("Unknown command in JSON: " + command_str);
    }
    msg.data = j.at("data");
}

struct Resp{
    int code;
    nlohmann::json data;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Resp, code, data)