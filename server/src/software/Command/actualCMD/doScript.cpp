#include "Command/actualCMD/headers/doScript.hpp"

void doScript::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle()) {
        auto ifs = std::make_shared<std::ifstream>(cmd.otherArgs[0]);
        if (!ifs->is_open()) {
            iounit->write("Такого скрипта не существует!\n");
        return;
    }
        iounit->addIStream(ifs);
    }
}

void doScript::AttachContext(const Context& context) {
    auto& tmpContext = dynamic_cast<const doScriptContext&>(context);
    this->iounit = &(tmpContext.iounit);
}

doScript::doScript()
    : Command(
          "do-script",
          "Выполнить скрипт \n do-script <имя-скрипта>") {};

doScriptContext::doScriptContext(IOunit& iounit)
    : iounit(iounit) {

      };

doScript::~doScript() {};

doScriptContext::~doScriptContext() {};
