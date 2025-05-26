
#pragma once

#include "Task.hpp"       

#include <nlohmann/json.hpp>


namespace nlohmann {

    NLOHMANN_JSON_SERIALIZE_ENUM(TaskState, {
        {TaskState::IDLE, "IDLE"},
        {TaskState::SUCCESS, "SUCCESS"},
        {TaskState::IN_WORK, "IN_WORK"},
        {TaskState::STOP_BY_USER, "STOP_BY_USER"},
        {TaskState::FAILED, "FAILED"}
    })

    template <>
    struct adl_serializer<Task> {
        static void to_json(json& j, const Task& t) {
            j = json{
                {"scenario", t.getScenario()},
                {"state", t.getState()},
                {"artefact", t.getArtef()},          
                {"processingStartTime", nullptr},
                {"processingEndTime", nullptr}
            };

            time_t startTime = t.getProcessingStartTime();
            if (startTime != static_cast<time_t>(0)) {
                j["processingStartTime"] = startTime;
            }

            time_t endTime = t.getProcessingEndTime();
            if (endTime != static_cast<time_t>(0)) {
                j["processingEndTime"] = endTime;
            }
        }

        static Task from_json(const json& j) {
            Scenario scenario = j.at("scenario").get<Scenario>();
            Task task(scenario);

            task.setState(j.value("state", TaskState::IDLE));

            if (j.contains("artefact")) {

            }

            time_t startTime = 0;
            if (j.contains("processingStartTime") && !j.at("processingStartTime").is_null()) {
                startTime = j.at("processingStartTime").get<time_t>();
            }
            task.setProcessingStartTime(startTime);

            time_t endTime = 0;
            if (j.contains("processingEndTime") && !j.at("processingEndTime").is_null()) {
                endTime = j.at("processingEndTime").get<time_t>();
            }
            task.setProcessingEndTime(endTime);

            return task;
        }
    };

} 


