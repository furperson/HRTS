#pragma once

#include <pqxx/pqxx>
#include <string>
#include <optional>

#include "Task.hpp"
#include "Scenario.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataBaseUnit {
private:
    pqxx::connection conn;
    void prepare_statements();

public:
    DataBaseUnit(const std::string& db_host, const std::string& db_port, const std::string& db_name,
        const std::string& db_user, const std::string& db_password);
    DataBaseUnit(const std::string& db_host, const std::string& db_port, const std::string& db_name,
            const std::string& db_user);
    ~DataBaseUnit();
    DataBaseUnit()  = delete;
    
    DataBaseUnit(const DataBaseUnit&) = delete;
    DataBaseUnit& operator=(const DataBaseUnit&) = delete;
    
    bool isConnected() const;


    std::string getUserPasswordHash(const std::string& username);

    bool saveScenario(std::string user,const Scenario& scenario);

    std::optional<Scenario> loadScenario(std::string user,const std::string& scenarioName); 

    bool saveTask(std::string user,const Task& task);

    std::optional<Task> loadTask(std::string user,const std::string& taskName); 

    
};