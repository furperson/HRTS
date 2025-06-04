#include "HwUnit/TaskWorker.hpp"

void TaskWorker::operator()(Task& task, BoardWrapper& board) const {

    time_t timestamp;

    task.setProcessingStartTime(timestamp);

    board.sRun.store(true);
    using namespace std::chrono_literals;
    // do something important
    for (int i = 0; i < 120; i++) {
        Sample smpl;
        task.artef.rawData.push_back(smpl);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(task.getScenario().getTestDurationMs()));
    time(&timestamp);
    task.setProcessingEndTime(timestamp);
    board.sRun.store(false);
    task.setState(TaskState::SUCCESS);
}

TaskWorker::TaskWorker(/* args */) {
}

TaskWorker::~TaskWorker() {
}
