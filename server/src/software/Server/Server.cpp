#include "Server/Server.hpp"

void Server::startServer(int argc, char* argv[]) {

    serverRunning = true;

    addTaskCMD.AttachContext(AddTaskContext(ioUnit, scenarioStore, taskStore));
    loadDataFromFileCMD.AttachContext(LoadDataToFileContext(ioUnit, *this, persistenceManager));
    offloadDataToFileCMD.AttachContext(OffloadDataToFileContext(ioUnit, *this, persistenceManager));
    printScenarioCMD.AttachContext(PrntScenContext(ioUnit, scenarioStore));
    showAllScenarioCMD.AttachContext(ShowAllContext(ioUnit, scenarioStore));
    showAllTask.AttachContext(ShowAllTaskContext(ioUnit, taskStore));
    startTaskCMD.AttachContext(StartTaskContext(ioUnit, hwUnit, taskStore));
    allHelpCMD.AttachContext(AllHelpContext(ioUnit, interpetator));
    exitCMD.AttachContext(ExitContext(persistenceManager));
    scenarioMakeCMD.AttachContext(ScenarioMakeContext(ioUnit, scenarioStore));
    doscript.AttachContext(doScriptContext(ioUnit));

    interpetator.addCMD(allHelpCMD);
    interpetator.addCMD(addTaskCMD);
    interpetator.addCMD(loadDataFromFileCMD);
    interpetator.addCMD(offloadDataToFileCMD);
    interpetator.addCMD(printScenarioCMD);
    interpetator.addCMD(showAllScenarioCMD);
    interpetator.addCMD(showAllTask);
    interpetator.addCMD(startTaskCMD);
    interpetator.addCMD(exitCMD);
    interpetator.addCMD(scenarioMakeCMD);
    interpetator.addCMD(doscript);

    ioUnit.addIStream(std::shared_ptr<std::istream>(&std::cin,[](std::istream*){}));
    ioUnit.addOStream(std::shared_ptr<std::ostream>(&std::cout,[](std::ostream*){}));

    // HARDWARE:
    BoardWrapper board1(52);
    BoardWrapper board2(42);
    this->hwUnit.addBoard(board1);
    this->hwUnit.addBoard(board2);

    while (serverRunning) {
        try {
            auto tmpCMD = PreParse(ioUnit.readLine());
            if (tmpCMD) {
                interpetator.processCMD(*tmpCMD);
            } else {
                ioUnit.write("Ошибка в команде около: " + tmpCMD.error() + "\n");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error while processing command: " << e.what() << std::endl;
        }
    }
}

Server::Server()
    : ioUnit(), hwUnit(), persistenceManager(*this), interpetator(ioUnit), serverRunning(false) {
}