#ifndef CLIENT_ADMIN_H
#define CLIENT_ADMIN_H

#include "client_protocolo.h"
#include "client_sockt.h"
#include <iostream>
#include <sstream>
#include <string>

#define INT16 2
#define ARG_ESPERADOS 3
#define RUN_ERROR 2
#define ARG_ERROR 1
#define NO_ERROR 0
#define HOST 1
#define PORT 2

#define DEFINE_S "define"
#define PUSH_S "push"
#define POP_S "pop"
#define EXIT_S "exit"
#define ERROR_COMMANDO "commando incorrecto"

class Admin
{
private:
    ClientSocket skt;
    ProtocoloCliente protocolo;
    void definir(std::string cola);
    void push(std::string cola, std::string a_escribir);
    void pop(std::string cola);
public:
    Admin(char *host, char *port);
    bool operar(std::string commando);
    ~Admin();
};

#endif
