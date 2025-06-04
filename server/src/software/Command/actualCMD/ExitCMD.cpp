#include "Command/actualCMD/headers/ExitCMD.hpp"

void ExitCMD::Execute(ParsedCMD& cmd) {
    if (persistenceManager != nullptr) {
        if (std::find(cmd.secArgs.begin(), cmd.secArgs.end(), "S") != cmd.secArgs.end()) {
            persistenceManager->Offload("backup");
        }
        std::exit(0);
    }
}

void ExitCMD::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const ExitContext&>(context);
    this->persistenceManager = &(tmpContext.persistenceManager);
}

ExitCMD::ExitCMD()
    : Command("exit", "команда exit выходит из программы \n"
                      "--S - выход с сохранением данных(файл рядом \"backup\")") {};

ExitCMD::~ExitCMD() {};

ExitContext::ExitContext(PersistenceManager& persistenceManager)
    : persistenceManager(persistenceManager) {};

ExitContext::~ExitContext() {};