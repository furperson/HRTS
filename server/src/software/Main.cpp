#include "Server/Server.hpp"



int main (int argc, char* argv[]) {
    // Устанавливаем обработчик для SIGINT
    signal(SIGINT, handle_sigint);
    std::cout <<"POLLL";
     
    std::string str;
    std::getline(std::cin, str);
    ParsedCMD pr = PreParse(str);
    for (; !pr.args.empty(); pr.args.pop_back())
        std::cout << pr.args.back() << std::endl;
    
    
    
}