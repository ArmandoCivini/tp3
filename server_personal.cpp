#include "server_personal.h"
#include "server_protocolo.h"
#include "server_queueumanager.h"
#include <utility>
#include <string>

#define FAIL 'f'
#define DEFINE 'd'
#define PUSH 'u'


Personal::Personal(Socket skt, QueueManager& colas)
: skt(std::move(skt)), colas(colas){
}

void Personal::definirCola(){
    std::string cola = protocolo.leerMensaje(skt);

    colas.nuevaQueue(cola);
}

void Personal::pushCola(){
    std::string cola = protocolo.leerMensaje(skt);
    std::string mensaje = protocolo.leerMensaje(skt);

    colas.pushIn(cola, mensaje);
}

void Personal::popCola(){
    std::string nombre = protocolo.leerMensaje(skt);
    std::string mensaje = colas.popIn(nombre);
    protocolo.crearMensaje(mensaje.length()-1, mensaje, skt);
}

bool Personal::leerIntencion(){
    char accion = protocolo.leerAccion(skt);
    if (accion == FAIL) return false;

    if (accion==DEFINE){
        definirCola();
    } else if (accion==PUSH){
        pushCola();
    } else{
        popCola();
    }
    return true;
}

void Personal::atender(){
    while (leerIntencion()){}
}

Personal::~Personal(){
}
