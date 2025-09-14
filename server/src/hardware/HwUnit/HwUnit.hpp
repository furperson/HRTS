#pragma once

#include "BoardWrapper.hpp"
#include "HwUnit/HwOrbitor.hpp"
#include "Task.hpp"

#include <algorithm>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// принимает
class HwUnit {
  private:
    std::vector<Task> taskQueue;
    std::vector<BoardWrapper*> boards;
    HwOrbitor orbitor;
    std::mutex taskQueueMutex;
    std::mutex boardsMutex;

  public:
    void startOrbitor();
    void putTask(Task&);
    void addBoard(BoardWrapper&);
    void removeBoard(BoardWrapper&);

    bool close(); // функция для корректного завершения работы HwUnit
    HwUnit() = default;
    ~HwUnit() = default;
};
