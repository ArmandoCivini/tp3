#include "client_protocolo.h"
#include "common_protocolo.h"
#include "client_sockt.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#define ACCION_POS 0
#define INT16 2
#define LEN_POS 1
#define HEAD_TAM 3
#define DOBLE_HEAD_TAM 5

#define DEFINE 'd'
#define PUSH 'u'
#define POP 'o'

ProtocoloCliente::ProtocoloCliente(){
}


int ProtocoloCliente::construirMensajeCola
(char accion, const std::string& cola, std::vector<char>& mensaje){
    uint16_t largo = cola.length();
    mensaje.resize(largo+HEAD_TAM);
    mensaje[ACCION_POS] = accion;
    std::vector<char> cola_v(cola.begin(), cola.end());
    Protocolo::agregarString(largo, &mensaje[LEN_POS], cola_v);
    return largo+HEAD_TAM;
}

int ProtocoloCliente::construirMensajeDefinir(const std::string& cola, std::vector<char>& mensaje){
    return construirMensajeCola(DEFINE, cola, mensaje);
}

int ProtocoloCliente::construirMensajePush
(const std::string& cola, const std::string& a_escribir, std::vector<char>& mensaje){
    uint16_t largo_cola = cola.length();
    uint16_t largo_a_escribir = a_escribir.length();
    mensaje.resize(largo_cola+largo_a_escribir+DOBLE_HEAD_TAM);
    mensaje[ACCION_POS] = PUSH;
    std::vector<char> cola_v(cola.begin(), cola.end());
    Protocolo::agregarString(largo_cola, &mensaje[LEN_POS], cola_v);
    std::vector<char> a_escribir_v(a_escribir.begin(), a_escribir.end());
    Protocolo::agregarString(largo_a_escribir, &mensaje[largo_cola+HEAD_TAM], a_escribir_v);
    return largo_cola+largo_a_escribir+DOBLE_HEAD_TAM;
}

int ProtocoloCliente::construirMensajePop(const std::string& cola, std::vector<char>& mensaje){
    return construirMensajeCola(POP, cola, mensaje);
}

void ProtocoloCliente::leerMensaje(ClientSocket& skt){
    std::string a_imprimir =  Protocolo::leerMensaje(skt);
    if (a_imprimir.empty()) return;
    a_imprimir.pop_back(); //para que no imprima '\0'
    std::cout << a_imprimir << "\n";
}

void ProtocoloCliente::enviarMensajePop(const std::string& cola, ClientSocket& skt){
    std::vector<char> mensaje;
    int largo = construirMensajePop(cola, mensaje);
    skt.write(mensaje.data(), largo);
}

void ProtocoloCliente::enviarMensajePush
(const std::string& cola, const std::string& a_escribir, ClientSocket& skt){
    std::vector<char> mensaje;
    int largo = construirMensajePush(cola, a_escribir, mensaje);
    skt.write(mensaje.data(), largo);
}

void ProtocoloCliente::enviarMensajeDefinir(const std::string& cola, ClientSocket& skt){
    std::vector<char> mensaje;
    int largo = construirMensajeDefinir(cola, mensaje);
    skt.write(mensaje.data(), largo);
}

ProtocoloCliente::~ProtocoloCliente(){
}
