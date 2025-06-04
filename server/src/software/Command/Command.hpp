#pragma once
#include "PreParser.hpp"

#include <string>

// абстрактный класс под передаваемый контекст в комманду
struct Context {
    virtual ~Context();
    // Context()=delete;
};

// Комманды совершают действие над
class Command {
  private:
    std::string CMDtitle;
    std::string CMDhelp;

  public:
    virtual const std::string getTitle();
    virtual const std::string getHelp();

    virtual void Execute(ParsedCMD&) = 0;

    virtual void AttachContext(const Context&) = 0;

    Command(std::string CMDtitle, std::string CMDhelp);
    virtual ~Command();
};

class InvalidArgsCMD : public std::exception {
  public:
    InvalidArgsCMD(const std::string& message) : message{message} {};

    const char* what() const noexcept override {
        return message.c_str(); // МБ ОШИБКА
    };

  private:
    std::string message;
};
