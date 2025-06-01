#pragma once

#include "Command/Command.hpp"
#include "IOunit/IOunit.hpp"
#include "Task.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

class ShowAllTask : public Command {
  private:
    /* data */
    IOunit* iounit = nullptr;
    std::vector<Task>* taskStore = nullptr;

    std::map<TaskState, std::string> stateToString = {{TaskState::IDLE, "IDLE"},
                                                      {TaskState::SUCCESS, "SUCCESS"},
                                                      {TaskState::IN_WORK, "IN_WORK"},
                                                      {TaskState::STOP_BY_USER, "STOP_BY_USER"},
                                                      {TaskState::FAILED, "FAILED"}};

  public:

    void AttachContext(const Context&) override;

    void Execute(ParsedCMD&) override;
    ShowAllTask() = default;
    ~ShowAllTask() override;
};

struct ShowAllTaskContext : public Context {
    ShowAllTaskContext(IOunit&, std::vector<Task>&);
    IOunit& iounit;
    std::vector<Task>& taskStore;
    ~ShowAllTaskContext() override;
    ShowAllTaskContext() = delete;
};
