#include "Command/actualCMD/OffloadDataToFileCMD.hpp"

#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

void OffloadDataToFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 1) {
        if (!(iounit == nullptr)) {
            meng->Offload(*server, cmd.args[0]);
        }
    }
}

void OffloadDataToFileCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("Сохраняет данные контейнеров в файл \n");
    }
}

std::string OffloadDataToFileCMD::getTitle() {
    return "OffloadDataToFile";
}

void OffloadDataToFileCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const OffloadDataToFileContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->server = &(tmpContext.server);
    this->meng = &(tmpContext.meng);
}

OffloadDataToFileContext::OffloadDataToFileContext(IOunit& iounit, Server& server,
                                                   PersistenceManager& meng)
    : iounit(iounit), server(server), meng(meng) {

      };

OffloadDataToFileCMD::~OffloadDataToFileCMD() {};

OffloadDataToFileContext::~OffloadDataToFileContext() {};
