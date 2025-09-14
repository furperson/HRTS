#include "CommandCli/actualCMD/headers/OffloadDataToFileCMD.hpp"

#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

void OffloadDataToFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        func.offloadServData(cmd.otherArgs[0]);
    }
}

OffloadDataToFileCMD::OffloadDataToFileCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli(
          "offload-file",
          "Команда offload-file сохраняет состояние сервера в файл \n offload-file <имя_файла>"),
      func(func), iounit(iounit) {};

OffloadDataToFileCMD::~OffloadDataToFileCMD() {};
