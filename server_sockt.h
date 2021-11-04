#ifndef SERVER_SOCKT_H
#define SERVER_SOCKT_H

#include "common_sockt.h"
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

#define EMPTY_FD -1
#define EMPTY_ERR -1
#define ERR_CORRECTO 0
#define ERROR_ADDR "error al obtener info de la direccion"
#define ERROR_INIT "error al iniciar socket"
#define ERROR_BIND "error al bindear socket"
#define ERROR_LISTEN "error al escuchar"

class ServerSocket : public Socket
{
private:
	bool isClosed;
public:
    ServerSocket(char *port, int q_max);
    Socket acceptClient(bool *end);
	void shutdownAccept();
    ~ServerSocket();
};

#endif
