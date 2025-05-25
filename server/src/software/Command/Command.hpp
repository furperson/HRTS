#include<string>

#include "PreParser.hpp"

//абстрактный класс под передаваемый контекст в комманду
struct Context
{
    virtual ~Context();
    Context()=delete;
};



//Комманды совершают действие над 
class Command
{
    public:
    
    virtual const std::string getTitle()=0;
    virtual void getHelp()=0;
   
    virtual void Execute(ParsedCMD&) =0;

    virtual void AttachContext(Context&) =0;

    virtual ~Command();

};

