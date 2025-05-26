#pragma once

#include "BitArtif.hpp"
#include "Scenario.hpp"

#include <ctime>

enum class TaskState { IDLE, SUCCESS, IN_WORK, STOP_BY_USER, FAILED };

// Единица запуска сценария
class Task {
  private:
    Scenario scenario;
    TaskState state;
    time_t processingStartTime;
    time_t processingEndTime;

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

    Task(const Scenario&);

    Task() = delete;
    ~Task() = default;
};
