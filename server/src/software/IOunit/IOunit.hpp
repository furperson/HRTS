#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// - получает input/output поток данных и реализует логику работы с ним

class IOunit {
  private:
    std::vector<std::shared_ptr<std::istream>> INstreams;
    std::vector<std::shared_ptr<std::ostream>> OUTstreams;

  public:
    bool addIStream(std::shared_ptr<std::istream>);
    bool addOStream(std::shared_ptr<std::ostream>);

    void write(std::string);
    // std::ostream popOUTstream();

    std::string readLine();
    // std::istream popINstream();
};

class BadIStream_error : public std::exception {
  public:
    BadIStream_error(const std::string& message) : message{message} {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }

  private:
    std::string message;
};