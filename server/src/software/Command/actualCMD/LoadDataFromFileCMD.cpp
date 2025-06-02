#include "Command/actualCMD/headers/LoadDataFromFileCMD.hpp"

#include "PersistenceManager/PersistenceManager.hpp"
#include "Server/Server.hpp"

void LoadDataFromFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.otherArgs.size() == 1) {
        if (!(iounit == nullptr)) {
            meng->Load(*server, cmd.otherArgs[0]);
        }
    }
}


void LoadDataFromFileCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const LoadDataToFileContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->server = &(tmpContext.server);
    this->meng = &(tmpContext.meng);
}

LoadDataToFileContext::LoadDataToFileContext(IOunit& iounit, Server& server,
                                             PersistenceManager& meng)
    : iounit(iounit), server(server), meng(meng) {

      };

LoadDataFromFileCMD::~LoadDataFromFileCMD() {};

LoadDataToFileContext::~LoadDataToFileContext() {};
