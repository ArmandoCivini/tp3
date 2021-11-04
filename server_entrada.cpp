#include "common_sockt.h"
#include "server_protocolo.h"
#include "server_sockt.h"
#include "server_queueumanager.h"
#include "server_personal.h"
#include "server_server.h"
#include <thread>
#include <iostream>
#include <fstream> 

#define ARG_ESPERADOS 2
#define RUN_ERROR 2
#define ARG_ERROR 1
#define NO_ERROR 0
#define PORT 1
#define MAX_Q 5

#define FAIL 'f'
#define DEFINE 'd'
#define PUSH 'u'
#define QUIT 'q'

#define ARG_ERROR_S "argumentos insuficientes"

int main(int argc, char *argv[]){
    if (argc < ARG_ESPERADOS){
        perror(ARG_ERROR_S);
        return ARG_ERROR;
    }
    try{
        Server server(argv[PORT], MAX_Q);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return RUN_ERROR;
    }
    return NO_ERROR;
}
