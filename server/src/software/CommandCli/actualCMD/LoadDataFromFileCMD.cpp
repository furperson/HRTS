#include "CommandCli/actualCMD/headers/LoadDataFromFileCMD.hpp"

#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

void LoadDataFromFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        func.loadServData(cmd.otherArgs[0]);
    }
}

LoadDataFromFileCMD::LoadDataFromFileCMD(InnerFunction& func, IOunit& iounit)
    : CommandCli(
          "load-file",
          "Команда load-file загружает всё состояние сервера из файла \n load-file <имя_файла>"),
      func(func), iounit(iounit) {};

LoadDataFromFileCMD::~LoadDataFromFileCMD() {};
