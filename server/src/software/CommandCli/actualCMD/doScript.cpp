#include "CommandCli/actualCMD/headers/doScript.hpp"

void doScript::Execute(ParsedCMD& cmd) {
    if (cmd.title == this->getTitle()) {
        func.doScript(cmd.otherArgs[0]);
    }
}

doScript::doScript(InnerFunction& func, IOunit& iounit)
    : CommandCli("do-script", "Выполнить скрипт \n do-script <имя-скрипта>"), func(func),
      iounit(iounit) {};

doScript::~doScript() {};
