#ifndef CLIENT_PROTOCOLO_H
#define CLIENT_PROTOCOLO_H

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

class ProtocoloCliente : public Protocolo
{
private:
    int construirMensajeCola(char accion, const std::string& cola, std::vector<char>& mensaje);
    int construirMensajeDefinir(const std::string& cola, std::vector<char>& mensaje);
    int construirMensajePush
    (const std::string& cola, const std::string& a_escribir, std::vector<char>& mensaje);
    int construirMensajePop(const std::string& cola, std::vector<char>& mensaje);
public:
    ProtocoloCliente();
    void leerMensaje(ClientSocket& skt);
    void enviarMensajePop(const std::string& cola, ClientSocket& skt);
    void enviarMensajeDefinir(const std::string& cola, ClientSocket& skt);
    void enviarMensajePush
    (const std::string& cola, const std::string& a_escribir, ClientSocket& skt);
    ~ProtocoloCliente();
};

#endif
