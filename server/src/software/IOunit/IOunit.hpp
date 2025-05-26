#pragma once

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>


// - получает input/output поток данных и реализует логику работы с ним 

class IOunit
{
private:
    std::vector<std::istream*> INstreams;
    std::vector<std::ostream*> OUTstreams; 
public:
    bool addIStream (std::istream&);
    bool addOStream (std::ostream&);

    void write(std::string);
    std::ostream popOUTstream();

    std::string readLine();
    std::istream popINstream();
};


class BadIStream_error : public std::exception
{
    public:
    BadIStream_error(const std::string& message): message{message}
    {}
    const char* what() const noexcept override
    {
        return message.c_str();    
    }
private:
    std::string message;    
};