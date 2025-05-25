#include "Task.hpp"

void Task::setProcessingStartTime(const time_t& processingStartTime) {
    this->processingStartTime = processingStartTime;
};
const time_t& Task::getProcessingStartTime() const {
    return processingStartTime;
};
void Task::setProcessingEndTime(const time_t& processingEndTime) {
    this->processingEndTime = processingEndTime;
};
const time_t& Task::getProcessingEndTime() const {
    return processingEndTime;
};

const BitArtef& Task::getArtef() const {
    return artef;
};

void Task::setState(const TaskState& state) {
    this->state = state;
};
const TaskState& Task::getState() const {
    return state;
};

const Scenario& Task::getScenario() const {
    return scenario;
};

Task::Task(const Scenario& scenario) : scenario(scenario) {
    this->state = TaskState::IDLE;
};