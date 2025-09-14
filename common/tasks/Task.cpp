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
const time_t& Task::getProcessingEndTime() const { // TODO прочекать УБ , добавить const &
    return processingEndTime;
};

const BitArtef& Task::getArtef() const {
    return artef;
};
const std::string& Task::getOwnername() const {
    return Owner_name_;
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

const std::string& Task::getTaskName() const {
    return taskName;
};

Task::Task(const Scenario& scenario, const std::string& taskName, const std::string& Owner_name_)
    : scenario(scenario), taskName(taskName), Owner_name_(Owner_name_) {
    this->state = TaskState::IDLE;
};