#include "DataBaseUnit.hpp"

#include <iostream>

DataBaseUnit::DataBaseUnit(const std::string& db_host, const std::string& db_port,
                           const std::string& db_name, const std::string& db_user,
                           const std::string& db_password)
    : conn("dbname=" + db_name + " user=" + db_user + " password=" + db_password +
           " host=" + db_host + " port=" + db_port) {
    prepare_statements();
};

DataBaseUnit::DataBaseUnit(const std::string& db_host, const std::string& db_port,
                           const std::string& db_name, const std::string& db_user)
    : conn("dbname=" + db_name + " user=" + db_user + " host=" + db_host + " port=" + db_port) {
    prepare_statements();
};

std::string DataBaseUnit::getUserPasswordHash(const std::string& username) {
    try {
        pqxx::work W(conn);

        pqxx::result R =
            W.exec("SELECT password_hash FROM users WHERE username = '" + username + "';  ");
        if (R.empty()) {
            return "";
        }
        auto row = R[0];
        return row["password_hash"].as<std::string>();
        W.commit();
    } catch (const std::exception& e) {
        throw e;
    }
};

bool DataBaseUnit::saveScenario(std::string user, const Scenario& scenario) {
    try {
        pqxx::work W(conn);

        W.exec_prepared("upsert_scenario", scenario.getScenarioName(), scenario.getOwnername(),
                        scenario.getTestDurationMs(), scenario.getStopScenarioPin(),
                        static_cast<json>(scenario.getPinNaming()).dump(), scenario.getFpgaFirmwareName(),
                        static_cast<json>( scenario.getPinScanEnable()).dump());

        W.commit();
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
};

std::optional<Scenario> DataBaseUnit::loadScenario(std::string user, const std::string& scenarioName) {
    try {
        pqxx::work W(conn);

        pqxx::result R = W.exec_prepared("get_scenario", user, scenarioName);

            if (R.empty()) {
                return std::nullopt;
            }

            auto row = R[0];
            return Scenario{
                row["scenario_name"].as<std::string>(),
                row["test_duration_ms"].as<int>(),
                row["stop_scenario_pin"].as<int>(),
                row["fpga_firmware_name"].as<std::string>(),
                static_cast<std::array<bool, 64>>( json::parse(row["pin_scan_enable"].as<std::string>())),
                static_cast<std::vector<PinBusGroup>>( json::parse( row["pinbusgroup"].as<std::string>())),
                row["owner_name"].as<std::string>()
            };

                

    } catch (const std::exception& e) {
        return std::nullopt;
    }
};

bool DataBaseUnit::saveTask(std::string user, const Task& task) {
    try {
        pqxx::work W(conn);

        W.exec_prepared("upsert_task", task.getTaskName(), task.getOwnername(),
                        task.getScenario().getScenarioName(), static_cast<int>(task.getState()),
                        static_cast<json>(task.getArtef()).dump(), task.getProcessingStartTime(),
                        task.getProcessingEndTime());
        W.commit();
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
};

std::optional<Task> DataBaseUnit::loadTask(std::string user, const std::string& taskName) {
    try {
        pqxx::work W(conn);

        pqxx::result R = W.exec_prepared("get_task", user, taskName);

            if (R.empty()) {
                return std::nullopt;
            }

            auto row = R[0];

            auto at = loadScenario(user,row["scenario_name"].as<std::string>());
            if(at){

                Task ts = Task{
                    at.value(),
                    row["task_name"].as<std::string>(),
                    row["owner_name"].as<std::string>()};

                    ts.setState( TaskState{row["state"].as<int>()});
                    ts.artef = static_cast<BitArtef>(json::parse(row["bitartef"].as<std::string>()));
                    ts.setProcessingStartTime(row["processing_start_time"].as<time_t>());
                    ts.setProcessingEndTime(row["processing_end_time"].as<time_t>());
                    return ts;
            }
            else {
                return std::nullopt;
            }

    } catch (const std::exception& e) {
        return std::nullopt;
    }
};

void DataBaseUnit::prepare_statements() {

    conn.prepare("upsert_scenario", R"(
        INSERT INTO scenarios (
            scenario_name, owner_name, test_duration_ms, stop_scenario_pin,
            PinBusGroup, fpga_firmware_name, pin_scan_enable
        ) VALUES ($1, $2, $3, $4, $5, $6, $7)
        ON CONFLICT (scenario_name, owner_name) DO UPDATE SET
            test_duration_ms = EXCLUDED.test_duration_ms,
            stop_scenario_pin = EXCLUDED.stop_scenario_pin,
            PinBusGroup = EXCLUDED.PinBusGroup,
            fpga_firmware_name = EXCLUDED.fpga_firmware_name,
            pin_scan_enable = EXCLUDED.pin_scan_enable;
    )");

    conn.prepare("get_scenario", R"(
        SELECT * FROM scenarios
        WHERE owner_name = $1 AND scenario_name = $2;
    )");

    conn.prepare("upsert_task", R"(
        INSERT INTO tasks (
            task_name, owner_name, scenario_name, state,
            BitArtef, processing_start_time, processing_end_time
        ) VALUES ($1, $2, $3, $4, $5, $6, $7)
        ON CONFLICT (task_name, owner_name) DO UPDATE SET
            scenario_name = EXCLUDED.scenario_name,
            state = EXCLUDED.state,
            BitArtef = EXCLUDED.BitArtef,
            processing_start_time = EXCLUDED.processing_start_time,
            processing_end_time = EXCLUDED.processing_end_time;
    )");

    conn.prepare("get_task", R"(
        SELECT * FROM tasks
        WHERE owner_name = $1 AND task_name = $2;
    )");
}

DataBaseUnit::~DataBaseUnit() {};