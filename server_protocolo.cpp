#include "server_protocolo.h"
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

ProtocoloServer::ProtocoloServer(){
}

void ProtocoloServer::crearMensaje(int largo, const std::string& mensaje, Socket& skt){
    std::vector<char> mnsj(largo+INT16);
    std::vector<char> mensaje_v(mensaje.begin(), mensaje.end());
    agregarString(largo, mnsj.data(), mensaje_v);
    skt.write(mnsj.data(), largo+INT16);
}

char ProtocoloServer::leerAccion(Socket& skt){
    std::vector<char> buf(LEN_POS+1);
    int estado = skt.read(buf.data(), LEN_POS);
    if (estado == ESTADO_FALLIDO) return FAIL;
    return buf[ACCION_POS];
}

ProtocoloServer::~ProtocoloServer(){
}
