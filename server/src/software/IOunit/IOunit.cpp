#include "IOunit.hpp"
#include <algorithm>


//Главная цель наследников данного класса  - работа с различным потоками ввода/вывода 

bool IOunit::addIStream (std::istream& Istream){
    if (!Istream.good() || std::find(INstreams.begin(), INstreams.end(), &Istream)!= INstreams.end()) { 
        return false; 
        //Идея - сделать более понятные значение возврата (возвращать исключения будет так себе, это относитльно ожидаемые ситуации)
    }

    INstreams.push_back(&Istream);
    return true;

}

bool IOunit::addOStream (std::ostream& Ostream){
    if (!Ostream.good() || std::find(OUTstreams.begin(), OUTstreams.end(), &Ostream) != OUTstreams.end()) { 
        return false; 
        //Идея - сделать более понятные значение возврата (возвращать исключения будет так себе, это относитльно ожидаемые ситуации)
    }
    OUTstreams.push_back(&Ostream);
    return true;
}

void IOunit::write(std::string str){
    *OUTstreams.back() << str;
}

std::string IOunit::readLine(){

    if(INstreams.size()>0){
    std::string TMPstr; 
    std::getline(*INstreams.back(),TMPstr);

    if((*INstreams.back()).eof()) {
        if(INstreams.size()==1){
            this->write("Программа завершена...");
            exit(0);
        }
        INstreams.pop_back();
    }

    if((*INstreams.back()).bad()) {
        throw BadIStream_error("В потоке взведён badbit, поток убран") ;
        INstreams.pop_back();
        
    }

    if((*INstreams.back()).fail()) {
        (*INstreams.back()).clear();
        throw BadIStream_error("В потоке взвёлся failbit ") ;
        
    }
    return TMPstr;
}
return "";
}