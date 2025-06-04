#pragma once

#include "BitArtif.hpp"
#include "Scenario.hpp"

#include <string>
#include <ctime>

enum class TaskState { IDLE, SUCCESS, IN_WORK, STOP_BY_USER, FAILED };

// Единица запуска сценария
class Task {
  private:
    Scenario scenario;
    TaskState state;
    time_t processingStartTime;
    time_t processingEndTime;
    std::string taskName;

  public:
    BitArtef artef;
    void setProcessingStartTime(const time_t&);
    const time_t& getProcessingStartTime() const;
    void setProcessingEndTime(const time_t&);
    const time_t& getProcessingEndTime() const;

    const BitArtef& getArtef() const;

    void setState(const TaskState&);
    const TaskState& getState() const;

    const Scenario& getScenario() const;
    const std::string& getTaskName() const;

    Task(const Scenario&,const std::string&);

    Task() = delete;
    ~Task() = default;
};
