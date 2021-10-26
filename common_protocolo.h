#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <stdint.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#define INT16 2


class Protocolo
{
private:
protected:
    uint16_t largo_mensaje;
    uint16_t char2toInt16(char *numero);
    void int16toChar2(uint16_t numero, char caracteres[INT16]);
    void agregarString(int largo, char *destino, char *mensaje);
public:
    Protocolo();
    uint16_t largoMensaje(char mensaje[INT16]);
    void decifrar(char *mensaje);
    std::string mensaje(char *mensaje);
    ~Protocolo();
};

Protocolo::Protocolo(){
}

uint16_t Protocolo::char2toInt16(char numero[INT16]){
    uint16_t num = numero[0] | numero[1] << 8;
    return ntohs(num);
}

void Protocolo::int16toChar2(uint16_t numero, char caracteres[2]){
    numero = htons(numero);
    caracteres[0] = numero >> 8; 
    caracteres[1] = 0xFF & numero; 
}

uint16_t Protocolo::largoMensaje(char mensaje[INT16]){
    largo_mensaje = char2toInt16(mensaje);
    return largo_mensaje;
}

std::string Protocolo::mensaje(char *mensaje){
    mensaje[largo_mensaje] = '\0';
    return std::string(mensaje);
}

void Protocolo::agregarString(int largo, char *destino, char *mensaje){
    int16toChar2(largo, destino);
    strncpy(&destino[2], mensaje, largo);
}

Protocolo::~Protocolo()
{
}

class ProtocoloCliente : public Protocolo
{
private:
    void agregarString(int largo, char *destino, char *mensaje);
    int construirMensajeCola(char accion, char *cola, char **mensaje);
public:
    ProtocoloCliente();
    int construirMensajeDefinir(char *cola, char **mensaje);
    int construirMensajePush(char *cola, char *a_escribir, char **mensaje);
    int construirMensajePop(char *cola, char **mensaje);
    ~ProtocoloCliente();
};

ProtocoloCliente::ProtocoloCliente(){
}


int ProtocoloCliente::construirMensajeCola(char accion, char *cola, char **mensaje){
    uint16_t largo = strlen(cola);
    char *men = (char *)malloc(sizeof(char)*(largo+3));
    men[0] = accion;
    Protocolo::agregarString(largo, &men[1], cola);
    *mensaje = men;
    return largo+3;
}

int ProtocoloCliente::construirMensajeDefinir(char *cola, char **mensaje){
    return construirMensajeCola('d', cola, mensaje);
}

int ProtocoloCliente::construirMensajePush(char *cola, char *a_escribir, char **mensaje){
    uint16_t largo_cola = strlen(cola);
    uint16_t largo_a_escribir = strlen(a_escribir);
    char *men = (char *)malloc(sizeof(char)*(largo_cola+largo_a_escribir+5));
    men[0] = 'u';
    Protocolo::agregarString(largo_cola, &men[1], cola);
    Protocolo::agregarString(largo_a_escribir, &men[largo_cola+3], a_escribir);
    *mensaje = men;
    return largo_cola+largo_a_escribir+5;
}

int ProtocoloCliente::construirMensajePop(char *cola, char **mensaje){
    return construirMensajeCola('o', cola, mensaje);
}


ProtocoloCliente::~ProtocoloCliente(){
}


class ProtocoloServer: public Protocolo
{
private:
public:
    ProtocoloServer();
    void crearMensaje(int largo, char *destino, char *mensaje);
    ~ProtocoloServer();
};

ProtocoloServer::ProtocoloServer(){
}

void ProtocoloServer::crearMensaje(int largo, char *destino, char *mensaje){
    agregarString(largo, destino, mensaje);
}

ProtocoloServer::~ProtocoloServer(){
}



#endif
