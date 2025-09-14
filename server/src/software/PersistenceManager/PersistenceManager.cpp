#include "PersistenceManager/PersistenceManager.hpp"

#include "Server/Server.hpp"

using json = nlohmann::json;

void PersistenceManager::Offload(const std::string& filename) {
    json j_root;
    j_root["scenarioStore"] = server->scenarioStore;
    j_root["taskStore"] = server->taskStore;
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }

    try {
        ofs << j_root.dump(4);
    } catch (const json::exception& e) {
        std::cerr << "JSON serialization error during offload: " << e.what() << std::endl;
    }
}

void PersistenceManager::Load(const std::string& filename) {

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }

    json j_root;
    try {
        ifs >> j_root;

        if (j_root.contains("scenarioStore")) {
            server->scenarioStore = j_root["scenarioStore"];
        }

        if (j_root.contains("taskStore")) {
            server->taskStore = j_root["taskStore"];
        }
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error while loading from " << filename << ": " << e.what()
                  << std::endl;
    }
}

void PersistenceManager::OffloadScen(const std::string& filename) {
    json j_root;
    j_root["scenarioStore"] = server->scenarioStore;
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }

    try {
        ofs << j_root.dump(4);
    } catch (const json::exception& e) {
        std::cerr << "JSON serialization error during offload: " << e.what() << std::endl;
    }
};
void PersistenceManager::OffloadTask(const std::string& filename) {
    json j_root;
    j_root["taskStore"] = server->taskStore;
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }

    try {
        ofs << j_root.dump(4);
    } catch (const json::exception& e) {
        std::cerr << "JSON serialization error during offload: " << e.what() << std::endl;
    }
};

void PersistenceManager::loadScen(const std::string& filename) {

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }

    json j_root;
    try {
        ifs >> j_root;

        if (j_root.contains("scenarioStore")) {
            auto jsonVec = j_root["scenarioStore"];
            server->scenarioStore.insert(server->scenarioStore.end(),
                                         std::make_move_iterator(jsonVec.begin()),
                                         std::make_move_iterator(jsonVec.end()));
        }
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error while loading from " << filename << ": " << e.what()
                  << std::endl;
    }
};
void PersistenceManager::loadTask(const std::string& filename) {

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }

    json j_root;
    try {
        ifs >> j_root;
        if (j_root.contains("taskStore")) {
            auto jsonVec = j_root["taskStore"];
            server->taskStore.insert(server->taskStore.end(),
                                     std::make_move_iterator(jsonVec.begin()),
                                     std::make_move_iterator(jsonVec.end()));
        }
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error while loading from " << filename << ": " << e.what()
                  << std::endl;
    }
};

PersistenceManager::PersistenceManager(Server& server) : server(&server) {};