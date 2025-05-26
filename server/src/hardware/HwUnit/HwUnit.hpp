#pragma once

#include <vector>
#include <queue>

#include "Task.hpp"
#include "BoardWrapper.hpp"
#include "HwUnit/HwOrbitor.hpp"
#include <algorithm>


// принимает 
class HwUnit 
{
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
