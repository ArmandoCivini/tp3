#include "common_protocolo.h"
#include "client_sockt.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#define INT16 2

Protocolo::Protocolo(){
}

uint16_t Protocolo::char2toInt16(char numero[INT16]){
    uint16_t num = *(uint16_t *)numero;
    return ntohs(num);
}

void Protocolo::int16toChar2(uint16_t numero, char caracteres[INT16]){
    numero = htons(numero);
    memcpy(caracteres, &numero, INT16);
}

uint16_t Protocolo::largoMensaje(std::vector<char> mensaje){
    return char2toInt16(mensaje.data());
}

std::string Protocolo::mensaje(std::vector<char> mensaje){
    return std::string(mensaje.begin(), mensaje.end());
}

void Protocolo::agregarString(int largo, char *destino, std::vector<char>& mensaje){
    int16toChar2(largo, destino);
    strncpy(&destino[INT16], mensaje.data(), largo);
}

std::string Protocolo::leerMensaje(Socket& skt){
    std::vector<char> largo_pop(INT16+1);
    skt.read(largo_pop.data(), INT16);
    int largo = Protocolo::largoMensaje(largo_pop);
    std::vector<char> mensaje(largo+1);
    std::string a_imprimir("");
    if (largo==0) return a_imprimir;
    skt.read(mensaje.data(), largo);
    a_imprimir =  Protocolo::mensaje(mensaje);
    return a_imprimir;
}

Protocolo::~Protocolo(){
}
