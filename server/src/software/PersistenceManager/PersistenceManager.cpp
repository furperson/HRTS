#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

using json = nlohmann::json;

void PersistenceManager::Offload(Server& server,const std::string& filename){
    json j_root;
    j_root["scenarioStore"] = server.scenarioStore;
    j_root["taskStore"] = server.taskStore;
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }

    try {
        ofs << j_root.dump(4);
        std::cout << "Data successfully offloaded to " << filename << std::endl;
    } catch (const json::exception& e) {
        std::cerr << "JSON serialization error during offload: " << e.what() << std::endl;
    }
}

void PersistenceManager::Load(Server& server,const std::string& filename){

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }

    json j_root;
    try {
        ifs >> j_root; 

        if (j_root.contains("scenarioStore")) {
            std::cout <<"LOL";
            server.scenarioStore = j_root["scenarioStore"];
        } 

        if (j_root.contains("taskStore")) {
            server.taskStore = j_root["taskStore"];
        } 
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error while loading from " << filename << ": " << e.what() << std::endl;
    } 
    
}