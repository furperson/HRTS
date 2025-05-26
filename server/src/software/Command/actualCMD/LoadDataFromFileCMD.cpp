#include "Command/actualCMD/LoadDataFromFileCMD.hpp"
#include "Server/Server.hpp"
#include "PersistenceManager/PersistenceManager.hpp"


void LoadDataFromFileCMD::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle() && cmd.args.size() == 1) {
        if (!(iounit == nullptr)) {
            meng->Load(*server,cmd.args[0]);
        }
    }
}

void LoadDataFromFileCMD::getHelp() {
    if (!(iounit == nullptr)) {
        iounit->write("загружает все данные из файла \n");
    }
}

std::string LoadDataFromFileCMD::getTitle() {
    return "LoadDataFromFile";
}

void LoadDataFromFileCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const LoadDataToFileContext&>(context);
    this->iounit = &(tmpContext.iounit);
    this->server = &(tmpContext.server);
    this->meng = &(tmpContext.meng);
}

LoadDataToFileContext::LoadDataToFileContext(IOunit& iounit,Server& server, PersistenceManager& meng):iounit(iounit),server(server),meng(meng){
    
};

LoadDataFromFileCMD::~LoadDataFromFileCMD() {};

LoadDataToFileContext::~LoadDataToFileContext() {};
