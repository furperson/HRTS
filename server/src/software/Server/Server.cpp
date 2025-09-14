#include "Server/Server.hpp"

void Server::initClientHandlers(int port) {
    if (!clientU.start_listening(port)) {
        ioUnit.write("Сервер не подключен , работа невозможна.");
        exit(1);
    }
};

void Server::init(int port) {
    serverStatus.store(ServerStatus::SERVER_READY);
    initCli();
    initClientHandlers(port);
    // HARDWARE:
    BoardWrapper board1(52);
    BoardWrapper board2(42);
    this->hwUnit.addBoard(board1);
    this->hwUnit.addBoard(board2);
};

void Server::initCli() {
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

    interpetator.addCMD(dbloadTaskCMD);
    interpetator.addCMD(dboffloadTaskCMD);
    interpetator.addCMD(dbloadScenarioCMD);
    interpetator.addCMD(dboffloadScenarioCMD);

    ioUnit.addIStream(std::shared_ptr<std::istream>(&std::cin, [](std::istream*) {}));
    ioUnit.addOStream(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream*) {}));
    // TODO unique ptr
}

void Server::startServer(int argc, char* argv[]) {

    serverStatus.store(ServerStatus::SERVER_RUNNING);

    while (serverStatus.load() == ServerStatus::SERVER_RUNNING) {
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

Server::Server(int argc, char* argv[])
    : ioUnit(), hwUnit(), persistenceManager(*this), interpetator(ioUnit),
      dataBaseUnit(argv[2], argv[3], argv[4], argv[5]), serverStatus(ServerStatus::SERVER_READY),
      func(*this, taskStore, scenarioStore, ioUnit, hwUnit, persistenceManager, interpetator,
           dataBaseUnit),
      addTaskCMD(func, ioUnit), loadDataFromFileCMD(func, ioUnit),
      offloadDataToFileCMD(func, ioUnit), printScenarioCMD(func, ioUnit),
      showAllScenarioCMD(func, ioUnit), showAllTask(func, ioUnit), startTaskCMD(func, ioUnit),
      allHelpCMD(func, ioUnit, interpetator), exitCMD(func), scenarioMakeCMD(func, ioUnit),
      doscript(func, ioUnit), clientU(func), dbloadTaskCMD(func, scenarioStore, taskStore, ioUnit),
      dboffloadTaskCMD(func, scenarioStore, taskStore, ioUnit),
      dbloadScenarioCMD(func, scenarioStore, taskStore, ioUnit),
      dboffloadScenarioCMD(func, scenarioStore, taskStore, ioUnit) {
}