#include "client_admin.h"
#include "client_protocolo.h"
#include "client_sockt.h"
#include <iostream>
#include <sstream>

#define ARG_ESPERADOS 3
#define RUN_ERROR 2
#define ARG_ERROR 1
#define NO_ERROR 0
#define HOST 1
#define PORT 2

#define ARG_ERROR_S "argumentos insuficientes"

int main(int argc, char *argv[]){
    if (argc < ARG_ESPERADOS){
        perror(ARG_ERROR_S);
        return ARG_ERROR;
    }
    try{
        ProtocoloCliente proto;
        std::string linea;
        Admin admin(argv[HOST], argv[PORT]);
        bool termino = true;
        while (termino && std::getline(std::cin, linea)){
            termino = admin.operar(linea);
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return RUN_ERROR;
    }
    return NO_ERROR;
}
