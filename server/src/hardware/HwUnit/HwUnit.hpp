#pragma once

#include "BoardWrapper.hpp"
#include "HwUnit/HwOrbitor.hpp"
#include "Task.hpp"

#include <algorithm>
#include <queue>
#include <vector>

// принимает
class HwUnit {
  private:
    std::vector<Task> taskQueue;
    std::vector<BoardWrapper*> boards;
    HwOrbitor orbitor;

  public:
    void startOrbitor();
    void putTask(Task&);
    void addBoard(BoardWrapper&);
    HwUnit() = default;
    ~HwUnit() = default;
};
