#include "BoardWrapper.hpp"
#include "Task.hpp"

#include <atomic>
#include <chrono>
#include <thread>

// Класс , обработчик задачи на плате
class TaskWorker {
  private:
    /* data */
  public:
    // функция , обработчик задания
    void operator()(Task& task, BoardWrapper& board) const;

    TaskWorker(/* args */);
    ~TaskWorker();
};