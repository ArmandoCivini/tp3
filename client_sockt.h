#ifndef CLIENT_SOCKT_H
#define CLIENT_SOCKT_H

#include "common_sockt.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdbool.h>

#define EMPTY_FD -1
#define EMPTY_ERR -1
#define ERROR_ADDR "error al obtener info de la direccion"
#define ERROR_CONEXION "error al conectar al servidor"

class ClientSocket : public Socket
{
private:
    struct addrinfo *resultado;
    void connection();
public:
    ClientSocket(char *host, char *port);
    ~ClientSocket();
};

#endif
