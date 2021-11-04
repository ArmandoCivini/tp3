#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include "client_sockt.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#define INT16 2

class Protocolo
{
private:
protected:
    uint16_t char2toInt16(char *numero);
    void int16toChar2(uint16_t numero, char caracteres[INT16]);
    void agregarString(int largo, char *destino, std::vector<char>& mensaje);
public:
    Protocolo();
    uint16_t largoMensaje(std::vector<char> mensaje);
    void decifrar(char *mensaje);
    std::string mensaje(std::vector<char> mensaje);
    std::string leerMensaje(Socket& skt);
    ~Protocolo();
};

#endif
