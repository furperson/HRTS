#pragma once

#include <vector>
#include <queue>

#include "Task.hpp"
#include "BoardWrapper.hpp"
#include "HwOrbitor.hpp"


// принимает 
class HwUnit 
{
private:
    std::vector<Task> taskQueue;
    std::vector<BoardWrapper> boards;
    HwOrbitor orbitor;
public:
    void putTask(Task);
    void addBoard(BoardWrapper);
    HwUnit(/* args */);
    ~HwUnit();
};
