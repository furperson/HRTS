#include "Server/Server.hpp"

void Server::startServer(int argc, char* argv[]) {

    serverRunning = true;

    AddTaskCMD addTaskCMD;
    LoadDataFromFileCMD loadDataFromFileCMD;
    OffloadDataToFileCMD offloadDataToFileCMD;
    PrintScenarioCMD printScenarioCMD;
    ShowAllScenarioCMD showAllScenarioCMD;
    ShowAllTask showAllTask;
    StartTaskCMD startTaskCMD;

    addTaskCMD.AttachContext(AddTaskContext(ioUnit, scenarioStore, taskStore));
    loadDataFromFileCMD.AttachContext(LoadDataToFileContext(ioUnit, *this, persistenceManager));
    offloadDataToFileCMD.AttachContext(OffloadDataToFileContext(ioUnit, *this, persistenceManager));
    printScenarioCMD.AttachContext(PrntScenContext(ioUnit, scenarioStore));
    showAllScenarioCMD.AttachContext(ShowAllContext(ioUnit, scenarioStore));
    showAllTask.AttachContext(ShowAllTaskContext(ioUnit, taskStore));
    startTaskCMD.AttachContext(StartTaskContext(ioUnit, hwUnit, taskStore));

    interpetator.addCMD(addTaskCMD);
    interpetator.addCMD(loadDataFromFileCMD);
    interpetator.addCMD(offloadDataToFileCMD);
    interpetator.addCMD(printScenarioCMD);
    interpetator.addCMD(showAllScenarioCMD);
    interpetator.addCMD(showAllTask);
    interpetator.addCMD(startTaskCMD);

    ioUnit.addIStream(std::cin);
    ioUnit.addOStream(std::cout);

    // HARDWARE:
    BoardWrapper board1(52);
    BoardWrapper board2(42);
    this->hwUnit.addBoard(board1);
    this->hwUnit.addBoard(board2);

    while (serverRunning) {
        try {
            auto tmpCMD = PreParse(ioUnit.readLine());
            if(tmpCMD){
                interpetator.processCMD(*tmpCMD);
            }
            else {
                ioUnit.write("Ошибка в команде : "+tmpCMD.error());
            }
        } catch (const std::exception& e) {
            std::cerr << "Error while processing command: " << e.what() << std::endl;
        }
    }
}

Server::Server()
    : ioUnit(), hwUnit(), persistenceManager(), interpetator(ioUnit), serverRunning(false) {
}