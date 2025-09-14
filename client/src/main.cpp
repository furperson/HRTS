#include "Client/Client.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    if(argc<2){
        exit(1);
        std::cout <<"мало аргументов! необходимо : \n username ";
    }
    Client client(argv[1]);
    

    client.initCli();
    client.run();
}