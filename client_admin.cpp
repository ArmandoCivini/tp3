#include "client_admin.h"
#include "client_protocolo.h"
#include "client_sockt.h"
#include <iostream>
#include <sstream>
#include <string>

#define DEFINE_S "define"
#define PUSH_S "push"
#define POP_S "pop"
#define EXIT_S "exit"
#define ERROR_COMMANDO "commando incorrecto"

Admin::Admin(char *host, char *port): skt(host, port){
}

void Admin::definir(std::string cola){
    protocolo.enviarMensajeDefinir(cola, skt);
}

void Admin::push(std::string cola, std::string a_escribir){
    protocolo.enviarMensajePush(cola, a_escribir, skt);
}

void Admin::pop(std::string cola){
    protocolo.enviarMensajePop(cola, skt);
    protocolo.leerMensaje(skt);
}

bool Admin::operar(std::string commando){
    std::istringstream stream(commando);
    std::string accion;
    std::getline(stream, accion, ' ');
    std::string cola;
    std::getline(stream, cola, ' ');
    if (accion == DEFINE_S){
        definir(cola);
        return true;
    } else if (accion == PUSH_S){
        std::string mensaje;
        std::getline(stream, mensaje, ' ');
        push(cola, mensaje);
        return true;
    } else if (accion == POP_S){
        pop(cola);
        return true;
    } else if (accion == EXIT_S){
        return false;
    }
    perror(ERROR_COMMANDO);
    return true; 
}

Admin::~Admin(){
}
