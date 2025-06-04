#pragma once

#include <atomic>
#include <string>
#include <mutex>

// обёртка , абстракция над физическим устройством(плате fpga)

enum class BoardState { IDLE, IN_WORK, DISABLED };

class BoardWrapper {
  private:
    BoardState boardState;
    int port;
    std::string boardName;

  public:
    std::atomic<bool> sRun;
    std::mutex boarsMutex;
    BoardWrapper() = delete;
    BoardWrapper(int);
    BoardWrapper(int, std::string);
    ~BoardWrapper();
};
