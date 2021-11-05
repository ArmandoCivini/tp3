#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

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
#define ESTADO_FALLIDO 0

#define FAIL 'f'

class ProtocoloServer: public Protocolo
{
private:
public:
    ProtocoloServer();
    void crearMensaje(int largo, const std::string& mensaje, Socket& skt);
    char leerAccion(Socket& skt);
    ~ProtocoloServer();
};

#endif
