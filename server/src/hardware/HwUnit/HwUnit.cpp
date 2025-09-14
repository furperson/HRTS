#include "HwUnit/HwUnit.hpp"

// std::ref(data)
// std::thread t(update_data_for_widget,w,std::ref(data));

void HwUnit::putTask(Task& task) {
    // taskQueue.push_back(task);
    // PLACEHOLDER
    time_t timestamp;
    time(&timestamp);
    for (int i = 0; i < 120; i++) {
        Sample smpl;
        task.artef.rawData.push_back(smpl);
    }
    task.setProcessingStartTime(timestamp);
    task.setProcessingEndTime(timestamp);
    task.setState(TaskState::SUCCESS);
};

void HwUnit::addBoard(BoardWrapper& boardWrapper) {
    if (std::find(boards.begin(), boards.end(), &boardWrapper) != boards.end()) {
        boards.push_back(&boardWrapper);
    }
};