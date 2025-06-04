#include "Command/actualCMD/headers/OffloadDataToFileCMD.hpp"

#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

void OffloadDataToFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        if (!(iounit == nullptr)) {
            meng->Offload(cmd.otherArgs[0]);
        }
    }
}

void OffloadDataToFileCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const OffloadDataToFileContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->server = &(tmpContext.server);
    this->meng = &(tmpContext.meng);
}

OffloadDataToFileCMD::OffloadDataToFileCMD()
    : Command(
          "offload-file",
          "Команда offload-file сохраняет состояние сервера в файл \n offload-file <имя_файла>") {};

OffloadDataToFileContext::OffloadDataToFileContext(IOunit& iounit, Server& server,
                                                   PersistenceManager& meng)
    : iounit(iounit), server(server), meng(meng) {

      };

OffloadDataToFileCMD::~OffloadDataToFileCMD() {};

OffloadDataToFileContext::~OffloadDataToFileContext() {};
